// Implemente uma lista estática de inteiros em C. A lista deve ter um
// tamanho máximo predefinido. Implemente funções para adicionar,
// remover e buscar elementos.

#include <stdio.h>
#include <locale.h>

#define MAX_SIZE 10

int lista[MAX_SIZE];
int tamanho = 0;

int adicionar(int n)
{
  if (tamanho < MAX_SIZE)
  {
    lista[tamanho++] = n;
    return 1;
  }

  return 0;
}

int remover(int n)
{
  for (int i = 0; i < tamanho; i++)
  {
    if (lista[i] == n)
    {
      for (int j = i; j < tamanho--; j++)
      {
        lista[j] = lista[j + 1];
      }
    }
  }
}

void exibir()
{
  for (int i = 0; i < tamanho; i++)
  {
    printf(" %d", lista[i]);
  }
}

int main()
{
  setlocale(LC_ALL, "Portuguese");
  for (int i = 0; i < MAX_SIZE; i++)
  {
    adicionar(i + 1);
  }

  exibir();

  return 0;
}