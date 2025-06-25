#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "busca.h"
#include "util.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Uso: %s <1=PD | 2=ShiftAnd> <arquivo_texto> <arquivo_padroes> <k>\n", argv[0]);
        return 1;
    }

    int algoritmo = atoi(argv[1]);
    char *texto = ler_arquivo(argv[2]);
    int n_padroes = 0;
    char **padroes = ler_linhas(argv[3], &n_padroes);
    int k = atoi(argv[4]);

    if (!texto || !padroes) {
        fprintf(stderr, "Erro ao ler arquivos.\n");
        return 1;
    }

    if (k < 0) {
        fprintf(stderr, "Valor de k deve ser >= 0.\n");
        return 1;
    }

    for (int i = 0; i < n_padroes; i++) {
        if (algoritmo == 1) {
            busca_programacao_dinamica(texto, padroes[i], k);
        } else if (algoritmo == 2) {
            busca_shift_and(texto, padroes[i], k);
        } else {
            fprintf(stderr, "Algoritmo inválido.\n");
            return 1;
        }
    }
    free(texto);
    liberar_linhas(padroes, n_padroes);
    return 0;
}
