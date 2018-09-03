#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct atributos{
	float sepal_length;
	float sepal_width;
	float petal_length;
	float petal_width;
	char class[15];
}atributos;

typedef struct distancia{
	float distancia;
	char class[15];
}distancia;

int LerTreino(atributos *treino, FILE *treino_arq);
int LerExemplo(atributos *exemplo, FILE *exemplo_arq);
void insertion_sort(distancia *v, int n);

int main(int argc, char const *argv[]){
	char nome[9];
	int k = 0;
	float dist = 0, conta = 0, lance = 0;
	atributos *treino, *exemplo;
	distancia *distancia_vet;
	FILE *treino_arq = NULL, *exemplo_arq = NULL;

	scanf("%s", nome);
	treino_arq = fopen(nome, "r+b");

	scanf("%s", nome);
	exemplo_arq = fopen(nome, "r+b");

	scanf("%d", &k);

	treino = (atributos*) malloc(155 * sizeof(atributos));
	exemplo = (atributos*) malloc(155 * sizeof(atributos));
	distancia_vet = (distancia*) malloc(155 * sizeof(distancia));

	int tamTreino = LerTreino(treino, treino_arq);
	int tamExemplo = LerExemplo(exemplo, exemplo_arq);

    if(tamExemplo < k){
        printf("k is invalid\n");
        return 0;
    }

	for (int i = 0; i < tamExemplo-2; ++i){
		for (int j = 0; j < tamTreino; ++j){
			dist = sqrt(pow(treino[j].sepal_length - exemplo[i].sepal_length, 2) + pow(treino[j].sepal_width - exemplo[i].sepal_width, 2) + pow(treino[j].petal_length - exemplo[i].petal_length, 2) + pow(treino[j].petal_width - exemplo[i].petal_width, 2));

			distancia_vet[j].distancia = dist;
			strcpy(distancia_vet[j].class, treino[j].class);
		}
		
		insertion_sort(distancia_vet, tamTreino);

		int a = 0, b = 0, c = 0;
		for (int j = 0; j < k; ++j){
			if(strlen(distancia_vet[j].class) == 9) a++;
			if(strlen(distancia_vet[j].class) == 13) b++;
			if(strlen(distancia_vet[j].class) == 12) c++;
		}

        char esperado[strlen(exemplo[i].class)-2];
        int m = 0;
        for (int j = 1; j <= strlen(exemplo[i].class)-3; ++j){
            esperado[m] = exemplo[i].class[j];
            m++;
        }
        esperado[strlen(exemplo[i].class)-3] = '\0';

		if (a > b && a > c){
            printf("setosa %s\n", esperado);
            if (strcmp("setosa", esperado) == 0) conta++;
        }
		if (b > a && b > c){
            printf("versicolor %s\n", esperado);
            if (strcmp("versicolor", esperado) == 0) conta++;
        }
		if (c > b && c > a){
            printf("virginica %s\n", esperado);
            if (strcmp("virginica", esperado) == 0) conta++;
        }
	}

    tamExemplo -= 2;

    printf("%0.4f\n", (float)conta/(float)tamExemplo);

	free(treino);
	free(exemplo);
	free(distancia_vet);
	return 0;
}

int LerTreino(atributos *treino, FILE *treino_arq){
	char linha[150], *token;
  	const char s[2] = ",";
  	int i = 0, j = 0;

    fgets(linha, 150, treino_arq);
    token = strtok(linha, s);
    token = strtok(NULL, s);

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
	return i+1;
}

int LerExemplo(atributos *exemplo, FILE *exemplo_arq){
	char linha[150], *token;
  	const char s[2] = ",";
  	int i = 0, j = 0;

    fgets(linha, 150, exemplo_arq);
    token = strtok(linha, s);
    token = strtok(NULL, s);

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
	return i+1;
}

void insertion_sort(distancia *v, int n){
	int i = 1; 

	while (i < n) {
		float chave = v[i].distancia;
		char classe[15]; 
		strcpy(classe, v[i].class);

		int j = i-1;
		while (j >= 0 && chave < v[j].distancia) {
			v[j+1].distancia = v[j].distancia;
			strcpy(v[j+1].class, v[j].class);
			j--;
		}
		v[j+1].distancia = chave;
		strcpy(v[j+1].class, classe);
		i++;
	}
}