#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "bmh.h"
#include "huffman.h"
#include "util.h"

void buscar(const unsigned char *texto, int n, const unsigned char *padrao, int m, const char *label) {
    struct timeval start, end;
    int comparacoes = 0;

    gettimeofday(&start, NULL);
    int ocorrencias = bmh(texto, n, padrao, m, &comparacoes);
    gettimeofday(&end, NULL);

    double tempo = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

    printf("%s: %d ocorrências | comparações: %d | tempo: %.6fs\n", label, ocorrencias, comparacoes, tempo);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <arquivo_texto> <arquivo_padroes>\n", argv[0]);
        return 1;
    }

    const char *texto_path = argv[1];
    const char *padroes_path = argv[2];

    // Comprimir texto
    comprimir_arquivo(texto_path, "texto.huff");

    // Carregar texto original
    FILE *f = fopen(texto_path, "r");
    fseek(f, 0, SEEK_END);
    int tamanho_texto = ftell(f);
    rewind(f);
    unsigned char *texto = malloc(tamanho_texto);
    fread(texto, 1, tamanho_texto, f);
    fclose(f);

    // Carregar texto comprimido
    int tamanho_comprimido = 0;
    unsigned char *comprimido = carregar_arquivo_binario("texto.huff", &tamanho_comprimido);

    // Ler padrões
    int n_padroes = 0;
    char **padroes = ler_linhas(padroes_path, &n_padroes);

    FILE *saida = fopen("saida.txt", "w");

    for (int i = 0; i < n_padroes; i++) {
        fprintf(saida, "%s\n", padroes[i]);

        // BMH em texto original
        buscar(texto, tamanho_texto, (unsigned char*)padroes[i], strlen(padroes[i]), "Original");

        // Comprimir padrão (fictício = xor 0xAA)
        unsigned char *padrao_comp = malloc(strlen(padroes[i]));
        for (int j = 0; j < strlen(padroes[i]); j++)
            padrao_comp[j] = padroes[i][j] ^ 0xAA;

        // BMH em texto comprimido
        buscar(comprimido, tamanho_comprimido, padrao_comp, strlen(padroes[i]), "Comprimido");

        free(padrao_comp);
    }

    fclose(saida);
    free(texto);
    free(comprimido);
    liberar_linhas(padroes, n_padroes);
    return 0;
}
