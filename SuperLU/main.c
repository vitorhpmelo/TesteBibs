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
    int *perm_c=NULL;
    int *perm_r=NULL;
    double *a=NULL;
    SuperMatrix A,AC;
    SuperMatrix L,U;
    int *etree;
    superlu_options_t options;
    set_default_options(&options);
    SuperLUStat_t stat;
    int relax;
    int panel_size;
    GlobalLU_t Glu;
    void *work;

 

    path =config();
    r_dmatfcsv(&mat,path,',',&nlin,&ncol);
    imprimirmat(mat,ncol,nlin);
    printf("\n");
    (void) matdb_to_CSC(mat,nlin,ncol,&nnz,&a,&r_index,&c_ptr);
    printf("Numero de não zeros %d\n\n",nnz);
	printf("Vetor de valores:\n");
	imprimirvet_double(a,nnz);
	printf("Vetor de linhas:\n");
	imprimirvet_int(r_index,nnz);
	printf("Vetor de col:\n");
	imprimirvet_int(c_ptr,ncol+1);
    printf("\n");

    dCreate_CompCol_Matrix(&A, nlin, ncol, nnz, a, r_index, c_ptr, SLU_NC, SLU_D, SLU_GE);
  
    //L=(SuperMatrix*) SUPERLU_MALLOC(sizeof(SuperMatrix));
    //U=(SuperMatrix*) SUPERLU_MALLOC(sizeof(SuperMatrix));
    etree=(int*)malloc((ncol)*sizeof(int));
    perm_c=(int*)malloc((ncol)*sizeof(int));
    perm_r=(int*)malloc((nlin)*sizeof(int));

    dPrint_CompCol_Matrix("A",&A);
    get_perm_c(3,&A,perm_c);
    sp_preorder(&options,&A,perm_c,etree,&AC);
    panel_size=sp_ienv(1);
    relax=sp_ienv(2);
    //options.ColPerm = NATURAL;
    options.Fact=DOFACT;
    StatInit(&stat);
    dgstrf(&options,&AC,relax,panel_size,etree,NULL,0,perm_c,perm_r,&L,&U,&Glu,&stat,&info);
    

    


    
    dPrint_SuperNode_Matrix("L",&L);
    printf("%d",info);

    printf("\n");

    return 0;
}