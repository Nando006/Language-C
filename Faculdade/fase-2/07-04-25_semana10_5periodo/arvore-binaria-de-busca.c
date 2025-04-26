#include <stdio.h>
#include <locale.h>

// Definindo a estrutura
typedef struct No {
  int valor;
  struct No *esq, *dir;
} No;

No *inserir(No *raiz, int valor) {
  if(raiz == NULL) {
    No* novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = novo->dir = NULL;
    return novo;
  }

  if(valor < raiz->valor) {
    raiz->esq = inserir(raiz->esq, valor);
  } else {
    raiz->dir = inserir(raiz->dir, valor);
  }

  return raiz;
}

No *buscar(No *raiz, int valor) {
  if(raiz == NULL || raiz->valor == valor) {
    return raiz;
  }

  if(valor < raiz->valor) {
    return buscar(raiz->esq, valor);
  } else {
    return buscar(raiz->dir, valor);
  }
}

No *remover(No *raiz, int valor) {
  if(raiz == NULL) return NULL;
  if(valor < raiz->valor) {
    raiz->esq = remover(raiz->esq, valor);
  } else if(valor > raiz->valor) {
    raiz->dir = remover(raiz->dir, valor);
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

    No* temp = menorValor(raiz->dir);
    raiz->valor = temp->valor;
    raiz->dir = remover(raiz->dir, temp->valor);
  }

  return raiz;
}

No *menorValor(No *raiz) {
  No *atual = raiz;
  while(atual && atual->esq != NULL) {
    atual = atual->esq;
  }

  return atual;
}

int main() {
  setlocale(LC_ALL, "Portuguese");

  return 0;
}