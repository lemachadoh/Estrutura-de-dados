
// ----------------------------// Estruturas //---------------------------- //
#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#define MAX 50 // Define o tamanho máximo das strings

// Estrutura que representa um nodo da árvore AVL
struct TNodo {
    char palavra[MAX];          // Palavra armazenada no nodo
    char mais_usada[MAX];      // Informações adicionais sobre a palavra
    int FB;                    // Fator de balanceamento
    struct TNodo *esq;        // Ponteiro para o filho à esquerda
    struct TNodo *dir;        // Ponteiro para o filho à direita
};

typedef struct TNodo ptNodo; // Define ptNodo como um ponteiro para TNodo

// ----------------------------// Funções //---------------------------- //

ptNodo* cria_AVL(); // Cria uma árvore vazia
ptNodo* InsereAVL(ptNodo *raiz, char palavra[], char mais_uso[], int *h); // Insere um novo nodo na árvore
ptNodo* consulta_AVL(ptNodo *raiz, char palavra[]); // Consulta um nodo na árvore dado uma palavra

// Funções de rotação para manter a árvore balanceada
ptNodo* rotacao_direita(ptNodo *nodo); // Realiza uma rotação simples para a direita
ptNodo* rotacao_esquerda(ptNodo *nodo); // Realiza uma rotação simples para a esquerda
ptNodo* rotacao_dupla_direita(ptNodo *nodo); // Realiza uma rotação dupla para a direita
ptNodo* rotacao_dupla_esquerda(ptNodo *nodo); // Realiza uma rotação dupla para a esquerda

// Funções auxiliares
int calcula_altura(ptNodo *nodo); // Calcula a altura de um nodo
int calcula_fator(ptNodo *nodo); // Calcula o fator de balanceamento de um nodo

// Funções para casos de rotação
ptNodo* Caso2(ptNodo *a, int *h); // Caso em que a rotação é feita para a direita
ptNodo* Caso1(ptNodo *a, int *h); // Caso em que a rotação é feita para a esquerda

// Verifica se a rotação a ser feita é simples ou dupla
int caso_esq(ptNodo *nodo); // Verifica se a rotação à direita é simples ou dupla
int caso_dir(ptNodo *nodo); // Verifica se a rotação à esquerda é simples ou dupla

// Funções para obter contagens
int Nodos_AVL(); // Retorna o número total de nodos na árvore
int rotacoes_AVL(); // Retorna o número total de rotações realizadas
void imprimeArvore(ptNodo *raiz, int k); // Imprime a árvore

int imprimeCompAVL(); // Imprime o número de comparações realizadas

#endif
