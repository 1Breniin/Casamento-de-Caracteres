#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **ler_linhas(const char *nome, int *n_linhas) {
    FILE *fp = fopen(nome, "r");
    if (!fp) return NULL;

    size_t tamanho = 0;
    char *linha = NULL;
    int capacidade = 10;
    char **linhas = malloc(capacidade * sizeof(char*));
    *n_linhas = 0;

    while (getline(&linha, &tamanho, fp) != -1) {
        linha[strcspn(linha, "\n")] = '\0';
        if (*n_linhas >= capacidade) {
            capacidade *= 2;
            linhas = realloc(linhas, capacidade * sizeof(char*));
        }
        linhas[*n_linhas] = strdup(linha);
        (*n_linhas)++;
    }

    free(linha);
    fclose(fp);
    return linhas;
}

void liberar_linhas(char **linhas, int n) {
    for (int i = 0; i < n; i++)
        free(linhas[i]);
    free(linhas);
}
