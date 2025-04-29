#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Struct Cliente
typedef struct {
  char nome[50];
  char email[200];
  int idade;
} Cliente;

// Struct Nó da AVL
typedef struct No {
  Cliente cliente;
  struct No *esq, *dir;
  int altura;
} No;

// Funções auxiliares
int altura(No *no) {
  return no ? no->altura : 0;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

void atualizarAltura(No *no) {
  if (no) no->altura = 1 + max(altura(no->esq), altura(no->dir));
}

int fatorBalanceamento(No *no) {
  return no ? altura(no->esq) - altura(no->dir) : 0;
}

// Rotações
No *rotacaoDireita(No *y) {
  No *x = y->esq;
  No *T2 = x->dir;

  x->dir = y;
  y->esq = T2;

  atualizarAltura(y);
  atualizarAltura(x);

  return x;
}

No *rotacaoEsquerda(No *x) {
  No *y = x->dir;
  No *T2 = y->esq;

  y->esq = x;
  x->dir = T2;

  atualizarAltura(x);
  atualizarAltura(y);

  return y;
}

No *balancear(No *no) {
  atualizarAltura(no);
  int fb = fatorBalanceamento(no);

  // Esquerda pesada
  if (fb > 1) {
    if (fatorBalanceamento(no->esq) < 0) {
      no->esq = rotacaoEsquerda(no->esq);
    }
    return rotacaoDireita(no);
  }

  // Direita pesada
  if (fb < -1) {
    if (fatorBalanceamento(no->dir) > 0) {
      no->dir = rotacaoDireita(no->dir);
    }
    return rotacaoEsquerda(no);
  }

  return no;
}

// Criação e inserção
No *criarNo(Cliente cliente) {
  No *novo = malloc(sizeof(No));
  novo->cliente = cliente;
  novo->esq = novo->dir = NULL;
  novo->altura = 1;
  return novo;
}

No *inserir(No *raiz, Cliente cliente) {
  if (!raiz) return criarNo(cliente);

  if (strcmp(cliente.nome, raiz->cliente.nome) < 0)
    raiz->esq = inserir(raiz->esq, cliente);
  else
    raiz->dir = inserir(raiz->dir, cliente);

  return balancear(raiz);
}

// Remoção
No *minValorNo(No *no) {
  while (no->esq) no = no->esq;
  return no;
}

No *remover(No *raiz, char *nome) {
  if (!raiz) return NULL;

  if (strcmp(nome, raiz->cliente.nome) < 0)
    raiz->esq = remover(raiz->esq, nome);
  else if (strcmp(nome, raiz->cliente.nome) > 0)
    raiz->dir = remover(raiz->dir, nome);
  else {
    if (!raiz->esq || !raiz->dir) {
      No *temp = raiz->esq ? raiz->esq : raiz->dir;
      free(raiz);
      return temp;
    }
    No *temp = minValorNo(raiz->dir);
    raiz->cliente = temp->cliente;
    raiz->dir = remover(raiz->dir, temp->cliente.nome);
  }

  return balancear(raiz);
}

// Atualizar dados
No *atualizar(No *raiz, char *nome, Cliente novo) {
  if (!raiz) return NULL;

  if (strcmp(nome, raiz->cliente.nome) < 0)
    raiz->esq = atualizar(raiz->esq, nome, novo);
  else if (strcmp(nome, raiz->cliente.nome) > 0)
    raiz->dir = atualizar(raiz->dir, nome, novo);
  else
    raiz->cliente = novo;

  return balancear(raiz);
}

// Percursos
void emOrdem(No *raiz) {
  if (raiz) {
    emOrdem(raiz->esq);
    printf("\nNome: %s\nEmail: %s\nIdade: %d\n", raiz->cliente.nome, raiz->cliente.email, raiz->cliente.idade);
    emOrdem(raiz->dir);
  }
}

void preOrdem(No *raiz) {
  if (raiz) {
    printf("\nNome: %s\nEmail: %s\nIdade: %d\n", raiz->cliente.nome, raiz->cliente.email, raiz->cliente.idade);
    preOrdem(raiz->esq);
    preOrdem(raiz->dir);
  }
}

void posOrdem(No *raiz) {
  if (raiz) {
    posOrdem(raiz->esq);
    posOrdem(raiz->dir);
    printf("\nNome: %s\nEmail: %s\nIdade: %d\n", raiz->cliente.nome, raiz->cliente.email, raiz->cliente.idade);
  }
}

// Buscar
void buscar(No *raiz, char *nome) {
  if (!raiz) {
    printf("\nCliente não encontrado.\n");
    return;
  }

  int cmp = strcmp(nome, raiz->cliente.nome);
  if (cmp == 0) {
    printf("\nNome: %s\nEmail: %s\nIdade: %d\n", raiz->cliente.nome, raiz->cliente.email, raiz->cliente.idade);
  } else if (cmp < 0) {
    buscar(raiz->esq, nome);
  } else {
    buscar(raiz->dir, nome);
  }
}

// Liberar memória
void liberarArvore(No *raiz) {
  if (raiz) {
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
  }
}

// Entrada de dados
Cliente criarCliente() {
  Cliente cliente;
  printf("\nDigite o nome do cliente: ");
  scanf(" %49[^\n]", cliente.nome);
  getchar();
  printf("Digite o email do cliente: ");
  scanf(" %199[^\n]", cliente.email);
  getchar();
  printf("Digite a idade do cliente: ");
  scanf("%d", &cliente.idade);
  getchar();
  return cliente;
}

// Main
int main() {
  setlocale(LC_ALL, "Portuguese");
  No *raiz = NULL;
  int opcao;
  char nome[50];

  while (1) {
    printf("\nMenu:\n1. Inserir\n2. Remover\n3. Atualizar\n4. Buscar\n5. Em ordem\n6. Pré-ordem\n7. Pós-ordem\n0. Sair\nOpção: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
      case 1:
        raiz = inserir(raiz, criarCliente());
        break;
      case 2:
        printf("\nNome do cliente para remover: ");
        scanf(" %49[^\n]", nome);
        getchar();
        raiz = remover(raiz, nome);
        break;
      case 3:
        printf("\nNome do cliente para atualizar: ");
        scanf(" %49[^\n]", nome);
        getchar();
        raiz = atualizar(raiz, nome, criarCliente());
        break;
      case 4:
        printf("\nNome do cliente para buscar: ");
        scanf(" %49[^\n]", nome);
        getchar();
        buscar(raiz, nome);
        break;
      case 5:
        emOrdem(raiz);
        break;
      case 6:
        preOrdem(raiz);
        break;
      case 7:
        posOrdem(raiz);
        break;
      case 0:
        liberarArvore(raiz);
        return 0;
      default:
        printf("Opção inválida!\n");
    }
  }

  return 0;
}
