#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"
#include "leitura.h"
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
    double **mat;
    double *A;
    lapack_int info_t,m,n,lda_t;
    lapack_int *ipiv_t;
    FILE *in;
    FILE *fou=NULL;
    path =config();
    (void) r_dmatfcsv(&mat,path,',',&nlin,&ncol);
   // fou=fopen("fout.csv","w");
    
    
    m=nlin;
    n=ncol;
    lda_t=maior(1,nlin);
    tam=menor(ncol,nlin);
    printf("Matriz lida \n\n");
    imprimirmat(mat,nlin,ncol);
    ipiv_t=(lapack_int *)malloc(tam*sizeof(lapack_int));
   
    A=(double*)calloc(nlin*ncol, sizeof(double));
    
    for (i=0;i<nlin;i++)
    {
        for (j=0;j<ncol;j++)
        {
            A[k]=mat[i][j];
            k++;
        }
    }
    info_t =LAPACKE_dgetrf(LAPACK_ROW_MAJOR,m,n,A,lda_t,ipiv_t);
  //  fimprimirmat(fou, mat,  nlin, ncol);
    printf("Matriz saida \n\n");
    imprimirmat( mat,  nlin, ncol);
    printf("%d\n\n",info_t);
    //
    //return 0;
}