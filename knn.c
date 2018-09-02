#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct atributos{
	float sepal_length;
	float sepal_width;
	float petal_length;
	float petal_width;
	char class[15];
}atributos;

void LerTreino(atributos *treino, FILE *treino_arq);
void LerExemplo(atributos *exemplo, FILE *exemplo_arq);

int main(int argc, char const *argv[]){
	char nome[9];
	FILE *treino_arq = NULL, *exemplo_arq = NULL;
	int k = 0;
	atributos *treino, *exemplo;

	scanf("%s", nome);
	treino_arq = fopen(nome, "r+b");

	scanf("%s", nome);
	exemplo_arq = fopen(nome, "r+b");

	scanf("%d", &k);

	treino = (atributos*) malloc(150 * sizeof(atributos));
	exemplo = (atributos*) malloc(150 * sizeof(atributos));

	LerTreino(treino, treino_arq);
	LerExemplo(exemplo, exemplo_arq);

	for (int i = 0; i < 50; ++i){
		printf("%f, %f, %f, %f, %s\n", exemplo[i].sepal_length,exemplo[i].sepal_width, exemplo[i].petal_length, exemplo[i].petal_width, exemplo[i].class);
	}

	free(treino);
	free(exemplo);
	return 0;
}

void LerTreino(atributos *treino, FILE *treino_arq){
	char linha[150], *token;
  	const char s[2] = ",";
  	int i = 0, j = 0;

    while(!feof(treino_arq)){
		fgets(linha, 150, treino_arq);
		token = strtok(linha, s);
		j = 0;
		while(token != NULL){    
			if (j == 0)treino[i].sepal_length = atof(token);
			if (j == 1)treino[i].sepal_width = atof(token);
			if (j == 2)treino[i].petal_length = atof(token);
			if (j == 3)treino[i].petal_width = atof(token);
			if (j == 4)strcpy(treino[i].class, token);

	    	token = strtok(NULL, s);
	    	j++;	    	
	   	}
	   	i++;
 	}

 	fclose(treino_arq);
	return;
}

void LerExemplo(atributos *exemplo, FILE *exemplo_arq){
	char linha[150], *token;
  	const char s[2] = ",";
  	int i = 0, j = 0;

    while(!feof(exemplo_arq)){
		fgets(linha, 150, exemplo_arq);
		token = strtok(linha, s);
		j = 0;
		while(token != NULL){    
			if (j == 0)exemplo[i].sepal_length = atof(token);
			if (j == 1)exemplo[i].sepal_width = atof(token);
			if (j == 2)exemplo[i].petal_length = atof(token);
			if (j == 3)exemplo[i].petal_width = atof(token);
			if (j == 4)strcpy(exemplo[i].class, token);

	    	token = strtok(NULL, s);
	    	j++;	    	
	   	}
	   	i++;
 	}

 	fclose(exemplo_arq);
	return;
}