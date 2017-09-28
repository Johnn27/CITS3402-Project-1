#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#include"stack.h"
#include"lattice.h"
#include"depthFirstSearch.h"

char setgraphnode(node n){
 if(n.populated)
 return 'O';
 else
 return '+';
}

void printgraph(node **n,int size){
 printf("Lattice: O means populated, + is empty\n");
 for(int i=0;i<size;i++){
  for(int ii=0;ii<size;ii++){
	if(ii==size-1)
	printf("%c",setgraphnode(n[i][ii]));
	else
	printf("%c ",setgraphnode(n[i][ii]));
  }
  printf("\n");
 } 
}

node** generateLattice(int size){
 time_t t;
 srand((unsigned) 1);//(unsigned) time(&t));	//Create seed for random number generator
//node* col = (node *)calloc(size*size,sizeof(node *));
node** n = (node **)malloc(size * sizeof(node *));

for (int i = 0; i < size; ++i)
    n[i] = malloc(size * sizeof(node));
 
for(int i=0;i<size;i++){
  for(int ii=0;ii<size;ii++){
     n[i][ii].visited = false;
     n[i][ii].xcoord = i;
     n[i][ii].ycoord = ii;
   if( prob > (double)rand()/(double)RAND_MAX ){ //If greater then a random number between 0 to 1
     n[i][ii].populated = true;
   }
  } 	
}
return n;
}


int main(int argc,char* argv[]){
int size = SETSIZE;
node** lattice = generateLattice(size);
printgraph(lattice,size);	
depthFirstSearch(lattice,size);
return 0;
}
