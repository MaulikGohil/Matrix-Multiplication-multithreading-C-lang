/*
* Author : Maulik Gohil (2768911)
* Change Log:
*	2020-02-03 > Created this file with the code you gave us as example in class having for loop in parent and child. Running fine!
*	2020-02-04 > Checked Online for the reference, added WIFEXITED(status) to check whether chile has exited or not. 
*		     Also added exit(EXIT_FAILURE); which I saw in the online code which I referred (Just another good way to write code).
*		   > Added Foo fnction call in the child and implemented the defination function on top with boy having simple for loop 
*	     	     to check.
*		   > Added few printf statements to check child is getting executed before than parent.
*		   > I changed waitpid() to this> waitpid(cpid, &status, WUNTRACED | WCONTINUED) as per the one solution saw online to 
*		     check what these does. I was giving wrong ordered output. Again changed to waitpid(cpid, &status, 0)
*		   > Implemented code for getting command line argumant and converting it to interger.
*	2020-02-05 > Implemented the body of function foo() [chiled stack modification on COW]. 
*		   > Added counter in foo to check, how many times COW will be taken place with given buffer size and cross-checked 
*		     with mannual solution.
*	2020-02-10 > Added start_timer() & Stop_timer function for time calculation.
*	2020-02-11 > Removed Extra Printf Statements and commentout few lines.
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void start_timer();
float stop_timer(void);

void foo(char* buffer, int sizeOfBuffer)
{
	int i;
	for(i=0; i< sizeOfBuffer; i=i+4096)
	{
		buffer[i]='a';
	}
}
void main(int argc, char *argv[])
{
	pid_t cpid, p;
	float time;
	int status,totalBytes, x;
		
	int memSize_Bytes =  atoi(argv[1]);
	//printf("Got command line argument value:%d \n", memSize_Bytes);
	
	int k = 1024; 	//To define KiloBytes
	totalBytes = k * memSize_Bytes;
	char* buffer = (char*) calloc(k, memSize_Bytes);

	start_timer();
	cpid = fork();
	if(cpid == -1)
	{
		printf("Error while generating Child.\n");
		exit(-1);
	}
	if(cpid == 0)
	{
		foo(buffer,totalBytes);
		exit(0);
	}
	else
	{
		p = waitpid(cpid, &status, 0);
		if(p == -1)
		{
			printf("Error while parent is waiting for child to exit \n");
			exit(EXIT_FAILURE);
		}
		/*if(WIFEXITED(status))
		{
			printf("Child exited with status=%d \n", WEXITSTATUS(status));
		}*/
		time = stop_timer();
		printf("Elapsed time > %f \n", time);
		exit(0);	
	}
}

