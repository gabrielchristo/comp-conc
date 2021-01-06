/*
Arquivo com a implementacao da tecnica de integracao numerica retangular para N threads

Alunos:
  Gabriel Martins Machado Christo 117217732
  Danilo Santos Vieira            115103034
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

//Definindo o tipo dos argumentos executados pelas threads
typedef struct
{
	int idThread;
	int	numberThread;
	int numberRectangle;
	int integrationLimitA;
	int integrationLimitB;
} typeArgumentsThreads;

//Funcao matematica continua, positiva que eh usada como integrando para o calculo da integral
double integratingFunction(double x)
{
	//Aplicando uma funcao de teste qualquer por enquanto
	return x * x;
}

//Funcao para Tratar e imprimir casos de erro
void throw(char* msg)
{
	printf("%s\n", msg);
	exit(-1);
}

//Funcao para empacotar argumentos das thread
typeArgumentsThreads* packArgumentsThreads(int idThread, int numberThread, int numberRectangle, double integrationLimitA, double integrationLimitB)
{
	//Definindo retorno da funcao
	typeArgumentsThreads* arguments = malloc(sizeof(typeArgumentsThreads));

	//Setando argumentos dentro da variavel de retorno
	arguments->idThread = idThread;
	arguments->integrationLimitA = integrationLimitA;
	arguments->integrationLimitB = integrationLimitB;
	arguments->numberRectangle = numberRectangle;
	arguments->numberThread = numberThread;

	//retornando argumentos empacotados
	return arguments;
}


//Funcao para a execucao sequencial do problema
double calculateAreaRectagleSequential(double integrationLimitA, double integrationLimitB, double numberRectangles)
{
	//Definindo acumulador para o valor da area dos retangulos(aproximacao para a integral)
	double partialSumOfRectagles = 0;

	//Percorrendo os retangulos executados por essa thread
	double intervalH = (integrationLimitB - integrationLimitA) / numberRectangles;
	int indexRectangle;
	for (indexRectangle = 0; indexRectangle < numberRectangles; indexRectangle++)
	{
		//Definindo valor do ponto medio do intervalo para ser usado como a altura do retangulo
		double previousX = integrationLimitA + intervalH * indexRectangle;
		double afterX = integrationLimitA + intervalH * (indexRectangle + 1);
		double middleX = (afterX + previousX) / 2;

		//Definindo dimensoes do retangulo para fazer o calculo do valor da area
		double base = intervalH;
		double height = integratingFunction(middleX);
		double area = height * base;

		//Atualizando a variavel acumuladora
		partialSumOfRectagles += area;
	}

	//Retornando valor aproximado para a integral
	return partialSumOfRectagles;
}

//Funcoes executada pelas threads
void* calculateAreaRectagleParallel(void* arguments)
{
	//Desempacotando argumentos
	typeArgumentsThreads* args = (typeArgumentsThreads*)arguments;
	int idThread = args->idThread;
	int numberThreads = args->numberThread;
	int integrationLimitA = args->integrationLimitA;
	int integrationLimitB = args->integrationLimitB;
	int numberRectangles = args->numberRectangle;

	//Acumulador para a area dos retangulos calculados por essa thread
	double* partialSumOfRectagles = calloc(1, sizeof(double));

	//Percorrendo os retangulos executados por essa thread
	double intervalH = (double)(integrationLimitB - integrationLimitA) / numberRectangles;
	int indexRectagle;
	double partialSum = 0;
	for (indexRectagle = idThread; indexRectagle < numberRectangles; indexRectagle += numberThreads)
	{
		//Definindo valor do ponto medio do intervalo para ser usado como a altura do retangulo
		double previousX = integrationLimitA + intervalH * indexRectagle;
		double afterX = integrationLimitA + intervalH * (indexRectagle + 1);
		double middleX = (afterX + previousX) / 2;

		//Definindo dimensoes do retangulo para fazer o calculo do valor da area
		double base = intervalH;
		double height = integratingFunction(middleX);
		double area = height * base;

		//Atualizando a variavel acumuladora
		partialSum += area;
	}

	//Liberando o espaco de memoria alocado para os argumentos
	free(args);

	//Atualizando e retornando o valor acumulado
	*partialSumOfRectagles = partialSum;
	pthread_exit((void*)partialSumOfRectagles);
}

//Funcao principal
int main(int argc, char** argv)
{
	if(argc != 4)
		throw("usage: ./executable limitA limitB rectangles");
	
	//Definindo variaveis para marcar o tempo do algoritmo
	double startTime, finishTime, totalTime;

	//Definindo qual modo executar(entre sequencial e paralelo)
	int use_sequential;
	printf("0 - parallel\n1 - sequential\n");
	scanf("%d", &use_sequential);

	//Definindo numero de threads caso seja escolhido modo paralelo
	int numberThreads = 0;
	if (!use_sequential) {
		printf("Threads number: ");
		scanf("%d", &numberThreads);
	}

	//Fazendo a marcacao de tempo de inicializacao(Por enquanto valores apenas como teste)
	GET_TIME(startTime);
	double integrationLimitA = atof(argv[1]);
	double integrationLimitB = atof(argv[2]);
	double numberRectangle = atof(argv[3]);
	double approximateValueOfIntegral = 0;
	double* sumPartialArea = malloc(sizeof(double));
	GET_TIME(finishTime);
	printf("Elapsed %lf seconds for initialization\n", finishTime - startTime);
	totalTime += (finishTime - startTime);

	//Fazendo a marcacao de tempo de desenvolvimento do algoritmo no modo sequencial
	if (use_sequential) {
		GET_TIME(startTime);
		approximateValueOfIntegral = calculateAreaRectagleSequential(integrationLimitA, integrationLimitB, numberRectangle);
		GET_TIME(finishTime);
		printf("Elapsed %lf seconds for sequential processing\n\n", finishTime - startTime);
		totalTime += (finishTime - startTime);
	}
	//Fazendo a marcacao de tempo de desenvolvimento do algoritmo no modo paralelo
	else {
		GET_TIME(startTime);
		pthread_t threads[numberThreads];

		//Percorrendo as threads para executar o callculo das areas dos retangulos
		for (int indexThread = 0; indexThread < numberThreads; indexThread++) {
			//Preparando os argumentos da funcao
			typeArgumentsThreads* arguments = packArgumentsThreads(indexThread, numberThreads, numberRectangle, integrationLimitA, integrationLimitB);

			//Executando o calculo da aproximacao das areas
			if (pthread_create(&threads[indexThread], NULL, calculateAreaRectagleParallel, (void*)arguments))
				throw("error on thread creation");
		}

		//Reunindo os resultados da areas parciais obtidos pelas threads
		for (int i = 0; i < numberThreads; i++)
		{
			//Atualizando o contador para a aproximacao da integral
			if (pthread_join(threads[i], (void**)&sumPartialArea))
				throw("error on joining thread");
			approximateValueOfIntegral += *sumPartialArea;
			free(sumPartialArea);
		}

		GET_TIME(finishTime);
		printf("Elapsed %lf seconds for parallel processing\n\n", finishTime - startTime);
		totalTime += (finishTime - startTime);
	}

	//Exibindo resultado
	printf("total time elapsed %lf\n", totalTime);
	printf("approximation to the integral %.15lf\n", approximateValueOfIntegral);
	return 0;

}

