#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>

void comprimir_arquivo(const char *entrada, const char *saida);
unsigned char *carregar_arquivo_binario(const char *nome, int *tamanho);
unsigned char *comprimir_padrao(const char *padrao, int *tamanho_comprimido);

#endif
