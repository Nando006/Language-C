# Árvores em C - Semana 11

Este diretório contém duas implementações de árvores em C para gerenciamento de cadastro de clientes:

1. **ArvoreBinariaDeBusca.c** - Implementação de uma árvore binária de busca simples
2. **ArvoreAVL.c** - Implementação de uma árvore AVL (balanceada)

## Estrutura Comum

Ambas implementações compartilham as mesmas estruturas básicas:

```c
// Estrutura do Cliente
typedef struct {
  char nome[50];
  char email[200];
  int idade;
} Cliente;

// Estrutura do Nó
typedef struct No {
  Cliente cliente;
  struct No *esq, *dir;
  // Em ArvoreAVL.c, temos um campo adicional: int altura;
} No;
```

## ArvoreBinariaDeBusca.c

A implementação da árvore binária de busca oferece as seguintes funcionalidades:

### Principais Funções

- **criarNo**: Aloca memória para um novo nó
- **criarCliente**: Obtém dados do cliente pelo usuário
- **adicionar**: Insere um cliente na árvore
- **remover**: Remove um cliente da árvore
- **atualizar**: Atualiza os dados de um cliente
- **listar**: Exibe todos os clientes em ordem alfabética
- **buscar**: Busca um cliente pelo nome
- **liberarArvore**: Libera a memória alocada pela árvore

### Funcionamento

- A ordenação é feita pelo nome do cliente
- A inserção e busca têm complexidade média de O(log n), mas no pior caso podem chegar a O(n)
- Não possui mecanismo de balanceamento, então a árvore pode ficar desbalanceada

### Menu de Operações

1. Adicionar Contato
2. Remover Contato
3. Atualizar Contato
4. Listar Contatos
5. Buscar Contato
0. Sair

## ArvoreAVL.c

A implementação da árvore AVL estende a árvore binária de busca com funcionalidades de balanceamento para garantir a eficiência das operações.

### Principais Funções

Além das funções da árvore binária, temos:

- **altura**: Obtém a altura de um nó
- **fatorBalanceamento**: Calcula o fator de balanceamento (altura da subárvore esquerda - altura da subárvore direita)
- **atualizarAltura**: Atualiza a altura de um nó
- **rotacaoDireita**: Realiza uma rotação simples à direita
- **rotacaoEsquerda**: Realiza uma rotação simples à esquerda
- **balancear**: Verifica o balanceamento e aplica as rotações necessárias
- **minValorNo**: Encontra o nó com o menor valor em uma subárvore

### Percursos

Ambas implementações suportam os três tipos de percurso, mas na AVL estão mais bem organizados:

- **emOrdem**: Visita esquerda, raiz, direita (ordem alfabética)
- **preOrdem**: Visita raiz, esquerda, direita
- **posOrdem**: Visita esquerda, direita, raiz

### Balanceamento

A árvore AVL mantém o balanceamento através:

1. **Fator de Balanceamento**: Diferença entre altura da subárvore esquerda e direita (deve ser -1, 0 ou 1)
2. **Rotações**: 
   - Simples à direita e à esquerda
   - Duplas (combinando rotações simples)
3. **Casos de Rotação**:
   - Esquerda-Esquerda: Rotação simples à direita
   - Direita-Direita: Rotação simples à esquerda
   - Esquerda-Direita: Rotação dupla à direita
   - Direita-Esquerda: Rotação dupla à esquerda

### Menu de Operações

1. Inserir
2. Remover
3. Atualizar
4. Buscar
5. Em ordem
6. Pré-ordem
7. Pós-ordem
0. Sair

## Diferenças Principais

| Característica | Árvore Binária | Árvore AVL |
|---|---|---|
| Balanceamento | Não possui | Automático após cada operação |
| Campo altura | Não possui | Presente em cada nó |
| Complexidade | O(log n) em média, O(n) no pior caso | O(log n) garantido |
| Rotações | Não possui | Implementa rotações para balanceamento |
| Percursos | Implementa em ordem | Implementa em ordem, pré-ordem e pós-ordem |

## Como Compilar e Executar

Para compilar qualquer um dos programas:

```bash
gcc ArvoreBinariaDeBusca.c -o arvore_binaria
gcc ArvoreAVL.c -o arvore_avl
```

Para executar:

```bash
./arvore_binaria
./arvore_avl
```

## Vantagens da Árvore AVL

- Mantém operações de busca, inserção e remoção com complexidade garantida O(log n)
- Evita degradação do desempenho para conjuntos de dados ordenados
- Garante altura balanceada mesmo após muitas inserções e remoções 