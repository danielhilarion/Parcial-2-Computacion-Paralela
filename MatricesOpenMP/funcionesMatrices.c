#include "funcionesMatrices.h"
#include <stdio.h>

void matrizInit(int n, double *matrizA, double *matrizB, double *matrizC){
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			matrizA[j+i*n] = 2.0 * (i+j);
			matrizB[j+i*n] = 3.2 * (i+j);
			matrizC[j+i*n] = 1.0;
		}		
	}
}

void multiplicacionMatrices(int n, double *matrizA, double *matrizB, double *matrizC){
	int i, j, k;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			double *pA, *pB, suma = 0.0;
			pA = matrizA+(i*n);
			pB = matrizB+j;
			for(k=0; k<n; k++){
				suma += (*pA * *pB);	
			}
			matrizC[i*n+j]=suma;
		}	
	}
}


void imprimirMatriz(int n, double *matriz){
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf("%f\t ", matriz[j+i*n]);
		}
		printf("\n");	
	}
}