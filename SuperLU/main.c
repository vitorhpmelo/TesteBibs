#include <stdlib.h>
#include <math.h>
#include "slu_ddefs.h"
#include "matriz.h"
#include "leitura.h"


int main()
{
    char* path;
    double ** mat=NULL;
    double **B;
    int nlin,ncol;
    int nnz,info;
    int *r_index=NULL,*c_ptr=NULL;
    double *a=NULL;
    SuperMatrix A,L,U;
    superlu_options_t options;
    set_default_options(&options);
    SuperLUStat_t stat;
    int relax=4;
    int panel_size=1;
    GlobalLU_t Glu;
    void *work;
    int lwork =0;
    int *etree;



    path =config();
    r_dmatfcsv(&mat,path,',',&nlin,&ncol);
    imprimirmat(mat,ncol,nlin);
    printf("\n");
    (void) matdb_to_CSC(mat,nlin,ncol,&nnz,&a,&r_index,&c_ptr);
    imprimirmat(mat,ncol,nlin);
    printf("Numero de não zeros %d\n\n",nnz);
	printf("Vetor de valores:\n");
	imprimirvet_double(a,nnz);
	printf("Vetor de linhas:\n");
	imprimirvet_int(r_index,nnz);
	printf("Vetor de col:\n");
	imprimirvet_int(c_ptr,ncol+1);
    printf("\n");
    (void) CSC_to_matdb(&B,nlin,ncol,&nnz,a,r_index,c_ptr);
    imprimirmat(B,ncol,nlin);
    dCreate_CompCol_Matrix(&A, nlin, ncol, nnz, a, r_index, c_ptr, SLU_NC, SLU_D, SLU_GE);
    dgstrf(&options,&A,relax,panel_size,NULL,work,lwork,r_index,c_ptr,&L,&U,&Glu,&stat,&info);


    printf("\n");

    return 0;
}