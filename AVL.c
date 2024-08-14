
// ------------------// Bibliotecas //------------------ //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"

// -------------------// Variáveis Globais // ------------------- //
int compAVL = 0;          // Contador global para o número de comparações na árvore AVL
int count = 0;           // Contador para controle na impressão da árvore
int count_nodos = 0;     // Contador total de nodos na árvore
int count_rot = 0;       // Contador total de rotações realizadas na árvore

// -------------------// Funções // ------------------- //

// Função que cria uma nova árvore AVL, inicializando como NULL
ptNodo* cria_AVL() {
    return NULL; // Retorna um ponteiro nulo
}

// Função que calcula a altura de um nodo
int calcula_altura(ptNodo* nodo) {
    int altura_esq, altura_dir;

    if (nodo == NULL) {
        return 0; // Se o nodo for nulo, altura é 0
    } else {
        altura_dir = calcula_altura(nodo->dir); // Calcula altura da subárvore direita
        altura_esq = calcula_altura(nodo->esq); // Calcula altura da subárvore esquerda

        // Retorna a altura máxima entre as duas subárvores + 1 para o nodo atual
        return (altura_dir > altura_esq) ? (1 + altura_dir) : (1 + altura_esq);
    }
}

// Função que calcula o fator de balanceamento de um nodo
int calcula_fator(ptNodo* nodo) {
    return (calcula_altura(nodo->esq) - calcula_altura(nodo->dir)); // Fator = altura esquerda - altura direita
}

// Função que insere uma nova palavra na árvore AVL
ptNodo* InsereAVL(ptNodo *a, char palavra[], char mais_uso[], int *h) {
    if (a == NULL) { // Se a árvore estiver vazia
        count_nodos++; // Incrementa o contador de nodos
        a = (ptNodo*)malloc(sizeof(ptNodo)); // Aloca memória para um novo nodo
        strcpy(a->palavra, palavra); // Copia a palavra para o nodo
        strcpy(a->mais_usada, mais_uso); // Copia a informação mais usada
        a->dir = NULL; // Inicializa o filho direito como nulo
        a->esq = NULL; // Inicializa o filho esquerdo como nulo
        a->FB = 0; // Inicializa o fator de balanceamento como 0
        *h = 1; // Indica que a altura da árvore aumentou
    } else {
        // Se a palavra a ser inserida é menor que a do nodo atual, insere na subárvore esquerda
        if (strcmp(palavra, a->palavra) < 0) {
            a->esq = InsereAVL(a->esq, palavra, mais_uso, h);
            if (*h) { // Se a altura da subárvore esquerda aumentou
                switch (a->FB) {
                    case -1:
                        a->FB = 0;
                        *h = 0;
                        break;
                    case 0:
                        a->FB = 1;
                        break;
                    case 1:
                        a = Caso1(a, h); // Caso de desbalanceamento 1
                        count_rot++; // Incrementa contador de rotações
                        break;
                }
            }
        } else {
            // Se a palavra a ser inserida é maior ou igual, insere na subárvore direita
            a->dir = InsereAVL(a->dir, palavra, mais_uso, h);
            if (*h) { // Se a altura da subárvore direita aumentou
                switch (a->FB) {
                    case 1:
                        a->FB = 0;
                        *h = 0;
                        break;
                    case 0:
                        a->FB = -1;
                        break;
                    case -1:
                        a = Caso2(a, h); // Caso de desbalanceamento 2
                        count_rot++; // Incrementa contador de rotações
                        break;
                }
            }
        }
    }
    return a; // Retorna o nodo (ou o nodo atualizado)
}

// Função para tratamento do caso 1 de desbalanceamento (rotação simples à direita)
ptNodo* Caso1(ptNodo *a, int *h) {
    ptNodo *z = a->esq; // Nodo à esquerda

    if (z->FB == 1) { // Se a subárvore esquerda também está desbalanceada à esquerda
        a = rotacao_direita(a); // Realiza rotação simples à direita
    } else {
        a = rotacao_dupla_direita(a); // Realiza rotação dupla à direita
    }

    a->FB = 0; // Ajusta o fator de balanceamento do nodo atual
    *h = 0; // Indica que a altura não aumentou
    return a; // Retorna o novo nodo
}

// Função para tratamento do caso 2 de desbalanceamento (rotação simples à esquerda)
ptNodo* Caso2(ptNodo *a, int *h) {
    ptNodo *z = a->dir; // Nodo à direita

    if (z->FB == -1) { // Se a subárvore direita também está desbalanceada à direita
        a = rotacao_esquerda(a); // Realiza rotação simples à esquerda
    } else {
        a = rotacao_dupla_esquerda(a); // Realiza rotação dupla à esquerda
    }

    a->FB = 0; // Ajusta o fator de balanceamento do nodo atual
    *h = 0; // Indica que a altura não aumentou
    return a; // Retorna o novo nodo
}

