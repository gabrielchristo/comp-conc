/*
Alunos:
  Gabriel Martins Machado Christo 117217732
  Danilo Santos Vieira            115103034
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timer.h"

#define TYPE float
#define TYPE_FORMAT "%f"
#define BUFFER_SIZE 128

typedef struct{
    TYPE** matrix;
    int lines;
    int columns;
} matrix_t;

typedef struct{
    matrix_t m1;
    matrix_t m2;
    matrix_t output;
	int currentThread;
	int totalThreads;
} worker;

worker* init_worker(matrix_t m1, matrix_t m2, matrix_t output, int crrtThread, int totalThreads)
{
	worker* w = malloc(sizeof(worker));
	w->m1 = m1;
	w->m2 = m2;
	w->output = output;
	w->currentThread = crrtThread;
	w->totalThreads = totalThreads;
	return w;
}

void throw(char *msg)
{
    printf("%s\n", msg);
    exit(-1);
}

matrix_t init_matrix(int lines, int columns)
{
    matrix_t m;
    m.lines = lines;
    m.columns = columns;

    m.matrix = calloc(lines, sizeof(TYPE));
    if(m.matrix == NULL) throw("error on memory allocation");

    for(int i = 0; i < lines; i++){
        m.matrix[i] = calloc(columns, sizeof(TYPE));
		if(m.matrix[i] == NULL) throw("error on memory allocation");
    }

    return m;
}

void free_matrix(matrix_t m)
{
	if(!m.matrix) return;
	
    for(int i = 0; i < m.lines; i++)
		if(m.matrix[i])
			free(m.matrix[i]);
	
	free(m.matrix);
}

matrix_t create_matrix_from_file(char* path)
{
    FILE* m_file = fopen(path, "r");
    if(m_file == NULL) throw("failed to open file");

    int l, c;
    fscanf(m_file, "%d %d", &l, &c);

    matrix_t m = init_matrix(l, c);

    for(int i = 0; i < l; i++)
		for(int j = 0; j < c; j++)
			fscanf(m_file, TYPE_FORMAT, &m.matrix[i][j]);

    return m;
}

void print_matrix(matrix_t m)
{
	char msg[BUFFER_SIZE]; memset(&msg[0], 0, BUFFER_SIZE);
	strcat(msg, "index %d,%d - ");
	strcat(msg, TYPE_FORMAT);
	strcat(msg, "\n");
	
    for(int i = 0; i < m.lines; i++)
		for(int j = 0; j < m.columns; j++)
			printf(msg, i, j, m.matrix[i][j]);
}

void sequential_multiply(matrix_t m1, matrix_t m2, matrix_t output)
{
    if(m1.columns != m2.lines) throw("dimension error");

    for(int i = 0; i < output.lines; i++)
		for(int j = 0; j < output.columns; j++)
			for(int k = 0; k < m1.columns; k++)
				output.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
}

void* parallel_multiply(void* arg)
{
	worker* w = (worker*) arg;
	
	for(int i = w->currentThread; i < w->output.lines; i += w->totalThreads){
	    //if(i > w->output.lines) pthread_exit(NULL);

	    for(int j = 0; j < w->output.columns; j++)
	        for(int k = 0; k < w->m1.columns; k++)
				w->output.matrix[i][j] += w->m1.matrix[i][k] * w->m2.matrix[k][j];
	}

	pthread_exit(NULL);
}

int main(int argc, char** argv)
{
    double start, finish, total;
	
	// input section
	int use_sequential;
	printf("0 - parallel\n1 - sequential\n");
	scanf("%d", &use_sequential);
	
	int threads_number = 0;
	if(!use_sequential){
		printf("Threads number: ");
		scanf("%d", &threads_number);
	}
	
	char matrix_file_1[BUFFER_SIZE];
	char matrix_file_2[BUFFER_SIZE];
	printf("First matrix filename: "); scanf("%s", &matrix_file_1);
	printf("Second matrix filename: "); scanf("%s", &matrix_file_2);
	
	// memory allocation
	GET_TIME(start);
    matrix_t m1 = create_matrix_from_file(matrix_file_1);
    matrix_t m2 = create_matrix_from_file(matrix_file_2);
	matrix_t m3 = init_matrix(m1.lines, m2.columns);
	GET_TIME(finish);
	printf("Elapsed %lf seconds for initialization\n", finish - start);
	total += (finish - start);

	// calculation sequential
	if(use_sequential){
		GET_TIME(start);
		sequential_multiply(m1, m2, m3);
		GET_TIME(finish);
		printf("Elapsed %lf seconds for sequential processing\n", finish - start);
		total += (finish - start);
	}
	// calculation parallel
	else{
		GET_TIME(start);
		pthread_t threads[threads_number];
		
		for(int i = 0; i < threads_number; i++){
			worker* w = init_worker(m1, m2, m3, i, threads_number);
			if(pthread_create(&threads[i], NULL, parallel_multiply, (void*)w))
				throw("error on thread creation");
		}
			
		for(int i = 0; i < threads_number; i++)
			if(pthread_join(threads[i], NULL))
				throw("error on joining thread");
			
		GET_TIME(finish);
		printf("Elapsed %lf seconds for parallel processing\n", finish - start);
		total += (finish - start);
	}
	
	// matrix output
	//print_matrix(m3);

	// memory deallocation
	GET_TIME(start);
    free_matrix(m1);
    free_matrix(m2);
	free_matrix(m3);
	GET_TIME(finish);
	printf("Elapsed %lf seconds for memory deallocation\n", finish - start);
	total += (finish - start);
	
	printf("Elapsed %lf seconds\n", total);
	

    return 0;
}
