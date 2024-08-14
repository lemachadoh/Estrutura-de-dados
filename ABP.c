
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "ABP.h"

int compABP = 0; // Contador global para o número de comparações feitas na árvore binária

// Função que converte uma string para minúsculas
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]); // Converte cada caractere para minúsculo
    }
}

// Função que cria uma nova árvore binária, inicializando como NULL
pNodoA* cria_arvore(void) {
    return NULL; // Retorna um ponteiro nulo
}

// Função que insere um novo nodo como raiz na árvore binária
pNodoA* InsereRaiz(pNodoA *a, char ch[], char mais_uso[]) {
    if (a == NULL) { // Se a árvore estiver vazia
        a = (pNodoA*) malloc(sizeof(pNodoA)); // Aloca memória para um novo nodo
        strcpy(a->info, ch); // Copia a informação para o nodo
        strcpy(a->mais_usada, mais_uso); // Copia a informação mais usada
        a->esq = NULL; // Inicializa o filho esquerdo como nulo
        a->dir = NULL; // Inicializa o filho direito como nulo
    }
    return a; // Retorna o novo nodo (ou o existente se já houver um)
}

// Função que consulta uma palavra na árvore binária
pNodoA* consultaABP(pNodoA *a, char palavra[]) {
    int cmp; // Variável para armazenar o resultado da comparação

    while (a != NULL) { // Enquanto houver nodos na árvore
        compABP++; // Incrementa o contador de comparações
        cmp = strcmp(palavra, a->info); // Compara a palavra com a informação do nodo atual

        if (cmp == 0) { // Se a palavra for encontrada
            compABP++; // Incrementa o contador de comparações
            return a; // Retorna o ponteiro para o nodo encontrado
        } else {
            compABP++; // Incrementa o contador de comparações
            if (cmp > 0) {
                a = a->esq; // Se a palavra é maior, segue para a subárvore esquerda
            } else {
                a = a->dir; // Se a palavra é menor, segue para a subárvore direita
            }
        }
    }
    return NULL; // Se a palavra não for encontrada, retorna NULL
}

// Função que insere uma nova palavra na árvore binária
pNodoA* InsereArvore(pNodoA *a, char ch[], char mais_uso[]) {
    if (a == NULL) { // Se a árvore estiver vazia
        a = (pNodoA*) malloc(sizeof(pNodoA)); // Aloca memória para um novo nodo
        strcpy(a->info, ch); // Copia a informação para o nodo
        strcpy(a->mais_usada, mais_uso); // Copia a informação mais usada
        a->esq = NULL; // Inicializa o filho esquerdo como nulo
        a->dir = NULL; // Inicializa o filho direito como nulo
    }

    // Compara a nova palavra com a informação do nodo atual
    int cmp = strcmp(ch, a->info);

    if (cmp > 0) {
        // Se a nova palavra é maior, insere na subárvore esquerda
        a->esq = InsereArvore(a->esq, ch, mais_uso);
    } else if (cmp < 0) {
        // Se a nova palavra é menor, insere na subárvore direita
        a->dir = InsereArvore(a->dir, ch, mais_uso);
    }
    return a; // Retorna a árvore (ou o nodo atualizado)
}

// Função que conta o número de nodos na árvore binária
int ContaNodos(pNodoA *a) {
    if (a == NULL) {
        return 0; // Se a árvore estiver vazia, retorna 0
    } else {
        return 1 + ContaNodos(a->esq) + ContaNodos(a->dir); // Conta o nodo atual e recursivamente os filhos
    }
}

// Função que imprime os nodos da árvore em pré-ordem
void ImprimepreFixadoEsq(pNodoA *a, int nivel) {
    int i;

    if (a != NULL) { // Se o nodo não for nulo
        for (i = 0; i < nivel; i++) // Imprime "=" de acordo com o nível do nodo
            printf("=");
        printf("%s\t%s\n", a->info, a->mais_usada); // Imprime a informação do nodo

        // Chama recursivamente para os filhos esquerdo e direito
        ImprimepreFixadoEsq(a->esq, nivel + 1);
        ImprimepreFixadoEsq(a->dir, nivel + 1);
    }
}

// Função para calcular a altura de uma árvore binária
int alturaABP(pNodoA* a) {
    int altEsq, altDir; // Variáveis para armazenar as alturas das subárvores

    if (a == NULL) {
        return 0; // Se o nodo for nulo, a altura é 0
    } else {
        altEsq = alturaABP(a->esq); // Calcula a altura da subárvore esquerda
        altDir = alturaABP(a->dir); // Calcula a altura da subárvore direita

        // Retorna a altura máxima entre as duas subárvores + 1 para o nodo atual
        return (altEsq > altDir) ? (1 + altEsq) : (1 + altDir);
    }
}

// Função que imprime o número de comparações feitas na árvore binária
int imprimeCompABP() {
    //printf("Numero de comparações usando uma Arvore Binaria de Pesquisa(ABP): %d\n", compABP);
    return compABP; // Retorna o contador de comparações
}
