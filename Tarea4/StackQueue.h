/*
 * StackQueue.h
 *
 *  Created on: Jun 28, 2018
 *      Author: Anahí
 */

#ifndef STACKQUEUE_H_
#define STACKQUEUE_H_

typedef void *Type;
typedef enum {false, true} bool;

typedef struct strStack *Stack;
typedef struct strQueue *Queue;



Stack createStack();
void destroyStack(Stack);
bool push(Stack, Type);
Type pop(Stack);
Type top(Stack);
bool isEmptyS(Stack);


Queue create_queue();
void destroy_queue(Queue);
void offer_queue(Queue, Type);
Type poll_queue(Queue);
Type peek_queue(Queue);
bool isEmptyQ(Queue);
int size_queue(Queue);



#endif /* STACKQUEUE_H_ */
