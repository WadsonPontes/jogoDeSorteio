#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SORTEIOS 20

void ler_aposta(int *aposta, int n);
void sorteia_valores(int sorteio[]);
int* compara_aposta(int *aposta, int *sorteio, int *qtdacertos, int na);
int* insertionSort(int *vetor, int n);

int main() {
	time_t t;
	int n, qtdacertos = 0;
	int *aposta, *sorteio, *acertos;
	srand((unsigned) time(&t));

	sorteio = (int *) malloc(NUM_SORTEIOS * sizeof(int));

	printf("Quantos numeros gostaria de apostar? ");
	scanf("%d", &n);

	aposta = (int *) malloc(n * sizeof(int));

	ler_aposta(aposta, n);
	sorteia_valores(sorteio);
	acertos = compara_aposta(aposta, sorteio, &qtdacertos, n);

	printf("Voce acertou %d numeros\n", qtdacertos);
	printf("Sao eles: ");

	for (int i = 0; i < qtdacertos; i++) {
		printf("%d ", acertos[i]);
	}
	printf("\n");

	free(aposta);
	free(sorteio);
	free(acertos);
	return 0;
}

void ler_aposta(int *aposta, int n) {
	int i = 0;

	printf("Faca sua aposta, digite %d numeros entre 1 e 99:\n", n);

	while (i < n) {
		int unico = 1;

		scanf("%d", &aposta[i]);

		for (int j = 0; j < i; j++) {
			if (aposta[i] == aposta[j]) {
				unico = 0;
				break;
			}
		}

		if (aposta[i] < 1 || aposta[i] > 99)
			printf("A aposta deve ser entre 1 e 99!\n");
		else if (unico == 0) {
			printf("Voce nao pode apostar no mesmo numero duas vezes!\n");
		}
		else
			i++;
	}

	aposta = insertionSort(aposta, n);

	printf("Sua aposta foi: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", aposta[i]);
	}
	printf("\n");
}

void sorteia_valores(int sorteio[]) {
	for (int i = 0; i < NUM_SORTEIOS; i++) {
		int unico = 1;

		sorteio[i] = (rand() % 99) + 1;

		for (int j = 0; j < i; j++) {
			if (sorteio[j] == sorteio[i]) {
				unico = 0;
				break;
			}
		}

		if (unico == 0)
			i--;
	}

	sorteio = insertionSort(sorteio, NUM_SORTEIOS);

	printf("Os numeros sorteados foram: ");
	for (int i = 0; i < NUM_SORTEIOS; i++) {
		printf("%d ", sorteio[i]);
	}
	printf("\n");
}

int* compara_aposta(int *aposta, int *sorteio, int *qtdacertos, int na) {
	int *apostascertas = (int *) malloc(NUM_SORTEIOS * sizeof(int));

	for (int i = 0; i < NUM_SORTEIOS; i++) {
		for (int j = 0; j < na; j++) {
			if (aposta[j] == sorteio[i]) {
				apostascertas[*qtdacertos] = aposta[j];
				(*qtdacertos)++;
			}
		}
	}

	return apostascertas;
}

int* insertionSort(int *vetor, int n) {
	int pivo, aux;

	for (int i = 1; i < n; i++) {
		pivo = i;

		while (pivo > 0 && vetor[pivo] < vetor[pivo - 1]) {
			aux = vetor[pivo];
			vetor[pivo] = vetor[pivo - 1];
			vetor[pivo - 1] = aux;
			pivo--;
		}
	}

	return vetor;
}