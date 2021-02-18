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
| 10^2                     | 0,002911 s     | 0,002877 s | 0,003265 s |
| 10^3                     | 0,002747 s     | 0,003256 s | 0,002958 s |
| 10^4                     | 0,002854 s     | 0,002422 s | 0,003853 s |
| 10^5                     | 0,007880 s     | 0,008891 s | 0,010585 s |
| 10^6                     | 0,023836 s     | 0,028939 s | 0,032887 s |
| 10^7                     | 0,080424 s     | 0,077513 s | 0,059903 s |
| 10^8                     | 0,439504 s     | 0,285185 s | 0,171490 s |

Como visto, apenas a partir de 10^7 elementos obtivemos desempenho melhor utilizando multithreading. Acreditamos que o overhead da criação dos objetos AlgorithmRunnable possa estar impactando um melhor ganho de desempenho.

Não foi possível efetuar testes com mais do que 10^9 elementos no vetor, pois acima desse valor extrapolamos o tamanho da heap alocada pela máquina virtual do java, gerando a exception OutOfMemoryError.

Em relação ao desenvolvimento foi muito interessante poder estudar e implementar o padrão thread pool, além de definir a estrutura geral do trabalho.

