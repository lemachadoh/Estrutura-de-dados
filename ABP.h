
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50 // Definindo uma constante MAX para o tamanho m�ximo das strings

// Estrutura de um nodo da �rvore bin�ria
struct TNodoA {
    char info[MAX];           // Informa��o armazenada no nodo
    char mais_usada[MAX];    // Informa��es sobre o uso mais frequente
    struct TNodoA *esq;      // Ponteiro para o filho � esquerda
    struct TNodoA *dir;      // Ponteiro para o filho � direita
};

typedef struct TNodoA pNodoA; // Tipo pNodoA � um apelido para struct TNodoA

// Fun��o que converte uma string para min�sculas
void toLowerCase(char *str);

// Fun��o que cria uma nova �rvore bin�ria
pNodoA* cria_arvore(void);

// Fun��o que consulta uma palavra na �rvore bin�ria
pNodoA* consultaABP(pNodoA *a, char palavra[]);

// Fun��o que insere um novo nodo na �rvore bin�ria
pNodoA* InsereArvore(pNodoA *a, char ch[], char mais_uso[]);

// Fun��o que conta o n�mero de nodos na �rvore bin�ria
int ContaNodos(pNodoA *a);

// Fun��o que calcula a altura da �rvore bin�ria
int alturaABP(pNodoA* a);

// Fun��o que imprime os nodos em pr�-ordem a partir de um n�vel espec�fico
void ImprimepreFixadoEsq(pNodoA *a, int nivel);

// Fun��o que imprime a �rvore bin�ria em uma representa��o compacta
int imprimeCompABP();
