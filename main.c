#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"
#include "leitura.h"
#include <lapacke.h>

int main ()
{
    int result;
    char *path;
    int nlin,ncol;
    double **mat;
    path =config();
    mat = r_dmatfcsv(path,'\t',&nlin,&ncol);
    imprimirmat( mat,  nlin, ncol);
    (void) =LAPACKE_dgetrf()

    
    return 0;
}