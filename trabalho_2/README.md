# Trabalho 2 - Computação Concorrente
## Quicksort paralelo

Gabriel Martins Machado Christo - 117217732

Danilo Santos Vieira - 115103034

### Arquitetura

Foi utilizado o conceito de ThreadPool, onde temos um determinado número de threads reutilizável, podendo executar diversas tarefas diferentes.


### Utilização

```
javac *.java
java QuickSort desiredArraySize desiredThreadsNumber
```

### Casos de teste




TODO:
* tabela com vetor/tempo de ordenação
pool de threads ?
ArrayBlockingQueue (implementa a interface BlockingQueue)
pior caso -> n^2 tarefas

problema: como saber o momento exato de parar as threads dos runnables