# Documentação: Implementação de Árvores Binárias de Busca (ABB)

## Introdução

Uma Árvore Binária de Busca (ABB) é uma estrutura de dados hierárquica onde cada nó possui no máximo dois filhos (esquerdo e direito). A característica fundamental de uma ABB é que, para qualquer nó:
- Todos os nós na subárvore esquerda possuem valores menores que o nó atual
- Todos os nós na subárvore direita possuem valores maiores que o nó atual

Nos exemplos implementados, utilizamos ABBs para:
1. Sistema de recomendação de filmes (ordenados por pontuação)
2. Sistema de gerenciamento de estoque (ordenados por ID do produto)

## Estruturas de Dados

### Exemplo 1: Sistema de Recomendação de Filmes

```c
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
```

### Exemplo 2: Sistema de Gerenciamento de Estoque

```c
typedef struct Produto {
  int id;
  char nome[50];
  int quantidade;
  float preco;
} Produto;

typedef struct No {
  Produto produto;
  struct No *esq, *dir;
} No;
```

## Operações Básicas Implementadas

### 1. Criação de Nó

```c
No *criarNo(Tipo dado) {
  No *novo = (No*)malloc(sizeof(No));
  novo->dado = dado;
  novo->esq = novo->dir = NULL;
  return novo;
}
```

Esta função aloca memória para um novo nó, inicializa seus dados e retorna um ponteiro para o nó criado.

### 2. Inserção

```c
No *inserir(No *raiz, Tipo dado) {
  if(raiz == NULL) return criarNo(dado);
  
  if(dado.chave < raiz->dado.chave) {
    raiz->esq = inserir(raiz->esq, dado);
  } else if(dado.chave > raiz->dado.chave) {
    raiz->dir = inserir(raiz->dir, dado);
  }
  
  return raiz;
}
```

A inserção é implementada recursivamente:
- Se a árvore estiver vazia, cria um novo nó
- Se a chave for menor que a raiz, insere na subárvore esquerda
- Se a chave for maior que a raiz, insere na subárvore direita

### 3. Busca

```c
No *buscar(No *raiz, ChaveTipo chave) {
  if(raiz == NULL || raiz->dado.chave == chave) {
    return raiz;
  }
  
  if(chave < raiz->dado.chave) {
    return buscar(raiz->esq, chave);
  }
  
  return buscar(raiz->dir, chave);
}
```

A busca também é implementada de forma recursiva:
- Se a raiz for nula ou contiver a chave, retorna a raiz
- Se a chave for menor, busca na subárvore esquerda
- Se a chave for maior, busca na subárvore direita

### 4. Remoção

```c
No *remover(No *raiz, ChaveTipo chave) {
  if(raiz == NULL) return NULL;
  
  if(chave < raiz->dado.chave) {
    raiz->esq = remover(raiz->esq, chave);
  } else if(chave > raiz->dado.chave) {
    raiz->dir = remover(raiz->dir, chave);
  } else {
    // Caso 1: Nó folha ou com apenas um filho
    if(raiz->esq == NULL) {
      No *temp = raiz->dir;
      free(raiz);
      return temp;
    } else if(raiz->dir == NULL) {
      No *temp = raiz->esq;
      free(raiz);
      return temp;
    }
    
    // Caso 2: Nó com dois filhos
    // Encontra o sucessor inorder (menor elemento na subárvore direita)
    No *temp = raiz->dir;
    while(temp->esq != NULL) {
      temp = temp->esq;
    }
    
    // Copia o conteúdo do sucessor para este nó
    raiz->dado = temp->dado;
    
    // Remove o sucessor
    raiz->dir = remover(raiz->dir, temp->dado.chave);
  }
  
  return raiz;
}
```

A remoção é a operação mais complexa, com três casos:
1. **Nó folha**: Simplesmente remove o nó
2. **Nó com um filho**: Remove o nó e conecta seu filho ao pai
3. **Nó com dois filhos**: Substitui pelo sucessor in-order (menor valor na subárvore direita)

### 5. Travessias (Percursos)

#### In-Order (Em-ordem)
```c
void percorrerEmOrdem(No *raiz) {
  if(raiz == NULL) return;
  
  percorrerEmOrdem(raiz->esq);
  processar(raiz->dado);
  percorrerEmOrdem(raiz->dir);
}
```

Visita os nós na ordem: esquerda → raiz → direita.
Útil para obter valores em ordem crescente.

#### Pre-Order (Pré-ordem)
```c
void percorrerPreOrdem(No *raiz) {
  if(raiz == NULL) return;
  
  processar(raiz->dado);
  percorrerPreOrdem(raiz->esq);
  percorrerPreOrdem(raiz->dir);
}
```

Visita os nós na ordem: raiz → esquerda → direita.
Útil para copiar a estrutura da árvore.

#### Post-Order (Pós-ordem)
```c
void percorrerPosOrdem(No *raiz) {
  if(raiz == NULL) return;
  
  percorrerPosOrdem(raiz->esq);
  percorrerPosOrdem(raiz->dir);
  processar(raiz->dado);
}
```

Visita os nós na ordem: esquerda → direita → raiz.
Útil para liberar memória da árvore.

## Aplicações Implementadas

### 1. Sistema de Recomendação de Filmes

- **Ordenação**: Filmes são ordenados por pontuação média (maior para menor)
- **Operações**:
  - Adicionar filme
  - Buscar filme por gênero
  - Listar top 5 filmes com maior pontuação
  - Atualizar pontuação de um filme

### 2. Sistema de Gerenciamento de Estoque

- **Ordenação**: Produtos são ordenados por ID
- **Operações**:
  - Adicionar produto
  - Remover produto
  - Listar produtos com estoque abaixo de um limite
  - Buscar produto por ID

## Complexidade das Operações

Para uma ABB não balanceada:

| Operação | Caso Médio | Pior Caso |
|----------|------------|-----------|
| Inserção | O(log n)   | O(n)      |
| Busca    | O(log n)   | O(n)      |
| Remoção  | O(log n)   | O(n)      |

O pior caso ocorre quando a árvore está desbalanceada (similar a uma lista encadeada).

## Considerações Práticas

1. **Tratamento do buffer de entrada**: Uso adequado de `getchar()` após `scanf()` para evitar problemas com a leitura de dados.

2. **Verificação de dados**: Validações para lidar com casos como árvore vazia ou nó não encontrado.

3. **Memória dinâmica**: Alocação e liberação adequada de memória para evitar vazamentos.

4. **Modularidade**: Funções específicas para cada operação, tornando o código mais legível e manutenível.

## Limitações da Implementação Atual

1. **Balanceamento**: As implementações não incluem mecanismos de balanceamento como AVL ou Rubro-Negra, o que pode levar a baixo desempenho em certos padrões de inserção.

2. **Persistência de dados**: Os dados são armazenados apenas em memória e são perdidos quando o programa termina.

## Conclusão

As Árvores Binárias de Busca são estruturas de dados versáteis e eficientes para operações de busca, inserção e remoção quando mantidas relativamente balanceadas. As implementações demonstradas mostram a flexibilidade das ABBs em diferentes contextos: recomendação de filmes e gerenciamento de estoque. 