/*
* Author : Maulik Gohil (2768911)
* Chnage Log:
*	2020-02-08 > Created this file. Used your class note as reference.
*		   > Read about struct timeval online and how to use it.
*	2020-02-10 > While checking the elapsed time in ep.c, I was getting time as 0, addred (float) as cast.
*/

#include<stdio.h>
#include<sys/time.h>

static struct timeval start, end;


void start_timer()
{
	gettimeofday(&start,NULL);
}

float stop_timer()
{	
	float elapsed_time;
	gettimeofday(&end,NULL);
	elapsed_time = (float)((end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)) / 1000000;
	return elapsed_time;	
}

