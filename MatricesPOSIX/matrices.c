#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "funcionesMatrices.h"
#include "funcionesTime.h"
#define SIZE_DATA (1024*1024*64*3)

static double MEM_CHUNK[SIZE_DATA];

// Estrategia declaración de todas las variables de forma global
int n;
int numThreads;
double *matrizA;
double *matrizB;
double *matrizC;

void *multiplicacionMatricesT(void *arg){
	
	int i, j, k; // contadores
	int idThreads; //Identificador del hilo
	int porcion; //porcion de la matriz A a enviar
	int inicioFila, finfila; //inicio y fin de la porcion
	
	idThreads = *((int *) (arg)); //Se obtiene el identificador del hilo secuencialmente
	porcion = n / numThreads; //Porcion a computar
	inicioFila = idThreads * porcion;
	finfila = (idThreads + 1) * porcion;

	for(i=inicioFila; i<finfila; i++){
		for(j=0; j<n; j++){
			double *pA, *pB, suma = 0.0;
			pA = matrizA + (i*n);
			pB = matrizB + j;
			for(k=0; k<n; k++, pA++, pB+=n){
				suma += (*pA * *pB);	
			}
			matrizC[i*n+j]=suma;
		}	
	}
	return 0;
}


int main(int argc, char **argv){

	int countThreads;
	pthread_t * hilos;
	
	n = (int) atof(argv[1]);
	numThreads = (int) atof(argv[2]);


	matrizA = MEM_CHUNK;
	matrizB = matrizA + n*n;
	matrizC = matrizB + n*n;
	
	matrizInit(n, matrizA, matrizB, matrizC);
	
	/*printf("Matriz A\n");
	imprimirMatriz(n, matrizA);
	
	printf("Matriz B\n");
	imprimirMatriz(n, matrizB);*/

	sampleStart();

	//Declaracion de hilos y asginacion de memoria
	hilos = (pthread_t *) malloc(numThreads*sizeof(pthread_t));
	//Se reparte el trabajo invocado en cada hilo
	for (countThreads = 0; countThreads<numThreads; countThreads++)
	{
		int *tID; //puntero identificador del hilo
		tID = (int *) malloc(sizeof(int));
		*tID = countThreads;
		pthread_create(&hilos[countThreads], NULL, multiplicacionMatricesT, (void *) tID);

	}

	for (countThreads = 0; countThreads < numThreads; countThreads++)
	{
		//Espera a que todos los hilos terminen al tiempo
		pthread_join(hilos[countThreads], NULL);
	}
	
	
	sampleStop();
	printTime();	
	return 0;
}
