
/* Programa desenvolvido por Leandra Machado e Ana Caroline de Jesus
   no intuito de concluir o trabalho da disciplina Estrutura de Dados
   14 de Agosto de 2024 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "AVL.h"
#include "ABP.h"

// Função para abrir arquivos e verificar erros
FILE* openFile(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode); // Tenta abrir o arquivo
    if (file == NULL) { // Verifica se houve erro na abertura
        printf("Erro ao abrir o arquivo: %s\n", filename);
        exit(1); // Finaliza o programa em caso de erro
    }
    return file; // Retorna o ponteiro do arquivo aberto
}

// Função para processar o dicionário
void processDictionary(FILE* dicionario, pNodoA** avl, ptNodo** abp) {
    char linha[1000]; // Buffer para armazenar linhas do dicionário
    char* palavra;    // Ponteiro para armazenar a palavra atual
    char* palavra2;   // Ponteiro para armazenar a segunda palavra

    int aH = 0; // Variável para controlar a altura da árvore AVL
    while (fgets(linha, sizeof(linha), dicionario)) { // Lê cada linha do dicionário
        palavra = strtok(linha, "\t\n"); // Separa a primeira palavra
        palavra2 = strtok(NULL, "\t\n"); // Separa a segunda palavra
        while (palavra != NULL) { // Enquanto houver palavras
            toLowerCase(palavra); // Converte a palavra para minúscula
            toLowerCase(palavra2); // Converte a segunda palavra para minúscula
            *avl = InsereAVL(*avl, palavra, palavra2, &aH); // Insere na árvore AVL
            *abp = InsereArvore(*abp, palavra, palavra2); // Insere na árvore ABP
            palavra = strtok(NULL, "\t\n"); // Continua a separar palavras
        }
    }
}

// Função para processar o arquivo de entrada
void processInputFile(FILE* txt_entrada, FILE* txtsimplificado, pNodoA* avl, ptNodo* abp) {
    char linha[1000]; // Buffer para armazenar linhas do arquivo de entrada
    char* palavra;    // Ponteiro para armazenar a palavra atual

    while (fgets(linha, sizeof(linha), txt_entrada)) { // Lê cada linha do arquivo de entrada
        palavra = strtok(linha, " \t\n"); // Separa a primeira palavra
        while (palavra != NULL) { // Enquanto houver palavras
            ptNodo* ptAVL = consulta_AVL(avl, palavra); // Consulta na árvore AVL
            if (ptAVL != NULL) { // Se a palavra for encontrada na AVL
                fprintf(txtsimplificado, "%s ", ptAVL->mais_usada); // Escreve a informação mais usada
            } else {
                pNodoA* ptABP = consultaABP(abp, palavra); // Consulta na árvore ABP
                if (ptABP != NULL) { // Se a palavra for encontrada na ABP
                    fprintf(txtsimplificado, "%s ", ptABP->mais_usada); // Escreve a informação mais usada
                } else {
                    fprintf(txtsimplificado, "%s ", palavra); // Se não encontrada, escreve a palavra original
                }
            }
            palavra = strtok(NULL, " \t\n"); // Continua a separar palavras
        }
        fprintf(txtsimplificado, "\n"); // Para separar linhas no arquivo de saída
    }
}

// Função para gerar estatísticas
void generateStatistics(FILE* stats_ger, ptNodo* abp, pNodoA* avl) {
    fprintf(stats_ger, "========  ESTATÍSTICAS ABP ============\n\n");
    fprintf(stats_ger, "Número de nodos: %d\n", ContaNodos(abp)); // Conta nodos na ABP
    fprintf(stats_ger, "Altura: %d\n", alturaABP(abp)); // Calcula altura da ABP
    fprintf(stats_ger, "Rotações: %d\n", 0); // Rotações da ABP (se aplicável)
    fprintf(stats_ger, "Comparações: %d\n", imprimeCompABP()); // Conta comparações na ABP

    fprintf(stats_ger, "\n\n\n");

    fprintf(stats_ger, "========  ESTATÍSTICAS AVL ============\n\n");
    fprintf(stats_ger, "Número de nodos: %d\n", Nodos_AVL()); // Conta nodos na AVL
    fprintf(stats_ger, "Altura: %d\n", calcula_altura(avl)); // Calcula altura da AVL
    fprintf(stats_ger, "Rotações: %d\n", rotacoes_AVL()); // Conta rotações na AVL
    fprintf(stats_ger, "Comparações: %d\n", imprimeCompAVL()); // Conta comparações na AVL
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Portuguese"); // Define locale para português

    if (argc != 5) { // Verifica se o número de argumentos está correto
        printf("Número incorreto de parâmetros.\n");
        return 1; // Retorna erro se o número de argumentos estiver incorreto
    }

    // Abre os arquivos necessários e verifica erros
    FILE* dicionario = openFile(argv[1], "r");
    FILE* txt_entrada = openFile(argv[2], "r");
    FILE* txtsimplificado = openFile(argv[3], "w");
    FILE* stats_ger = openFile(argv[4], "w");

    // Cria árvores vazias para AVL e ABP
    pNodoA* avl = cria_AVL();
    ptNodo* abp = cria_arvore();

    processDictionary(dicionario, &avl, &abp); // Processa o dicionário
    fclose(dicionario); // Fecha o arquivo do dicionário após o processamento

    processInputFile(txt_entrada, txtsimplificado, avl, abp); // Processa o arquivo de entrada
    fclose(txt_entrada); // Fecha o arquivo de entrada
    fclose(txtsimplificado); // Fecha o arquivo simplificado após o processamento

    generateStatistics(stats_ger, abp, avl); // Gera estatísticas
    fclose(stats_ger); // Fecha o arquivo de estatísticas após a escrita

    return 0; // Retorna sucesso
}
