/*
 * Tarea4.c
 *
 *  Created on: Jun 28, 2018
 *      Author: Anahí
 */

#include<stdlib.h>
#include<stdio.h>
#include "StackQueue.h"
#include<string.h>



//***********************************************************************************************

bool balancedBrackets(char *exp);

int main(void){
	setbuf(stdout,NULL);
	char exp[100];
	bool ans;
	printf("Ingrese la expresion para checar sus parentesis\n");
	gets(exp);
	ans=balancedBrackets(exp);
	if(ans==false)
		printf("NO ESTA BALANCEADA\n");
	else
		printf("SI ESTA BALANCEADA CORRECTAMENTE\n");
	return 0;
}

bool balancedBrackets(char *exp){
	Stack MyStack;
	int n=0;
	bool ans;
	char *temp;
	MyStack=createStack();
	while(exp[n]!='\0'){
		if(exp[n]=='('||exp[n]=='['){
			push(MyStack,(void *)&exp[n]);
		}
		else{
			if(exp[n]==')'||exp[n]==']'){
				if(isEmptyS(MyStack)==true)
					return false;

				temp=(char*)pop(MyStack);
				if(exp[n]==')'){
					if(*temp=='(')
						ans=true;
					else
						ans=false;
				}

				if(exp[n]==']'){
					if(*temp=='[')
						ans=true;
					else
						ans=false;
				}
			}
		}
		n++;
	}
	if(isEmptyS(MyStack)==false)
			return false;
	return ans;
}
//**************************************************************************************
/*
char * InfixToPosfix(char *exp);
bool hasHigherPrecedence(char* top, char *operator);

int main(void){
	setbuf(stdout,NULL);
	char exp[100];
	char *ans;
	printf("Ingrese la expresion infija\n");
	gets(exp);
	ans=InfixToPosfix(exp);
	return 0;
}


char * InfixToPosfix(char *exp){

	Stack MyStack=createStack();
	Queue EndQueue=create_queue();
	Queue BegQueue=create_queue();
	char *temp, *topS;
	char *esp=" ";
	int n=0;
	while(exp[n]!='\0'){
		offer_queue(BegQueue,(void*)&exp[n]);
		n++;
	}

	while(isEmptyQ(BegQueue)==false){
		temp=(char*)poll_queue(BegQueue);
		//printf("Beg= %c\n",*temp);
		if(*temp>=48&&*temp<=57){
			//printf("Yo soy un numero\n");
			offer_queue(EndQueue,temp);
		}
		else if(*temp=='('){
			//printf("Yo soy un (\n");
			push(MyStack,(void *)temp);
			offer_queue(EndQueue,(void*)esp);//angrega espacio
		}


		else if(*temp=='+'||*temp=='-'||*temp=='*'||*temp=='/'){
			//printf("Yo soy un operador \n");
			offer_queue(EndQueue,(void*)esp);//agrega espacio
			if(isEmptyS(MyStack)==false){
				topS=(char*)top(MyStack);

				while(*topS!='(' &&  isEmptyS(MyStack)==false){
					if(hasHigherPrecedence(topS,temp)==true){
						topS=(char*)pop(MyStack);
						printf("TOPf is= %c temp is= %c\n",*topS,*temp);
						offer_queue(EndQueue,(void*)topS);
						topS=(char*)top(MyStack);
					}
					else
						break;
				}
			}
			push(MyStack,(void *)temp);

		}



		else if(*temp==')'){
			//printf("Yo soy un )\n");
			offer_queue(EndQueue,esp);
			topS=(char*)top(MyStack);
			while(*topS!='(' &&  isEmptyS(MyStack)!=true){
				topS=(char*)pop(MyStack);
				//printf("TOP is= %c\n",*topS);
				offer_queue(EndQueue,topS);
				topS=(char*)top(MyStack);
			}

			if(isEmptyS(MyStack)!=true){
				topS=(char*)top(MyStack);
				//printf("TOP is= %c\n",*topS);
				if(*topS=='(')
					topS=(char*)pop(MyStack);
				//printf("TOP is= %c\n",*topS);
			}

		}
		else if(isEmptyS(MyStack)!=true){
			while(isEmptyS(MyStack)==true){
				topS=(char*)pop(MyStack);
				//printf("TOP is= %c\n",*topS);
				offer_queue(EndQueue,(void*)esp);
				offer_queue(EndQueue,(void*)topS);
			}
		}
	}

	destroyStack(MyStack);
	destroy_queue(BegQueue);

	while(isEmptyQ(EndQueue)==false){
		temp=(char*)poll_queue(EndQueue);
		printf("%c",*temp);

	}

	return temp;

}

bool hasHigherPrecedence(char* topS, char *operator){
	//printf("Si llegó: %c\n",*topS);
	if(*topS=='*'||*topS=='/'){
			return true;
	}
	else if (*topS=='+'||*topS=='-')
	{
		if(*operator=='*'||*operator=='/'){
			return false;
		}
		else
			return true;
	}
	return false;
}*/

