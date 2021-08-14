#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"
#include "leitura.h"
#include <lapack.h>
#include <lapacke.h>
#include "lapacke_utils.h"

int main ()
{
    char *path;
    int nlin,ncol;
    int i,j,k=0;
    double **mat;
    double *A;
    lapack_int info_t,m,n,lda_t;
    lapack_int *ipiv_t;
    //ipiv_t=NULL;
    FILE *in;
    FILE *fou=NULL;
    path =config();
    mat = r_dmatfcsv(path,'\t',&nlin,&ncol);
    
    m=nlin;
    n=ncol;
    lda_t=m;
    //in=fopen("In.csv","w");
    //fou=fopen("batata.csv","w");
    //fimprimirmat(in, mat,  nlin, ncol);
    //imprimirmat( mat,  nlin, ncol);
    A=(double*)calloc(nlin*ncol*2, sizeof(double));
    
    for (i=0;i<nlin;i++)
    {
        for (j=0;j<ncol;j++)
        {
            A[k]=mat[i][j];
            k++;
        }
    }
    info_t =LAPACKE_dgetrf(LAPACK_ROW_MAJOR,m,n,*mat,lda_t,ipiv_t);
    //fimprimirmat(fou, mat,  nlin, ncol);
    imprimirmat( mat,  nlin, ncol);
    printf("%d\n\n",info_t);
    //fclose(in);
    //fclose(ou);
    
    return 0;
}