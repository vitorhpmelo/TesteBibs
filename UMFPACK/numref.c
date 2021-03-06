#include <stdio.h>
#include <time.h>
#include <math.h>
#include "leitura.h"
#include "matriz.h"
#include "umfpack.h"
#define zero 1e-14



int numref(double **A,int nlin,int ncol,int printU,int printPEF)
{
    int i,nref=0;
    int nnz,Lnnz,Unnz,n_row,n_col,nz_udiag;
    int    *Tj,*Ap,recip ;
    int    *Ti,*Ai,*map;
    double *Tx, *Ax,*Lx,*Ux,*Dx,*Rs,*control,*info;;
    int *Lp,*Lj,*Up,*Ui,*P,*Q,*TUj;
    double **U;
    void *Symbolic, *Numeric ;
    clock_t Tini,tfat,tref;
    double Tfat,Tref;
    FILE* out;

    Tini=clock();
    control = (double *) malloc(UMFPACK_CONTROL*sizeof(double));
    info = (double *) malloc(UMFPACK_INFO*sizeof(double));
    umfpack_di_defaults(control);

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
    
    tref=clock();
    
    if(printU==1)
    {
  
        out=fopen("matsaida.csv","w");
        fimprimirmat(out,U,ncol,ncol);
        fclose(out);
    }

    if(printPEF==1)
    {
        Tfat=(double) (tfat-Tini)/CLOCKS_PER_SEC;
        Tref=(double) (tref-Tini)/CLOCKS_PER_SEC;
        printf("Tempo de fatoraca: %f\n",Tfat);
        printf("Tempo número de referencias: %f\n",Tref);           
    }

    umfpack_di_free_symbolic (&Symbolic) ;
    umfpack_di_free_numeric (&Numeric) ;
    free(control);
    free(info);
    liberarMatrizdina(U,ncol);   
   



    return nref;
}
