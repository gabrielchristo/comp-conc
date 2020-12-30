# Trabalho 1 - Computação Concorrente

Gabriel Martins Machado Christo - 117217732

Danilo Santos Vieira - 115103034


Problema escolhido:
Integração numérica retangular

## Descrição do problema

O valor da integral definida de uma função equivale a área limitada entre a curva de uma função positiva e o eixo x e
entre os valores das extremidades da integral definida em um plano cartesiano. Ela pode ser aproximada utilizando o 
somatório de Riemann, que basicamente pode ser interpretado como a soma das áreas de vários retângulos de igual base 
que são inscritos dentro da área abaixo da curva e limitada entre os valores dos limites de integração.

Portanto quanto mais retângulos são utilizados mais ajustáveis eles se tornam para tentar inscrever a área abaixo
da curva(integral), de modo que quanto mais retângulos inserimos mais próximos ficamos do valor real da área abaixo
da curva.

A ideia é implementar uma forma de aproximar o valor da integral de algumas funções utilizando a técnica de
integração numérica retangular, onde vamos aproximar o valor da integral(área abaixo da curva) com um número de N 
retângulos somando a área de cada um deles.

### Projeto da Solução

Ao fazer todas as inicializações e verificações de funções apropriadas, escolhemos o número de retângulos (N) para
aproximar a integral dimensionado os retângulos de modo a se encaixarem dentro dos limites de integração e teremos
que determinar a área de  cada retângulo. Para determinar a área dos retângulos os distribuiremos para as threads de 
modo que cada thread vai calcular a área do retângulo que tiver um índice múltiplo do seu índice. No fim somaremos o
valor de cada retângulo aproximante e teremos a aproximação para a integral




## Casos de teste



## Desempenho
