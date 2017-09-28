#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include "lattice.h"
#include "stack.h"


bool checkIfAvailable(node *tocheck);
void pushIfNeeded(node *theNode, Stack *toVisit);

void depthFirstSearch(node** lattice, int size){
	Stack *toVisit = initStack();  //creates a queue to make a to do list for sites to check
	int maxSize = 0;
	bool** visitedMatrix = (bool**)malloc(size*sizeof(bool*));
	for(int i = 0; i < size; i++){
	visitedMatrix[i] = (bool *)malloc(size * sizeof(bool));
	}
	//check from the left to the right first
	for(int i = 0; i < size; i++){
		int istart = i;
		int jstart = 0;
		int ii;
		int jj;
		
	printf("Current row in loop is:%i \n",i); 	
		pushIfNeeded(&lattice[istart][jstart],toVisit);
		
		if(lattice[istart][jstart].populated){printf("EMPTY \n");}		
		int currentSize=0;
		while(!isEmpty(toVisit)){
			currentSize++;
			
			stackNode *pulled = pop(toVisit);
			
			istart = pulled->x;
			jstart = pulled->y;
			

			printf("TEST %i, %i \n",istart,jstart);

			free(pulled);
			
			//check north
			
			ii = istart;
			jj = jstart;
			ii--;
			if(ii == -1 ){
			ii = size-1;	
			}
			pushIfNeeded(&lattice[ii][jj],toVisit);
			
			//check south
			ii = istart;
			jj = jstart;
			ii++;
			ii = ii % size;
			pushIfNeeded(&lattice[ii][jj], toVisit);

			
			//check east
			ii = istart;
			jj = jstart;
			jj++;
			jj = jj % size;
			pushIfNeeded(&lattice[ii][jj], toVisit);
			
			//check west
			ii = istart;
			jj = jstart;
			jj--;
			if(jj == -1 ){
			jj = size-1;	
			}
			pushIfNeeded(&lattice[ii][jj], toVisit);
			
		}
		if(currentSize>maxSize){
		maxSize = currentSize;
			}
	}
	printf("Maximum cluster is: %i \n",maxSize);	
	
}

bool checkForPerculation(Stack * cluster){
	return true;
}

void pushIfNeeded(node *theNode, Stack *toVisit){
		if(checkIfAvailable(theNode)){
		theNode->visited = true;
		push(theNode->xcoord, theNode->ycoord, toVisit);
		}
}

bool checkIfAvailable(node *toCheck){
	if(toCheck->visited == false){
		if(toCheck->populated == true) return true;
	}
	return false;
}














