#include <stdlib.h>
#include <math.h>
#include "slu_ddefs.h"
#include "matriz.h"
#include "leitura.h"


int main()
{
    char* path;
    double ** mat;
    int nlin,ncol;
    int nnz;
    int *a, *r_index,*c_ptr;
    


    path =config();
    mat = r_dmatfcsv(path,',',&nlin,&ncol);
    imprimirmat(mat,ncol,nlin);

    (void) matdb_to_CSC(mat,nlin,ncol,&nnz,a,r_index,c_ptr);
    

    return 0;
}