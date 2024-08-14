
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "ABP.h"

int compABP = 0; // Contador global para o n�mero de compara��es feitas na �rvore bin�ria

// Fun��o que converte uma string para min�sculas
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]); // Converte cada caractere para min�sculo
    }
}

// Fun��o que cria uma nova �rvore bin�ria, inicializando como NULL
pNodoA* cria_arvore(void) {
    return NULL; // Retorna um ponteiro nulo
}

// Fun��o que insere um novo nodo como raiz na �rvore bin�ria
pNodoA* InsereRaiz(pNodoA *a, char ch[], char mais_uso[]) {
    if (a == NULL) { // Se a �rvore estiver vazia
        a = (pNodoA*) malloc(sizeof(pNodoA)); // Aloca mem�ria para um novo nodo
        strcpy(a->info, ch); // Copia a informa��o para o nodo
        strcpy(a->mais_usada, mais_uso); // Copia a informa��o mais usada
        a->esq = NULL; // Inicializa o filho esquerdo como nulo
        a->dir = NULL; // Inicializa o filho direito como nulo
    }
    return a; // Retorna o novo nodo (ou o existente se j� houver um)
}

// Fun��o que consulta uma palavra na �rvore bin�ria
pNodoA* consultaABP(pNodoA *a, char palavra[]) {
    int cmp; // Vari�vel para armazenar o resultado da compara��o

    while (a != NULL) { // Enquanto houver nodos na �rvore
        compABP++; // Incrementa o contador de compara��es
        cmp = strcmp(palavra, a->info); // Compara a palavra com a informa��o do nodo atual

        if (cmp == 0) { // Se a palavra for encontrada
            compABP++; // Incrementa o contador de compara��es
            return a; // Retorna o ponteiro para o nodo encontrado
        } else {
            compABP++; // Incrementa o contador de compara��es
            if (cmp > 0) {
                a = a->esq; // Se a palavra � maior, segue para a sub�rvore esquerda
            } else {
                a = a->dir; // Se a palavra � menor, segue para a sub�rvore direita
            }
        }
    }
    return NULL; // Se a palavra n�o for encontrada, retorna NULL
}

// Fun��o que insere uma nova palavra na �rvore bin�ria
pNodoA* InsereArvore(pNodoA *a, char ch[], char mais_uso[]) {
    if (a == NULL) { // Se a �rvore estiver vazia
        a = (pNodoA*) malloc(sizeof(pNodoA)); // Aloca mem�ria para um novo nodo
        strcpy(a->info, ch); // Copia a informa��o para o nodo
        strcpy(a->mais_usada, mais_uso); // Copia a informa��o mais usada
        a->esq = NULL; // Inicializa o filho esquerdo como nulo
        a->dir = NULL; // Inicializa o filho direito como nulo
    }

    // Compara a nova palavra com a informa��o do nodo atual
    int cmp = strcmp(ch, a->info);

    if (cmp > 0) {
        // Se a nova palavra � maior, insere na sub�rvore esquerda
        a->esq = InsereArvore(a->esq, ch, mais_uso);
    } else if (cmp < 0) {
        // Se a nova palavra � menor, insere na sub�rvore direita
        a->dir = InsereArvore(a->dir, ch, mais_uso);
    }
    return a; // Retorna a �rvore (ou o nodo atualizado)
}

// Fun��o que conta o n�mero de nodos na �rvore bin�ria
int ContaNodos(pNodoA *a) {
    if (a == NULL) {
        return 0; // Se a �rvore estiver vazia, retorna 0
    } else {
        return 1 + ContaNodos(a->esq) + ContaNodos(a->dir); // Conta o nodo atual e recursivamente os filhos
    }
}

// Fun��o que imprime os nodos da �rvore em pr�-ordem
void ImprimepreFixadoEsq(pNodoA *a, int nivel) {
    int i;

    if (a != NULL) { // Se o nodo n�o for nulo
        for (i = 0; i < nivel; i++) // Imprime "=" de acordo com o n�vel do nodo
            printf("=");
        printf("%s\t%s\n", a->info, a->mais_usada); // Imprime a informa��o do nodo

        // Chama recursivamente para os filhos esquerdo e direito
        ImprimepreFixadoEsq(a->esq, nivel + 1);
        ImprimepreFixadoEsq(a->dir, nivel + 1);
    }
}

// Fun��o para calcular a altura de uma �rvore bin�ria
int alturaABP(pNodoA* a) {
    int altEsq, altDir; // Vari�veis para armazenar as alturas das sub�rvores

    if (a == NULL) {
        return 0; // Se o nodo for nulo, a altura � 0
    } else {
        altEsq = alturaABP(a->esq); // Calcula a altura da sub�rvore esquerda
        altDir = alturaABP(a->dir); // Calcula a altura da sub�rvore direita

        // Retorna a altura m�xima entre as duas sub�rvores + 1 para o nodo atual
        return (altEsq > altDir) ? (1 + altEsq) : (1 + altDir);
    }
}

// Fun��o que imprime o n�mero de compara��es feitas na �rvore bin�ria
int imprimeCompABP() {
    //printf("Numero de compara��es usando uma Arvore Binaria de Pesquisa(ABP): %d\n", compABP);
    return compABP; // Retorna o contador de compara��es
}
