// Sistema de recomendação de filmes
// Implemente uma ABB para armazenar filmes

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct {
  char nome[50];
  char genero[50];
  int classificacaoIndicativa;
  float pontuacaoMedia;
} Filme;

typedef struct No {
  Filme filme;
  struct No *esq, *dir;
} No;

No *criarNo(Filme filme) {
  No *novo = (No*)malloc(sizeof(No));
  novo->filme = filme;
  novo->esq = novo->dir = NULL;
  return novo;
}

Filme criarFilme() {
  Filme novoFilme;
  
  printf("Digite o nome do filme: ");
  fgets(novoFilme.nome, 49, stdin);
  novoFilme.nome[strcspn(novoFilme.nome, "\n")] = '\0'; // Remove o \n do final

  printf("Digite o gênero do filme: ");
  fgets(novoFilme.genero, 49, stdin);
  novoFilme.genero[strcspn(novoFilme.genero, "\n")] = '\0'; // Remove o \n do final

  printf("Digite a classificação indicativa do filme: ");
  scanf("%d", &novoFilme.classificacaoIndicativa);
  getchar(); // Limpa o buffer

  printf("Digite a pontuação média do filme: ");
  scanf("%f", &novoFilme.pontuacaoMedia);
  getchar(); // Limpa o buffer

  return novoFilme;
}

No *inserir(No *raiz, Filme filme) {
  if(raiz == NULL) return criarNo(filme);

  if(filme.pontuacaoMedia > raiz->filme.pontuacaoMedia) {
    raiz->dir = inserir(raiz->dir, filme);
  } else {
    raiz->esq = inserir(raiz->esq, filme);
  }

  return raiz;
}

void buscarFilme(No *raiz, char genero[]) {
  if(raiz == NULL) {
    return;
  }

  // Busca em toda a árvore
  if(strcmp(raiz->filme.genero, genero) == 0) {
    printf("Filme encontrado: %s (Gênero: %s, Pontuação: %.1f)\n", 
           raiz->filme.nome, raiz->filme.genero, raiz->filme.pontuacaoMedia);
  }

  // Visita ambos os lados da árvore
  buscarFilme(raiz->esq, genero);
  buscarFilme(raiz->dir, genero);
}

void listarFilmesTop5Pontuacao(No *raiz, int *contador) {
  if(raiz == NULL || *contador >= 5) return;
  
  listarFilmesTop5Pontuacao(raiz->dir, contador);

  if(*contador < 5) {
    printf("%d. %s - Pontuação: %.2f\n", *contador + 1, raiz->filme.nome, raiz->filme.pontuacaoMedia);
    (*contador)++;
  }

  listarFilmesTop5Pontuacao(raiz->esq, contador);
}

void atualizarPontuacao(No *raiz, char nome[], float novaPontuacao) {
  if(raiz == NULL) return;

  if(strcmp(raiz->filme.nome, nome) == 0) {
    raiz->filme.pontuacaoMedia = novaPontuacao;
  } else if(strcmp(raiz->filme.nome, nome) < 0) {
    atualizarPontuacao(raiz->dir, nome, novaPontuacao);
  } else {
    atualizarPontuacao(raiz->esq, nome, novaPontuacao);
  }
}

int main() {
  setlocale(LC_ALL, "Portuguese");

  No *raiz = NULL;
  int opcao, contador = 0;
  char nome[50];
  float novaPontuacao;

  while(1) {
    printf("\nSistema de Recomendação de Filmes\n");
    printf("1. Adicionar filme\n");
    printf("2. Buscar filme por gênero\n");
    printf("3. Listar top 5 filmes com maior pontuação\n");
    printf("4. Atualizar pontuação de um filme\n");
    printf("5. Sair\n");
    printf("\nEscolha uma opção: ");
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer após ler a opção

    switch(opcao) {
      case 1:
        raiz = inserir(raiz, criarFilme());
      break;

      case 2:
        printf("Digite o gênero do filme: ");
        fgets(nome, 49, stdin);
        nome[strcspn(nome, "\n")] = '\0'; // Remove o \n do final
        buscarFilme(raiz, nome);
      break;

      case 3:
        contador = 0; // Reinicia o contador antes de listar
        printf("\nTop 5 filmes com maior pontuação:\n");
        listarFilmesTop5Pontuacao(raiz, &contador);
        if (contador == 0) {
          printf("Nenhum filme cadastrado ainda.\n");
        }
      break;

      case 4:
        printf("Digite o nome do filme: ");
        fgets(nome, 49, stdin);
        nome[strcspn(nome, "\n")] = '\0'; // Remove o \n do final
        
        printf("Digite a nova pontuação: ");
        scanf("%f", &novaPontuacao);
        getchar(); // Limpa o buffer
        
        atualizarPontuacao(raiz, nome, novaPontuacao);
      break;

      case 5:
        printf("\n\nSaindo...\n");
        free(raiz);
        exit(0);
      break;

      default:
        printf("Opção inválida! Tente novamente.\n");
      break;
    }
  }

  return 0;
}