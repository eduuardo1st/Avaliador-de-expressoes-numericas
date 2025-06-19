#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "expressao.h"

#define PI 3.14159265358979323846

// ========================
// Funções ctype personalizadas
// ========================
int isSpaceCustom(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

int isDigitCustom(char c) {
    return c >= '0' && c <= '9';
}

// ========================
// Pilhas
// ========================
typedef struct {
    char dados[512][64];
    int topo;
} PilhaStr;

typedef struct {
    float dados[512];
    int topo;
} PilhaFloat;

void initPilhaStr(PilhaStr *p) { p->topo = -1; }
void pushStr(PilhaStr *p, const char *s) { strcpy(p->dados[++(p->topo)], s); }
char* popStr(PilhaStr *p) { return (p->topo == -1) ? "" : p->dados[(p->topo)--]; }
char* topoStr(PilhaStr *p) { return (p->topo == -1) ? "" : p->dados[p->topo]; }

void initPilhaFloat(PilhaFloat *p) { p->topo = -1; }
void pushFloat(PilhaFloat *p, float f) { p->dados[++(p->topo)] = f; }
float popFloat(PilhaFloat *p) { return (p->topo == -1) ? 0 : p->dados[(p->topo)--]; }

// ========================
// Funções Auxiliares
// ========================
int ehFuncao(const char *str, char *nomeFunc) {
    const char *funcoes[] = {"raiz", "sen", "cos", "tg", "log"};
    for (int i = 0; i < 5; i++) {
        if (strncmp(str, funcoes[i], strlen(funcoes[i])) == 0) {
            strcpy(nomeFunc, funcoes[i]);
            return (int)strlen(funcoes[i]);
        }
    }
    return 0;
}

int obterPrecedencia(const char *op) {
    if (!strcmp(op, "+") || !strcmp(op, "-")) return 1;
    if (!strcmp(op, "*") || !strcmp(op, "/") || !strcmp(op, "%")) return 2;
    if (!strcmp(op, "^")) return 3;
    if (ehFuncao(op, (char[8]){})) return 4; // Funções têm alta precedência
    return 0; // Para parênteses
}

int ehOperador(const char *op) {
    return !strcmp(op, "+") || !strcmp(op, "-") ||
           !strcmp(op, "*") || !strcmp(op, "/") ||
           !strcmp(op, "%") || !strcmp(op, "^");
}

// ========================
// Infixa -> Posfixa (Algoritmo Shunting-yard)
// ========================
char *getFormaPosFixa(char *Str) {
    static char saida[512];
    saida[0] = '\0';
    PilhaStr pilha;
    initPilhaStr(&pilha);
    int i = 0;
    char token[64];
    char nomeFunc[8];

    while (Str[i]) {
        if (isSpaceCustom(Str[i])) {
            i++;
            continue;
        }

        if (isDigitCustom(Str[i]) || Str[i] == '.') {
            int j = 0;
            while (isDigitCustom(Str[i]) || Str[i] == '.') {
                token[j++] = Str[i++];
            }
            token[j] = '\0';
            strcat(saida, token);
            strcat(saida, " ");
        } else if (ehFuncao(&Str[i], nomeFunc)) {
            pushStr(&pilha, nomeFunc);
            i += strlen(nomeFunc);
        } else if (Str[i] == '(') {
            pushStr(&pilha, "(");
            i++;
        } else if (Str[i] == ')') {
            while (pilha.topo != -1 && strcmp(topoStr(&pilha), "(") != 0) {
                strcat(saida, popStr(&pilha));
                strcat(saida, " ");
            }
            popStr(&pilha); // Remove '(' da pilha
            
            if (pilha.topo != -1 && ehFuncao(topoStr(&pilha), (char[8]){})) {
                strcat(saida, popStr(&pilha));
                strcat(saida, " ");
            }
            i++;
        } else { // É um operador
            char op[2] = {Str[i], '\0'};
            while (pilha.topo != -1 && strcmp(topoStr(&pilha), "(") != 0 &&
                   obterPrecedencia(topoStr(&pilha)) >= obterPrecedencia(op)) {
                strcat(saida, popStr(&pilha));
                strcat(saida, " ");
            }
            pushStr(&pilha, op);
            i++;
        }
    }

    while (pilha.topo != -1) {
        strcat(saida, popStr(&pilha));
        strcat(saida, " ");
    }

    if (strlen(saida) > 0 && saida[strlen(saida) - 1] == ' ') {
        saida[strlen(saida) - 1] = '\0';
    }

    return saida;
}


// ========================
// Posfixa -> Infixa
// ========================
char *getFormaInFixa(char *Str) {
    static char saida[512];
    saida[0] = '\0';

    typedef struct {
        char expressao[512];
        int precedencia;
    } ItemPilha;

    ItemPilha pilha[512];
    int topo = -1;

    char buffer[512];
    strcpy(buffer, Str);
    char *token = strtok(buffer, " ");

    while (token) {
        if (isDigitCustom(token[0]) || (token[0] == '.' ) || (strlen(token) > 1 && token[0] == '-')) {
            topo++;
            strcpy(pilha[topo].expressao, token);
            pilha[topo].precedencia = 5; // Precedência máxima para números
        } else if (ehOperador(token)) {
            if (topo < 1) { return "Error"; }
            ItemPilha b = pilha[topo--];
            ItemPilha a = pilha[topo--];
            int precAtual = obterPrecedencia(token);

            char exprA[512], exprB[512];
            
            // Regra de parentesização: se a precedência do operando for menor que a do operador atual, adicione parênteses.
            if (a.precedencia < precAtual) {
                sprintf(exprA, "(%s)", a.expressao);
            } else {
                strcpy(exprA, a.expressao);
            }

            if (b.precedencia < precAtual) {
                 sprintf(exprB, "(%s)", b.expressao);
            } else {
                strcpy(exprB, b.expressao);
            }
            
            char novaExpr[512];
            sprintf(novaExpr, "%s %s %s", exprA, token, exprB);
            
            // Para garantir o estilo da tabela, parentesiza-se a expressão resultante
            if(topo > -1){ // Não parentesiza a expressão final
                char temp[512];
                sprintf(temp, "(%s)", novaExpr);
                strcpy(novaExpr, temp);
            }

            topo++;
            strcpy(pilha[topo].expressao, novaExpr);
            pilha[topo].precedencia = precAtual;

        } else { // É uma função
            if (topo < 0) { return "Error"; }
            ItemPilha a = pilha[topo--];
            
            char novaExpr[512];
            sprintf(novaExpr, "%s(%s)", token, a.expressao);

            topo++;
            strcpy(pilha[topo].expressao, novaExpr);
            pilha[topo].precedencia = 4;
        }
        token = strtok(NULL, " ");
    }
    
    if (topo == 0) {
        strcpy(saida, pilha[topo].expressao);
    } else {
        strcpy(saida, "Invalid Expression");
    }
    
    return saida;
}


// ========================
// Avaliação da Expressão Posfixa
// ========================
float getValorPosFixa(char *StrPosFixa) {
    PilhaFloat pilha;
    initPilhaFloat(&pilha);
    char buffer[512];
    strcpy(buffer, StrPosFixa);
    char *token = strtok(buffer, " ");
    float a, b;

    while (token) {
        if (isDigitCustom(token[0]) || (token[0] == '.' ) || (strlen(token) > 1 && token[0] == '-')) {
            pushFloat(&pilha, atof(token));
        } else if (ehOperador(token)) {
            if (pilha.topo < 1) return NAN;
            b = popFloat(&pilha);
            a = popFloat(&pilha);
            if (!strcmp(token, "+")) pushFloat(&pilha, a + b);
            else if (!strcmp(token, "-")) pushFloat(&pilha, a - b);
            else if (!strcmp(token, "*")) pushFloat(&pilha, a * b);
            else if (!strcmp(token, "/")) {
                if (b == 0) return NAN;
                pushFloat(&pilha, a / b);
            } else if (!strcmp(token, "%")) {
                if (b == 0) return NAN;
                pushFloat(&pilha, fmodf(a, b));
            } else if (!strcmp(token, "^")) {
                pushFloat(&pilha, powf(a, b));
            }
        } else { // É função
            if (pilha.topo < 0) return NAN;
            a = popFloat(&pilha);
            if (!strcmp(token, "raiz")) {
                if (a < 0) return NAN;
                pushFloat(&pilha, sqrtf(a));
            } else if (!strcmp(token, "sen")) {
                pushFloat(&pilha, sinf(a * PI / 180.0f));
            } else if (!strcmp(token, "cos")) {
                pushFloat(&pilha, cosf(a * PI / 180.0f));
            } else if (!strcmp(token, "tg")) {
                 if (fmodf(a, 180) == 90) return NAN;
                pushFloat(&pilha, tanf(a * PI / 180.0f));
            } else if (!strcmp(token, "log")) {
                if (a <= 0) return NAN;
                pushFloat(&pilha, log10f(a));
            }
        }
        token = strtok(NULL, " ");
    }
    return (pilha.topo == 0) ? popFloat(&pilha) : NAN;
}


// ========================
// Avaliação da Expressão Infixa
// ========================
float getValorInFixa(char *StrInFixa) {
    char *posFixa = getFormaPosFixa(StrInFixa);
    return getValorPosFixa(posFixa);
}