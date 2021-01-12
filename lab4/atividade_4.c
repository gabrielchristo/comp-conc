/* 
	Gabriel Martins Machado Christo - 117217732
	Danilo Santos Vieira - 115103034
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS  4

/* Variaveis globais */
int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;

/* Thread A */
void *A (void *t) {

  pthread_mutex_lock(&x_mutex);
  x++;
  printf("%s\n", (char*)t);
  if (x==2) {
      pthread_cond_broadcast(&x_cond);
  }
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}

/* Thread B */
void *B (void *t) {
	
  pthread_mutex_lock(&x_mutex);
  if (x < 2) { 
     pthread_cond_wait(&x_cond, &x_mutex);
  }
  printf("%s\n", (char*)t);
  pthread_mutex_unlock(&x_mutex); 
  
  pthread_exit(NULL);
}

/* Funcao principal */
int main(int argc, char *argv[]) {
  int i; 
  pthread_t threads[NTHREADS];
  
  char* tudo_bem = "tudo bem?";
  char* bom_dia = "bom dia!";
  char* boa_tarde = "boa tarde!";
  char* ate_mais = "ate mais!";

  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&x_mutex, NULL);
  pthread_cond_init (&x_cond, NULL);

  /* Cria as threads */
  pthread_create(&threads[3], NULL, B, (void*)boa_tarde);
  pthread_create(&threads[2], NULL, B, (void*)ate_mais);
  pthread_create(&threads[1], NULL, A, (void*)bom_dia);
  pthread_create(&threads[0], NULL, A, (void*)tudo_bem);

  /* Espera todas as threads completarem */
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  printf ("\nFIM\n");

  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&x_mutex);
  pthread_cond_destroy(&x_cond);
}
