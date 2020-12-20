/*
	Gabriel
	Danilo
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "timer.h"

void throw(char* msg)
{
	printf("%s\n", msg);
	exit(-1);
}

double sequential(int precision)
{
	double result = 0;
	
	for(int i = 0; i < precision; i++)
		result += pow(-1, i)/(2*i + 1);
	
	return 4 * result;
}

int main(int argc, char** argv)
{
	if(argc < 2)
		throw("missing arguments");
	
	int p = atoi(argv[1]);
	
	double start, finish;
	
	GET_TIME(start);
	double r = sequential(p);
	GET_TIME(finish);
	printf("error %.15lf\n", fabs(M_PI - r));
	
	printf("elapsed %lf seconds\n", finish - start);
	
	return 0;
}