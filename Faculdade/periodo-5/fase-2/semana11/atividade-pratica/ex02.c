// Gerenciamento de Estoque em Tempo Real
// Contexto: Empresa de e-commerce precisa gerenciar estoques de produtos em tempo real para evitar vendas de itens esgotados.
// Tarefas: Desenvolva uma ABB para gerenciar o estoque de produtos
// Cada nó contém:
// ? ID do produto 
// ? Nome do produto 
// ? Quantidade em estoque 
// ? Preço 
// ? A árvore deve ser ordenada pelo ID do produto. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Produto{
  int id;
  char nome[50];
  int quantidade;
  float preco;
} Produto;

typedef struct No {
  Produto produto;
  struct No *esq, *dir;
} No;

No *criarNo(Produto produto) {
  No *novo = (No*)malloc(sizeof(No));
  novo->produto = produto;
  novo->esq = novo->dir = NULL;
  return novo;
}

Produto criarProduto(int *idProduto) {
  Produto novoProduto;

  // Incrementa o ID para o próximo produto
  (*idProduto)++;
  novoProduto.id = *idProduto;

  printf("\nDigite o nome do produto: ");
  scanf("%49[^\n]", novoProduto.nome);
  getchar();

  printf("Digite a quantidade em estoque: ");
  scanf("%d", &novoProduto.quantidade);
  getchar();

  printf("Digite o preço do produto: ");
  scanf("%f", &novoProduto.preco);
  getchar();

  return novoProduto;
}

No *adicionar(No *raiz, Produto produto) {
  if(raiz == NULL) {
    return criarNo(produto);
  }

  if(produto.id < raiz->produto.id) {
    raiz->esq = adicionar(raiz->esq, produto);
  } else if(produto.id > raiz->produto.id) {
    raiz->dir = adicionar(raiz->dir, produto);
  }

  return raiz;
}

No *remover(No *raiz, int id) {
  if(raiz == NULL) {
    return NULL;
  }

  if(id < raiz->produto.id) {
    raiz->esq = remover(raiz->esq, id);
  } else if(id > raiz->produto.id) {
    raiz->dir = remover(raiz->dir, id);
  } else {
    if(raiz->esq == NULL) {
      No *temp = raiz->dir;
      free(raiz);
      return temp;
    } else if(raiz->dir == NULL) {
      No *temp = raiz->esq;
      free(raiz);
      return temp;
    }

    No *temp = raiz->dir;
    while(temp->esq != NULL) {
      temp = temp->esq;
    }

    raiz->produto = temp->produto;
    raiz->dir = remover(raiz->dir, temp->produto.id);
  }

  return raiz;
}

void listar(No *raiz, int limite, int *encontrado) {
  if(raiz == NULL) return;

  // Visita o lado esquerdo primeiro
  listar(raiz->esq, limite, encontrado);
   
  // Processa o nó atual - mostra apenas produtos com estoque abaixo do limite
  if(raiz->produto.quantidade < limite) {
    printf("\n?? ESTOQUE BAIXO - \nProduto ID: %d\nNome: %s\nQuantidade: %d\nPreço: R$%.2f\n",
           raiz->produto.id, raiz->produto.nome, raiz->produto.quantidade, raiz->produto.preco);
    *encontrado = 1; // Marca que encontrou pelo menos um produto
  }
   
  // Visita o lado direito depois
  listar(raiz->dir, limite, encontrado);
}

No *buscar(No *raiz, int id) {
  if(raiz == NULL || raiz->produto.id == id) {
    return raiz;
  }

  if(id < raiz->produto.id) {
    return buscar(raiz->esq, id);
  }

  return buscar(raiz->dir, id);
}

int main() {
  setlocale(LC_ALL, "Portuguese");

  No *raiz = NULL;
  int opcao, id = 0, limite;  // Inicializa id com 0
  Produto produto;

  while(1) {
    printf("1. Adicionar Produto\n");
    printf("2. Remover Produto\n");
    printf("3. Listar Produtos com Estoque Baixo\n");
    printf("4. Buscar Produto por ID\n");
    printf("5. Sair\n");
    printf("\nEscolha uma opção: ");
    scanf(" %d", &opcao);
    getchar();

    switch(opcao) {
      case 1:
        
        produto = criarProduto(&id);
        raiz = adicionar(raiz, produto);
        printf("\n\nProduto adicionado com sucesso!\n");
      break;

      case 2:
        printf("Digite o ID do produto a ser removido: ");
        scanf("%d", &id);
        getchar(); // Limpa o buffer
        raiz = remover(raiz, id);
        printf("Produto removido com sucesso!\n");
      break;
      
      case 3:
        printf("Digite o limite de estoque para alertas: ");
        scanf("%d", &limite);
        getchar(); // Limpa o buffer
        printf("\nProdutos com estoque abaixo de %d:\n", limite);
        int encontrado = 0;
        listar(raiz, limite, &encontrado);
        if(!encontrado) {
          printf("Nenhum produto encontrado com estoque abaixo de %d.\n", limite);
        }
      break;

      case 4:
        printf("Digite o ID do produto a ser buscado: ");
        scanf("%d", &id);
        getchar(); // Limpa o buffer
        No *resultado = buscar(raiz, id);
        if(resultado != NULL) {
          printf("Produto encontrado:\n");
          printf("ID: %d\nNome: %s\nQuantidade: %d\nPreço: R$%.2f\n",
                 resultado->produto.id, resultado->produto.nome, resultado->produto.quantidade, resultado->produto.preco);
        } else {
          printf("Produto não encontrado!\n");
        }
      break;
      
      case 5:
        printf("Saindo do programa...\n");
        exit(0);
      break;
      
      default:
        printf("Opção inválida!\n");
      break;
    }
  }

  return 0;
}