# Trabalho 3 - Computação Concorrente

Gabriel

Danilo

## Objetivo

Processamento paralelo de arquivos, com objetivo de:

- Detectar maior sequência de valores idênticos
- Quantidade de sequências contínuas do mesmo valor de tamanho 3 
- Quantidade de sequências do padrão 012345


## Premissas

- Os arquivos processados conterão uma sequência de númeors inteiros, com valores de 0 a 5

- O arquivo deverá ser lido em blocos de tamanho N

- blocos devem entrar no buffer na mesma ordem que estão no arquivo

- bloco só pode sair do buffer após todas as threads efetuarem a busca de padrões nele

- O arquivo deverá ser guardado em memória em um buffer com M entradas

- Cada padrão de busca deve ter sua própria thread

- O primeiro valor do arquivo é um long long int e indica o número de valores no resto do arquivo

- O arquivo de entrada deve estar no formato binário


## Arquitetura

Todo o projeto foi desenvolvido na linguagem C



## Utilização

```
gcc main.c -o output
./output readingBlockSize bufferSize
```






## TODO

- erro quando n/m nao eh divisivel pelo numero de elementos no arquivo
- checar corretude
- contador de blocos?
- avaliar valores de N/M para menor tempo de execucao
