#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>
#include "busca.h"

void busca_programacao_dinamica(const char *texto, const char *padrao, int k, FILE *saida) {
    int n = strlen(texto);
    int m = strlen(padrao);
    int **D = malloc((m+1) * sizeof(int*));
    for (int i = 0; i <= m; i++)
        D[i] = malloc((n+1) * sizeof(int));

    struct timeval start, end;
    gettimeofday(&start, NULL);

    int comparacoes = 0;

    for (int j = 0; j <= n; j++)
        D[0][j] = 0;
    for (int i = 1; i <= m; i++)
        D[i][0] = i;

    printf("%s", padrao);
    
    int primeira_ocorrencia = 1;

    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= m; i++) {
            comparacoes++;
            int custo = (padrao[i - 1] == texto[j - 1]) ? 0 : 1;
            int insercao = D[i][j - 1] + 1;
            int delecao = D[i - 1][j] + 1;
            int substituicao = D[i - 1][j - 1] + custo;
            D[i][j] = (insercao < delecao ? (insercao < substituicao ? insercao : substituicao) :
                          (delecao < substituicao ? delecao : substituicao));
        }
        if (D[m][j] <= k) {
            int posicao = j - m + 1;
            printf(" %d", posicao);
            
            // Escrever no arquivo apenas para k=0 (busca exata)
            if (k == 0 && saida) {
                if (primeira_ocorrencia) {
                    fprintf(saida, "%d", posicao);
                    primeira_ocorrencia = 0;
                } else {
                    fprintf(saida, " %d", posicao);
                }
            }
        }
    }

    // Finalizar linha no arquivo para k=0
    if (k == 0 && saida) {
        fprintf(saida, "\n");
    }

    gettimeofday(&end, NULL);
    double tempo = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    printf("\n");
    fprintf(stderr, "Programação Dinâmica (k=%d): %d comparações, %.6fs\n", k, comparacoes, tempo);

    for (int i = 0; i <= m; i++)
        free(D[i]);
    free(D);
}

void busca_shift_and(const char *texto, const char *padrao, int k, FILE *saida) {
    int m = strlen(padrao);
    int n = strlen(texto);

    if (m > 31) {
        printf("Padrão muito longo para Shift-And (máx 31).\n");
        return;
    }

    uint32_t B[256] = {0};
    for (int i = 0; i < m; i++)
        B[(unsigned char)padrao[i]] |= (1 << i);

    uint32_t R[k + 1];
    for (int i = 0; i <= k; i++)
        R[i] = 0;

    struct timeval start, end;
    gettimeofday(&start, NULL);

    int comparacoes = 0;
    printf("%s", padrao);
    
    int primeira_ocorrencia = 1;

    for (int j = 0; j < n; j++) {
        uint32_t oldR = R[0];
        R[0] = ((R[0] << 1) | 1) & B[(unsigned char)texto[j]];
        comparacoes++;

        for (int e = 1; e <= k; e++) {
            uint32_t temp = R[e];
            R[e] = ((R[e] << 1) | 1) & B[(unsigned char)texto[j]];
            R[e] |= (oldR << 1) | oldR | R[e - 1];
            oldR = temp;
        }

        if (R[k] & (1 << (m - 1))) {
            int posicao = j - m + 2;
            printf(" %d", posicao);
            
            // Escrever no arquivo apenas para k=0 (busca exata)
            if (k == 0 && saida) {
                if (primeira_ocorrencia) {
                    fprintf(saida, "%d", posicao);
                    primeira_ocorrencia = 0;
                } else {
                    fprintf(saida, " %d", posicao);
                }
            }
        }
    }

    // Finalizar linha no arquivo para k=0
    if (k == 0 && saida) {
        fprintf(saida, "\n");
    }

    gettimeofday(&end, NULL);
    double tempo = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    printf("\n");
    fprintf(stderr, "Shift-And (k=%d): %d comparações, %.6fs\n", k, comparacoes, tempo);
}
