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
bool** visitedMatrix;

void siteCheck(int istart, int jstart, node** lattice, int size, Stack *toVisit);
void bondCheck(int istart, int jstart, node** lattice, int size, Stack *toVisit);




void depthFirstSearch(node** lattice, int size, int siteMode){
	// Stack *toVisit = initStack();  //creates a queue to make a to do list for sites to check
	int maxSize = 0;
	
	omp_lock_t maxLock;
	omp_init_lock(&maxLock);

	visitedMatrix = (bool**) malloc(size * sizeof(bool *));
	for(int i = 0; i < size; i++){
	visitedMatrix[i] = malloc(size * sizeof(bool));
	}
	
	//check from the left to the right first
	bool* permaColumns = (bool*) malloc(size * sizeof(bool));
	bool* permaRows  = (bool*) malloc(size * sizeof(bool));

	
	#pragma omp parallel shared(visitedMatrix)
	{
		Stack *toVisit = initStack();
		bool* columns = (bool*) malloc(size * sizeof(bool));
		bool* rows = (bool*) malloc(size * sizeof(bool));
		#pragma omp for 
		for(int j = 0; j < size; j++){
			for(int i = 0; i < size; i++){
				int istart = i;
				int jstart = j;
				//int ii;
				//int jj;
				
			 //printf("Current row in loop is:%i \n",i); 
	//if visitedmatrix[i][j] is false
				if(visitedMatrix[istart][jstart] == false){
				pushIfNeeded(&lattice[istart][jstart],toVisit);
				}
				//if(lattice[istart][jstart].populated == false){printf("EMPTY\n");}		
				int currentSize = 0;
				columns = (bool*) realloc(columns, size * sizeof(bool));
				rows = (bool*) realloc(rows, size * sizeof(bool));
				
				while(!isEmpty(toVisit)){
					currentSize++;
				
					stackNode pulled = pop(toVisit);
					
					istart = pulled.x;
					jstart = pulled.y;
					columns[istart] = true;
					rows[jstart] = true;
					
					//update arrays
					//printf("TEST %i, %i \n",istart,jstart);
					
					//check north
					//if(lattice[istart][jstart].northconnection = true){
						//lattice[start][j] = visted
						//push(lattice[istart][jstart -1].xcoord,ycoord)
					//}
					if(siteMode == 1){
						siteCheck(istart,jstart,lattice,size,toVisit);
					}
					else{ 
						bondCheck(istart,jstart,lattice,size,toVisit);
					}

				}
				omp_set_lock(&maxLock);
				if(currentSize >= maxSize) {
					maxSize = currentSize;
					for(int j = 0; j < size; j++){
						permaColumns[j] = columns[j];
						permaRows[j] = rows[j];
					}
				}
				omp_unset_lock(&maxLock);
				for(int j = 0; j < size; j++){
					columns[j] = false;
					rows[j] = false;
				}	
			}
		}
	}
	//}
	bool percolates = checkForPerculation(permaRows,permaColumns,size);
	printf("size: %i\npercolates: %s\n",maxSize,percolates ? "true\n":"false\n");
	omp_destroy_lock(&maxLock);
	//free(columns);
	//free(rows);
}






void siteCheck(int istart, int jstart, node** lattice, int size, Stack *toVisit){
	//check north
				int ii = istart;
				int jj = jstart;
				ii--;
				if(ii == -1 ){
				ii = size - 1;	
				}
				pushIfNeeded(&lattice[ii][jj],toVisit);
				ii++;
				
				//check south
				ii++;
				ii = ii % size;
				pushIfNeeded(&lattice[ii][jj], toVisit);
				ii--;

				
				//check east
				ii = istart;
				jj = jstart;
				jj++;
				jj = jj % size;
				pushIfNeeded(&lattice[ii][jj], toVisit);
				jj--;
				
				//check west
				ii = istart;
				jj = jstart;
				jj--;
				if(jj == -1 ){
				jj = size-1;	
				}
				pushIfNeeded(&lattice[ii][jj], toVisit);
				jj++;
}

void bondCheck(int istart, int jstart, node** lattice, int size, Stack *toVisit){
	//check north
	if(lattice[istart][jstart].northcon){
		int special = jstart - 1;
		if(special<0){
			special += size;
		}
		pushIfNeeded(&lattice[istart][special], toVisit);
	}

	//check south
	if(lattice[istart][jstart].southcon){
		pushIfNeeded(&lattice[istart][(jstart + 1) % size], toVisit);
	}



	//check east
	if(lattice[istart][jstart].eastcon){
		pushIfNeeded(&lattice[(istart + 1) % size][jstart], toVisit);
	}

	//check west
	if(lattice[istart][jstart].westcon){
		int special = istart - 1;
		if(special<0){
			special += size;
		}
		pushIfNeeded(&lattice[special][jstart], toVisit);
	}
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
			visitedMatrix[theNode->xcoord][theNode->ycoord] = true;
			push(theNode->xcoord, theNode->ycoord, toVisit);
		}
}

bool checkIfAvailable(node toCheck){
	if(toCheck.visited == false){
		if(toCheck.populated == true) return true;
	}
	return false;
}













