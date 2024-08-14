
// ------------------// Bibliotecas //------------------ //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"

// -------------------// Vari�veis Globais // ------------------- //
int compAVL = 0;          // Contador global para o n�mero de compara��es na �rvore AVL
int count = 0;           // Contador para controle na impress�o da �rvore
int count_nodos = 0;     // Contador total de nodos na �rvore
int count_rot = 0;       // Contador total de rota��es realizadas na �rvore

// -------------------// Fun��es // ------------------- //

// Fun��o que cria uma nova �rvore AVL, inicializando como NULL
ptNodo* cria_AVL() {
    return NULL; // Retorna um ponteiro nulo
}

// Fun��o que calcula a altura de um nodo
int calcula_altura(ptNodo* nodo) {
    int altura_esq, altura_dir;

    if (nodo == NULL) {
        return 0; // Se o nodo for nulo, altura � 0
    } else {
        altura_dir = calcula_altura(nodo->dir); // Calcula altura da sub�rvore direita
        altura_esq = calcula_altura(nodo->esq); // Calcula altura da sub�rvore esquerda

        // Retorna a altura m�xima entre as duas sub�rvores + 1 para o nodo atual
        return (altura_dir > altura_esq) ? (1 + altura_dir) : (1 + altura_esq);
    }
}

// Fun��o que calcula o fator de balanceamento de um nodo
int calcula_fator(ptNodo* nodo) {
    return (calcula_altura(nodo->esq) - calcula_altura(nodo->dir)); // Fator = altura esquerda - altura direita
}

// Fun��o que insere uma nova palavra na �rvore AVL
ptNodo* InsereAVL(ptNodo *a, char palavra[], char mais_uso[], int *h) {
    if (a == NULL) { // Se a �rvore estiver vazia
        count_nodos++; // Incrementa o contador de nodos
        a = (ptNodo*)malloc(sizeof(ptNodo)); // Aloca mem�ria para um novo nodo
        strcpy(a->palavra, palavra); // Copia a palavra para o nodo
        strcpy(a->mais_usada, mais_uso); // Copia a informa��o mais usada
        a->dir = NULL; // Inicializa o filho direito como nulo
        a->esq = NULL; // Inicializa o filho esquerdo como nulo
        a->FB = 0; // Inicializa o fator de balanceamento como 0
        *h = 1; // Indica que a altura da �rvore aumentou
    } else {
        // Se a palavra a ser inserida � menor que a do nodo atual, insere na sub�rvore esquerda
        if (strcmp(palavra, a->palavra) < 0) {
            a->esq = InsereAVL(a->esq, palavra, mais_uso, h);
            if (*h) { // Se a altura da sub�rvore esquerda aumentou
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
                        count_rot++; // Incrementa contador de rota��es
                        break;
                }
            }
        } else {
            // Se a palavra a ser inserida � maior ou igual, insere na sub�rvore direita
            a->dir = InsereAVL(a->dir, palavra, mais_uso, h);
            if (*h) { // Se a altura da sub�rvore direita aumentou
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
                        count_rot++; // Incrementa contador de rota��es
                        break;
                }
            }
        }
    }
    return a; // Retorna o nodo (ou o nodo atualizado)
}

// Fun��o para tratamento do caso 1 de desbalanceamento (rota��o simples � direita)
ptNodo* Caso1(ptNodo *a, int *h) {
    ptNodo *z = a->esq; // Nodo � esquerda

    if (z->FB == 1) { // Se a sub�rvore esquerda tamb�m est� desbalanceada � esquerda
        a = rotacao_direita(a); // Realiza rota��o simples � direita
    } else {
        a = rotacao_dupla_direita(a); // Realiza rota��o dupla � direita
    }

    a->FB = 0; // Ajusta o fator de balanceamento do nodo atual
    *h = 0; // Indica que a altura n�o aumentou
    return a; // Retorna o novo nodo
}

// Fun��o para tratamento do caso 2 de desbalanceamento (rota��o simples � esquerda)
ptNodo* Caso2(ptNodo *a, int *h) {
    ptNodo *z = a->dir; // Nodo � direita

    if (z->FB == -1) { // Se a sub�rvore direita tamb�m est� desbalanceada � direita
        a = rotacao_esquerda(a); // Realiza rota��o simples � esquerda
    } else {
        a = rotacao_dupla_esquerda(a); // Realiza rota��o dupla � esquerda
    }

    a->FB = 0; // Ajusta o fator de balanceamento do nodo atual
    *h = 0; // Indica que a altura n�o aumentou
    return a; // Retorna o novo nodo
}

