#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GET_MAX_ELEMENTS(x, y) ((x) > (y) ? (x) : (y))
#define GET_MIN_ELEMENTS(x, y) ((x) < (y) ? (x) : (y))

int my_rand(int min, int max) {
	return (int)rand()%(max-min+1)+min;
}

int **get_matris(size_t n) {
	int **matris = NULL;

	if((matris = (int**)malloc(sizeof(int*)*n)) == NULL) {
		perror("memory error!! ");
		exit(1);
	}

	for(size_t i=0;i<n;i++) {
		if((matris[i] = (int*)malloc(sizeof(int)*n)) == NULL) {
			perror("memory error!! ");
			exit(1);
		}
		for(size_t j=0;j<n;j++)
			matris[i][j] = my_rand(10,99);
	}

	return matris;
}

double get_average(int *array, size_t size) {
	double average = 0.0;

	for(size_t i=0;i<size;i++)
		average += array[i];
	return average/(double)size;
}

double get_max_average(int **matris, size_t size) {
	double average = 0.0;
	for(size_t i=0;i<size;i++)
		for(size_t j=0;j<size;j++)
			average += matris[i][j];

	return average/(double)(size*size);
}

double get_nearest_average(double *averages, double maxAverage, size_t size) {
	double *differences = NULL;
	size_t idx = 0;

	if((differences = (double*)malloc(sizeof(double)*size)) == NULL)
		perror("memory error");

	for(size_t i=0;i<size;i++)
		differences[idx++] = GET_MAX_ELEMENTS(maxAverage, averages[i]) - GET_MIN_ELEMENTS(maxAverage, averages[i]);

	double min = maxAverage;

	for(size_t i=0;i<size;i++)
		if(min > differences[i])
			min = differences[i];

	for(size_t i=0;i<size;i++)
		if(min == differences[i])
			return averages[i];

	free(differences);

	return 0.0;
}

void print_matris(int **array, size_t size) {
	printf("\n");
	for(size_t i=0;i<size;i++) {
		for(size_t j=0;j<size;j++)
			printf("%d ", array[i][j]);
		printf("\n");
	}

	printf("\n\n");
}

int main() {
	srand((unsigned)time(NULL));

	int **matris = NULL;
	size_t n=0;

	printf("boyut girin: ");
	scanf("%zu", &n);

	matris = get_matris(n);
	print_matris(matris, n);

	double *averages = NULL;
	double maxAverage = get_max_average(matris, n);

	if((averages = (double*)malloc(sizeof(double)*n)) == NULL)
		perror("memory error\n");

	for(size_t i=0;i<n;i++)
		averages[i] = get_average(matris[i], n);

	for(size_t i=0;i<n;i++)
		printf("row %zu averages: %.3lf\n", i,averages[i]);

	printf("\nmax averages: %.3lf\n", maxAverage);
	printf("nearest maxAverages : %.3lf\n", get_nearest_average(averages, maxAverage, n));

	free(averages);
	for(size_t i=0;i<n;i++)
		free(matris[i]);
	free(matris);
}
