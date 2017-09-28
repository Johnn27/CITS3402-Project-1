#include <stdio.h>
#include <omp.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 2000
int main(){

clock_t begin = clock();
omp_set_num_threads(4);
srand(time(NULL));

float array[SIZE];
for(int i = 0;i<SIZE;i++)
{
array[i] = (float) rand()/(float)RAND_MAX;
}

float total = 0;
float localSum = 0;

#pragma omp parallel shared(total) private(localSum)
{
#pragma omp for
	for(int i = 0;i<SIZE;i++){
	localSum += array[i];
	}
total+= localSum;
	printf("TOTALSUM - %g \n",total);	
	
	
	clock_t end = clock();
	double time_spent = (double) (end - begin)/ CLOCKS_PER_SEC;
	
	printf("The Parallel region is executed by thread %i and time %10.6f \n		",omp_get_thread_num(),time_spent);
}

float totalparallel = 0;
	for(int i = 0;i<SIZE;i++){
	totalparallel += array[i];
	}	
	printf("TOTALSUM NON PARALLEL -  %g\n",totalparallel);
return 0;
}

