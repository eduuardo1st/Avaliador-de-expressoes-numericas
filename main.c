#include <stdio.h>
#include <string.h>
#include <math.h>

#include "expressao.h"

int main() {
    Expressao exp;

    printf("=== Avaliador de Expressões ===\n\n");

    // Teste 1
    strcpy(exp.inFixa, "(3 + 4) * 5");
    strcpy(exp.posFixa, getFormaPosFixa(exp.inFixa));
    printf("Infixa: %s\n", exp.inFixa);
    printf("Posfixa: %s\n", exp.posFixa);
    printf("Infixa convertida: %s\n", getFormaInFixa(exp.posFixa));
    printf("Valor na posfixa: %.5f\n", getValorPosFixa(exp.posFixa));
    printf("Valor na infixa: %.5f\n", getValorInFixa(exp.inFixa));
    printf("------------------------------------------------------------\n");

    // Teste 2
    strcpy(exp.inFixa, "7 * 2 + 4");
    strcpy(exp.posFixa, getFormaPosFixa(exp.inFixa));
    printf("Infixa: %s\n", exp.inFixa);
    printf("Posfixa: %s\n", exp.posFixa);
    printf("Infixa convertida: %s\n", getFormaInFixa(exp.posFixa));
    printf("Valor na posfixa: %.5f\n", getValorPosFixa(exp.posFixa));
    printf("Valor na infixa: %.5f\n", getValorInFixa(exp.inFixa));
    printf("------------------------------------------------------------\n");

    // Teste 3
    strcpy(exp.inFixa, "8 + (5 * (2 + 4))");
    strcpy(exp.posFixa, getFormaPosFixa(exp.inFixa));
    printf("Infixa: %s\n", exp.inFixa);
    printf("Posfixa: %s\n", exp.posFixa);
    printf("Infixa convertida: %s\n", getFormaInFixa(exp.posFixa));
    printf("Valor na posfixa: %.5f\n", getValorPosFixa(exp.posFixa));
    printf("Valor na infixa: %.5f\n", getValorInFixa(exp.inFixa));
    printf("------------------------------------------------------------\n");

    // Teste 4
    strcpy(exp.inFixa, "(6 / 2 + 3) * 4");
    strcpy(exp.posFixa, getFormaPosFixa(exp.inFixa));
    printf("Infixa: %s\n", exp.inFixa);
    printf("Posfixa: %s\n", exp.posFixa);
    printf("Infixa convertida: %s\n", getFormaInFixa(exp.posFixa));
    printf("Valor na posfixa: %.5f\n", getValorPosFixa(exp.posFixa));
    printf("Valor na infixa: %.5f\n", getValorInFixa(exp.inFixa));
    printf("------------------------------------------------------------\n");

    // Teste 5
    strcpy(exp.inFixa, "9 + (5 * (2 + 8 * 4))");
    strcpy(exp.posFixa, getFormaPosFixa(exp.inFixa));
    printf("Infixa: %s\n", exp.inFixa);
    printf("Posfixa: %s\n", exp.posFixa);
    printf("Infixa convertida: %s\n", getFormaInFixa(exp.posFixa));
    printf("Valor na posfixa: %.5f\n", getValorPosFixa(exp.posFixa));
    printf("Valor na infixa: %.5f\n", getValorInFixa(exp.inFixa));
    printf("------------------------------------------------------------\n");

    // Teste 6
    strcpy(exp.inFixa, "log(2 + 3) / 5");
    strcpy(exp.posFixa, getFormaPosFixa(exp.inFixa));
    printf("Infixa: %s\n", exp.inFixa);
    printf("Posfixa: %s\n", exp.posFixa);
    printf("Infixa convertida: %s\n", getFormaInFixa(exp.posFixa));
    printf("Valor na posfixa: %.5f\n", getValorPosFixa(exp.posFixa));
    printf("Valor na infixa: %.5f\n", getValorInFixa(exp.inFixa));
    printf("------------------------------------------------------------\n");

    // Teste 7
    strcpy(exp.inFixa, "(log(10))^3 + 2");
    strcpy(exp.posFixa, getFormaPosFixa(exp.inFixa));
    printf("Infixa: %s\n", exp.inFixa);
    printf("Posfixa: %s\n", exp.posFixa);
    printf("Infixa convertida: %s\n", getFormaInFixa(exp.posFixa));
    printf("Valor na posfixa: %.5f\n", getValorPosFixa(exp.posFixa));
    printf("Valor na infixa: %.5f\n", getValorInFixa(exp.inFixa));
    printf("------------------------------------------------------------\n");

    // Teste 8
    strcpy(exp.inFixa, "(45 + 60) * cos(30)");
    strcpy(exp.posFixa, getFormaPosFixa(exp.inFixa));
    printf("Infixa: %s\n", exp.inFixa);
    printf("Posfixa: %s\n", exp.posFixa);
    printf("Infixa convertida: %s\n", getFormaInFixa(exp.posFixa));
    printf("Valor na posfixa: %.5f\n", getValorPosFixa(exp.posFixa));
    printf("Valor na infixa: %.5f\n", getValorInFixa(exp.inFixa));
    printf("------------------------------------------------------------\n");

    // Teste 9
    strcpy(exp.inFixa, "sen(45)^2 + 0.5");
    strcpy(exp.posFixa, getFormaPosFixa(exp.inFixa));
    printf("Infixa: %s\n", exp.inFixa);
    printf("Posfixa: %s\n", exp.posFixa);
    printf("Infixa convertida: %s\n", getFormaInFixa(exp.posFixa));
    printf("Valor na posfixa: %.5f\n", getValorPosFixa(exp.posFixa));
    printf("Valor na infixa: %.5f\n", getValorInFixa(exp.inFixa));
    printf("------------------------------------------------------------\n");

    printf("=== Fim dos testes ===\n");

    return 0;
}
