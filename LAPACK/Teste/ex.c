#include <stdio.h>
#define size 3

#include <stdlib.h>
#include <string.h>
#include "matriz.h"
#include "leitura.h"
#include <lapack.h>
#include <lapacke.h>



void main()
{
int i, j, c1,c2, nrhs, ipiv[size], ok, LDA, LDB ;
double matrix[size][size];
double b[size] ;
char trans ;

c1 = size ;
c2 = 1 ;
LDA = size ;
LDB = size ;
nrhs = 1 ;
trans = 'N' ;

int lwork = size ;
double work[lwork] ;

matrix[0][0] = 2. ;
matrix[1][0] = 1. ;
matrix[2][0] = 1. ;
matrix[0][1] = 4. ;
matrix[1][1] = -6. ;
matrix[2][1] = 0. ;
matrix[0][2] = -2. ;
matrix[1][2] = 7. ;
matrix[2][2] = 2. ;

b[0] = 5. ;
b[1] =-2. ;
b[2] = 9. ;

printf("\noriginal matrix \n\n") ;
for (i=0;i<size;i++) { for(j=0;j<size;j++) { printf("%10.4lf",matrix[j][i]) ; } printf("\n") ; } ;
printf("\n\n") ;

dgetrf_(&c1, &c1, matrix, &LDA, ipiv, &ok) ;

printf("\nLU decomposed matrix \n\n") ;
for (i=0;i<size;i++) { for(j=0;j<size;j++) { printf("%10.4lf",matrix[j][i]) ; } printf("\n") ; } ;
printf("\n\n") ;

printf("row order in terms of original row order\n\n") ;
for(j=0;j<size;j++) { printf("%3d",ipiv[j]) ; } printf("\n") ; 

if (ok !=0) printf("\nok = %3d\n",ok) ;

dgetrs_(&trans, &c1, &nrhs, matrix, &LDA, ipiv, b, &LDB, &ok) ;

printf("\nsolution vector\n\n") ;
for (i=0;i<size;i++) { printf("%10.4lf",b[i]) ; } 

printf("\n\n") ;

}