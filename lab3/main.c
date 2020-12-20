/*
	Gabriel Martins Machado Christo 117217732
	Danilo Santos Vieira			115103034
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "timer.h"

int precision;
int threadsNumber;

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

void* parallel(void* arg)
{
	long int id = (long int) arg;
	double* parcial = calloc(1, sizeof(double));
	
	int block = precision/threadsNumber;
	int crrtBegin = id * block;
	int crrtEnd = id == (threadsNumber-1) ? precision : crrtBegin + block;
	
	for(int i = crrtBegin; i < crrtEnd; i++)
		*parcial += pow(-1, i)/(2*i + 1);
	
	printf("thread id %d begin %d end %d value %lf\n", id, crrtBegin, crrtEnd, *parcial);
	
	pthread_exit((void*)parcial);
}

int main(int argc, char** argv)
{
	if(argc != 3)
		throw("usage: ./executable precision threads");
	precision = atoi(argv[1]);
	threadsNumber = atoi(argv[2]);
	
	double start, finish, result;
	double* parcial = malloc(sizeof(double));
	pthread_t threads[threadsNumber];
	
	GET_TIME(start);
	result = sequential(precision);
	printf("value: %lf\tsequential error %.15lf\n", result, fabs(M_PI - result));
	result = 0;
	GET_TIME(finish);
	printf("elapsed %lf seconds for sequential\n\n", finish - start);
	
	GET_TIME(start);
	for(long int i = 0; i < threadsNumber; i++){
		if(pthread_create(&threads[i], NULL, parallel, (void*)i))
			throw("error on thread creation");
	}
	for(long int i = 0; i < threadsNumber; i++){
		if(pthread_join(threads[i], (void**)&parcial))
			throw("error on joining thread");
		result += *parcial;
		free(parcial);
	}
	GET_TIME(finish);
	printf("value: %lf\tparallel error %.15lf\n", 4*result, fabs(M_PI - 4*result));
	printf("elapsed %lf seconds for parallel\n\n", finish - start);
	
	return 0;
}