#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

// ===================== STRUCT =====================

// Struct Item:
// Representa um componente com nome, tipo e quantidade.
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ===================== VARIÁVEIS =====================

// Vetor mochila:
// Armazena até 10 itens coletados.
Item mochila[10];
int numItens = 0;

// ===================== FUNÇÕES =====================

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.
void limparTela() {
    for(int i = 0; i < 30; i++) printf("\n");
}

// exibirMenu():
// Apresenta o menu principal ao jogador.
void exibirMenu() {
    printf("============================================\n");
    printf("Itens na Mochila: %d/10\n\n", numItens);

    printf("1. Adicionar Item (Loot)\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens na Mochila\n");
    printf("4. Buscar Item\n");
    printf("0. Sair\n");
    printf("--------------------------------------------\n");
    printf("Escolha uma opcao: ");
}

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
void inserirItem() {
    if(numItens >= 10) {
        printf("\nMochila cheia!\n");
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n");

    printf("Nome do item: ");
    scanf("%s", mochila[numItens].nome);

    printf("Tipo do item (arma, municao, cura, etc.): ");
    scanf("%s", mochila[numItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[numItens].quantidade);

    numItens++;

    printf("\nItem adicionado com sucesso!\n");
}

// removerItem():
// Permite remover um componente da mochila pelo nome.
void removerItem() {
    char nome[30];
    int encontrado = -1;

    printf("\nDigite o nome do item para remover: ");
    scanf("%s", nome);

    for(int i = 0; i < numItens; i++) {
        if(strcmp(mochila[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if(encontrado == -1) {
        printf("\nItem nao encontrado!\n");
        return;
    }

    for(int i = encontrado; i < numItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    numItens--;

    printf("\nItem removido com sucesso!\n");
}

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens() {
    printf("\n--- ITENS NA MOCHILA (%d/10) ---\n", numItens);
    printf("--------------------------------------------\n");
    printf("NOME\t\t| TIPO\t\t| QUANTIDADE\n");
    printf("--------------------------------------------\n");

    for(int i = 0; i < numItens; i++) {
        printf("%-15s | %-10s | %d\n",
            mochila[i].nome,
            mochila[i].tipo,
            mochila[i].quantidade
        );
    }

    printf("--------------------------------------------\n");
}

// buscarItem():
// Busca sequencial por nome.
void buscarItem() {
    char nome[30];
    int encontrado = 0;

    printf("\nDigite o nome do item para buscar: ");
    scanf("%s", nome);

    for(int i = 0; i < numItens; i++) {
        if(strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if(!encontrado) {
        printf("\nItem nao encontrado!\n");
    }
}

// ===================== MAIN =====================

int main() {
    int opcao;

    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Buscar item (busca sequencial)
    // 0. Sair

    do {
        exibirMenu();
        scanf("%d", &opcao);

        limparTela();

        switch(opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;

            case 2:
                removerItem();
                listarItens();
                break;

            case 3:
                listarItens();
                break;

            case 4:
                buscarItem();
                break;

            case 0:
                printf("\nSaindo...\n");
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