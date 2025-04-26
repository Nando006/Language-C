#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define MAX_SIZE_1 10000

void insertionSort(int arr[], int n, int *movimentos)
{
  int i, key, j;

  *movimentos = 0;

  for (i = 1; i < n; i++)
  {
    key = arr[i];
    j = i - 1;

    while (j >= 0 && arr[j] > key)
    {
      arr[j + 1] = arr[j];
      j = j - 1;
      (*movimentos)++;
    }
    arr[j + 1] = key;
  }
}

void swap(int *a, int *b, int *movimentos)
{
  int t = *a;
  *a = *b;
  *b = t;
  (*movimentos)++;
}

int partition(int arr[], int low, int high, int *movimentos)
{
  int pivo = arr[high];
  int i = low - 1;
  for (int j = low; j <= high - 1; j++)
  {
    if (arr[j] <= pivo)
    {
      i++;
      swap(&arr[i], &arr[j], movimentos);
    }
  }
  swap(&arr[i + 1], &arr[high], movimentos);
  return (i + 1);
}

void quickSort(int arr[], int low, int high, int *movimentos)
{
  if (low < high)
  {
    int pi = partition(arr, low, high, movimentos);
    quickSort(arr, low, pi - 1, movimentos);
    quickSort(arr, pi + 1, high, movimentos);
  }
}

void printArray(int arr[], int size)
{
  for (int i = 0; i < size; i++)
  {
    printf(" %d", arr[i]);
  }
}

void processandoI(int arr[], int size, int i)
{
  clock_t start, end;
  double time;
  int movimentos = 0;

  if (i == 0)
  {
    start = clock();
    quickSort(arr, 0, size - 1, &movimentos);
    end = clock();
  }
  else
  {
    start = clock();
    insertionSort(arr, size, &movimentos);
    end = clock();
  }

  time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

  printf("\n\n");
  printArray(arr, size);
  printf("\n\nTempo de execução: %.3f", time);
  printf("\nNúmero de movimentos: %d", movimentos);
}

int main()
{
  setlocale(LC_ALL, "Portuguese");

  int arr[MAX_SIZE_1];
  int arrTwo[MAX_SIZE_1];
  for (int i = 0; i < MAX_SIZE_1; i++)
  {
    arr[i] = rand() % MAX_SIZE_1 - 1;
    arrTwo[i] = rand() % MAX_SIZE_1 - 1;
  }

  processandoI(arr, MAX_SIZE_1, 0);

  processandoI(arrTwo, MAX_SIZE_1, 1);

  return 0;
}