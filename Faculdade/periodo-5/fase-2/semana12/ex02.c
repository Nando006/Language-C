// 2 - Implemente uma estrutura de dados que leia números inteiros e organize-os utilizando uma árvore AVL

// 30, 40, 24, 58, 48, 26, 11, 13, 14
// 20,15,25,10,30,24,17,12,5,3
// 40, 30, 50, 45, 55, 52
// 20, 15, 25, 12, 17, 24, 30, 10, 14, 13
// 20, 15, 25, 12, 17, 30, 26

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore AVL
typedef struct No {
    int valor;
    struct No *esquerda;
    struct No *direita;
    int altura;
} No;

// Função para criar um novo nó
No* criarNo(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->altura = 1;
    return novo;
}

// Função para obter a altura de um nó
int altura(No* no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

// Função para obter o máximo entre dois números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para obter o fator de balanceamento de um nó
int fatorBalanceamento(No* no) {
    if (no == NULL)
        return 0;
    return altura(no->esquerda) - altura(no->direita);
}

// Função para atualizar a altura de um nó
void atualizarAltura(No* no) {
    if (no != NULL)
        no->altura = 1 + max(altura(no->esquerda), altura(no->direita));
}

// Rotação simples à direita
No* rotacaoDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    atualizarAltura(y);
    atualizarAltura(x);

    return x;
}

// Rotação simples à esquerda
No* rotacaoEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    atualizarAltura(x);
    atualizarAltura(y);

    return y;
}

// Função para inserir um valor na árvore AVL
No* inserir(No* no, int valor) {
    // Inserção normal de BST
    if (no == NULL)
        return criarNo(valor);

    if (valor < no->valor)
        no->esquerda = inserir(no->esquerda, valor);
    else if (valor > no->valor)
        no->direita = inserir(no->direita, valor);
    else
        return no; // Valores duplicados não são permitidos

    // Atualizar altura do nó atual
    atualizarAltura(no);

    // Obter o fator de balanceamento
    int balanceamento = fatorBalanceamento(no);

    // Casos de desbalanceamento

    // Rotação simples à direita
    if (balanceamento > 1 && valor < no->esquerda->valor)
        return rotacaoDireita(no);

    // Rotação simples à esquerda
    if (balanceamento < -1 && valor > no->direita->valor)
        return rotacaoEsquerda(no);

    // Rotação dupla à esquerda
    if (balanceamento > 1 && valor > no->esquerda->valor) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Rotação dupla à direita
    if (balanceamento < -1 && valor < no->direita->valor) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

// Função para imprimir a árvore em ordem
void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        emOrdem(raiz->direita);
    }
}

// Função para imprimir a árvore em pré-ordem
void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

// Função para imprimir a árvore em pós-ordem
void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

// Função para liberar a memória da árvore
void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

int main() {
    No* raiz = NULL;
    int valores[] = {30, 40, 24, 58, 48, 26, 11, 13, 14};
    int n = sizeof(valores) / sizeof(valores[0]);

    printf("Inserindo valores na árvore AVL...\n");
    for (int i = 0; i < n; i++) {
        raiz = inserir(raiz, valores[i]);
    }

    printf("\nPercurso em ordem: ");
    emOrdem(raiz);
    printf("\n");

    printf("Percurso em pré-ordem: ");
    preOrdem(raiz);
    printf("\n");

    printf("Percurso em pós-ordem: ");
    posOrdem(raiz);
    printf("\n");

    liberarArvore(raiz);
    return 0;
}