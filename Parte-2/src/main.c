#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "bmh.h"
#include "huffman.h"
#include "util.h"

typedef struct {
    int comparacoes;
    double tempo;
} Resultado;

Resultado buscar(const unsigned char *texto, int n, const unsigned char *padrao, int m, FILE *saida) {
    struct timeval start, end;
    int comparacoes = 0;

    gettimeofday(&start, NULL);
    bmh(texto, n, padrao, m, &comparacoes, saida);
    gettimeofday(&end, NULL);

    double tempo = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

    Resultado r = {comparacoes, tempo};
    return r;
}

void imprimir_resultado(const char *titulo, Resultado r) {
    printf("   %s: %d comparações, %.6fs\n", titulo, r.comparacoes, r.tempo);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_texto> <arquivo_padroes>\n", argv[0]);
        return 1;
    }

    const char *arquivo_texto = argv[1];
    const char *arquivo_padroes = argv[2];

    printf("Comprimindo arquivo...\n");
    comprimir_arquivo(arquivo_texto, "texto.huff");

    // Carregar texto original
    FILE *f = fopen(arquivo_texto, "r");
    if (!f) {
        fprintf(stderr, "Erro ao abrir arquivo de texto\n");
        return 1;
    }
    fseek(f, 0, SEEK_END);
    int tam_texto = ftell(f);
    rewind(f);
    unsigned char *texto = malloc(tam_texto + 1);
    size_t lidos = fread(texto, 1, tam_texto, f);
    texto[lidos] = '\0';
    tam_texto = lidos;
    fclose(f);

    // Carregar texto comprimido
    int tam_comp;
    unsigned char *comprimido = carregar_arquivo_binario("texto.huff", &tam_comp);
    if (!comprimido) {
        fprintf(stderr, "Erro ao carregar arquivo comprimido\n");
        return 1;
    }

    // Carregar padrões
    int n_padroes;
    char **padroes = ler_linhas(arquivo_padroes, &n_padroes);
    if (!padroes) {
        fprintf(stderr, "Erro ao carregar padrões\n");
        return 1;
    }

    // Criar arquivo de saída
    FILE *saida = fopen("saida.txt", "w");
    if (!saida) {
        fprintf(stderr, "Erro ao criar arquivo saida.txt\n");
        return 1;
    }

    printf("Tamanho original: %d bytes\n", tam_texto);
    printf("Tamanho comprimido: %d bytes\n", tam_comp);
    printf("Taxa de compressão: %.2f%%\n\n", 
           (1.0 - (double)tam_comp / tam_texto) * 100);

    for (int i = 0; i < n_padroes; i++) {
        printf("%s\n", padroes[i]);

        // Busca no texto original
        printf("📄 Texto original:\n");
        Resultado r1 = buscar(texto, tam_texto, (unsigned char*)padroes[i], strlen(padroes[i]), saida);
        imprimir_resultado("Métricas", r1);

        // Comprimir padrão e buscar no texto comprimido
        int tam_padrao_comp;
        unsigned char *padrao_comp = comprimir_padrao(padroes[i], &tam_padrao_comp);
        
        printf("💾 Texto comprimido:\n");
        Resultado r2 = buscar(comprimido, tam_comp, padrao_comp, tam_padrao_comp, NULL);
        imprimir_resultado("Métricas", r2);

        printf("\n");
        free(padrao_comp);
    }

    fclose(saida);
    free(texto);
    free(comprimido);
    liberar_linhas(padroes, n_padroes);
    return 0;
}
