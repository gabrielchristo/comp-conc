# Relat�rio - Laborat�rio 3

Gabriel Martins Machado Christo - 117217732

Danilo Santos Vieira - 115103034

Foi utilizada a estrat�gia de dividir em blocos sequenciais as itera��es necess�rias (de acordo com a precis�o pedida) para a f�rmula de Leibniz


| Precis�o/Threads | 1            | 2            | 4            | Acelera��o - 2 threads | Acelera��o - 4 threads |
|------------------|--------------|--------------|--------------|------------------------|------------------------|
| 10^3             | 0.000894 s   | 0.001303 s   | 0.002143 s   | -31%                   | -58%                   |
| 10^5             | 0.030654 s   | 0.011864 s   | 0.010315 s   | 258%                   | 297%                   |
| 10^7             | 1.941752 s   | 0.992281 s   | 0.993485 s   | 195%                   | 195%                   |
| 10^9             | 212.947665 s | 112.019016 s | 117.034754 s | 190%                   | 181%                   |


Os testes foram realizados em um computador dual core. Este � um motivo pelo qual observamos que os testes com 4 threads n�o obtiveram um ganho de desempenho relevante

N�o houve diferen�a nos resultados finais. Ambos os processamentos paralelo e sequencial possuem a mesma taxa de converg�ncia, por�m no processamento concorrente � poss�vel finalizar o somat�rio mais rapidamente