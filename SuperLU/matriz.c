#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "leitura.h"
#define zero 1e-15


double** matrizDinamica(int linha, int coluna)
{

    //aloca matriz dinamica

	int i;
	double** mat;
	mat = (double**)calloc(linha, sizeof(double*));
	for (i = 0; i < linha; i++)
	{
		mat[i] = (double*)calloc(coluna, sizeof(double));
	}
	return mat;
}

void liberarMatrizdina(double** mat, int linha)
{
	int i;
	for (i = 0; i < linha; i++)
	{
		free(mat[i]);
	}
	free(mat);
}

int matdb_to_CSC(double **A, int nlin,int ncol,int* nnz, double* a,int* r_index, int* c_ptr  )
{


	int i,j,k,m;

	(*nnz)=0;
	//contar o numero de elementos não nulos

	for(i=0;i<nlin;i++)
	{
		for(j=0;j<ncol;j++)
		{
			if (fabs(A[i][j])>zero) 
			{
				(*nnz)++;
			}
			
		}
	}
	a=(double*)malloc((*nnz)*sizeof(double));
	r_index=(int*)malloc((*nnz)*sizeof(int));
	c_ptr=(int*)malloc((ncol+1)*sizeof(int));

	k=0;
	m=0;
	for(j=0;j<ncol;j++)
	{
		for(i=0;i<ncol;i++)
		{
			
			if (fabs(A[i][j])>zero) 
			{
				a[k]=A[i][j];
				r_index[k]=i;
				k++;
			}
		}
		c_ptr[m]=k;
		m++;

	}



	printf("Numero de não zeros %d\n\n",(*nnz));
	printf("Vetor de valores:\n");
	imprimirvet_double(a,*nnz);
	printf("Vetor de linhas:\n");
	imprimirvet_int(r_index,*nnz);
	printf("Vetor de col:\n");
	imprimirvet_int(c_ptr,ncol+1);

	return 0;
}

int CSC_to_matdb (double **A, int nlin,int ncol,int* nnz, int* a,int* r_index, int* c_ptr  )
{

	return 0;
}