/*
 * hilos.c
 *
 *  Created on: Jun 10, 2018
 *      Author: Anahí
 */



#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

typedef struct {
	long long int superior;
	long long int inferior;
	double        resultado;
}limites;

DWORD WINAPI  pi(void *param);

int main(void)
{
	setbuf(stdout, NULL);

	double f=0;
	int ms, i, noHilos;
	long long int r,LIM=50000000000;

	HANDLE array_handles[16]; //arreglo de handles
	limites limite[16];      //arreglo para los limites de cada for

	printf("¿Hilos?\n"),
	scanf("%d",&noHilos);
	clock_t start = clock();
	r= LIM/noHilos;

	for(i=0;i<noHilos;i++){
		limite[i].inferior=r*i+1;
		limite[i].superior=r*(i+1);
		limite[i].resultado=0;
		array_handles[i]=CreateThread(NULL,0,pi,(void *)&limite[i],0,NULL);
	}

	 WaitForMultipleObjects(noHilos, array_handles, TRUE, INFINITE);

	for(i=0;i<noHilos;i++){
			f=f+limite[i].resultado;
			}

	clock_t end = clock();
	printf("Pi: %0.10lf\n",f);
	ms= 1000*(end-start)/CLOCKS_PER_SEC;
	printf("Tiempo %d ms",ms);
	return 0;
}

DWORD WINAPI  pi(void * param){
	limites *l=(limites*)param;
	long long int i;

	for (i=l->inferior;i<l->superior;i++){
		l->resultado+=(i &1 ? 1.0 : -1.0 )/(2*i-1);
	}

	l->resultado=(l->resultado)*4;
	return 0;
}