// Fun��o para rota��o simples � direita
ptNodo* rotacao_direita(ptNodo *p) {
    ptNodo *u = p->esq; // Nodo � esquerda

    p->esq = u->dir; // Ajusta o filho esquerdo do nodo atual
    u->dir = p; // Realiza a rota��o
    p->FB = 0; // Ajusta o fator de balanceamento do nodo atual
    p = u; // Atualiza o ponteiro para o novo nodo
    return p; // Retorna o novo nodo
}

// Fun��o para rota��o simples � esquerda
ptNodo* rotacao_esquerda(ptNodo *p) {
    ptNodo *z = p->dir; // Nodo � direita

    p->dir = z->esq; // Ajusta o filho direito do nodo atual
    z->esq = p; // Realiza a rota��o
    p->FB = 0; // Ajusta o fator de balanceamento do nodo atual
    p = z; // Atualiza o ponteiro para o novo nodo
    return p; // Retorna o novo nodo
}

// Fun��o para rota��o dupla � direita
ptNodo* rotacao_dupla_direita(ptNodo *p) {
    ptNodo *u = p->esq; // Nodo � esquerda
    ptNodo *v = u->dir; // Nodo � direita do nodo � esquerda

    u->dir = v->esq; // Ajusta o filho direito do nodo � esquerda
    v->esq = u; // Realiza a rota��o
    p->esq = v->dir; // Ajusta o filho esquerdo do nodo atual
    v->dir = p; // Realiza a rota��o

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

// Fun��o para rota��o dupla � esquerda
ptNodo* rotacao_dupla_esquerda(ptNodo *p) {
    ptNodo *z = p->dir; // Nodo � direita
    ptNodo *y = z->esq; // Nodo � esquerda do nodo � direita

    z->esq = y->dir; // Ajusta o filho esquerdo do nodo � direita
    y->dir = z; // Realiza a rota��o
    p->dir = y->esq; // Ajusta o filho direito do nodo atual
    y->esq = p; // Realiza a rota��o

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

// Fun��o para consultar um nodo na �rvore AVL
ptNodo* consulta_AVL(ptNodo* raiz, char palavra[]) {
    if (raiz == NULL) {
        return NULL; // Se a �rvore estiver vazia, retorna NULL
    } else {
        int comparacao = strcmp(palavra, raiz->palavra); // Compara a palavra

        if (comparacao == 0) { // Se a palavra for encontrada
            compAVL++; // Incrementa o contador de compara��es
            return raiz; // Retorna o nodo encontrado
        } else if (comparacao > 0) { // Se a palavra � maior
            compAVL++; // Incrementa o contador de compara��es
            return consulta_AVL(raiz->esq, palavra); // Consulta na sub�rvore esquerda
        } else {
            compAVL++; // Incrementa o contador de compara��es
            return consulta_AVL(raiz->dir, palavra); // Consulta na sub�rvore direita
        }
    }
}

// Fun��es de verifica��es

// Fun��o que verifica se � caso esquerdo
int caso_esq(ptNodo* nodo) {
    return (calcula_fator(nodo->esq) > 0) ? 0 : 1; // Retorna 0 se for caso esquerdo, 1 caso contr�rio
}

// Fun��o que verifica se � caso direito
int caso_dir(ptNodo* nodo) {
    return (calcula_fator(nodo->dir) < 0) ? 0 : 1; // Retorna 0 se for caso direito, 1 caso contr�rio
}

// Fun��o que imprime a �rvore em ordem
void imprimeArvore(ptNodo *raiz, int k) {
    if (raiz != NULL && count <= k) { // Se o nodo n�o for nulo e n�o ultrapassar o limite
        imprimeArvore(raiz->dir, k); // Imprime a sub�rvore direita
        count++; // Incrementa o contador

        if (count <= k) { // Se n�o ultrapassar o limite
            printf("Palavra: %s\n", raiz->palavra); // Imprime a palavra do nodo
        }

        imprimeArvore(raiz->esq, k); // Imprime a sub�rvore esquerda
    }
}

// Fun��o que retorna o n�mero total de nodos na �rvore
int Nodos_AVL() {
    return count_nodos; // Retorna o contador de nodos
}

// Fun��o que retorna o n�mero total de rota��es realizadas
int rotacoes_AVL() {
    return count_rot; // Retorna o contador de rota��es
}

// Fun��o que reseta o contador de impress�es
void reseta_count() {
    count = 0; // Reseta o contador
}

// Fun��o que imprime o n�mero de compara��es realizadas
int imprimeCompAVL() {
    // printf("Numero de compara��es usando uma �rvore Bin�ria de Pesquisa Balanceada (AVL): %d\n", compAVL);
    return compAVL; // Retorna o contador de compara��es
}
