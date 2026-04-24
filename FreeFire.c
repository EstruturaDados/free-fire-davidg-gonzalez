#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de componentes para construção da torre de fuga.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

// ===================== STRUCT =====================

// Struct Item:
// Representa um componente com nome, tipo e prioridade.
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ===================== VARIÁVEIS =====================

// Vetor mochila:
// Armazena até 20 componentes coletados.
Componente mochila[20];
int numItens = 0;

bool ordenadoPorNome = false;
int comparacoes = 0;

// ===================== FUNÇÕES =====================

// limparTela():
void limparTela() {
    for(int i = 0; i < 30; i++) printf("\n");
}

// exibirMenu():
void exibirMenu() {
    printf("=============================================================\n");
    printf("PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
    printf("=============================================================\n");
    printf("Itens na Mochila: %d/20\n", numItens);
    printf("Status da Ordenacao por Nome: %s\n\n", ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");

    printf("1. Adicionar Componente\n");
    printf("2. Descartar Componente\n");
    printf("3. Listar Componentes (Inventario)\n");
    printf("4. Organizar Mochila (Ordenar Componentes)\n");
    printf("5. Busca Binaria por Componente-Chave\n");
    printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
    printf("-------------------------------------------------------------\n");
    printf("Escolha uma opcao: ");
}

// inserirItem():
void inserirItem() {
    if(numItens >= 20) {
        printf("\nMochila cheia!\n");
        return;
    }

    printf("\n--- Coletando Novo Componente ---\n");

    printf("Nome: ");
    scanf("%s", mochila[numItens].nome);

    printf("Tipo (Estrutural, Eletronico, Energia): ");
    scanf("%s", mochila[numItens].tipo);

    printf("Prioridade (1-10): ");
    scanf("%d", &mochila[numItens].prioridade);

    numItens++;
    ordenadoPorNome = false;

    printf("\nComponente adicionado com sucesso!\n");
}

// removerItem():
void removerItem() {
    char nome[30];
    int pos = -1;

    printf("\nDigite o nome do componente para descartar: ");
    scanf("%s", nome);

    for(int i = 0; i < numItens; i++) {
        if(strcmp(mochila[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }

    if(pos == -1) {
        printf("\nComponente nao encontrado!\n");
        return;
    }

    for(int i = pos; i < numItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    numItens--;
    printf("\nComponente removido!\n");
}

// listarItens():
void listarItens() {
    printf("\n--- INVENTARIO ATUAL (%d/20) ---\n", numItens);
    printf("-------------------------------------------------------------\n");
    printf("NOME           | TIPO         | PRIORIDADE\n");
    printf("-------------------------------------------------------------\n");

    for(int i = 0; i < numItens; i++) {
        printf("%-14s | %-12s | %d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].prioridade);
    }

    printf("-------------------------------------------------------------\n");
}

// ===================== ORDENAÇÕES =====================

// Bubble Sort (por nome)
void bubbleSortNome() {
    comparacoes = 0;
    for(int i = 0; i < numItens - 1; i++) {
        for(int j = 0; j < numItens - i - 1; j++) {
            comparacoes++;
            if(strcmp(mochila[j].nome, mochila[j+1].nome) > 0) {
                Componente temp = mochila[j];
                mochila[j] = mochila[j+1];
                mochila[j+1] = temp;
            }
        }
    }
    ordenadoPorNome = true;
}

// Insertion Sort (por tipo)
void insertionSortTipo() {
    comparacoes = 0;
    for(int i = 1; i < numItens; i++) {
        Componente key = mochila[i];
        int j = i - 1;

        while(j >= 0 && strcmp(mochila[j].tipo, key.tipo) > 0) {
            comparacoes++;
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = key;
    }
}

// Selection Sort (por prioridade)
void selectionSortPrioridade() {
    comparacoes = 0;
    for(int i = 0; i < numItens - 1; i++) {
        int min = i;
        for(int j = i + 1; j < numItens; j++) {
            comparacoes++;
            if(mochila[j].prioridade > mochila[min].prioridade) {
                min = j;
            }
        }
        Componente temp = mochila[i];
        mochila[i] = mochila[min];
        mochila[min] = temp;
    }
}

// menuDeOrdenacao():
void menuDeOrdenacao() {
    int op;
    clock_t inicio, fim;
    double tempo;

    printf("\n--- Estrategia de Organizacao ---\n");
    printf("1. Por Nome (Ordem Alfabetica)\n");
    printf("2. Por Tipo\n");
    printf("3. Por Prioridade\n");
    printf("0. Cancelar\n");
    printf("Escolha o criterio: ");
    scanf("%d", &op);

    inicio = clock();

    switch(op) {
        case 1:
            bubbleSortNome();
            printf("\nMochila organizada por NOME.\n");
            break;
        case 2:
            insertionSortTipo();
            printf("\nMochila organizada por TIPO.\n");
            break;
        case 3:
            selectionSortPrioridade();
            printf("\nMochila organizada por PRIORIDADE.\n");
            break;
        default:
            printf("\nCancelado.\n");
            return;
    }

    fim = clock();
    tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("Analise de Desempenho: %d comparacoes | Tempo: %.6f s\n", comparacoes, tempo);

    listarItens();
}

// ===================== BUSCA BINÁRIA =====================

// buscaBinariaPorNome():
void buscaBinaria() {
    if(!ordenadoPorNome) {
        printf("\nOrdene por NOME antes da busca binaria!\n");
        return;
    }

    char chave[30];
    printf("\nDigite o nome do componente-chave: ");
    scanf("%s", chave);

    int inicio = 0, fim = numItens - 1;

    while(inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, chave);

        if(cmp == 0) {
            printf("\nComponente-chave encontrado!\n");
            printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                   mochila[meio].nome,
                   mochila[meio].tipo,
                   mochila[meio].prioridade);
            return;
        }
        else if(cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("\nComponente nao encontrado!\n");
}

// ===================== MAIN =====================

int main() {
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        limparTela();

        switch(opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                menuDeOrdenacao();
                break;
            case 5:
                buscaBinaria();
                break;
            case 0:
                printf("\nAtivando torre de fuga...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }

        printf("\nPressione Enter para continuar...");
        getchar();
        getchar();

        limparTela();

    } while(opcao != 0);

    return 0;
}