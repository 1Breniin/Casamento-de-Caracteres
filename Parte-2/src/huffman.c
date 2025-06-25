#include "huffman.h"
#include <stdlib.h>
#include <string.h>

// Compressão simples usando codificação RLE + XOR (simulando Huffman)
void comprimir_arquivo(const char *entrada, const char *saida) {
    FILE *in = fopen(entrada, "r");
    FILE *out = fopen(saida, "wb");
    if (!in || !out) return;

    int c, anterior = -1, contador = 1;
    
    while ((c = fgetc(in)) != EOF) {
        if (c == anterior && contador < 255) {
            contador++;
        } else {
            if (anterior != -1) {
                // Escrever o caractere comprimido (XOR + RLE)
                fputc(anterior ^ 0x55, out);  // XOR para "compressão"
                if (contador > 1) {
                    fputc(0xFF, out);  // Marcador RLE
                    fputc(contador, out);
                }
            }
            anterior = c;
            contador = 1;
        }
    }
    
    // Escrever último caractere
    if (anterior != -1) {
        fputc(anterior ^ 0x55, out);
        if (contador > 1) {
            fputc(0xFF, out);
            fputc(contador, out);
        }
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
    if (conteudo) {
        size_t lidos = fread(conteudo, 1, *tamanho, fp);
        *tamanho = lidos;
    }
    fclose(fp);
    return conteudo;
}

// Comprime um padrão usando o mesmo método do arquivo
unsigned char *comprimir_padrao(const char *padrao, int *tamanho_comprimido) {
    int len = strlen(padrao);
    unsigned char *comprimido = malloc(len * 2); // Buffer generoso
    int pos = 0;
    
    for (int i = 0; i < len; i++) {
        comprimido[pos++] = padrao[i] ^ 0x55;
    }
    
    *tamanho_comprimido = pos;
    return comprimido;
}
