/*
* Author : Maulik Gohil
* Chnage Log:
*	2020-02-06 > Created this file. Copied the initial code from et.c including foo() function.
*		   > Chnaged name of void *foo() to matrixMul() and implemented the simple matrix multiplication code as you showed us
*		     in class. Also defined all three matrix in global space. Defined N=160 also. 
*		   > In main, I assigned all the values of matrix A and B as 1, and RES matrix as 0.
*		   > Changed few variable names: Example - memSize_Bytes (et.c file)> nThreads
*	2020-02-07 > Defined array of thread and implemented loop for creating each thread.
*		   > Then defined tid[] array and allocated memory to it using malloc.
*		   > added tid[i]=i; in for loop and also made changes to pass this values as parameters whcih calling the matrixMul().
*		   > Changed due to error: pthread_create(&thread[i],NULL,matrixMul,&tid[i]); --> 
*			                   pthread_create(&thread[i],NULL,(void *)matrixMul,&tid[i]); 
*		   > Removed pthread_join statements, Implemented pthread_barrier.
*	2020-02-08 > Changed: pthread_barrier_init(&barrier,NULL,nThread); --> pthread_barrier_init(&barrier,NULL,nThread+1);
*		   > Implemeted for loop to see the output. Working fine!
*	2020-02-11 > Added start_timer() & Stop_timer function for time calculation. Defination in the global space. Checked the results.
*/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define n 160
int nThread;
int a[n][n];
int b[n][n];
int res[n][n];
pthread_barrier_t barrier;

void start_timer(void);
float stop_timer(void);

void *matrixMul(int *tid)
{
	int myid = *tid;
	int startValue = myid*(n/nThread);
	int endValue = (myid+1)*(n/nThread);
	int i,j,k;
	for(i=startValue;i<endValue;i++){
		for(j=0;j<n;j++){
			for(k=0;k<n;k++){
				res[i][j]=res[i][j]+(a[i][k]*b[k][j]);
			}
		}
	}
	pthread_barrier_wait(&barrier);
}

void main(int argc,char* argv[])
{
	int i,j;
	float time;
	for(i=0; i<n; i++){
		for(j=0;j<n;j++){
			a[i][j]=1;
			b[i][j]=1;
			res[i][j]=0;
		}
	}	
	nThread =  atoi(argv[1]);
	//printf("Got command line argument # of Thread - %d \n", nThread);

	pthread_t thread[nThread];
	pthread_barrier_init(&barrier,NULL,nThread+1);

	int* tid = (int*) malloc(nThread*sizeof(int));
	
	start_timer();
	for(i=0;i<nThread;i++)
	{
		tid[i]=i;
		pthread_create(&thread[i],NULL,(void *)matrixMul,&tid[i]);
	}

	pthread_barrier_wait(&barrier);
	time = stop_timer();
	/*for(i=0; i<n; i++){
		for(j=0;j<n;j++)
		{
			printf(" %d ",res[i][j]);
		}
	printf("\n");
	}*/
	printf("Elapsed time > %f \n",time);
	pthread_barrier_destroy(&barrier);
}
