#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>
#include<errno.h>

#include"stack.h"
#include"lattice.h"
#include"depthFirstSearch.h"

char* setgraphnode(node n){
 char* o = {"O"};
 char* p = {"+"};
 if(n.populated)
 return o;
 else
 return p;
}

char* appendString(char * str1, char * str2){
 char * new_str;
if((new_str = malloc(strlen(str1)+strlen(str2)+1)) != NULL){
    new_str[0] = '\0';   // ensures the memory is an empty string
    strcat(new_str,str1);
    strcat(new_str,str2);
} else {
    fprintf(stderr,"malloc failed!\n");
    // exit?
}
return new_str;
}

void printgraph(node **n,int size,int type ){
if(type == 1){
 printf("Lattice: O means populated, + is empty\n");
 for(int i=0;i<size;i++){
  for(int ii=0;ii<size;ii++){
  if(ii==size-1)
  printf("%s",setgraphnode(n[i][ii]));
  else
  printf("%s ",setgraphnode(n[i][ii]));
  }
  printf("\n");
 } 
}

if(type == 2){
 printf("Lattice: O means populated, -- is for bond\n");
 for(int ii = 0; ii<size; ii++){
  char* botline = {""};
  char* topline = {""};
  char* midline = {""};
   for(int i = 0; i<size; i++){
  //printf(" ");
  if(n[i][ii].westcon)
  midline = appendString(midline, "-");
  else
  midline = appendString(midline, " ");
  // if(ii==size-1)
  // midline = appendString(midline, setgraphnode(n[i][ii]));
  // else
  midline = appendString(midline, setgraphnode(n[i][ii]));
  if(n[i][ii].eastcon)
  midline = appendString(midline, "-");
  else
  midline = appendString(midline, " ");
  if(n[i][ii].southcon){
  // char str[5];
  // sprintf(str, "%d", ii);
  //botline = appendString(botline, str);
  botline = appendString(botline, "|  ");
  }
  else
  botline = appendString(botline, "   ");

  if(n[i][ii].northcon){
  topline = appendString(topline, "|  ");
  }
  else
  topline = appendString(topline, "   ");
    }
  printf(" %s \n",topline);
  printf("%s",midline);
  printf("\n %s \n",botline);
  free(topline);
  free(midline);
  free(botline);
  } 
 }
}

node** generateLatticeBond(int size,double prob){
node** n = (node **)malloc(size * sizeof(node *));
for (int i = 0; i < size; ++i)
    n[i] = (node*) malloc(size * sizeof(node));
 
for(int i=0;i<size;i++){
  for(int ii=0;ii<size;ii++){ //Initialise each node and assume all node is populated
     n[i][ii].visited = false;
     n[i][ii].xcoord = i;
     n[i][ii].ycoord = ii;
     n[i][ii].populated = true;
   n[i][ii].northcon = false;  
   n[i][ii].southcon = false;
   n[i][ii].eastcon = false;
   n[i][ii].westcon = false;  
   
  }   
}

for(int i=0;i<size;i++){
  for(int ii=0;ii<size;ii++){ //Initialise bonds within sites
  // if(ii==0){ //Only necessary to do the top bonds at the start
  //    if( prob > (double)rand()/(double)RAND_MAX ){ //If greater then a random number between 0 to 1
  //   n[i][ii].northcon = true;
  //   n[i][size - 1].southcon = true;
  //    }
  // }
  // if(i==0){
  //    if( prob > (double)rand()/(double)RAND_MAX ) {
  //   n[i][ii].westcon = true;
  //   n[size - 1][ii].eastcon = true;  
  //    }
  // }
     if( prob > (double)rand()/(double)RAND_MAX ) {    
    n[i][ii].southcon = true;
    n[i][(ii + 1) % size].northcon = true;  
     }    
     if( prob > (double)rand()/(double)RAND_MAX ) {
    n[i][ii].eastcon = true;
    n[(i + 1) % size][ii].westcon = true; 
     }
  }   
}
return n;
}

node** generateLatticeSite(int size,double prob){
//node* col = (node *)calloc(size*size,sizeof(node *));
node** n = (node **) malloc(size * sizeof(node *));


for (int i = 0; i < size; ++i)
    n[i] = (node*) malloc(size * sizeof(node));
 
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
int size = atoi(argv[1]);
double prob = atof(argv[2]);
// time_t t;
  //Create seed for random number generator
srand((int) 1 /*time(&t)*/);
node** lattice = generateLatticeBond(size,prob);
if(size < 128){
printgraph(lattice,size,2); 
}
//depthFirstSearch(lattice,size);
depthFirstSearch(lattice,size,2);
return 0;
}