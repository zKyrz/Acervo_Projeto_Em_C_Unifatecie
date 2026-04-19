#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* Configurações do sistema */
#define MAX_LIVROS 100
#define MAX_TITULO 100

typedef struct {
    int id;
    char titulo[MAX_TITULO];
} Livro;

/**
 * Limpa o buffer do teclado.
 * Essencial para evitar leitura de caracteres residuais (como o \n do Enter)
 * que poderiam corromper os próximos scanf.
 */
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Remove um registro da biblioteca baseado no ID.
 * Ao encontrar o alvo, deslocamos os elementos subsequentes para manter 
 * a integridade do array (evitando "buracos" na lista).
 */
bool remover_livro(Livro biblioteca[], int *total, int id_alvo) {
    for (int i = 0; i < *total; i++) {
        if (biblioteca[i].id == id_alvo) {
            /* Desloca os itens para a esquerda para preencher a lacuna */
            for (int j = i; j < *total - 1; j++) {
                biblioteca[j] = biblioteca[j + 1];
            }
            (*total)--;
            return true;
        }
    }
    return false;
}

void listar_livros(Livro biblioteca[], int total) {
    printf("\n--- Inventario Atual (%d livros) ---\n", total);
    
    if (total == 0) {
        printf("A prateleira esta vazia.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("[%03d] %s\n", biblioteca[i].id, biblioteca[i].titulo);
    }
    printf("------------------------------------\n");
}

int main() {
    /* Dados mockados para inicialização do sistema */
    Livro biblioteca[MAX_LIVROS] = {
        {1, "As Cronicas de Narnia (C. S. Lewis)"},
        {2, "Cartas de um Diabo a Seu Aprendiz (C. S. Lewis)"},
        {3, "Stormdancer (Jay Kristoff)"},
        {4, "Nevernight (Jay Kristoff)"},
        {5, "Neuromancer (William Gibson)"},
        {6, "Count Zero (William Gibson)"},
        {7, "Androides Sonham com Ovelhas Eletricas? (Philip K. Dick)"},
        {8, "O Homem do Castelo Alto (Philip K. Dick)"}
    };
    
    int total_livros = 8;
    int opcao, id_entrada;

    printf("Sistema de Gestao de Biblioteca Pessoal iniciado.\n");

    do {
        printf("\nMENU:\n1. Listar Acervo\n2. Doar Livro (Remover)\n3. Sair\n");
        printf("Opcao: ");
        
        /* Proteção contra entrada de dados que não sejam inteiros */
        if (scanf("%d", &opcao) != 1) {
            printf("Erro: Por favor, insira um numero valido.\n");
            limpar_buffer();
            continue;
        }

        switch(opcao) {
            case 1:
                listar_livros(biblioteca, total_livros);
                break;

            case 2:
                printf("Digite o ID do livro para remocao: ");
                scanf("%d", &id_entrada);
                
                if (remover_livro(biblioteca, &total_livros, id_entrada)) {
                    printf("Sucesso: Livro [%d] removido do inventario.\n", id_entrada);
                } else {
                    printf("Aviso: ID [%d] nao localizado.\n", id_entrada);
                }
                break;

            case 3:
                printf("Encerrando sessao...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}