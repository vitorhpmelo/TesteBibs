#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matriz.h"
#include "leitura.h"
#include "slu_ddefs.h"

void main(int argc, char *argv[])
{
/*
* Purpose
* =======
*
* This is the small 5x5 example used in the Sections 2 and 3 of the
* Users’ Guide to illustrate how to call a SuperLU routine, and the
* matrix data structures used by SuperLU.
*
*/
SuperMatrix A, L, U, B;
double **mat;
double *a, *rhs;
double s, u, p, e, r, l;
int *asub, *xa;
int *perm_r; /* row permutations from partial pivoting */
int *perm_c; /* column permutation vector */
int nrhs, info, i, m, n, nnz, permc_spec;
superlu_options_t options;
SuperLUStat_t stat;
GlobalLU_t Glu;
NCformat *Ustore;
/* Initialize matrix A. */
int relax,panel_size;
int *etree;

r_dmatfcsv(&mat,"./mat_test.csv",',',&m,&n);
(void) matdb_to_CSC(mat,m,n,&nnz,&a,&asub,&xa);



dCreate_CompCol_Matrix(&A, m, n, nnz, a, asub, xa, SLU_NC, SLU_D, SLU_GE);
/* Create right-hand side matrix B. */
nrhs = 1;
if ( !(rhs = doubleMalloc(m * nrhs)) ) ABORT("Malloc fails for rhs[].");
for (i = 0; i < m; ++i) rhs[i] = 1.0;
dCreate_Dense_Matrix(&B, m, nrhs, rhs, m, SLU_DN, SLU_D, SLU_GE);
//if ( !(perm_r = intMalloc(m)) ) ABORT("Malloc fails for perm_r[].");
//if ( !(perm_c = intMalloc(n)) ) ABORT("Malloc fails for perm_c[].");
perm_c=(int*)malloc((m)*sizeof(int));
etree=(int*)malloc((m)*sizeof(int));
perm_r=(int*)malloc((n)*sizeof(int));

/* Set the default input options. */
set_default_options(&options);
options.ColPerm = NATURAL;
/* Initialize the statistics variables. */
StatInit(&stat);
/* Solve the linear system. */

panel_size=sp_ienv(1);
relax=sp_ienv(2);

//dgstrf(&options,&A,relax,panel_size,etree,NULL,0,perm_c,perm_r,&L,&U,&Glu,&stat,&info);

dgssv(&options, &A, perm_c, perm_r, &L, &U, &B, &stat, &info);
dPrint_CompCol_Matrix("A", &A);
dPrint_CompCol_Matrix("U", &U);
dPrint_SuperNode_Matrix("L", &L);
printf("\n%d\n",info);
Ustore = (NCformat *) U.Store;
printf("\n\nnumero de nao zeros %d\n\n",Ustore->nnz);
print_int_vec("\nperm_r", m, perm_r);
/* De-allocate storage */
SUPERLU_FREE (rhs);
SUPERLU_FREE (perm_r);
SUPERLU_FREE (perm_c);
Destroy_CompCol_Matrix(&A);
Destroy_SuperMatrix_Store(&B);
Destroy_SuperNode_Matrix(&L);
Destroy_CompCol_Matrix(&U);
StatFree(&stat);
}


