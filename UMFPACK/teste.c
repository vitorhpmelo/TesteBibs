#include <stdio.h>
#include <time.h>
#include <math.h>
#include "leitura.h"
#include "matriz.h"
#include "umfpack.h"
#include "numref.h"

#define zero 1e-14






int main (void)
{
    double **A;
    int nlin,ncol,nref;
    char* path;
    

    path=config();
    (void) r_dmatfcsv(&A,path,',',&nlin,&ncol);
  
   
    nref=numref(A,nlin,ncol,1,1);

    printf("O sistema precisa de %d referencia (s)\n\n",nref);



    return (0) ;
}
