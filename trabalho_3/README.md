# Trabalho 3 - Computação Concorrente

Gabriel Christo 117217732

Danilo Santos Vieira 115103034

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

Todo o projeto foi desenvolvido na linguagem C. Fora a main, temos quatro threads rodando em paralelo:

- file reader: responsável por ir efetuando a leitura dos blocos de tamanho N do arquivo e ir adicionando os elementos no buffer de tamanho M

- same value three times: vai buscar sequências triplas de bloco em bloco

- larger identical values: vai buscar a maior sequência do arquivo, de bloco em bloco

- fixed sequence: vai buscar a quantidade de ocorrências da sequência 012345, de bloco em bloco


## Utilização

```
gcc main.c -o output
./output readingBlockSize bufferSize
```

## Casos de Teste

| Valores        | Tempo    |
|----------------|----------|
|  M = 1, N = 1  | 0.1635 s |
| M = 2, N = 2   | 0.1151 s |
| M = 3, N = 3   | 0.0948 s |
| M = 5, N = 5   | 0.0793 s |
| M = 6, N = 6   | 0.0656 s |
| M = 10, N = 10 | 0.0771 s |

