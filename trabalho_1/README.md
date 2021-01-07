# Trabalho 1 - Computação Concorrente

Gabriel Martins Machado Christo - 117217732

Danilo Santos Vieira - 115103034


Problema escolhido: Integração numérica retangular


### Descrição do problema

O valor da integral definida de uma função equivale a área limitada entre a curva de uma função positiva e o eixo x entre os valores das extremidades da integral definida em um plano cartesiano. Ela pode ser aproximada utilizando o somatório de Riemann, que pode ser interpretado como a soma das áreas de vários retângulos de igual base que são inscritos dentro da área abaixo da curva e limitada entre os valores dos limites de integração

Portanto quanto mais retângulos são utilizados mais ajustáveis eles se tornam para tentar inscrever a área abaixo da curva (integral), de modo que quanto mais retângulos inserimos mais próximos ficamos do valor real da área abaixo da curva

A ideia é implementar uma forma de aproximar o valor da integral de algumas funções utilizando a técnica de integração numérica retangular, onde vamos aproximar o valor da integral(área abaixo da curva) com um número N retângulos somando a área de cada um deles


### Projeto da Solução

Ao fazer todas as inicializações e verificações de funções apropriadas, escolhemos o número de retângulos N dimensionando os mesmos de modo a se encaixarem dentro dos limites de integração e da altura da curva da função, além de possuírem base de igual tamanho. Para determinar a área dos N retângulos os distribuiremos para as M threads de modo que cada thread vai calcular a área de N/M retângulos, sendo o (possível) resto da divisão distribuído igualmente entre as threads até que seja finalizado o somatório. No fim somaremos o valor da área de cada retângulo e teremos a aproximação para a integral


### Casos de teste e Desempenho

Após avaliada a corretude do programa, realizamos os seguintes testes (processador quad-core) para f(x) = x^2 no intervalo [0, 10.000]


| Retângulos/Threads | 1 (sequencial) | 2           | 4          | 8          | Aceleração com 2 threads | Aceleração com 4 threads | Aceleração com 8 threads |
|:------------------:|----------------|-------------|------------|------------|--------------------------|--------------------------|--------------------------|
| 10^2               | 0.000011 s     | 0.000429 s  | 0.000966 s | 0.002035 s | -97%                     | -98%                     | -99%                     |
| 10^3               | 0.000055 s     | 0.000845 s  | 0.000908 s | 0.002292 s | -93%                     | -94%                     | -97%                     |
| 10^4               | 0.000224 s     | 0.000747 s  | 0.001014 s | 0.004030 s | -70%                     | -78%                     | -94%                     |
| 10^5               | 0.002156 s     | 0.002103 s  | 0.001522 s | 0.002389 s | 102%                     | 141%                     | -10%                     |
| 10^6               | 0.020711 s     | 0.015241 s  | 0.009247 s | 0.006681 s | 131%                     | 216%                     | 299%                     |
| 10^7               | 0.221659 s     | 0.114601 s  | 0.059659 s | 0.041993 s | 192%                     | 369%                     | 524%                     |
| 10^8               | 2.080984 s     | 1.076766 s  | 0.542039 s | 0.340311 s | 194%                     | 385%                     | 611%                     |
| 10^9               | 21.036839 s    | 10.751905 s | 5.979838 s | 3.740672 s | 195%                     | 352%                     | 562%                     |
| 10^10              | 29.531917 s    | 15.126627 s | 8.254159 s | 5.350048 s | 195%                     | 358%                     | 552%                     |

Como observado na tabela, é notável o ganho de desempenho da execução paralela em virtude da execução sequencial quando exigida uma alta carga de processamento (neste caso a partir do uso de 10^5 ou mais retângulos)

Também é interessante notar que o ganho de desempenho é quase proporcional ao número de threads utilizado, pelo menos até o uso de 8 threads, pois acima disso se tornam frequentes as trocas de contexto para execução dos fluxos, podendo obter ganhos de desempenho até mesmo menores do que com 8 ou menos threads
