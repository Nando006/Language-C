#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
  char nome[50];
  char email[200];
  int idade;
} Cliente;

typedef struct No {
  Cliente cliente;
  struct No *esq, *dir;
} No;

No *criarNo(Cliente cliente) {
  No *novo = (No *)malloc(sizeof(No));
  if(novo == NULL) {
    printf("Erro ao alocar memória\n");
    exit(1);
  }

  novo->cliente = cliente;
  novo->dir = novo->esq = NULL;

  return novo;
}

Cliente criarCliente() {
  Cliente cliente;

  printf("\n\nDigite o nome do cliente: ");
  scanf("%49[^\n]", cliente.nome);
  getchar();

  printf("\nDigite o e-mail do cliente: ");
  scanf("%199[^\n]", cliente.email);
  getchar();

  printf("\nDigite a idade do cliente: ");
  scanf("%d", &cliente.idade);
  getchar();

  return cliente;
}

No *adicionar(No *raiz, Cliente cliente) {
  if(raiz == NULL) return criarNo(cliente);

  // Comparação por nome
  if(strcmp(cliente.nome, raiz->cliente.nome) < 0) {
    raiz->esq = adicionar(raiz->esq, cliente); // Vai para a esquerda
  } else {
    raiz->dir = adicionar(raiz->dir, cliente); // Vai para a direita
  }

  return raiz;
}

No *remover(No *raiz, char *nome) {
  if(raiz == NULL) {
    return NULL;
  }

  if(strcmp(nome, raiz->cliente.nome) < 0) {
    raiz->esq = remover(raiz->esq, nome);
  } else if(strcmp(nome, raiz->cliente.nome) > 0) {
    raiz->dir = remover(raiz->dir, nome);
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

    raiz->cliente = temp->cliente;
    raiz->dir = remover(raiz->dir, temp->cliente.nome);
  }

  return raiz;
}

No *atualizar(No *raiz, char *nome, Cliente novo) {
  if(raiz == NULL) {
    return NULL;
  }

  if(strcmp(nome, raiz->cliente.nome) < 0) {
    raiz->esq = atualizar(raiz->esq, nome, novo);
  } else if(strcmp(nome, raiz->cliente.nome) > 0) {
    raiz->dir = atualizar(raiz->dir, nome, novo);
  } else {
    raiz->cliente = novo;
  }

  return raiz;
}

void listar(No *raiz) {
  if(raiz == NULL) {
    return;
  }

  listar(raiz->esq);
  printf("\n\nNome: %s\n", raiz->cliente.nome);
  printf("E-mail: %s\n", raiz->cliente.email);
  printf("Idade: %d\n", raiz->cliente.idade);
  listar(raiz->dir);
}

void buscar(No *raiz, char *nome) {
  if(raiz == NULL) {
    return;
  }

  buscar(raiz->esq, nome);
  if(strcmp(raiz->cliente.nome, nome) == 0) {
    printf("\n\nNome: %s\n", raiz->cliente.nome);
    printf("E-mail: %s\n", raiz->cliente.email);
    printf("Idade: %d\n", raiz->cliente.idade);
  }
  buscar(raiz->dir, nome);
}

void liberarArvore(No *raiz) {
  if(raiz != NULL) {
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
  }
}

int main() {
  setlocale(LC_ALL, "Portuguese");

  No *raiz = NULL;
  int opcao;
  char nome[50];
  Cliente cliente;

  while(1) {
    printf("\nMenu\n");
    printf("1. Adicionar Contato\n");
    printf("2. Remover Contato\n");
    printf("3. Atualizar Contato\n");
    printf("4. Listar Contatos\n");
    printf("5. Buscar Contato\n");
    printf("0. Sair\n");
    
    printf("\nEscolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

    switch(opcao) {
      case 1:
        cliente = criarCliente();
        raiz = adicionar(raiz, cliente);
        printf("\nContato adicionado com sucesso!\n");
        break;

      case 2:
        printf("\nDigite o nome do contato a ser removido: ");
        scanf("%49[^\n]", nome);
        getchar();
        raiz = remover(raiz, nome);
        printf("\nContato removido com sucesso!\n");
        break;

      case 3:
        printf("\nDigite o nome do contato a ser atualizado: ");
        scanf("%49[^\n]", nome);
        getchar();
        printf("\nDigite os novos dados do contato:\n");
        cliente = criarCliente();
        raiz = atualizar(raiz, nome, cliente);
        printf("\nContato atualizado com sucesso!\n");
        break;

      case 4:
        printf("\nLista de Contatos:\n");
        listar(raiz);
        break;

      case 5:
        printf("\nDigite o nome do contato a ser buscado: ");
        scanf("%49[^\n]", nome);
        getchar();
        printf("\nResultado da busca:\n");
        buscar(raiz, nome);
        break;

      case 0:
        liberarArvore(raiz);
        printf("\nPrograma encerrado.\n");
        return 0;

      default:
        printf("\nOpção inválida!\n");
        break;
    }
  }

  return 0;
}
