#include <stdio.h>
#include <time.h>
#include <math.h>
#include "leitura.h"
#include "matriz.h"
#include "umfpack.h"
#define zero 1e-14




int main (void)
{
    double **A,**U;
    clock_t Tini,tfat,tnref;
    char* path;
    int i,nref=0;
    int nnz,nlin,ncol,Lnnz,Unnz,n_row,n_col,nz_udiag;
    int    *Tj,*Ap,recip ;
    int    *Ti,*Ai,*map;
    double *Tx, *Ax,*Lx,*Ux,*Dx,*Rs;
    int *Lp,*Lj,*Up,*Ui,*P,*Q;
    int *TUj;//matrizes triplet U
    double *control,*info;
    FILE *out;
    control = (double *) malloc(UMFPACK_CONTROL*sizeof(double));
    info = (double *) malloc(UMFPACK_INFO*sizeof(double));
    path=config();
    (void) r_dmatfcsv(&A,path,',',&nlin,&ncol);
    umfpack_di_defaults(control);
    Tini=clock();

    void *Symbolic, *Numeric ;


    (void) matdb_to_triplet(A,nlin,ncol,&nnz,&Tx,&Ti,&Tj);

    control[UMFPACK_STRATEGY]=UMFPACK_STRATEGY_UNSYMMETRIC;
    control[UMFPACK_ORDERING]=UMFPACK_ORDERING_CHOLMOD;
    
	Ax=(double*)malloc(nnz*sizeof(double));
	Ai=(int*)malloc(nnz*sizeof(int));
	Ap=(int*)calloc((ncol+1),sizeof(int));
    map=(int*)malloc(nnz*sizeof(int));

    
    
    (void) umfpack_di_triplet_to_col(nlin,ncol,nnz,Ti,Tj,Tx,Ap,Ai,Ax,map);
    free(Tx);
    free(Ti);
    free(Tj);
    

    (void) umfpack_di_symbolic (nlin, ncol, Ap, Ai, Ax, &Symbolic, control, info) ;// realiza a fatoracao simbolica de uma matriz
    (void) umfpack_di_numeric (Ap, Ai, Ax, Symbolic, &Numeric, control, info) ;
    free(Ax);
    free(Ap);
    free(Ai);
    (void) umfpack_di_get_lunz(&Lnnz,&Unnz,&n_row,&n_col,&nz_udiag,Numeric);
    umfpack_di_report_info(control,info);


    Ux=(double*)malloc(Unnz*sizeof(double));
	Ui=(int*)malloc(Unnz*sizeof(int));
	Up=(int*)calloc((ncol+1),sizeof(int));

    Lx=(double*)malloc(Lnnz*sizeof(double));
	Lj=(int*)malloc(Lnnz*sizeof(int));
	Lp=(int*)calloc((nlin+1),sizeof(int));

    P=(int*)calloc((nlin),sizeof(int)); //Permutação de linhas
    Q=(int*)calloc((ncol),sizeof(int));// Permutação de colunas

    i=min(nlin,ncol);
    Dx=(double*)malloc((min(nlin,ncol))*sizeof(double));// Min colxlin The diagonal of U is also returned in Dx and Dz.

    //do recip This argument defines how the scale factors Rs are to be interpretted
    Rs=(double*)malloc(nlin*sizeof(double));//The row scale factors are returned in Rs
    (void) umfpack_di_get_numeric(Lp,Lj,Lx,Up,Ui,Ux,P,Q,Dx,&recip,Rs,Numeric);
    tfat=clock();
    

    TUj=(int *) malloc(Unnz*sizeof(int));


    (void) umfpack_di_col_to_triplet(ncol,Up,TUj);


    (void) triplet_to_matdb(&U,n_col,n_col,TUj,Ui,Ux,Unnz);

    free(Ux);
    free(Ui);
    free(Up);
    free(TUj);   
    free(Lp);    
    free(Lj);
    free(Lx);



    for(i=0; i<n_col;i++)
    {
        if(fabs(U[i][i])<zero) nref++;
    }

    tnref=clock();

    out=fopen("matsaida.csv","w");
    fimprimirmat(out,U,ncol,ncol);

    printf("O sistema precisa de %d referencia (s)\n\n",nref);

    double tempo= (double) (tfat-Tini)/ CLOCKS_PER_SEC;
    printf("Tempo de fatoracao: %f \n\n",tempo);
    tempo=(double) (tnref-Tini)/ CLOCKS_PER_SEC;
    printf("Tempo de detref: %f \n\n",tempo);

    umfpack_di_free_symbolic (&Symbolic) ;
    umfpack_di_free_numeric (&Numeric) ;
    free(control);
    free(info);
    liberarMatrizdina(U,ncol);   
   
    
    return (0) ;
}
