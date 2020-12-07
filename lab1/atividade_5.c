/*
Alunos:
	Gabriel Martins Machado Christo 117217732
	Danilo Santos Vieira 			115103034
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <pthread.h>

#define N 15
#define NTHREADS 2

void *increaseByOne(void* arg) {
  int* array = (int*) arg;
  for(int i = 0; i < N; i++) array[i]++;
  pthread_exit(NULL);
}

void printArray(char* msg, int* array){
	printf("%s\n", msg);
	for(int i = 0; i < N; i++) printf("Index %d: %d\n", i, array[i]);
	printf("\n");
}

int main() {
  pthread_t tid_sistema[NTHREADS]; 
  int thread;
  
  int array[N];
  memset(array, 0, N*sizeof(int));
  printArray("valores iniciais", &array[0]);

  for(thread=0; thread<NTHREADS; thread++) {
    if (pthread_create(&tid_sistema[thread], NULL, increaseByOne, (void*) &array[0])) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }
  
  for (thread=0; thread<NTHREADS; thread++) {
    if (pthread_join(tid_sistema[thread], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
  }
  
  printArray("valores finais", &array[0]);
  pthread_exit(NULL);
}
