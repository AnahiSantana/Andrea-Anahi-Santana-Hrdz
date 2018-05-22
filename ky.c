/*
 * ky.c
 *
 *  Created on: 22/05/2018
 *      Author: is715773
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	setbuf(stdout, NULL);
	char cadena[50];
	char y;
	int des, x, i;

	printf("Ingrese la cadena que desea cifrar\n");
	scanf("%s",&cadena);
	printf("Ingrese el desplazacimento que desea\n");
	scanf("%d",&des);

	x=strlen(cadena);

	for (i=0; i<x; i++)
	{
		y= cadena[i]+des;
		if (y>122)
		{
			y=y-26;
		}
		printf("%c",y);
	}
}
