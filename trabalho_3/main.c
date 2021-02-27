/*
	Gabriel
	Danilo
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

static int N = 0; // tamanho do bloco de leitura (recebido por argv)
static int M = 0; // tamanho do buffer (recebido por argv)

#define default_sequence_size 6 // tamanho da sequencia pre definida
static int default_sequence[default_sequence_size] = {0 ,1, 2, 3, 4, 5}; // sequencia pre definida

static char* binfile = "entrada.bin";

// mensagem de erro e finalizacao do programa
void throw(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(-1);
}

// cria o arquivo binario com a sequencia a ser processada
void generate_input_file()
{
	FILE *file = fopen(binfile, "wb");
	
	if(file == NULL)
		throw("Error creating binary file");
	
	// escrevendo sequencia exemplo no arquivo
	int numberOfValues = 30;
	int values[30] = {1,2,3,1,1,1,1,2,3,4,5,5,5,5,5,5,5,0,0,0,3,3,3,0,1,2,3,4,5,0};
	
	fwrite(&numberOfValues, sizeof(int), 1, file);
	fwrite(&values[0], sizeof(int), numberOfValues, file);
	
	// TODO escrever valores aleatorios no arquivo
	
	fclose(file);
}

// thread para leitura do arquivo e escrita no buffer
void* file_reader(void* arg)
{
	return NULL;
}

// thread para pesquisa pela sequencia pre definida
void* fixed_sequence(void* arg)
{
	return NULL;
}

// thread para computar maior sequencia de valores iguais
void* larger_identical_values(void* arg)
{
	return NULL;
}

// thread para computar numero de sequencias de tamanho 3 com mesmo valor
void* same_value_three_times(void* arg)
{
	return NULL;
}

// ponto de entrada
int main(int argc, char** argv)
{
	if(argc != 3)
		throw("Usage: ./executable readingBlockSize bufferSize");
	
	N = atoi(argv[1]);
	M = atoi(argv[2]);
	
	printf("N:%d M:%d\n", N, M);
	
	for(int i = 0; i < default_sequence_size; i++)
		printf("[%x]", default_sequence[i]);
	printf("\n");
	
	generate_input_file();
	
	// TODO criar threads
	
	// TODO join nas threads e receber valores
	
	fprintf(stdout, "Maior sequencia de valores identicos: \n");
	fprintf(stdout, "Quantidade de triplas: \n");
	fprintf(stdout, "Quantidade de ocorrencias da sequencia <012345>: \n");
	
	
	return 0;
}