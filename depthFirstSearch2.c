#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include "lattice.h"
#include "stack.h"


bool checkIfAvailable2(node tocheck);
void pushIfNeeded2(node * theNode, Stack *toVisit);
bool checkForPerculation2(bool* rows,bool* columns, int size);

void depthFirstSearch2(node** lattice, int size){
	Stack *toVisit = initStack();  //creates a queue to make a to do list for sites to check
	int maxSize = 0;
	bool** visitedMatrix = (bool**)malloc(size * sizeof(bool *));
	//omp_lock_t maxLock;
	//omp_lock_t visitLock;
	
	//omp_init_lock(&maxLock);
	//omp_init_lock(&visitLock);

	for(int i = 0; i < size; i++){
	visitedMatrix[i] = malloc(size * sizeof(bool));
	}
	
	//check from the left to the right first
	bool* permaColumns = (bool*) malloc(size * sizeof(bool));
	bool* permaRows  = (bool*) malloc(size * sizeof(bool));
	bool* columns = (bool*) malloc(size * sizeof(bool));
	bool* rows = (bool*) malloc(size * sizeof(bool));
	for(int j = 0; j < size; j++){
		for(int i = 0; i < size; i++){
			int istart = i;
			int jstart = j;
			int ii;
			int jj;
		//printf("Current row in loop is:%i \n",i); 
//if visitedmatrix[i][j] is false		
			pushIfNeeded2(&lattice[istart][jstart],toVisit);
			
			//if(lattice[istart][jstart].populated == false){printf("EMPTY\n");}		
			int currentSize = 0;
			// columns = (bool*) realloc(columns, size * sizeof(bool));
			// rows = (bool*) realloc(rows, size * sizeof(bool));
			
			while(!isEmpty(toVisit)){
				currentSize++;
			
				stackNode pulled = pop(toVisit);
				
				istart = pulled.x;
				jstart = pulled.y;
				columns[istart] = true;
				rows[jstart] = true;
				
				//update arrays
				//printf("TEST %i, %i \n",istart,jstart);
				ii = istart;
				jj = jstart;
				//check north
				if(lattice[ii][jj].northcon){
				ii--;
				if(ii == -1 ){
				ii = size-1;	
				}
				pushIfNeeded2(&lattice[ii][jj],toVisit);
				printf("Pushing north neighbour at %i %i\n",j,i);
				}
				//check south
				if(lattice[ii][jj].southcon){
				ii++;
				ii = ii % size;
				pushIfNeeded2(&lattice[ii][jj], toVisit);
				printf("Pushing south neighbour \n");
				}
				
				//check east
				if(lattice[ii][jj].eastcon){
				jj++;
				jj = jj % size;
				pushIfNeeded2(&lattice[ii][jj], toVisit);
				printf("Pushing east neighbour \n");
				}				
				//check west
				if(lattice[ii][jj].westcon){
				jj--;
				if(jj == -1 ){
				jj = size-1;	
				}
				pushIfNeeded2(&lattice[ii][jj], toVisit);
				}
			}
			if(currentSize >= maxSize) {
				maxSize = currentSize;
				for(int j = 0; j < size; j++){
					permaColumns[j] = columns[j];
					permaRows[j] = rows[j];
				}
			}
			for(int j = 0; j < size; j++){
				columns[j] = false;
				rows[j] = false;
			}

		}
	}
	bool percolates = checkForPerculation2(permaRows,permaColumns,size);
	printf("size: %i\npercolates: %s\n",maxSize,percolates ? "true\n":"false\n");
	free(columns);
	free(rows);
}

bool checkForPerculation2(bool* rows, bool* columns, int size){
	bool allTrue = true;
	for(int i = 0; i < size; i++){
		if(!rows[i]){
			allTrue = false;
		}
	}
	if(allTrue) {
		return true;
	}
	allTrue = true;
	for(int i = 0; i < size; i++){
		if(!columns[i]){
			allTrue = false;
		}
	}
	return allTrue;
	//in each item of biggest
	
	return true;
}

void pushIfNeeded2(node * theNode, Stack * toVisit){
			if(checkIfAvailable2(*theNode)){
				printf("PUSHING\n");
			theNode->visited = true;
			push(theNode->xcoord, theNode->ycoord, toVisit);
		}
}

bool checkIfAvailable2(node toCheck){
	if(toCheck.visited == false){
		if(toCheck.populated == true) return true;
	}
	return false;
}













