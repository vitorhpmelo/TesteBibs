


#ifndef matriz_H
#define matriz_H

int matrizDinamica(double*** mat,int linha, int coluna);
void liberarMatrizdina(double** mat, int linha);
int matdb_to_CSC(double **A, int nlin,int ncol,int* nnz, double** a,int** r_index, int** c_ptr  );
int CSC_to_matdb (double ***A, int nlin,int ncol,int* nnz, double* a,int* r_index, int* c_ptr  );
int matdb_to_triplet(double **A,int nlin,int ncol,int *nnz,double **Ax,int** Ai,int** Aj);
#endif



