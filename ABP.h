
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50 // Definindo uma constante MAX para o tamanho máximo das strings

// Estrutura de um nodo da árvore binária
struct TNodoA {
    char info[MAX];           // Informação armazenada no nodo
    char mais_usada[MAX];    // Informações sobre o uso mais frequente
    struct TNodoA *esq;      // Ponteiro para o filho à esquerda
    struct TNodoA *dir;      // Ponteiro para o filho à direita
};

typedef struct TNodoA pNodoA; // Tipo pNodoA é um apelido para struct TNodoA

// Função que converte uma string para minúsculas
void toLowerCase(char *str);

// Função que cria uma nova árvore binária
pNodoA* cria_arvore(void);

// Função que consulta uma palavra na árvore binária
pNodoA* consultaABP(pNodoA *a, char palavra[]);

// Função que insere um novo nodo na árvore binária
pNodoA* InsereArvore(pNodoA *a, char ch[], char mais_uso[]);

// Função que conta o número de nodos na árvore binária
int ContaNodos(pNodoA *a);

// Função que calcula a altura da árvore binária
int alturaABP(pNodoA* a);

// Função que imprime os nodos em pré-ordem a partir de um nível específico
void ImprimepreFixadoEsq(pNodoA *a, int nivel);

// Função que imprime a árvore binária em uma representação compacta
int imprimeCompABP();
