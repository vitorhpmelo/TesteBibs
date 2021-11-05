#include <stdio.h>
#include <time.h>
#include <math.h>
#include "leitura.h"
#include "matriz.h"
#include <cholmod.h>
#include "SuiteSparseQR_C.h"
#define zero 1e-14



int numrefQR(double **A,int nlin,int ncol)
{
    int i,r,nref=0;
    int index = 0;
    int rank;
    long econ=nlin;
    //declara a matriz no formato triplet
    cholmod_triplet *T_SS = NULL;
    cholmod_triplet *Q_T= NULL;
    cholmod_triplet *R_T= NULL;
    //declara a matriz no formato sparso
    cholmod_sparse *A_SS=NULL;
    cholmod_sparse *Q=NULL;
    cholmod_sparse *R=NULL;
    long *E;
    double **Qd=NULL;
    double **Rr=NULL;

    //inicia os parâmtros da suitesparse
    cholmod_common Common, *c;

    c = &Common;
    cholmod_l_start(c);

    T_SS=cholmod_l_allocate_triplet(nlin,ncol,ncol*nlin,0,CHOLMOD_REAL,c);
    A_SS = cholmod_l_allocate_sparse(nlin, ncol, ncol*nlin, 0, 0, 0, CHOLMOD_REAL, c);
    Q_T=cholmod_l_allocate_triplet(nlin,ncol,ncol*nlin,0,CHOLMOD_REAL,c);
    R_T=cholmod_l_allocate_triplet(ncol,ncol,ncol*ncol,0,CHOLMOD_REAL,c);
    (void) matrizDinamica(&Qd,nlin,ncol);
    (void) matrizDinamica(&Rr,ncol,ncol);
    
    for (i = 0; i < nlin; i++)
    {
        for (r = 0; r < ncol; r++)
        {
            if (A[i][r] != 0)
            {
                ((long int *)T_SS->i)[index] = i;
                ((long int *)T_SS->j)[index] = r;
                ((double *)T_SS->x)[index] = A[i][r];       
                T_SS->nnz += 1;
                index += 1;
            }
        }
    }   

    A_SS = cholmod_l_triplet_to_sparse(T_SS, ncol*nlin, c);

    rank = SuiteSparseQR_C_QR(SPQR_ORDERING_BEST,SPQR_DEFAULT_TOL,econ,A_SS,&Q,&R,&E,c);
    Q_T=cholmod_l_sparse_to_triplet(Q,c);
    R_T=cholmod_l_sparse_to_triplet(R,c);

    for (index = 0; index < (int) Q_T->nzmax; index++)
    {
        Qd[((long int *)Q_T->i)[index]][((long int *)Q_T->j)[index]]=((double *)Q_T->x)[index];
        
    }   
    for (index = 0; index < (int) R_T->nzmax; index++)
    {
    
        Rr[((long int *)R_T->i)[index]][((long int *)R_T->j)[index]]=((double *)R_T->x)[index];
        
    }  

    FILE *arquivoR;
    FILE *arquivoQ;

    arquivoR=fopen("matR.csv","w");
    arquivoQ=fopen("matQ.csv","w");
    fimprimirmat(arquivoR,Rr,ncol,ncol);
    fimprimirmat(arquivoQ,Qd,nlin,ncol);


    printf("%d\n",rank);

    


    return nref;
}
