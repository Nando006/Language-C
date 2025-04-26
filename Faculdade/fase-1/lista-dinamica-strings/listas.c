#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da lista encadeada
typedef struct Node {
    char *data;
    struct Node *next;
} Node;

// Função para criar um novo nó
Node* createNode(const char *str) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        perror("Falha na alocação de memória");
        exit(EXIT_FAILURE);
    }
    newNode->data = strdup(str);
    newNode->next = NULL;
    return newNode;
}

// Função para adicionar uma string à lista
void addString(Node **head, const char *str) {
    Node *newNode = createNode(str);
    newNode->next = *head;
    *head = newNode;
}

// Função para remover uma string
void removeString(Node **head, const char *str) {
    Node *current = *head, *prev = NULL;
    while (current != NULL && strcmp(current->data, str) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("String não encontrada.\n");
        return;
    }
    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current->data);
    free(current);
}

// Função para buscar uma string
int searchString(Node *head, const char *str) {
    Node *current = head;
    while (current) {
        if (strcmp(current->data, str) == 0) {
            return 1; // Encontrado
        }
        current = current->next;
    }
    return 0; // Não encontrado
}

// Função para liberar a lista
void freeList(Node *head) {
    Node *current = head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}

// Função para exibir a lista
void printList(Node *head) {
    Node *current = head;
    while (current) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main() {
    Node *head = NULL;
    
    addString(&head, "Hello");
    addString(&head, "World");
    addString(&head, "C Language");
    
    printf("Lista de strings:\n");
    printList(head);

    printf("\nRemovendo 'World'...\n");
    removeString(&head, "World");

    printf("Lista após remoção:\n");
    printList(head);

    if (searchString(head, "Hello")) {
        printf("\n'Hello' foi encontrado na lista.\n");
    } else {
        printf("\n'Hello' não foi encontrado na lista.\n");
    }

    freeList(head);
    return 0;
}