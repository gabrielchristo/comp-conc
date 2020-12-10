/*
Alunos:
  Gabriel Martins Machado Christo
  Danilo Santos Vieira
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "timer.h"

typedef struct{
    float** matrix;
    int lines;
    int columns;
} matrix_t;

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

    m.matrix = calloc(lines, sizeof(float));
    if(m.matrix == NULL) throw("error on memory allocation");

    for(int i = 0; i < lines; i++){
        m.matrix[i] = calloc(columns, sizeof(float));
	if(m.matrix[i] == NULL) throw("error on memory allocation");
    }

    return m;
}

void free_matrix(matrix_t m)
{
    for(int i = 0; i < m.lines; i++) free(m.matrix[i]);
    free(m.matrix);
}

matrix_t create_matrix_from_file(char* path)
{
    FILE* m_file = fopen(path, "r");
    if(m_file == NULL) throw("failed to open file");

    int l, c;
    fscanf(m_file, "%d %d", &l, &c);

    matrix_t m = init_matrix(l, c);

    for(int i = 0; i < l; i++){
	for(int j = 0; j < c; j++){
	    fscanf(m_file, "%f", &m.matrix[i][j]);
	}
    }

    return m;
}

void print_matrix(matrix_t m)
{
    for(int i = 0; i < m.lines; i++){
	for(int j = 0; j < m.columns; j++){
		printf("index %d,%d - %f\n", i, j, m.matrix[i][j]);
	}
    }
}


int main(int argc, char** argv)
{
    double start, finish;
    GET_TIME(start);
    
    matrix_t m1 = create_matrix_from_file("matriz_1.txt");
    matrix_t m2 = create_matrix_from_file("matriz_2.txt");

    print_matrix(m1);
    print_matrix(m2);

    free_matrix(m1);
    free_matrix(m2);

    GET_TIME(finish);
    printf("elapsed %lf seconds\n", finish - start);

    return 0;
}
