#include "bmh.h"
#include <string.h>

int bmh(const unsigned char *texto, int n, const unsigned char *padrao, int m, int *comparacoes, FILE *saida) {
    int tabela[256];

    // Preparar tabela de deslocamento
    for (int i = 0; i < 256; i++) tabela[i] = m;
    for (int i = 0; i < m - 1; i++) tabela[padrao[i]] = m - 1 - i;

    printf("   Posições: ");
    int ocorrencias = 0;
    int i = 0;
    int primeira_ocorrencia = 1;
    
    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0 && ++(*comparacoes) && padrao[j] == texto[i + j]) j--;
        if (j < 0) {
            printf("%d ", i + 1); // indexação baseada em 1
            if (saida) {
                if (primeira_ocorrencia) {
                    fprintf(saida, "%d", i + 1);
                    primeira_ocorrencia = 0;
                } else {
                    fprintf(saida, " %d", i + 1);
                }
            }
            ocorrencias++;
            i++;
        } else {
            i += tabela[texto[i + m - 1]];
        }
    }
    
    if (ocorrencias == 0) {
        printf("(nenhuma)");
    }
    printf("\n");
    if (saida) fprintf(saida, "\n");
    
    return ocorrencias;
}
