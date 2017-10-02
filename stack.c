#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "stack.h"







// stackNode *tailNode;
// stackNode *start;



Stack * initStack(){
	Stack *newStack = (Stack *) malloc(sizeof(Stack));
	newStack->start = NULL;
	return newStack;
}
// void startStack(int x, int y){
	// start = (stackNode *) malloc (sizeof(stackNode));
	// start->x = x; 
	// start->y = y;
        // start->parent = NULL;
	// start->next = NULL;

	
	// tailNode = start;			//head is set to tail as there is only one elemen

// }



void push(int x, int y, Stack * stack){ //adding an element to the end of the que
	stackNode *a;
	a = (stackNode*) malloc(sizeof(stackNode));
	a->x = x;
	a->y = y;
	//printf("pushing x:%i and y:%i\n",a->x,a->y);
	if(stack->start){
		a->next = stack->start;
		stack->start = a;
	}
	else{
	stack->start = a;
	}
}

stackNode pop(Stack *stack){
	// if(stack->start == NULL) {
	// 	printf("empty stack");
	// 	return;// NULL;
	// }
	stackNode result = *stack->start;
	stackNode * togo = stack->start;
	stack->start = stack->start->next;
	//printf("popping x:%i and y:%i\n",result->x,result->y);
	free(togo);
	return result;
}

bool isEmpty(Stack * s){
	if(s->start == NULL) {
		//printf("empty\n"); 
		return true;
	}
	else return false;
}