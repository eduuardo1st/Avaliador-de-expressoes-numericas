# Avaliador de Expressões Numéricas em C

Este projeto implementa um avaliador de expressões numéricas em linguagem C. Ele é capaz de converter expressões da notação infixa para pós-fixa (Notação Polonesa Reversa - RPN) e calcular o valor numérico dessas expressões. O projeto faz uso extensivo da estrutura de dados Pilha para gerenciar operadores e operandos durante os processos de conversão e avaliação.

## Funcionalidades

*   **Conversão Infixa para Pós-fixa**: Transforma expressões matemáticas da forma usual (infixa) para a notação pós-fixa.
*   **Conversão Pós-fixa para Infixa**: Reconstrói a expressão infixa a partir de sua forma pós-fixa, adicionando parênteses quando necessário para manter a precedência correta.
*   **Avaliação de Expressões Pós-fixas**: Calcula o valor numérico de expressões em notação pós-fixa.
*   **Avaliação de Expressões Infixas**: Calcula o valor numérico de expressões em notação infixa, utilizando a conversão interna para pós-fixa.
*   **Suporte a Operadores Básicos**: Adição (`+`), Subtração (`-`), Multiplicação (`*`), Divisão (`/`), Módulo (`%`), Potenciação (`^`).
*   **Suporte a Funções Matemáticas**: Raiz quadrada (`raiz`), Seno (`sen`), Cosseno (`cos`), Tangente (`tg`), Logaritmo na base 10 (`log`).

## Estrutura do Projeto

O projeto é composto pelos seguintes arquivos:

*   `expressao.h`: Contém as definições da estrutura `Expressao` e os protótipos das funções de conversão e avaliação.
*   `expressao.c`: Implementa as funções declaradas em `expressao.h`, incluindo as lógicas para manipulação de pilhas, conversão de notação e avaliação de expressões.
*   `main.c`: Contém a função principal (`main`) que demonstra o uso das funcionalidades do avaliador através de uma série de testes com diferentes expressões.

## Como Compilar

Para compilar o projeto, você precisará de um compilador C (como o GCC). Navegue até o diretório raiz do projeto no seu terminal e execute o seguinte comando:

```bash
gcc main.c expressao.c -o avaliador -lm
```

*   `gcc`: O compilador C.
*   `main.c expressao.c`: Os arquivos fonte a serem compilados.
*   `-o avaliador`: Define o nome do executável de saída como `avaliador`.
*   `-lm`: Linka a biblioteca matemática (necessária para funções como `sqrt`, `sin`, `cos`, `tan`, `log10`, `pow`, `fmod`).

## Como Executar

Após a compilação bem-sucedida, você pode executar o programa a partir do terminal:

```bash
./avaliador
```

O programa irá exibir os resultados dos testes pré-definidos no arquivo `main.c`, mostrando as expressões infixas, suas conversões para pós-fixa, a reconstrução para infixa e os valores calculados.

## Exemplo de Uso (do `main.c`)

```c
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "expressao.h"

int main() {
    Expressao exp;
    printf("=== Avaliador de Expressoes ===\n\n");

    // Teste 1
    strcpy(exp.inFixa, "(3 + 4) * 5");
    strcpy(exp.posFixa, getFormaPosFixa(exp.inFixa));
    printf("Infixa: %s\n", exp.inFixa);
    printf("Posfixa: %s\n", exp.posFixa);
    printf("Infixa convertida: %s\n", getFormaInFixa(exp.posFixa));
    printf("Valor na posfixa: %.5f\n", getValorPosFixa(exp.posFixa));
    printf("Valor na infixa: %.5f\n", getValorInFixa(exp.inFixa));
    printf("------------------------------------------------------------\n");

    // Outros testes...

    printf("=== Fim dos testes ===\n");
    return 0;
}
```

## Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou enviar pull requests para melhorias, correções de bugs ou novas funcionalidades.

## Licença

Este projeto está licenciado sob a [Licença MIT](https://opensource.org/licenses/MIT).