// Função para rotação simples à direita
ptNodo* rotacao_direita(ptNodo *p) {
    ptNodo *u = p->esq; // Nodo à esquerda

    p->esq = u->dir; // Ajusta o filho esquerdo do nodo atual
    u->dir = p; // Realiza a rotação
    p->FB = 0; // Ajusta o fator de balanceamento do nodo atual
    p = u; // Atualiza o ponteiro para o novo nodo
    return p; // Retorna o novo nodo
}

// Função para rotação simples à esquerda
ptNodo* rotacao_esquerda(ptNodo *p) {
    ptNodo *z = p->dir; // Nodo à direita

    p->dir = z->esq; // Ajusta o filho direito do nodo atual
    z->esq = p; // Realiza a rotação
    p->FB = 0; // Ajusta o fator de balanceamento do nodo atual
    p = z; // Atualiza o ponteiro para o novo nodo
    return p; // Retorna o novo nodo
}

// Função para rotação dupla à direita
ptNodo* rotacao_dupla_direita(ptNodo *p) {
    ptNodo *u = p->esq; // Nodo à esquerda
    ptNodo *v = u->dir; // Nodo à direita do nodo à esquerda

    u->dir = v->esq; // Ajusta o filho direito do nodo à esquerda
    v->esq = u; // Realiza a rotação
    p->esq = v->dir; // Ajusta o filho esquerdo do nodo atual
    v->dir = p; // Realiza a rotação

    // Ajusta os fatores de balanceamento
    if (v->FB == 1) {
        p->FB = -1;
    } else {
        p->FB = 0;
    }

    if (v->FB == -1) {
        u->FB = 1;
    } else {
        u->FB = 0;
    }

    p = v; // Atualiza o ponteiro para o novo nodo
    return p; // Retorna o novo nodo
}

// Função para rotação dupla à esquerda
ptNodo* rotacao_dupla_esquerda(ptNodo *p) {
    ptNodo *z = p->dir; // Nodo à direita
    ptNodo *y = z->esq; // Nodo à esquerda do nodo à direita

    z->esq = y->dir; // Ajusta o filho esquerdo do nodo à direita
    y->dir = z; // Realiza a rotação
    p->dir = y->esq; // Ajusta o filho direito do nodo atual
    y->esq = p; // Realiza a rotação

    // Ajusta os fatores de balanceamento
    if (y->FB == -1) {
        p->FB = 1;
    } else {
        p->FB = 0;
    }

    if (y->FB == 1) {
        z->FB = -1;
    } else {
        z->FB = 0;
    }

    p = y; // Atualiza o ponteiro para o novo nodo
    return p; // Retorna o novo nodo
}

// Função para consultar um nodo na árvore AVL
ptNodo* consulta_AVL(ptNodo* raiz, char palavra[]) {
    if (raiz == NULL) {
        return NULL; // Se a árvore estiver vazia, retorna NULL
    } else {
        int comparacao = strcmp(palavra, raiz->palavra); // Compara a palavra

        if (comparacao == 0) { // Se a palavra for encontrada
            compAVL++; // Incrementa o contador de comparações
            return raiz; // Retorna o nodo encontrado
        } else if (comparacao > 0) { // Se a palavra é maior
            compAVL++; // Incrementa o contador de comparações
            return consulta_AVL(raiz->esq, palavra); // Consulta na subárvore esquerda
        } else {
            compAVL++; // Incrementa o contador de comparações
            return consulta_AVL(raiz->dir, palavra); // Consulta na subárvore direita
        }
    }
}

// Funções de verificações

// Função que verifica se é caso esquerdo
int caso_esq(ptNodo* nodo) {
    return (calcula_fator(nodo->esq) > 0) ? 0 : 1; // Retorna 0 se for caso esquerdo, 1 caso contrário
}

// Função que verifica se é caso direito
int caso_dir(ptNodo* nodo) {
    return (calcula_fator(nodo->dir) < 0) ? 0 : 1; // Retorna 0 se for caso direito, 1 caso contrário
}

// Função que imprime a árvore em ordem
void imprimeArvore(ptNodo *raiz, int k) {
    if (raiz != NULL && count <= k) { // Se o nodo não for nulo e não ultrapassar o limite
        imprimeArvore(raiz->dir, k); // Imprime a subárvore direita
        count++; // Incrementa o contador

        if (count <= k) { // Se não ultrapassar o limite
            printf("Palavra: %s\n", raiz->palavra); // Imprime a palavra do nodo
        }

        imprimeArvore(raiz->esq, k); // Imprime a subárvore esquerda
    }
}

// Função que retorna o número total de nodos na árvore
int Nodos_AVL() {
    return count_nodos; // Retorna o contador de nodos
}

// Função que retorna o número total de rotações realizadas
int rotacoes_AVL() {
    return count_rot; // Retorna o contador de rotações
}

// Função que reseta o contador de impressões
void reseta_count() {
    count = 0; // Reseta o contador
}

// Função que imprime o número de comparações realizadas
int imprimeCompAVL() {
    // printf("Numero de comparações usando uma Árvore Binária de Pesquisa Balanceada (AVL): %d\n", compAVL);
    return compAVL; // Retorna o contador de comparações
}
