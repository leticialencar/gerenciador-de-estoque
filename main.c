#include <stdio.h>
#include <string.h>

#define max_produtos_na_lista 10
//quantidade de cadastros que o usuário pode realizar

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
        printf("Você não pode cadastrar mais itens, pois a quantidade de cadastros chegou ao limite!\n");
    } else {
        Produto produto;
        printf("\nIniciando o cadastro do produto\n");

        //loop para verificar se o código do produto ja existe
        while (1) {
            printf("Insira o código do produto (máximo 8 dígitos):\n");
            scanf("%s", produto.codigo);

            if (strlen(produto.codigo) > 8) {
                printf("O código do produto deve ter no máximo 8 dígitos!\n");
                continue;
            }

            //verifica se o codigo que o usuario digitou já existe
            int i;
            for (i = 0; i < total_cadastros; i++) {
                if (strcmp(produto.codigo, produtos[i].codigo) == 0) {
                    printf("Já existe um prouto com esse código! Digite outro.\n");
                    break;
                }
            }

            if (i == total_cadastros) {
                //se o codigo for diferente
                break;
            }
        }

        printf("Insira a descrição do produto:\n");
        scanf(" %[^\n]", produto.descricao); 
        //[^\n] para ler toda descricao que o usuario digitar, junto com os espacos

        printf("Insira a quantidade de produtos no estoque:\n");
        while (scanf("%d", &produto.quantidade) != 1 || produto.quantidade < 0) {
            printf("Quantidade inválida! Por favor, digite apenas números inteiros positivos:\n");

            while (getchar() != '\n');
            //limpa o que o usuario digitou anteriormente e pede para que ele digite novamente
        }

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
    //indice que vai guardar a posicao do produto na lista, ele comeca como -1 pra indicar que nao foi encontrado nada ainda

    for (int i = 0; i < total_cadastros; i++) {
        if (strcmp(codigo, lista[i]) == 0) {
            //compara o codigo que o usuario digitou (codigo) com o codigo do produto ja cadastrado (lista[i])
            index = i;
            //guarda a posicao que o produto esta
            break;
        }
    }

    if (index == -1) {
        //caso o indice continue como -1
        printf("Produto com código %s não encontrado!\n", codigo);
        return;
    }

    for (int i = index; i < total_cadastros - 1; i++) {
        //for que comeca na posicao onde esta o produto que vai ser removido e vai ate o penultimo item da lista
        produtos[i] = produtos[i + 1];
        //move o produto da proxima posicao pra cima
        strcpy(lista[i], lista[i + 1]);
        //move o codigo do proximo produto para a posicao atual
    }

    total_cadastros--;
    //diminui o total de cadastros pq agora tem um a menos

    printf("Produto com código %s removido com sucesso!\n", codigo);
}

void ExibirProdutos() {
    if (total_cadastros == 0) {
        printf("\nNenhum produto cadastrado.\n");
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
        printf("Por gentileza, escolha a opção que você deseja realizar: ");
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
