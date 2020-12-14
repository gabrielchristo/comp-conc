# Relatório - Laboratório 2

Danilo Santos Vieira - 115103034

Gabriel Martins Machado Christo - 117217732

| Dimensão/Threads | 1        | 2        | Aceleração |
|------------------|----------|----------|------------|
| 500              | 4.1745   | 3.1801   | 131%       |
| 1000             | 43.5112  | 30.9728  | 140%       |
| 2000             | 560.3144 | 407.0316 | 137%       |

| Dimensão/Threads | 1        | 4        | Aceleração |
|------------------|----------|----------|------------|
| 500              | 4.1745   | 3.1387   | 133%       |
| 1000             | 43.5112  | 30.2918  | 143%       |
| 2000             | 560.3144 | 378.3855 | 148%       |

Os testes foram realizados em um computador dual-core, e como podemos notar não houve uma melhora de desempenho significativa passando de 2 para 4 threads, exceto no caso da matriz de dimensões 2000x2000, possivelmente pelo grande número de entradas
