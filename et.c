/*
* Author : Maulik Gohil (2768911)
* Change Log:
*	2020-02-03 > Created this file with the code you gave us as example in class having for INCR and DECR functions and Main thread *		     waiting for child threads to exit. Running fine!
*	2020-02-05 > Copied initail code of main function and the whole foo function from ep.c file.
*		   > Removed one pthread_create statement which call DECR function. Removed both INCR and DECR function.
*		   > Added (void *foo) instead of just (void foo) as pthread_create needs a reference(Address) of the function to be called.
*		   > Added Counter to check whether loop in Foo running proprly or not. [Same as ep.c] 
*		   > Added few Printf statements to check thread finishes before main thread exits. (Got few Errors due to scope of the   			     variables!!!)
*	2020-02-06 > Variables int totalBytes; and char* buffer; defined as global so that I  don't need to worry about passing that
*		     values from pthread_create arguments. Checked by running it.
*	2020-02-10 > Added start_timer() & Stop_timer function for time calculation. Defined in the global space. Checked the results.
*	2020-02-11 > Removed Extra Printf Statements.
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void start_timer(void);
float stop_timer(void);

int memSize_Bytes;
char* buffer;
int totalBytes;

void *foo()
{
	int i;
	for(i=0; i< totalBytes; i=i+4096)
	{
		buffer[i]='a';
	}
}

void main(int argc, char *argv[])
{
	memSize_Bytes =  atoi(argv[1]);
	//printf("Got command line argument value:%d \n", memSize_Bytes);
	float time;

	int k = 1024; 	//To define KiloBytes
	totalBytes = k * memSize_Bytes;
	buffer = (char*) calloc(k, memSize_Bytes);

	pthread_t pthread;

	start_timer();
	pthread_create(&pthread,NULL,foo,NULL);
	pthread_join(pthread,NULL);
	time = stop_timer();

	printf("Elapsed time > %f \n",time);
}
