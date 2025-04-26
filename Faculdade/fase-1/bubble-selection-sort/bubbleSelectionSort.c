#include <stdio.h>
#include <locale.h>
#include <time.h>

#define MAX_100 100
#define MAX_1000 1000
#define MAX_10000 10000

// Definindo as listas
int listaB100[MAX_100], listaB1000[MAX_1000], listaB10000[MAX_10000];
int listaS100[MAX_100], listaS1000[MAX_1000], listaS10000[MAX_10000];

// Definindo variáveis para capturar movimentações
int movB100, movB1000, movB10000;
int movS100, movS1000, movS10000;

// Definindo variáveis de captura de tempo (ms)
double timeB100, timeB1000, timeB10000;
double timeS100, timeS1000, timeS10000;

void bubbleSort(int arr[], int n, int *mov)
{

  int i, j, temp;

  *mov = 0;

  for (i = 0; i < n - 1; i++)
  {

    for (j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {

        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;

        (*mov)++;
      }
    }
  }
}

void selectionSort(int arr[], int n, int *mov)
{

  int i, j, min_idx, temp;

  *mov = 0;

  for (i = 0; i < n - 1; i++)
  {

    min_idx = i;
    for (j = i + 1; j < n; j++)
    {

      if (arr[j] < arr[min_idx])
      {

        min_idx = j;
      }
    }

    if (min_idx != i)
    {
      temp = arr[min_idx];
      arr[min_idx] = arr[i];
      arr[i] = temp;
      (*mov)++;
    }
  }
}

void processandoB(int arr[], int maxSize, int *mov, double *time)
{
  // Pegando as funções de tempo da lib time
  clock_t start, end;

  for (int i = 0; i < maxSize; i++)
  {
    arr[i] = maxSize - i;
  }

  start = clock();
  bubbleSort(arr, maxSize, mov);
  end = clock();

  *time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
}

void processandoS(int arr[], int maxSize, int *mov, double *time)
{
  // Pegando as funções de tempo da lib time
  clock_t start, end;

  for (int i = 0; i < maxSize; i++)
  {
    arr[i] = maxSize - i;
  }

  start = clock();
  selectionSort(arr, maxSize, mov);
  end = clock();

  *time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
}

int main()
{
  setlocale(LC_ALL, "Portuguese");

  // Lista Bubble
  processandoB(listaB100, MAX_10000, &movB10000, &timeB10000);

  printf("\n\nBubble Sort\n- Tamanho: %d\n- Tempo (ms): %.3f\n- Movimentações: %d", MAX_10000, timeB10000, movB10000);

  // Lista Selection
  processandoS(listaS100, MAX_10000, &movS10000, &timeS10000);

  printf("\n\nSelection Sort\n- Tamanho: %d\n- Tempo (ms): %.3f\n- Movimentações: %d", MAX_10000, timeS10000, movS10000);

  return 0;
}