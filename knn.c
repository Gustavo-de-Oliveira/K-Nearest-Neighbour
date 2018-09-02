#include <stdio.h>
#include <stdlib.h>

typedef struct atributos{
	float sepeal_length;
	float sepal_width;
	float petal_length;
	float petal_width;
}atributos;

int main(int argc, char const *argv[]){
	char nome[9];
	FILE *treino = NULL, *exemplo = NULL;
	int k = 0;

	scanf("%s", nome);
	treino = fopen(nome, "r");

	scanf("%s", nome);
	exemplo = fopen(nome, "r");

	scanf("%d", &k);

	return 0;
}