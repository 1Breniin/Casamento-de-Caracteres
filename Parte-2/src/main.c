#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "bmh.h"
#include "huffman.h"
#include "util.h"

typedef struct {
    int ocorrencias;
    int comparacoes;
    double tempo;
} Resultado;

Resultado buscar(const unsigned char *texto, int n, const unsigned char *padrao, int m) {
    struct timeval start, end;
    int comparacoes = 0;

    gettimeofday(&start, NULL);
    int ocorrencias = bmh(texto, n, padrao, m, &comparacoes);
    gettimeofday(&end, NULL);

    double tempo = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

    Resultado r = {ocorrencias, comparacoes, tempo};
    return r;
}

void imprimir_resultado(const char *titulo, Resultado r) {
    printf("🔹 %s:\n", titulo);
    printf("   Ocorrências     : %d\n", r.ocorrencias);
    printf("   Comparações     : %d\n", r.comparacoes);
    printf("   Tempo (segundos): %.6f\n", r.tempo);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_texto> <arquivo_padroes>\n", argv[0]);
        return 1;
    }

    const char *arquivo_texto = argv[1];
    const char *arquivo_padroes = argv[2];

    comprimir_arquivo(arquivo_texto, "texto.huff");

    FILE *f = fopen(arquivo_texto, "r");
    fseek(f, 0, SEEK_END);
    int tam_texto = ftell(f);
    rewind(f);
    unsigned char *texto = malloc(tam_texto);
    fread(texto, 1, tam_texto, f);
    fclose(f);

    int tam_comp;
    unsigned char *comprimido = carregar_arquivo_binario("texto.huff", &tam_comp);

    int n_padroes;
    char **padroes = ler_linhas(arquivo_padroes, &n_padroes);
    FILE *saida = fopen("saida.txt", "w");

    for (int i = 0; i < n_padroes; i++) {
        printf("Padrão: \"%s\"\n\n", padroes[i]);
        fprintf(saida, "%s\n", padroes[i]);

        Resultado r1 = buscar(texto, tam_texto, (unsigned char*)padroes[i], strlen(padroes[i]));
        imprimir_resultado("Texto original", r1);

        unsigned char *padrao_comp = malloc(strlen(padroes[i]));
        for (int j = 0; j < strlen(padroes[i]); j++)
            padrao_comp[j] = padroes[i][j] ^ 0xAA;

        Resultado r2 = buscar(comprimido, tam_comp, padrao_comp, strlen(padroes[i]));
        imprimir_resultado("Texto comprimido", r2);

        printf("------------------------------------------------------------\n\n");
        free(padrao_comp);
    }

    fclose(saida);
    free(texto);
    free(comprimido);
    liberar_linhas(padroes, n_padroes);
    return 0;
}
