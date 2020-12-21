# Relatório - Laboratório 3

Gabriel Martins Machado Christo - 117217732

Danilo Santos Vieira - 115103034

Foi utilizada a estratégia de dividir em blocos sequenciais as iterações necessárias (de acordo com a precisão pedida) para a fórmula de Leibniz


| Precisão/Threads | 1            | 2            | 4            | Aceleração - 2 threads | Aceleração - 4 threads |
|------------------|--------------|--------------|--------------|------------------------|------------------------|
| 10^3             | 0.000894 s   | 0.001303 s   | 0.002143 s   | -31%                   | -58%                   |
| 10^5             | 0.030654 s   | 0.011864 s   | 0.010315 s   | 258%                   | 297%                   |
| 10^7             | 1.941752 s   | 0.992281 s   | 0.993485 s   | 195%                   | 195%                   |
| 10^9             | 212.947665 s | 112.019016 s | 117.034754 s | 190%                   | 181%                   |


Os testes foram realizados em um computador dual core. Este é um motivo pelo qual observamos que os testes com 4 threads não obtiveram um ganho de desempenho relevante

Não houve diferença nos resultados finais. Ambos os processamentos paralelo e sequencial possuem a mesma taxa de convergência, porém no processamento concorrente é possível finalizar o somatório mais rapidamente