/*
 * StackQueue.c
 *
 *  Created on: Jun 28, 2018
 *      Author: Anahí
 */


#include <stdio.h>
#include<stdlib.h>
#include"StackQueue.h"

//Implementacion STACK
//***************************************************************************************************
struct strNodeS{
	Type data;
	struct strNodeS *prior;
};

typedef struct strNodeS NodeS;

struct strStack{
	NodeS *top;
	int size;
};

Stack createStack(){
	Stack new=(Stack)malloc(sizeof(struct strStack));
	if(new==NULL)
		return NULL;
	new->top=NULL;
	new->size=0;
	return new;
}

void destroyStack(Stack who){
	while(isEmptyS(who)!=true)
		pop(who);
	free(who);
}

bool push(Stack who, Type data){
	NodeS *newNodeS=(NodeS *)malloc(sizeof(NodeS));
	if(newNodeS==NULL)
		return false;
	newNodeS->prior= who->top;
	newNodeS->data=data;  //Cuidado aquí
	who->size+=1;
	who->top=newNodeS;
	return true;
}

Type pop(Stack who){
	if (who->top==NULL)
		return NULL;
	Type temp;
	NodeS *tempNodeS;
	temp=who->top->data;
	who->size--;
	tempNodeS=who->top;
	who->top=who->top->prior;
	free(tempNodeS);
	return temp;
}

Type top(Stack who){
	if (who->top==NULL)
		return NULL;
	return who->top->data;
}

bool isEmptyS(Stack who){
	if (who->size==0)
		return true;
	else
		return false;
}

// implementacion Queue
//***************************************************************************************************
struct strNodeQ{
	Type data;
	struct strNodeQ *next;
};

typedef struct strNodeQ NodeQ;

struct strQueue{
	NodeQ *first;
	NodeQ *last;
	int size;
};

bool isEmptyQ(Queue who){
	if (who->size==0)
		return true;
	return false;
}

int size_queue(Queue who){
	return who->size;
}

Queue create_queue(){
	Queue new=(Queue)malloc(sizeof(struct strQueue));
	new->first=NULL;
	new->last=NULL;
	new->size=0;
	return new;
}

void destroy_queue(Queue who){
	while(isEmptyQ(who)==false)
		poll_queue(who);
}

void offer_queue(Queue who, Type data){
	NodeQ *newNodeQ=(NodeQ *)malloc(sizeof(struct strNodeQ));
	newNodeQ->next=NULL;
	newNodeQ->data=data;
	if(isEmptyQ(who)==true){
		who->first=newNodeQ;
		who->last=newNodeQ;
	}
	else{
		who->last->next=newNodeQ;
		who->last=newNodeQ;
	}
	who->size++;
}

Type poll_queue(Queue who){
	NodeQ *tempNodeQ;
	Type tempData;
	if(isEmptyQ(who)==false){
		tempNodeQ=who->first;
		tempData=who->first->data;
		who->first=who->first->next;
		free(tempNodeQ);
		who->size--;
		if(isEmptyQ(who)==true)
			who->last=NULL;
		return tempData;
	}
	return NULL;
}

Type peek_queue(Queue who){
	if(isEmptyQ(who)==false)
		return who->first->data;
	else
		return NULL;
}

