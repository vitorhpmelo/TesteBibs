#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"
#include "leitura.h"
#include <lapack.h>
#include <lapacke.h>


int maior(int a,int b)
{
    if (a<b)
    {
        return b;
    }
    else
    {
        return a;
    }
}
int menor(int a,int b)
{
    if (a>b)
    {
        return b;
    }
    else
    {
        return a;
    }
}

int main ()
{
    char *path;
    int nlin,ncol;
    int i,j,k=0,tam;
    double **mat,**mat_o;
    double *A;
    lapack_int info_t,m,n,lda_t;
    lapack_int *ipiv_t;
    FILE *in;
    FILE *fou=NULL;
    path =config();
    (void) r_dmatfcsv(&mat,path,',',&nlin,&ncol);
   // fou=fopen("fout.csv","w");
    int info,lda;
    


    matrizDinamica(&mat_o,nlin,ncol);
    m=nlin;
    n=ncol;
    lda=maior(1,nlin);
    tam=menor(ncol,nlin);
    printf("Matriz lida \n\n");
    imprimirmat(mat,nlin,ncol);
    //ipiv_t=(int *)malloc(tam*sizeof(int));
   
    A=(double*)calloc(nlin*ncol, sizeof(double));
    
    for (i=0;i<nlin;i++)
    {
        for (j=0;j<ncol;j++)
        {
            A[k]=mat[i][j];
            k++;
        }
    }
    
    dgetrf_(&nlin,&ncol,A,&lda,ipiv_t,&info);

    k=0;

    for (i=0;i<nlin;i++)
    {
        for (j=0;j<ncol;j++)
        {
            mat_o[i][j]=A[k];
            k++;
        }
    }

    printf("\n\nMatriz LU \n\n");

    imprimirmat(mat_o,nlin,ncol);


    //fimprimirmat(fou, mat,  nlin, ncol);
    //printf("Matriz saida \n\n");
    //imprimirmat( &mat,  nlin, ncol);
    //for (i=0;i<ncol;i++)
    //{
    //    printf("%e\t",mat[i][i]);
    //}
    //printf("\n%d\n\n",info);
    //
    //return 0;
}