


#ifndef matriz_H
#define matriz_H

double** matrizDinamica(int linha, int coluna);
void liberarMatrizdina(double** mat, int linha);
int matdb_to_CSC(double **A, int nlin,int ncol,int* nnz, int* a,int* r_index, int* c_ptr  );
int CSC_to_matdb (double **A, int nlin,int ncol,int* nnz, int* a,int* r_index, int* c_ptr  );
#endif



