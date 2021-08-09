#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"
#include "leitura.h"




int main ()
{
    int result;
    char *path;
    int nlin,ncol;
    double **mat;
    path =config();
    mat = r_dmatfcsv(path,'\t',&nlin,&ncol);
    imprimirmat( mat,  nlin, ncol);

    return 0;
}