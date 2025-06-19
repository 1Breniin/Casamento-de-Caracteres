#ifndef UTIL_H
#define UTIL_H

char *ler_arquivo(const char *nome);
char **ler_linhas(const char *nome, int *n_linhas);
void liberar_linhas(char **linhas, int n);

#endif
