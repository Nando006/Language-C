#include <stdio.h>
#include <locale.h>

// ---------- MERGE SORT ---------- //
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2]; // Vetores temporários

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0; j = 0; k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// ---------- SHELL SORT ---------- //
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// ---------- BUSCA SEQUENCIAL ---------- //
int buscaSequencial(int arr[], int n, int chave) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == chave)
            return i;
    }
    return -1;
}

// ---------- BUSCA BINÁRIA ---------- //
int buscaBinaria(int arr[], int n, int chave) {
    int inicio = 0, fim = n - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (arr[meio] == chave)
            return meio;
        else if (arr[meio] < chave)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// ---------- FUNÇÃO PARA IMPRIMIR O VETOR ---------- //
void imprimirVetor(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// ---------- MAIN PARA TESTE ---------- //
int main() {
	
	setlocale(LC_ALL,"Portuguese");
	
    int vetor1[] = {32, 71, 12, 45, 26, 80, 53, 33};
    int vetor2[] = {32, 71, 12, 45, 26, 80, 53, 33};
    int n = sizeof(vetor1) / sizeof(vetor1[0]);

    printf("Vetor original:\n");
    imprimirVetor(vetor1, n);

    // Teste Merge Sort
    mergeSort(vetor1, 0, n - 1);
    printf("\nVetor ordenado com Merge Sort:\n");
    imprimirVetor(vetor1, n);

    // Teste Shell Sort
    shellSort(vetor2, n);
    printf("\nVetor ordenado com Shell Sort:\n");
    imprimirVetor(vetor2, n);

    // Teste Busca Sequencial
    int chave = 45;
    int resultadoSeq = buscaSequencial(vetor2, n, chave);
    if (resultadoSeq != -1)
        printf("\nBusca Sequencial: valor %d encontrado na posição %d.\n", chave, resultadoSeq);
    else
        printf("\nBusca Sequencial: valor %d não encontrado.\n", chave);

    // Teste Busca Binária (em vetor ordenado com Merge Sort)
    int resultadoBin = buscaBinaria(vetor1, n, chave);
    if (resultadoBin != -1)
        printf("Busca Binária: valor %d encontrado na posição %d.\n", chave, resultadoBin);
    else
        printf("Busca Binária: valor %d não encontrado.\n", chave);

    return 0;
}

