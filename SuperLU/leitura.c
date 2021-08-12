#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"
#include "leitura.h"


char *config()
{
    FILE *arquivo=NULL;
    arquivo = fopen("config.txt","r");
    char p;
    char *path;
    path=(char*) malloc(100*sizeof(char));
    while ((p=fgetc(arquivo))!=EOF)
    {
        if (p!='\n')strncat(path,&p,1);
        
    }
    return path;
    
}


double** r_dmatfcsv(char path[100],char sep,int *nlin,int *ncol)//Lê uma matriz de double em csv
{
    
    FILE *arquivo=NULL;
    char p;
    char num[100];
    num[0]='\0';
    *nlin=0;
    *ncol=0;
    double **mat;
    int i =0,j=0;
    arquivo = fopen(path,"r");
   
    if (arquivo==NULL) return NULL;
    while ((p=fgetc(arquivo))!=EOF)
    {
        if (p==sep && (*nlin)==0) (*ncol)++;
        if (p=='\n') (*nlin)++;
    }

    mat=matrizDinamica(*nlin,*ncol);

    rewind(arquivo);


    while ((p=fgetc(arquivo))!=EOF)
    {
         
        if (p==sep){
            
            mat[i][j]=(double) atof(num);
            j++;
            num[0]='\0';
        }
        else if (p=='\n') 
        {
            mat[i][j]=(double) atof(num);
            i++;
            num[0]='\0';
        }
        else 
        {
            strncat(num,&p,1);
        }
    }


    return mat;
}

void imprimirmat(double** mat, int linha, int col)
{
	int i, j;
	for (i = 0; i < linha; i++)
	{

		for (j = 0; j < col; j++)
		{
			printf("%.2e\t ", mat[i][j]);
		}
		printf("\n");
	}
}

void fimprimirmat(FILE* arquivo, double** mat, int linha, int col)
{
	int i, j;
	for (i = 0; i < linha; i++)
	{

		for (j = 0; j < col; j++)
		{
			fprintf(arquivo, "%.2e\t ", mat[i][j]);
		}
		fprintf(arquivo, "\n");
	}
}
