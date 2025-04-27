#include <stdio.h>
#include <locale.h>
#include <time.h>

void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int arr[], int low, int high)
{
  int pivo = arr[high];
  int i = low - 1;
  for (int j = low; j <= high - 1; j++)
  {
    if (arr[j] <= pivo)
    {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
  if (low < high)
  {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

int main()
{
  setlocale(LC_ALL, "Portuguese");

  clock_t start, end;
  double time;

  int arr[] = {923, 283, 2038, 82733, 87, 29, 1, 2378, 237, 714, 12, 23937, 38, 847, 120};

  int n = sizeof(arr) / sizeof(arr[0]);

  start = clock();
  quickSort(arr, 0, n - 1);
  end = clock();

  time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

  for (int i = 0; i < n; i++)
  {
    printf(" %d", arr[i]);
  }

  printf("\n\nTempo de execução: %.3f", time);

  return 0;
}