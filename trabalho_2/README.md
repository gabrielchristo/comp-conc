# Trabalho 2 - Computa��o Concorrente
## Quicksort paralelo

Gabriel Martins Machado Christo - 117217732

Danilo Santos Vieira - 115103034

### Arquitetura

O trabalho foi inteiramente desenvolvido em Java. Foi utilizado o conceito de ThreadPool, onde temos um determinado n�mero de threads reutiliz�vel, podendo executar diversas tarefas diferentes.

RunnableQueue - estrutura de dados em fila thread-safe para serem inseridas/removidas as tarefas do algoritmo.

ThreadPool - interface com a piscina de threads e fila de tarefas a serem executadas.

Worker - runnable respons�vel por pegar e executar as tarefas da fila.

AlgorithmRunnable - runnable que inicializa o algoritmo quicksort e vai colocando as chamadas recursivas na fila de tarefas do thread pool.

QuickSort - classe principal que inicializa o array com valores aleat�rios, thread pool e a chamada prim�ria do AlgorithmRunnable.


### Utiliza��o

```
javac *.java -Xlint:unchecked -g
java QuickSort tamanhoDoArray numeroDeThreads
```

*no ambiente windows basta executar o script Build.bat para compilar o projeto*

### Casos de teste




TODO:
tabela com tam vetor/tempo de ordena��o
java -XX:+PrintFlagsFinal -version | grep HeapSize
java -Xmx[]