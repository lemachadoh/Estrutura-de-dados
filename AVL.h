
// ----------------------------// Estruturas //---------------------------- //
#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#define MAX 50 // Define o tamanho m�ximo das strings

// Estrutura que representa um nodo da �rvore AVL
struct TNodo {
    char palavra[MAX];          // Palavra armazenada no nodo
    char mais_usada[MAX];      // Informa��es adicionais sobre a palavra
    int FB;                    // Fator de balanceamento
    struct TNodo *esq;        // Ponteiro para o filho � esquerda
    struct TNodo *dir;        // Ponteiro para o filho � direita
};

typedef struct TNodo ptNodo; // Define ptNodo como um ponteiro para TNodo

// ----------------------------// Fun��es //---------------------------- //

ptNodo* cria_AVL(); // Cria uma �rvore vazia
ptNodo* InsereAVL(ptNodo *raiz, char palavra[], char mais_uso[], int *h); // Insere um novo nodo na �rvore
ptNodo* consulta_AVL(ptNodo *raiz, char palavra[]); // Consulta um nodo na �rvore dado uma palavra

// Fun��es de rota��o para manter a �rvore balanceada
ptNodo* rotacao_direita(ptNodo *nodo); // Realiza uma rota��o simples para a direita
ptNodo* rotacao_esquerda(ptNodo *nodo); // Realiza uma rota��o simples para a esquerda
ptNodo* rotacao_dupla_direita(ptNodo *nodo); // Realiza uma rota��o dupla para a direita
ptNodo* rotacao_dupla_esquerda(ptNodo *nodo); // Realiza uma rota��o dupla para a esquerda

// Fun��es auxiliares
int calcula_altura(ptNodo *nodo); // Calcula a altura de um nodo
int calcula_fator(ptNodo *nodo); // Calcula o fator de balanceamento de um nodo

// Fun��es para casos de rota��o
ptNodo* Caso2(ptNodo *a, int *h); // Caso em que a rota��o � feita para a direita
ptNodo* Caso1(ptNodo *a, int *h); // Caso em que a rota��o � feita para a esquerda

// Verifica se a rota��o a ser feita � simples ou dupla
int caso_esq(ptNodo *nodo); // Verifica se a rota��o � direita � simples ou dupla
int caso_dir(ptNodo *nodo); // Verifica se a rota��o � esquerda � simples ou dupla

// Fun��es para obter contagens
int Nodos_AVL(); // Retorna o n�mero total de nodos na �rvore
int rotacoes_AVL(); // Retorna o n�mero total de rota��es realizadas
void imprimeArvore(ptNodo *raiz, int k); // Imprime a �rvore

int imprimeCompAVL(); // Imprime o n�mero de compara��es realizadas

#endif
