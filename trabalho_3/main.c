/*
	Gabriel Martins Machado Christo 117217732
	Danilo Santos Vieira 115103034
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "timer.h"

int timeToStop = 0; // indica momento de finalizacao da leitura do arquivo

int maiorSequencia = 0; // maior sequencia de valores iguais
int maiorSequenciaValor = 0; // valor literal da maior sequencia
int maiorSequenciaIndex = 0; // indice do inicio da maior sequencia
int sequencia3Iguais = 0; // numero de triplas
int sequencia0a5 = 0; // numero de sequencias 012345

static int N = 0; // tamanho do bloco de leitura (recebido por argv)
static int M = 0; // tamanho do buffer (recebido por argv)

int *blocoAtual = NULL; // buffer de tamanho M do bloco compartilhado entre as threads
int tamBlocoAtual = 0; // tamanho atual do bloco

static char* binfile = "entrada.bin"; // nome do arquivo binario

#define NTHREADS 4 // numero de thread fora a main
#define NTHREADS_PESQUISA 2 // numero de threads efetivamente utilizando a barreira
int contador = NTHREADS_PESQUISA; // numero de threads executando na barreira
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // mutex
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // variavel de condicao da barreira
pthread_cond_t condSearch = PTHREAD_COND_INITIALIZER; // variavel de condicao das threads de pesquisa

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
	
	// TODO escrever valores aleatorios no arquivo ?
	
	fclose(file);
}

void printArray(char* msg, int* array, int size)
{
	printf("%s ", msg);
	for(int i = 0; i < size; i++)
		printf("%d ", array[i]);
	printf("\n");
}

// condicao de barreira para threads de pesquisa
void barreira()
{
	pthread_mutex_lock(&mutex);
	
	contador--;
	if(contador > 0){
		printf("thread de pesquisa bloqueada na barreira\n");
		pthread_cond_wait(&condSearch, &mutex);
	}
	else {
		
		printf("ultima thread de pesquisa entrou na barreira\n");
		contador = NTHREADS_PESQUISA;
		
		// limpando buffer do bloco atual para proxima leitura
		tamBlocoAtual = 0;
		memset(blocoAtual, 0, M);
		
		printf("limpei bloco atual e desbloqueei threads na barreira\n");
		// sinalizando threads
		pthread_cond_signal(&cond);
		pthread_cond_broadcast(&condSearch);
	}
	pthread_mutex_unlock(&mutex);
}

// adiciona inteiro ao final do bloco atual
void push(int value)
{
	if(tamBlocoAtual == M) return;
	blocoAtual[tamBlocoAtual++] = value;
}

// thread para leitura do arquivo e escrita no buffer
void* file_reader(void* arg)
{
	FILE *file = fopen(binfile, "rb");
	fseek(file, sizeof(int), SEEK_SET); // ignorando primeiro elemento do arquivo (tamanho da lista)
	
	// buffer temporario de tamanho n para leitura
	int buffer[N];

	int readResponse;
	while((readResponse = fread(&buffer, sizeof(int), N, file)) == N ){
		for(int i = 0; i < N; i++){
			
			pthread_mutex_lock(&mutex);
			
			// se for recebido menos elementos que o tamanho do bloco, estamos na ultima iteracao
			// nesse caso atualizamos a variavel global M para adequar a logica ao ultimo bloco
			//if(readResponse < N){
			//	M = readResponse;
			//	printf("valor de elementos lidos menor que N, ultima iteracao\n");
			//}
			
			// checando buffer cheio
			while(tamBlocoAtual == M){
				printf("loop de leitura bloqueou devido buffer cheio\n");
				pthread_cond_wait(&cond, &mutex);
			}
			// adicionando novo elemento no bloco atual
			push(buffer[i]);
			
			printArray("bloco apos adicionar elemento", blocoAtual, tamBlocoAtual);
			
			// sinalizando threads de pesquisa apos cada insercao
			pthread_cond_broadcast(&condSearch);
			
			pthread_mutex_unlock(&mutex);
		}
	}
	printf("fim do loop de leitura do arquivo\n");
	
	pthread_mutex_lock(&mutex);
	timeToStop = 1; // hora de parar os loops das threads de pesquisa
	pthread_mutex_unlock(&mutex);
	
	fclose(file); // fechando arquivo
	
	return NULL;
}

// thread para computar numero de sequencias de tamanho 3 com mesmo valor
void* same_value_three_times(void* arg)
{
	static int primeiroValor = -1;
	static int contador3Valores = 0;

	while(1){
		
		pthread_mutex_lock(&mutex);
		// aguardando buffer ficar cheio para processamento
		while(tamBlocoAtual < M && !timeToStop){
			printf("thread 3 valores iguais esperando buffer ficar cheio\n");
			pthread_cond_wait(&condSearch, &mutex);	
		}
		printf("thread 3 valores iguais desbloqueada\n");
		pthread_mutex_unlock(&mutex);
	
		if(primeiroValor == -1)
			primeiroValor = blocoAtual[0]; // se for primeira iteração tenho que inicializar o valor estatico
	
		// checando tres valores repetidos
		for(int i = 0; i < M; i++){
			if(blocoAtual[i] == primeiroValor){
				contador3Valores++;
			}
			else {
				primeiroValor = blocoAtual[i];
				contador3Valores = 1;
			}
			if(contador3Valores == 3){
				sequencia3Iguais++;
				contador3Valores = 0;
				printf("sequencia de 3 valores iguais no indice %d (ultimo indice da tripla) com valor %d\n", i, primeiroValor);
			}
			else printf("nada encontrado nesse bloco na thread de 3 valores iguais\n");
		}
		
		barreira(); // entrando na barreira das threads de pesquisa
		
		if(timeToStop) break; // parando loop no fim do arquivo
		
	}
	
	return NULL;
}

// thread para pesquisa pela sequencia pre definida
void* fixed_sequence(void* arg)
{
	// variaveis da maquina de estados
	static int estado = -1;
	
	while(1){
		
		pthread_mutex_lock(&mutex);
		
		// aguardando buffer ficar cheio para processamento
		while(tamBlocoAtual < M && !timeToStop){
			printf("thread sequencia 0 a 5 esperando buffer ficar cheio\n");
			pthread_cond_wait(&condSearch, &mutex);	
		}
		printf("thread sequencia 0 a 5 desbloqueada\n");
		
		pthread_mutex_unlock(&mutex);
		
		// maquina de estados para checar a sequencia desejada
		for(int i = 0; i < M; i++){
			switch(estado){
				case -1:
					if(blocoAtual[i] == 0){
						estado = 0;
						printf("estado inicial 0\n");
					} else estado = -1;
					break;
				case 0:
					if(blocoAtual[i] == 1){
						estado = 1;
						printf("estado 0 para 1\n");
					} else estado = -1;
					break;
				case 1:
					if(blocoAtual[i] == 2){
						estado = 2;
						printf("estado 1 para 2\n");
					} else estado = -1;
					break;
				case 2:
					if(blocoAtual[i] == 3){ 
						estado = 3;
						printf("estado 2 para 3\n");
					} else estado = -1;
					break;
				case 3:
					if(blocoAtual[i] == 4){ 
						estado = 4;
						printf("estado 3 para 4\n");
					} else estado = -1;
					break;
				case 4:
					if(blocoAtual[i] == 5){
						estado = 5;
						printf("estado 4 para 5\n");
					} else estado = -1;
					break;
			}
		}
		
		if(estado == 5){
			sequencia0a5++;
			estado = 0;
			printf("encontrada sequencia de 0 a 5\n");
		}
		else printf("nada encontrado nesse bloco na thread sequencia de 0 a 5\n");
		
		barreira(); // entrando na barreira das threads de pesquisa
		
		if(timeToStop) break; // parando loop no fim do arquivo
		
	}
	return NULL;
}

// thread para computar maior sequencia de valores iguais
void* larger_identical_values(void* arg)
{
	return NULL;
}

// ponto de entrada
int main(int argc, char** argv)
{
	if(argc != 3)
		throw("Usage: ./executable readingBlockSize bufferSize");
	
	// definicao variaveis de medicao de tempo
	double start, finish;
	
	// tamanho do bloco de leitura
	N = atoi(argv[1]);
	
	// tamanho do buffer compartilhado
	M = atoi(argv[2]);
	blocoAtual = (int*) malloc(sizeof(int) * M);
	
	// criando arquivo binario
	//generate_input_file();
	
	// inicio medicao de tempo
	GET_TIME(start);
	
	// criando threads
	pthread_t threads[NTHREADS];
	if(pthread_create(&threads[0], NULL, fixed_sequence, NULL)) throw("error on thread creation");
	if(pthread_create(&threads[1], NULL, larger_identical_values, NULL)) throw("error on thread creation");
	if(pthread_create(&threads[2], NULL, same_value_three_times, NULL)) throw("error on thread creation");
	if(pthread_create(&threads[3], NULL, file_reader, NULL)) throw("error on thread creation");
	
	// join nas threads
	for(int i = 0; i < NTHREADS; i++)
		pthread_join(threads[i], NULL);
	
	// fim de execucao
	GET_TIME(finish);
	
	// destruindo mutex e condvar
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	pthread_cond_destroy(&condSearch);
	
	fprintf(stdout, "\n\nTempo corrido: %lf segundos\n\n", finish - start);
	
	fprintf(stdout, "Maior sequencia de valores identicos: %d\n", maiorSequencia);
	fprintf(stdout, "Quantidade de triplas: %d\n", sequencia3Iguais);
	fprintf(stdout, "Quantidade de ocorrencias da sequencia <012345>: %d\n", sequencia0a5);
	
	return 0;
}
