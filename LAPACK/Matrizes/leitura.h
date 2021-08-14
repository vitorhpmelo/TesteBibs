#ifndef leitura_H
#define leitura_H

char *config();
double** r_dmatfcsv(char path[100],char sep,int *nlin,int *ncol);
void imprimirmat(double** mat, int linha, int col);
void fimprimirmat(FILE* arquivo, double** mat, int linha, int col);

#endif