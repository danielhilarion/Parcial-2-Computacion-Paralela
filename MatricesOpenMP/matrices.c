#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "funcionesMatrices.h"
#include "funcionesTime.h"
#define SIZE_DATA (1024*1024*64*3)

static double MEM_CHUNK[SIZE_DATA];


int main(int argc, char **argv){

	int n = (int) atof(argv[1]); //tamaño de la matriz
	int numThreads = (int) atof(argv[2]);// cantidad de hilos a emplear

//#pragma omp parallel

	double *matrizA, *matrizB, *matrizC;
	matrizA = MEM_CHUNK;
	matrizB = matrizA + n*n;
	matrizC = matrizB + n*n;

//#pragma omp master
	
	matrizInit(n, matrizA, matrizB, matrizC);

	/*printf("Matriz A\n");
	imprimirMatriz(n, matrizA);
	
	printf("Matriz B\n");
	imprimirMatriz(n, matrizB);*/

	omp_set_num_threads(numThreads);
	sampleStart();

#pragma omp parallel for
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			double *pA, *pB, suma = 0.0;
			pA = matrizA+(i*n);
			pB = matrizB+j;
			for(int k=0; k<n; k++){
				suma += (*pA * *pB);	
			}
			matrizC[i*n+j]=suma;
		}	
	}

	sampleStop();	
	
	printTime();	
	return 0;

}
