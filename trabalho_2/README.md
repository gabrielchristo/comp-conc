# Trabalho 2 - Computação Concorrente
## Quicksort paralelo

Gabriel Martins Machado Christo - 117217732

Danilo Santos Vieira - 115103034

### Arquitetura

O trabalho foi inteiramente desenvolvido em Java. Foi utilizado o conceito de ThreadPool, onde temos um determinado número de threads reutilizável, podendo executar diversas tarefas diferentes.

RunnableQueue - estrutura de dados em fila thread-safe para serem inseridas/removidas as tarefas do algoritmo.

ThreadPool - interface com a piscina de threads e fila de tarefas a serem executadas.

Worker - runnable responsável por pegar e executar as tarefas da fila.

AlgorithmRunnable - runnable que inicializa o algoritmo quicksort e vai colocando as chamadas recursivas na fila de tarefas do thread pool.

QuickSort - classe principal que inicializa o array com valores aleatórios, thread pool e a chamada primária do AlgorithmRunnable.


### Utilização

```
javac *.java -Xlint:unchecked -g
java QuickSort tamanhoDoArray numeroDeThreads
```

*no ambiente windows basta executar o script Build.bat para compilar o projeto*

### Casos de teste




TODO:
tabela com tam vetor/tempo de ordenação
java -XX:+PrintFlagsFinal -version | grep HeapSize
java -Xmx[]