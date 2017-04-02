// composed by Yu Zhang(001259692)

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define DIM 5
int A[DIM * DIM];
int B[DIM * DIM];
int C[DIM * DIM];
pthread_t p[DIM];

void InitializeMatrix(int *X)
{
	int i, j;
	for (i = 0; i < DIM; i++)
		for (j = 0; j < DIM; j++)
			X[i * DIM + j] = random() % 10;
}
void PrintMatrix(int *X)
{
	int i, j;
	for (i = 0; i < DIM; i++)
	{
		for (j = 0; j < DIM; j++)
			printf("%3d ", X[i * DIM + j]);
		printf("\n");
	}
	printf("\n");
}
void MultiplyMatrices()
{
	int i, j, k;
	for (i = 0; i < DIM; i++)
	{
		for (j = 0; j < DIM; j++)
		{
			int sum = 0;
			for (k = 0; k < DIM; k++)
				sum += A[i * DIM + k] * B[k * DIM + j];
			C[i * DIM + j] = sum;
		}
	}
}
// So race condition will not happen in this scenario.
void *MultiplyMatricesParallel(void *i){
	int j, k;
	for (j = 0; j < DIM; j++){
		int sum = 0;
		for (k = 0; k < DIM; k++)
			sum += A[(int)i * DIM + k] * B[k*DIM + j];
		C[(int)i * DIM + j] = sum;
	}
	return NULL;

}
int main()
{
	InitializeMatrix(A);
	InitializeMatrix(B);
	for (int i = 0; i < DIM; i++)
		pthread_create(&p[i], NULL, MultiplyMatricesParallel, i);
	for (int i = 0; i < DIM; i++)
		pthread_join(p[i], NULL);
	// MultiplyMatrices();
	PrintMatrix(A);
	PrintMatrix(B);
	PrintMatrix(C);
	printf("Solution to (b:\n");
	printf("Threre is no need to include any locks because race condition will not happen in this scenario.\n");
	printf("Each thread is created to call MultiplyMatricesParallel to mordify different element in the matix");
	return 0;
}