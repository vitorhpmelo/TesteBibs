#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


double** matrizDinamica(int linha, int coluna)
{

    //aloca matriz dinamica

	int i;
	double** mat;
	mat = (double**)calloc(linha, sizeof(double*));
	for (i = 0; i < linha; i++)
	{
		mat[i] = (double*)calloc(coluna, sizeof(double));
	}
	return mat;
}   