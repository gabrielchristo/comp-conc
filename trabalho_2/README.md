# Trabalho 2 - Computa��o Concorrente
## Quicksort paralelo

Gabriel Martins Machado Christo - 117217732

Danilo Santos Vieira - 115103034

### Arquitetura

Foi utilizado o conceito de ThreadPool, onde temos um determinado n�mero de threads reutiliz�vel, podendo executar diversas tarefas diferentes.


### Utiliza��o

```
javac *.java
java QuickSort desiredArraySize desiredThreadsNumber
```

### Casos de teste




TODO:
* tabela com vetor/tempo de ordena��o
pool de threads ?
ArrayBlockingQueue (implementa a interface BlockingQueue)
pior caso -> n^2 tarefas

problema: como saber o momento exato de parar as threads dos runnables