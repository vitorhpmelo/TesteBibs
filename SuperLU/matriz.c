#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "leitura.h"
#define zero 1e-15


int matrizDinamica(double*** mat,int linha, int coluna)
{
   //aloca matriz dinamica
	int i;

	(*mat) = (double**)calloc(linha, sizeof(double*));
	for (i = 0; i < linha; i++)
	{
		(*mat)[i] = (double*)calloc(coluna, sizeof(double));
	}
	return 0;
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

int matdb_to_CSC(double **A, int nlin,int ncol,int* nnz, double** a,int** r_index, int** c_ptr  )
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
	(*a)=(double*)malloc((*nnz)*sizeof(double));
	(*r_index)=(int*)malloc((*nnz)*sizeof(int));
	(*c_ptr)=(int*)calloc((ncol+1),sizeof(int));
	//imprimirmat(*A,ncol,nlin);
	k=0;
	m=0;
	(*c_ptr[m])=k;

	for(j=0;j<ncol;j++)
	{
		for(i=0;i<nlin;i++)
		{
			if (fabs(A[i][j])>zero) 
			{
				(*a)[k]=A[i][j];
				(*r_index)[k]=i;
				k++;
			}
		}
		m++;
		(*c_ptr)[m]=k;

	}



	//printf("Numero de não zeros %d\n\n",(*nnz));
	//printf("Vetor de valores:\n");
	//imprimirvet_double(a,*nnz);
	//printf("Vetor de linhas:\n");
	//imprimirvet_int(r_index,*nnz);
	//printf("Vetor de col:\n");
	//imprimirvet_int(c_ptr,ncol+1);

	return 0;
}

int CSC_to_matdb (double ***A, int nlin,int ncol,int* nnz, double* a,int* r_index, int* c_ptr  )
{


	int i,j,k,m;
	(void) matrizDinamica(A,nlin,ncol);

	i=0;
	j=0;
	k=0;

	for(m=0;m<ncol;m++)
	{
		for(j=0;j<c_ptr[m+1]-c_ptr[m];j++)
		{
			(*A)[r_index[k]][c_ptr[m]]=a[k];
			k++;
		}
	}


	return 0;
}