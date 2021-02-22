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

| Tamanho do Vetor/Threads | 1 (sequencial) | 2          | 4          |
|:------------------------:|----------------|------------|------------|
| 10^2                     | 0,002932 s     | 0,004415 s | 0,008783 s |
| 10^3                     | 0,005753 s     | 0,010748 s | 0,010342 s |
| 10^4                     | 0,010831 s     | 0,010210 s | 0,007859 s |
| 10^5                     | 0,709994 s     | 0,509366 s | 0,257365 s |
| 10^6                     | 17,80181 s     | 8,802109 s | 4,804662 s |
| 10^7                     | 1676,209 s     | 725,3019 s | 493,0026 s |

Como visto, apenas a partir de 10^5 elementos obtivemos desempenho melhor utilizando multithreading. Acreditamos que o overhead da criação dos objetos AlgorithmRunnable possa estar impactando um melhor ganho de desempenho.

Não foi possível efetuar testes com mais do que 10^9 elementos no vetor, pois acima desse valor extrapolamos o tamanho da heap alocada pela máquina virtual do java, gerando a exception OutOfMemoryError.

No caso de 10^8 o tempo de execução aumentava consideravelmente, por essa razão não fizemos as medições para este caso.

Em relação ao desenvolvimento foi muito interessante poder estudar e implementar o padrão thread pool, além de definir a estrutura geral do trabalho.
