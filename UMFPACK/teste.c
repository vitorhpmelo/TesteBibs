#include <stdio.h>
#include "leitura.h"
#include "matriz.h"
#include "umfpack.h"

int    n = 5 ;

double b [ ] = {8., 45., -3., 3., 19.} ;
double x [5] ;

int main (void)
{
    double *null = (double *) NULL ;
    double **A;
    int i ;
    int nnz,nlin,ncol,Lnnz,Unnz,n_row,n_col,nz_udiag;
    int    *Tj,*Ap,*do_recip ;
    int    *Ti,*Ai,*map;
    double *Tx, *Ax,*Lx,*Ux,*Dx,*Rs;
    int *Lp,*Lj,*Up,*Ui,*P,*Q;

    void *Symbolic, *Numeric ;
    (void) r_dmatfcsv(&A,"./Matrizes/matrizex.csv",',',&nlin,&ncol);
    imprimirmat(A,nlin,ncol);
    (void) matdb_to_triplet(A,nlin,ncol,&nnz,&Tx,&Ti,&Tj);

	Ax=(double*)malloc(nnz*sizeof(double));
	Ai=(int*)malloc(nnz*sizeof(int));
	Ap=(int*)calloc((ncol+1),sizeof(int));

    (void) umfpack_di_triplet_to_col(nlin,ncol,nnz,Ti,Tj,Tx,Ap,Ai,Ax,map);
    (void) umfpack_di_symbolic (n, n, Ap, Ai, Ax, &Symbolic, null, null) ;
    (void) umfpack_di_numeric (Ap, Ai, Ax, Symbolic, &Numeric, null, null) ;
    (void) umfpack_di_get_lunz(&Lnnz,&Unnz,&n_row,&n_col,&nz_udiag,Numeric);

    Ux=(double*)malloc(Unnz*sizeof(double));
	Ui=(int*)malloc(Unnz*sizeof(int));
	Up=(int*)calloc((ncol+1),sizeof(int));
    Lx=(double*)malloc(Lnnz*sizeof(double));
	Lj=(int*)malloc(Lnnz*sizeof(int));
	Lp=(int*)calloc((nlin+1),sizeof(int));
    P=(int*)calloc((nlin),sizeof(int)); //Permutação de linhas
    Q=(int*)calloc((ncol),sizeof(int));// Permutação de colunas
    Dx=(double*)calloc((ncol),sizeof(double));// Min colxlin The diagonal of U is also returned in Dx and Dz.
    //do recip This argument defines how the scale factors Rs are to be interpretted
    Rs=(double*)malloc(nlin*sizeof(double));//The row scale factors are returned in Rs
    (void) umfpack_di_get_numeric(Lp,Lj,Lx,Up,Ui,Ux,P,Q,Dx,do_recip,Rs,Numeric);
    umfpack_di_free_symbolic (&Symbolic) ;
    (void) umfpack_di_solve (UMFPACK_A, Ap, Ai, Ax, x, b, Numeric, null, null) ;
    umfpack_di_free_numeric (&Numeric) ;
    for (i = 0 ; i < n ; i++) printf ("x [%d] = %g\n", i, x [i]) ;

    CSC_to_matdb(&A,n,n,&nnz,Ax,Ai,Ap);
    
    imprimirmat(A,n,n);
    
    return (0) ;
}
