#include <stdio.h>
#include <locale.h>
#include <time.h>

void insertionSort(int arr[], int n)
{
  int i, key, j;
  for (i = 1; i < n; i++)
  {
    key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > key)
    {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

int main()
{
  setlocale(LC_ALL, "Portuguese");

  clock_t start, end;
  double time;

  int arr[] = {40, 30, 20, 100, 2, 14, 94, 1846, 200, 987, 689, 923};

  int n = sizeof(arr) / sizeof(arr[0]);

  start = clock();
  insertionSort(arr, n);
  end = clock();

  time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

  for (int i = 0; i < n; i++)
  {
    printf(" %d", arr[i]);
  }

  printf("\n\nTempo de execução %.3f", time);

  return 0;
}