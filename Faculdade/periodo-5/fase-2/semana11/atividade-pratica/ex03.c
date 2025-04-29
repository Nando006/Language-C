// Agenda de contato inteligente
// Contexo: Aplicativos de agenda precisam organizar contatos de forma eficiente para permitir buscas rápidas e ordenadas
// Tarefa: Crie uma ABB para gerenciar contatos, onde cada nó contém:
// - Nome completo
// - Número de telefone
// - Endereço de e-mail
// A árvore deve ser ordenada pelo nome completo

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

typedef struct {
  char nome[50];
  char telefone[20];
  char email[200];
} Contato;

typedef struct No {
  Contato contato;
  struct No *esq, *dir;
} No;

No *criarNo(Contato contato) {
  No *novo = (No *)malloc(sizeof(No));
  if(novo == NULL) {
    printf("Erro ao alocar memória!\n");
    exit(1);
  }

  novo->contato = contato;
  novo->esq = novo->dir = NULL;
  return novo;
}

Contato criarContato() {
  Contato novoContato;

  printf("Digite o nome: ");
  scanf("%49[^\n]", novoContato.nome);
  getchar();

  printf("Digite o telefone: ");
  scanf("%19[^\n]", novoContato.telefone);
  getchar();

  printf("Digite o e-mail: ");
  scanf("%199[^\n]", novoContato.email);
  getchar();

  return novoContato;
}

No *adicionar(No *raiz, Contato contato) {
  if(raiz == NULL) {
    return criarNo(contato);
  }

  if(strcmp(contato.nome, raiz->contato.nome) < 0) {
    raiz->esq = adicionar(raiz->esq, contato);
  } else if(strcmp(contato.nome, raiz->contato.nome) > 0) {
    raiz->dir = adicionar(raiz->dir, contato);
  }

  return raiz;
}

No *remover(No *raiz, char *nome) {
  if(raiz == NULL) {
    return NULL;
  }

  if(strcmp(nome, raiz->contato.nome) < 0) {
    raiz->esq = remover(raiz->esq, nome);
  } else if(strcmp(nome, raiz->contato.nome) > 0) {
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

    raiz->contato = temp->contato;
    raiz->dir = remover(raiz->dir, temp->contato.nome);
  }

  return raiz;
}

No *atualizar(No *raiz, char *nome, Contato novoContato) {
  if(raiz == NULL) {
    return NULL;
  }

  if(strcmp(nome, raiz->contato.nome) < 0) {
    raiz->esq = atualizar(raiz->esq, nome, novoContato);
  } else if(strcmp(nome, raiz->contato.nome) > 0) {
    raiz->dir = atualizar(raiz->dir, nome, novoContato);
  } else {
    raiz->contato = novoContato;
  }

  return raiz;
}

void buscar(No *raiz, char *nome) {
  if(raiz == NULL) {
    return;
  }

  buscar(raiz->esq, nome);

  if(strcmp(raiz->contato.nome, nome) == 0) {
    printf("Nome: %s\n", raiz->contato.nome);
    printf("Telefone: %s\n", raiz->contato.telefone);
    printf("E-mail: %s\n", raiz->contato.email);
  }

  buscar(raiz->dir, nome);
}

void listar(No *raiz) {
  if(raiz == NULL) {
    return;
  }

  listar(raiz->esq);

  printf("Nome: %s\n", raiz->contato.nome);
  printf("Telefone: %s\n", raiz->contato.telefone);
  printf("E-mail: %s\n", raiz->contato.email);

  listar(raiz->dir);
}

// Implementar uma função de autocompletar para nome do contato
void autoCompletar(No *raiz, char *prefixo) {
  if(raiz == NULL) {
    return;
  }

  if(strncmp(raiz->contato.nome, prefixo, strlen(prefixo)) == 0) {
    printf("Nome: %s\n", raiz->contato.nome);
  } 

  autoCompletar(raiz->esq, prefixo);
  autoCompletar(raiz->dir, prefixo);
}

int main() {
  setlocale(LC_ALL, "Portuguese");

  No *raiz = NULL;
  int opcao;
  char nome[50];
  Contato novoContato;
  char prefixo[50];

  while(1) {
    printf("\nMenu:\n");
    printf("1. Adicionar contato\n");
    printf("2. Remover contato\n");
    printf("3. Atualizar contato\n");
    printf("4. Buscar contato\n");
    printf("5. Listar contatos\n");
    printf("6. Autocompletar\n");
    printf("7. Sair\n");

    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

    switch(opcao) {
      case 1:
        printf("Digite o nome: ");
        scanf("%49[^\n]", novoContato.nome);
        getchar();

        printf("Digite o telefone: ");
        scanf("%19[^\n]", novoContato.telefone);
        getchar();

        printf("Digite o e-mail: ");
        scanf("%199[^\n]", novoContato.email);
        getchar();

        raiz = adicionar(raiz, novoContato);
        printf("Contato adicionado com sucesso!\n");
      break;
      case 2:
        printf("Digite o nome do contato a ser removido: ");
        scanf("%49[^\n]", nome);
        getchar();

        raiz = remover(raiz, nome);
        printf("Contato removido com sucesso!\n");
      break;
      case 3:
        printf("Digite o nome do contato a ser atualizado: ");
        scanf("%49[^\n]", nome);
        getchar();

        printf("Digite o novo nome: ");
        scanf("%49[^\n]", novoContato.nome);
        getchar();  

        printf("Digite o novo telefone: ");
        scanf("%19[^\n]", novoContato.telefone);
        getchar();

        printf("Digite o novo e-mail: "); 
        scanf("%199[^\n]", novoContato.email);
        getchar();

        raiz = atualizar(raiz, nome, novoContato);
        printf("Contato atualizado com sucesso!\n");
      break;
      case 4:
        printf("Digite o nome do contato a ser buscado: ");
        scanf("%49[^\n]", nome);
        getchar();

        printf("Buscando contato...\n");
        buscar(raiz, nome);
      break;
      case 5:
        printf("Listando contatos...\n");
        listar(raiz);
      break;
      case 6:
        printf("Digite o prefixo para autocompletar: ");
        scanf("%49[^\n]", prefixo);
        getchar();

        printf("Autocompletar...\n");
        autoCompletar(raiz, prefixo);
      break;
      case 7:
        printf("Saindo...\n");
        free(raiz);
        return 0;
      break;
      default:
        printf("Opção inválida!\n");
      break;
    }
  }

  return 0;
}

