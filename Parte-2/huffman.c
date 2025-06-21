#include "huffman.h"
#include <stdlib.h>
#include <string.h>

void comprimir_arquivo(const char *entrada, const char *saida) {
    FILE *in = fopen(entrada, "r");
    FILE *out = fopen(saida, "wb");
    if (!in || !out) return;

    int c;
    while ((c = fgetc(in)) != EOF) {
        fputc(c ^ 0xAA, out); // compressão fictícia: xor com 0xAA
    }

    fclose(in);
    fclose(out);
}

unsigned char *carregar_arquivo_binario(const char *nome, int *tamanho) {
    FILE *fp = fopen(nome, "rb");
    if (!fp) return NULL;

    fseek(fp, 0, SEEK_END);
    *tamanho = ftell(fp);
    rewind(fp);

    unsigned char *conteudo = malloc(*tamanho);
    fread(conteudo, 1, *tamanho, fp);
    fclose(fp);
    return conteudo;
}
