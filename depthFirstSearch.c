#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>
#include "lattice.h"
#include "stack.h"


bool checkIfAvailable(node tocheck);
void pushIfNeeded(node * theNode, Stack *toVisit);
bool checkForPerculation(bool* rows,bool* columns, int size);

void depthFirstSearch(node** lattice, int size){
	Stack *toVisit = initStack();  //creates a queue to make a to do list for sites to check
	int maxSize = 0;
	bool** visitedMatrix = (bool**)malloc(size * sizeof(bool *));
	omp_lock_t maxLock;
	omp_lock_t visitLock;
	
	omp_init_lock(&maxLock);
	omp_init_lock(&visitLock);

	for(int i = 0; i < size; i++){
	visitedMatrix[i] = malloc(size * sizeof(bool));
	}
	
	//check from the left to the right first
	bool* permaColumns;
	bool* permaRows;
	for(int j = 0; j < size; j++){
		for(int i = 0; i < size; i++){
			int istart = i;
			int jstart = j;
			int ii;
			int jj;
			
		//printf("Current row in loop is:%i \n",i); 
//if visitedmatrix[i][j] is false		
			pushIfNeeded(&lattice[istart][jstart],toVisit);
			
			//if(lattice[istart][jstart].populated == false){printf("EMPTY\n");}		
			int currentSize = 0;
			bool* columns = (bool*) malloc(size * sizeof(bool));
			bool* rows = (bool*) malloc(size * sizeof(bool));
			//new array of bools for columns
			//new array of bools for rows
			while(!isEmpty(toVisit)){
				currentSize++;
			
				stackNode pulled = pop(toVisit);
				
				istart = pulled.x;
				jstart = pulled.y;
				columns[istart] = true;
				rows[jstart] = true;
				
				//update arrays
				//printf("TEST %i, %i \n",istart,jstart);
				//free(pulled);
				
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
			if(currentSize >= maxSize) {
				maxSize = currentSize;
				permaColumns = columns;
				permaRows = rows;
			}
			free(rows);
			free(columns);
		}
	}
	bool percolates = checkForPerculation(permaRows,permaColumns,size);
	printf("size: %i\npercolates: %s\n",maxSize,percolates ? "true\n":"false\n");
}

bool checkForPerculation(bool* rows, bool* columns, int size){
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

void pushIfNeeded(node * theNode, Stack * toVisit){
			if(checkIfAvailable(*theNode)){
			theNode->visited = true;
			push(theNode->xcoord, theNode->ycoord, toVisit);
		}
}

bool checkIfAvailable(node toCheck){
	if(toCheck.visited == false){
		if(toCheck.populated == true) return true;
	}
	return false;
}













