#include <stdio.h>
#include <string.h>

#define max_produtos_na_lista 10

typedef struct Produto {
    char codigo[9];
    char descricao[100];
    int quantidade;
} Produto;

Produto produtos[max_produtos_na_lista];  
char lista[max_produtos_na_lista][9];  
int total_cadastros = 0;  

void CadastrarProduto() {
    if (total_cadastros >= max_produtos_na_lista) {
        printf("Você não pode cadastrar mais itens!\n");
    } else {
        Produto produto;
        printf("\nIniciando o cadastro do produto\n");

        printf("Insira o código do produto (máximo 8 caracteres):\n");
        scanf("%8s", produto.codigo); 

        printf("Insira a descrição do produto:\n");
        scanf(" %[^\n]", produto.descricao); 

        printf("Insira a quantidade de produtos no estoque:\n");
        scanf("%d", &produto.quantidade); 

        produtos[total_cadastros] = produto;

        for (int i = 0; i < 9; i++) {
            lista[total_cadastros][i] = produto.codigo[i]; 
        }

        total_cadastros++;

        printf("Produto cadastrado com sucesso!\n");
        printf("Código: %s\n", produto.codigo);
        printf("Descrição: %s\n", produto.descricao);
        printf("Quantidade: %d\n", produto.quantidade);
    }
}


void RemoverProduto(char codigo[]) {
    int index = -1;

    for (int i = 0; i < total_cadastros; i++) {
        int j;
        for (j = 0; j < 9; j++) {
            if (codigo[j] != lista[i][j]) {
                break;
            }
        }
        if (j == 9) {  
            index = i; 
            break;
        }
    }

    if (index == -1) {
        printf("Produto com código %s não encontrado!\n", codigo);
        return;
    }

    for (int i = index; i < total_cadastros - 1; i++) {
        produtos[i] = produtos[i + 1];  
        for (int j = 0; j < 9; j++) {
            lista[i][j] = lista[i + 1][j];  
        }
    }

    total_cadastros--;

    printf("Produto com código %s removido com sucesso!\n", codigo);
}

void ExibirProdutos() {
    if (total_cadastros == 0) {
        printf("Nenhum produto cadastrado.\n");
    } else {
        for (int i = 0; i < total_cadastros; i++) {
            printf("\nProduto %d:\n", i + 1);
            printf("Código: %s\n", produtos[i].codigo);
            printf("Descrição: %s\n", produtos[i].descricao);
            printf("Quantidade: %d\n", produtos[i].quantidade);
        }
    }
}

int main() {
    int opcao;
    do {
        printf("\nSistema de Gerenciamento de Estoque\n");
        printf("1. Adicionar Produto\n");
        printf("2. Remover Produto\n");
        printf("3. Exibir Produtos\n");
        printf("4. Sair\n");
        printf("Escolha a opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                CadastrarProduto();
                break;
            case 2:
                {
                    char codigo[9];
                    printf("Insira o código do produto que deseja remover: ");
                    scanf("%8s", codigo);
                    RemoverProduto(codigo);
                }
                break;
            case 3:
                ExibirProdutos();
                break;
            case 4:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opcao != 4);

    return 0;
}
