# Trabalho 2 - Computação Concorrente
## Quicksort paralelo

Gabriel Martins Machado Christo - 117217732

Danilo Santos Vieira - 115103034

### Arquitetura

Foi utilizado o conceito de ThreadPool, onde temos um determinado número de threads reutilizável, podendo executar diversas tarefas diferentes.

ThreadPool - interface com a piscina de threads e fila de tarefas a serem executadas
Worker - runnable responsável por pegar e executar as tarefas da fila
QuickSort - runnable que inicializa o algoritmo quicksort e vai colocando as chamadas recursivas na fila de tarefas do thread pool


### Utilização

```
javac *.java
java QuickSort desiredArraySize desiredThreadsNumber
```

### Casos de teste




TODO:
* tabela com vetor/tempo de ordenação

ArrayBlockingQueue (implementa a interface BlockingQueue)
pior caso -> n^2 tarefas

problema: como saber o momento exato de parar as threads dos runnables
* join na chamada principal e subchamads