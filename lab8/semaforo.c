
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define WRITERS 2 // numero de escritores
#define READERS 2 // numero de leitores
#define CYCLES 3 // numero maximo de ciclos por thread

sem_t em_e, em_l, escr, leit; // semaforos
int e = 0, l = 0; // numero atual de escritores e leitores

void throw(char* msg)
{
	printf("%s\n", msg);
	exit(-1);
}

void show(int id, char* msg)
{
	char* type = id <= READERS ? "L" : "E"; // checando pelo id se e thread leitora ou escritora
	int newid = id <= READERS ? id : id - READERS;
	printf("[%s%d] %s\n", type, newid, msg);
}

void* leitor(void* arg)
{
	int id = *(int*)arg;
	int cycle = 0; // contador de ciclos
	
	while(cycle < CYCLES)
	{
		show(id, "aguardando para poder ler");
		sem_wait(&leit); // bloqueando leitura devido prioridade para escrita
		
		sem_wait(&em_l); // mutex leitura
		l++;
		if(l==1){
			sem_wait(&escr); // bloqueando escrita se for primeiro leitor
			show(id, "bloqueou escrita devido ser primeiro leitor");
		}
		sem_post(&em_l);
		
		sem_post(&leit); // desbloqueando leitura
		
		// leitura
		show(id, "leu");
		
		sem_wait(&em_l); // mutex leitura
		l--;
		if(l==0){
			sem_post(&escr); // libera escrita se for ultimo leitor
			show(id, "desbloqueou escrita devido ser ultimo leitor");
		}
		sem_post(&em_l);
		
		cycle++;
	}
}

void* escritor(void* arg)
{
	int id = *(int*)arg;
	int cycle = 0; // contador de ciclos
	
	while(cycle < CYCLES)
	{
		sem_wait(&em_e); // mutex escrita
		e++;
		if(e==1){
			sem_wait(&leit); // bloqueia leitura se for primeiro escritor
			show(id, "bloqueou leitura por ser primeiro escritor");
		}
		sem_post(&em_e);
		
		show(id, "aguardando para poder escrever");
		sem_wait(&escr); // bloqueia a escrita
		
		// escrita
		show(id, "escrevendo");
		
		sem_post(&escr); // libera a escrita
		show(id, "finalizou escrita");
		
		sem_wait(&em_e); // mutex escrita
		e--;
		if(e==0){
			sem_post(&leit); // libera leitura se for ultimo escritor
			show(id, "desbloqueou leitura por ser ultimo escritor");
		}
		sem_post(&em_e);
		
		cycle++;
	}
}

int main(int argc, char** argv)
{
	// inicializando semaforos
	sem_init(&escr, 0, 1);
	sem_init(&leit, 0, 1);
	sem_init(&em_e, 0, 1);
	sem_init(&em_l, 0, 1);
	
	// inicializando threads
	pthread_t threads[READERS + WRITERS];
	int thread_ids[READERS + WRITERS];
	
	// leitores
	for (int i = 0; i < READERS; i++){
		thread_ids[i] = i + 1;
		if (pthread_create(&threads[i], NULL, leitor, (void*)&thread_ids[i]))
			throw("error on thread creation");
	}
		
	// escritores
	for (int i = 0; i < WRITERS; i++){
		thread_ids[i + READERS] = READERS + i + 1;
		if (pthread_create(&threads[i + READERS], NULL, escritor, (void*)&thread_ids[i + READERS]))
			throw("error on thread creation");
	}
		
	// join nas threads
	for (int i = 0; i < READERS + WRITERS; i++)
		pthread_join(threads[i], NULL);
	
	// liberando semaforos
	sem_destroy(&escr);
	sem_destroy(&leit);
	sem_destroy(&em_e);
	sem_destroy(&em_l);
	
	return 0;
}