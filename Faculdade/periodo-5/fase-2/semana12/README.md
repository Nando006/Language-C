# Exercícios de Árvore AVL - Semana 12

Este diretório contém dois exercícios relacionados à implementação e análise de árvores AVL.

## Exercício 1 (ex1.c)

O primeiro exercício é uma análise teórica que pede para desenhar as árvores AVL resultantes da inserção de diferentes sequências de números, mostrando as rotações necessárias para manter o balanceamento.

### Sequências analisadas:
1. 30, 40, 24, 58, 48, 26, 11, 13, 14
2. 20, 15, 25, 10, 30, 24, 17, 12, 5, 3
3. 40, 30, 50, 45, 55, 52
4. 20, 15, 25, 12, 17, 24, 30, 10, 14, 13
5. 20, 15, 25, 12, 17, 30, 26

Para cada sequência, o exercício mostra:
- A evolução da árvore após cada inserção
- As rotações necessárias para manter o balanceamento
- O tipo de rotação aplicada (simples ou dupla, à esquerda ou à direita)

## Exercício 2 (ex02.c)

O segundo exercício é uma implementação prática de uma árvore AVL em C. O código inclui:

### Estrutura de Dados
```c
typedef struct No {
    int valor;
    struct No *esquerda;
    struct No *direita;
    int altura;
} No;
```

### Funcionalidades Implementadas:
1. **Operações Básicas**
   - Criação de nós
   - Cálculo de altura
   - Cálculo do fator de balanceamento

2. **Rotações**
   - Rotação simples à direita
   - Rotação simples à esquerda
   - Rotação dupla à esquerda
   - Rotação dupla à direita

3. **Inserção**
   - Insere novos valores mantendo o balanceamento
   - Evita valores duplicados
   - Aplica rotações automaticamente quando necessário

4. **Percursos**
   - Em ordem (esquerda, raiz, direita)
   - Pré-ordem (raiz, esquerda, direita)
   - Pós-ordem (esquerda, direita, raiz)

5. **Gerenciamento de Memória**
   - Função para liberar a memória alocada

### Como Usar
O programa demonstra a inserção da primeira sequência de números (30, 40, 24, 58, 48, 26, 11, 13, 14) e mostra os três tipos de percurso da árvore resultante.

Para compilar e executar:
```bash
gcc ex02.c -o ex02
./ex02
```

## Conceitos Importantes

### Árvore AVL
Uma árvore AVL é uma árvore binária de busca balanceada, onde a diferença de altura entre as subárvores esquerda e direita de qualquer nó é no máximo 1.

### Fator de Balanceamento
É calculado como: altura(subárvore esquerda) - altura(subárvore direita)
- Se > 1: desbalanceada à esquerda
- Se < -1: desbalanceada à direita
- Se entre -1 e 1: balanceada

### Tipos de Rotação
1. **Rotação Simples à Direita**
   - Usada quando a subárvore esquerda está mais alta
   - O filho esquerdo se torna a nova raiz

2. **Rotação Simples à Esquerda**
   - Usada quando a subárvore direita está mais alta
   - O filho direito se torna a nova raiz

3. **Rotação Dupla**
   - Combinação de duas rotações simples
   - Usada quando o desbalanceamento está em uma subárvore interna 