<<<<<<< HEAD
/*
Arquivo com a implementaÁ„o da tÈcnica de integraÁ„o numÈrica retangular (ou trapezoidal) para N threads

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

//FunÁ„o matem·tica continua, positiva (e com segunda derivada continua para caso de integraÁ„o numÈrica trapezoidal)
//que È usada como integrando para o c·lculo da integral
double integratingFunction(double x)
{
	//Aplicando uma funÁ„o de teste qualquer por enquanto
	return x * x;
}

//FunÁ„o para Tratar e imprimir casos de erro
void throw(char* msg)
{
	printf("%s\n", msg);
	exit(-1);
}

//FunÁ„o para empacotar argumentos das thread
typeArgumentsThreads* packArgumentsThreads(int idThread, int numberThread, int numberRectangle, double integrationLimitA, double integrationLimitB)
{
	//Definindo retorno da funÁ„o
	typeArgumentsThreads* arguments = malloc(sizeof(typeArgumentsThreads));

	//Setando argumentos dentro da vari·vel de retorno
	arguments->idThread = idThread;
	arguments->integrationLimitA = integrationLimitA;
	arguments->integrationLimitB = integrationLimitB;
	arguments->numberRectangle = numberRectangle;
	arguments->numberThread = numberThread;

	//retornando argumentos empacotados
	return arguments;
}


//FunÁ„o para a execuÁ„o sequencial do problema
double calculateAreaRectagleSequential(double integrationLimitA, double integrationLimitB, double numberRectangles)
{
	//Definindo acumulador para o valor da ·rea dos ret‚ngulos(aproximaÁ„o para a integral)
	double partialSumOfRectagles = 0;

	//Percorrendo os ret‚ngulos executados por essa thread
	double intervalH = (integrationLimitB - integrationLimitA) / numberRectangles;
	int indexRectangle;
	for (indexRectangle = 0; indexRectangle < numberRectangles; indexRectangle++)
	{
		//Definindo valor do ponto mÈdio do intervalo para ser usado como a altura do ret‚ngulo
		double previousX = integrationLimitA + intervalH * indexRectangle;
		double afterX = integrationLimitA + intervalH * (indexRectangle + 1);
		double middleX = (afterX + previousX) / 2;

		//Definindo dimensıes do ret‚ngulo para fazer o c·lculo do valor da ·rea
		double base = intervalH;
		double height = integratingFunction(middleX);
		double area = height * base;

		//Atualizando a vari·vel acumuladora
		partialSumOfRectagles += area;
	}

	//Retornando valor aproximado para a integral
	return partialSumOfRectagles;
}

//FunÁıes executada pelas threads
void* calculateAreaRectagleParallel(void* arguments)
{
	//Desempacotando argumentos
	typeArgumentsThreads* args = (typeArgumentsThreads*)arguments;
	int idThread = args->idThread;
	int numberThreads = args->numberThread;
	int integrationLimitA = args->integrationLimitA;
	int integrationLimitB = args->integrationLimitB;
	int numberRectangles = args->numberRectangle;

	//Acumulador para a ·rea dos ret‚ngulos calculados por essa thread
	double* partialSumOfRectagles = calloc(1, sizeof(double));

	//Percorrendo os ret‚ngulos executados por essa thread
	double intervalH = (double)(integrationLimitB - integrationLimitA) / numberRectangles;
	int indexRectagle;
	double partialSum = 0;
	for (indexRectagle = idThread; indexRectagle < numberRectangles; indexRectagle += numberThreads)
	{
		//Definindo valor do ponto mÈdio do intervalo para ser usado como a altura do ret‚ngulo
		double previousX = integrationLimitA + intervalH * indexRectagle;
		double afterX = integrationLimitA + intervalH * (indexRectagle + 1);
		double middleX = (afterX + previousX) / 2;

		//Definindo dimensıes do ret‚ngulo para fazer o c·lculo do valor da ·rea
		double base = intervalH;
		double height = integratingFunction(middleX);
		double area = height * base;

		//Atualizando a vari·vel acumuladora
		partialSum += area;
	}

	//Liberando o espaÁo de memÛria alocado para os argumentos
	free(args);

	//Atualizando e retornando o valor acumulado
	*partialSumOfRectagles = partialSum;
	pthread_exit((void*)partialSumOfRectagles);
}

//FunÁ„o principal
int main(int argc, char** argv)
{
	//Definindo variaveis para marcar o tempo do algoritmo
	double startTime, finishTime, totalTime;

	//Definindo qual modo executar(entre sequencial e paralelo)
	int use_sequential;
	printf("0 - parallel\n1 - sequential\n");
	scanf("%d", &use_sequential);

	//Definindo n˙mero de threads caso seja escolhido modo paralelo
	int numberThreads = 0;
	if (!use_sequential) {
		printf("Threads number: ");
		scanf("%d", &numberThreads);
	}

	//Fazendo a marcaÁ„o de tempo de inicializaÁ„o(Por enquanto valores apenas como teste)
	GET_TIME(startTime);
	double integrationLimitA = 0;
	double integrationLimitB = 1;
	double numberRectangle = 100;
	double approximateValueOfIntegral = 0;
	double* sumPartialArea = malloc(sizeof(double));
	GET_TIME(finishTime);
	printf("Elapsed %lf seconds for initialization\n", finishTime - startTime);
	totalTime += (finishTime - startTime);

	//Fazendo a marcaÁ„o de tempo de desenvolvimento do algoritmo no modo sequencial
	if (use_sequential) {
		GET_TIME(startTime);
		approximateValueOfIntegral = calculateAreaRectagleSequential(integrationLimitA, integrationLimitB, numberRectangle);
		GET_TIME(finishTime);
		printf("Elapsed %lf seconds for sequential processing\n", finishTime - startTime);
		totalTime += (finishTime - startTime);
	}
	//Fazendo a marcaÁ„o de tempo de desenvolvimento do algoritmo no modo paralelo
	else {
		GET_TIME(startTime);
		pthread_t threads[numberThreads];

		//Percorrendo as threads para executar o c·lculo das ·reas dos ret‚ngulos
		for (int indexThread = 0; indexThread < numberThreads; indexThread++) {
			//Preparando os argumentos da funÁ„o
			typeArgumentsThreads* arguments = packArgumentsThreads(indexThread, numberThreads, numberRectangle, integrationLimitA, integrationLimitB);

			//Executando o c·lculo da aproximaÁ„o das ·reas
			if (pthread_create(&threads[indexThread], NULL, calculateAreaRectagleParallel, (void*)arguments))
				throw("error on thread creation");
		}

		//Reunindo os resultados da ·reas parciais obtidos pelas threads
		for (int i = 0; i < numberThreads; i++)
		{
			//Atualizando o contador para a aproximaÁ„o da integral
			if (pthread_join(threads[i], (void**)&sumPartialArea))
				throw("error on joining thread");
			approximateValueOfIntegral += *sumPartialArea;
			free(sumPartialArea);
		}

		GET_TIME(finishTime);
		printf("Elapsed %lf seconds for parallel processing\n", finishTime - startTime);
		totalTime += (finishTime - startTime);
	}

	//Exibindo resultado
	printf("approximation to the integral %lf\n", approximateValueOfIntegral);
	return 0;

}

=======
/*
Arquivo com a implementa√ß√£o da t√©cnica de integra√ß√£o num√©rica retangular (ou trapezoidal) para N threads

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

//Fun√ß√£o matem√°tica continua, positiva (e com segunda derivada continua para caso de integra√ß√£o num√©rica trapezoidal)
//que √© usada como integrando para o c√°lculo da integral
double integratingFunction(double x)
{
	//Aplicando uma fun√ß√£o de teste qualquer por enquanto
	return x * x;
}

//Fun√ß√£o para Tratar e imprimir casos de erro
void throw(char* msg)
{
	printf("%s\n", msg);
	exit(-1);
}

//Fun√ß√£o para empacotar argumentos das thread
typeArgumentsThreads* packArgumentsThreads(int idThread, int numberThread, int numberRectangle, double integrationLimitA, double integrationLimitB)
{
	//Definindo retorno da fun√ß√£o
	typeArgumentsThreads* arguments = malloc(sizeof(typeArgumentsThreads));

	//Setando argumentos dentro da vari√°vel de retorno
	arguments->idThread = idThread;
	arguments->integrationLimitA = integrationLimitA;
	arguments->integrationLimitB = integrationLimitB;
	arguments->numberRectangle = numberRectangle;
	arguments->numberThread = numberThread;

	//retornando argumentos empacotados
	return arguments;
}


//Fun√ß√£o para a execu√ß√£o sequencial do problema
double calculateAreaRectagleSequential(double integrationLimitA, double integrationLimitB, double numberRectangles)
{
	//Definindo acumulador para o valor da √°rea dos ret√¢ngulos(aproxima√ß√£o para a integral)
	double partialSumOfRectagles = 0;

	//Percorrendo os ret√¢ngulos executados por essa thread
	double intervalH = (integrationLimitB - integrationLimitA) / numberRectangles;
	int indexRectangle;
	for (indexRectangle = 0; indexRectangle < numberRectangles; indexRectangle++)
	{
		//Definindo valor do ponto m√©dio do intervalo para ser usado como a altura do ret√¢ngulo
		double previousX = integrationLimitA + intervalH * indexRectangle;
		double afterX = integrationLimitA + intervalH * (indexRectangle + 1);
		double middleX = (afterX + previousX) / 2;

		//Definindo dimens√µes do ret√¢ngulo para fazer o c√°lculo do valor da √°rea
		double base = intervalH;
		double height = integratingFunction(middleX);
		double area = height * base;

		//Atualizando a vari√°vel acumuladora
		partialSumOfRectagles += area;
	}

	//Retornando valor aproximado para a integral
	return partialSumOfRectagles;
}

//Fun√ß√µes executada pelas threads
void* calculateAreaRectagleParallel(void* arguments)
{
	//Desempacotando argumentos
	typeArgumentsThreads* args = (typeArgumentsThreads*)arguments;
	int idThread = args->idThread;
	int numberThreads = args->numberThread;
	int integrationLimitA = args->integrationLimitA;
	int integrationLimitB = args->integrationLimitB;
	int numberRectangles = args->numberRectangle;

	//Acumulador para a √°rea dos ret√¢ngulos calculados por essa thread
	double* partialSumOfRectagles = calloc(1, sizeof(double));

	//Percorrendo os ret√¢ngulos executados por essa thread
	double intervalH = (double)(integrationLimitB - integrationLimitA) / numberRectangles;
	int indexRectagle;
	double partialSum = 0;
	for (indexRectagle = idThread; indexRectagle < numberRectangles; indexRectagle += numberThreads)
	{
		//Definindo valor do ponto m√©dio do intervalo para ser usado como a altura do ret√¢ngulo
		double previousX = integrationLimitA + intervalH * indexRectagle;
		double afterX = integrationLimitA + intervalH * (indexRectagle + 1);
		double middleX = (afterX + previousX) / 2;

		//Definindo dimens√µes do ret√¢ngulo para fazer o c√°lculo do valor da √°rea
		double base = intervalH;
		double height = integratingFunction(middleX);
		double area = height * base;

		//Atualizando a vari√°vel acumuladora
		partialSum += area;
	}

	//Liberando o espa√ßo de mem√≥ria alocado para os argumentos
	free(args);

	//Atualizando e retornando o valor acumulado
	*partialSumOfRectagles = partialSum;
	pthread_exit((void*)partialSumOfRectagles);
}

//Fun√ß√£o principal
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

	//Definindo n√∫mero de threads caso seja escolhido modo paralelo
	int numberThreads = 0;
	if (!use_sequential) {
		printf("Threads number: ");
		scanf("%d", &numberThreads);
	}

	//Fazendo a marca√ß√£o de tempo de inicializa√ß√£o(Por enquanto valores apenas como teste)
	GET_TIME(startTime);
	double integrationLimitA = atof(argv[1]);
	double integrationLimitB = atof(argv[2]);
	double numberRectangle = atof(argv[3]);
	double approximateValueOfIntegral = 0;
	double* sumPartialArea = malloc(sizeof(double));
	GET_TIME(finishTime);
	printf("Elapsed %lf seconds for initialization\n", finishTime - startTime);
	totalTime += (finishTime - startTime);

	//Fazendo a marca√ß√£o de tempo de desenvolvimento do algoritmo no modo sequencial
	if (use_sequential) {
		GET_TIME(startTime);
		approximateValueOfIntegral = calculateAreaRectagleSequential(integrationLimitA, integrationLimitB, numberRectangle);
		GET_TIME(finishTime);
		printf("Elapsed %lf seconds for sequential processing\n", finishTime - startTime);
		totalTime += (finishTime - startTime);
	}
	//Fazendo a marca√ß√£o de tempo de desenvolvimento do algoritmo no modo paralelo
	else {
		GET_TIME(startTime);
		pthread_t threads[numberThreads];

		//Percorrendo as threads para executar o c√°lculo das √°reas dos ret√¢ngulos
		for (int indexThread = 0; indexThread < numberThreads; indexThread++) {
			//Preparando os argumentos da fun√ß√£o
			typeArgumentsThreads* arguments = packArgumentsThreads(indexThread, numberThreads, numberRectangle, integrationLimitA, integrationLimitB);

			//Executando o c√°lculo da aproxima√ß√£o das √°reas
			if (pthread_create(&threads[indexThread], NULL, calculateAreaRectagleParallel, (void*)arguments))
				throw("error on thread creation");
		}

		//Reunindo os resultados da √°reas parciais obtidos pelas threads
		for (int i = 0; i < numberThreads; i++)
		{
			//Atualizando o contador para a aproxima√ß√£o da integral
			if (pthread_join(threads[i], (void**)&sumPartialArea))
				throw("error on joining thread");
			approximateValueOfIntegral += *sumPartialArea;
			free(sumPartialArea);
		}

		GET_TIME(finishTime);
		printf("Elapsed %lf seconds for parallel processing\n", finishTime - startTime);
		totalTime += (finishTime - startTime);
	}

	//Exibindo resultado
	printf("approximation to the integral %.15lf\n", approximateValueOfIntegral);
	return 0;

}

>>>>>>> c54d37536f50b5f0c82c5e5a59d6702ab3e6321f
