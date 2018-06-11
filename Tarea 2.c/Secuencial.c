/*
 * Secuencial.c
 *
 *  Created on: Jun 5, 2018
 *      Author: Anahí
 */
//
//#include<stdio.h>
//#include<stdlib.h>
//#include<time.h>
//
//
//void pi();
//
//int main(void)
//{
//	setbuf(stdout, NULL);
//	clock_t start = clock();
//	int ms;
//	pi();
//	clock_t end = clock();
//	ms= 1000*(end-start)/CLOCKS_PER_SEC;
//	printf("Tiempo %d ms",ms);
//	return 0;
//}
//
//void pi()
//{
//	double f=0;
//	long long int i;
//	for (i=1;i<50000000000;i++){
//		f+=(i &1 ? 1.0 : -1.0 )/(2*i-1);
//	}
//
//	f=f*4;
//	printf("Pi: %0.10lf\n",f);
//}
