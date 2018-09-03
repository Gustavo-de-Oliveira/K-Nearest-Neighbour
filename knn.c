#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct atributos{//Tipo usado para armazenar os dados da linha/imagem
	float sepal_length;
	float sepal_width;
	float petal_length;
	float petal_width;
	char class[15];
}atributos;

typedef struct distancia{//Tipo usado para armazenar as distancias euclidianas
	float distancia;
	char class[15];
}distancia;

int LerCSV(atributos *vetor, FILE *arq);
void insertion_sort(distancia *v, int n);

int main(int argc, char const *argv[]){
	char nome[9];
	int k = 0;
	float dist = 0, conta = 0, lance = 0;
	atributos *treino, *exemplo;
	distancia *distancia_vet;
	FILE *treino_arq = NULL, *exemplo_arq = NULL;

	scanf("%s", nome);//Lê o nome do arquivos de treino
	treino_arq = fopen(nome, "r+b");

	scanf("%s", nome);//Lê o nome do arquivo de exemplo
	exemplo_arq = fopen(nome, "r+b");

	scanf("%d", &k);//Lê o número de K's a serem analizados

	treino = (atributos*) malloc(155 * sizeof(atributos));//Vetor que vai armazenar os dados de treino
	exemplo = (atributos*) malloc(155 * sizeof(atributos));//Vetor que vai armazenar os dados de exemplo
	distancia_vet = (distancia*) malloc(155 * sizeof(distancia));//Vetor que vai armazenar as distâncias e a classe esperada

	int tamTreino = LerCSV(treino, treino_arq);
	int tamExemplo = LerCSV(exemplo, exemplo_arq);

    if(tamExemplo < k){//Se k for maior que o número de linhas no arquivo de exemplo então retorna erro
        printf("k is invalid\n");
        return 0;
    }

	for (int i = 0; i < tamExemplo-2; ++i){
		for (int j = 0; j < tamTreino; ++j){
			//Calculo da distância euclidiana
			dist = sqrt(pow(treino[j].sepal_length - exemplo[i].sepal_length, 2) + pow(treino[j].sepal_width - exemplo[i].sepal_width, 2) + pow(treino[j].petal_length - exemplo[i].petal_length, 2) + pow(treino[j].petal_width - exemplo[i].petal_width, 2));

			//Armazena a distancia e a classe no vetor distancia
			distancia_vet[j].distancia = dist;
			strcpy(distancia_vet[j].class, treino[j].class);
		}
		
		insertion_sort(distancia_vet, tamTreino);//Organiza o vetor de distância
		
		/*
		a - Representa a quantidade de aparições de Setosas
		b - Representa a quantidade de aparições de Versiscolor
		c - Representa a quantidade de aparições de virginica
		Aparições nos k primeiros do vetor distância
		*/
		int a = 0, b = 0, c = 0;
		for (int j = 0; j < k; ++j){
			if(strlen(distancia_vet[j].class) == 9) a++;
			if(strlen(distancia_vet[j].class) == 13) b++;
			if(strlen(distancia_vet[j].class) == 12) c++;
		}


		//Remove as aspas das strings geradas pela função strtok
        char esperado[strlen(exemplo[i].class)-2];
        int m = 0;
        for (int j = 1; j <= strlen(exemplo[i].class)-3; ++j){
            esperado[m] = exemplo[i].class[j];
            m++;
        }
        esperado[strlen(exemplo[i].class)-3] = '\0';

        //Verifica qual mais apareceu e printa na tela
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

    tamExemplo -= 2;//Quantidade de linhas lidas no arquivo exemplo menos linha inicial com o cabeçalho e a ultima linha com nenhum dado

    //Conta: total de acertos/tamExemplo: Total de linhas
    printf("%0.4f\n", (float)conta/(float)tamExemplo);

	free(treino);
	free(exemplo);
	free(distancia_vet);
	return 0;
}

//Descrição: Função que lê todos os dados dos arquivos CSV e armazena em um vetor
int LerCSV(atributos *vetor, FILE *arq){
	char linha[150], *token;
	//linha:Armazena os dados da linha do arquivo .csv;
	//token:Usado para o auxilio na função strtok para separar os dados a partir das virgulas
  	const char s[2] = ",";
  	//s:Usado na função strtok
  	int i = 0, j = 0;//Contadores

    fgets(linha, 150, arq);//Lê a linha
    token = strtok(linha, s);//separa usando a virgula como delimitador(A primeira linha é o cabeçalho, portanto nada acontece)
    token = strtok(NULL, s);//Pula para a próxima linha

    while(!feof(arq)){
		fgets(linha, 150, arq);//Lê as próximos linhas com dados
		token = strtok(linha, s);
		j = 0;
		while(token != NULL){//Assim que separado os dados são armazenados em seus lugares a partir de um contador que diz onde deve-se guardar
			if (j == 0)vetor[i].sepal_length = atof(token);
			if (j == 1)vetor[i].sepal_width = atof(token);
			if (j == 2)vetor[i].petal_length = atof(token);
			if (j == 3)vetor[i].petal_width = atof(token);
			if (j == 4)strcpy(vetor[i].class, token);

	    	token = strtok(NULL, s);//Próxima linha
	    	j++;	    	
	   	}
	   	i++;
 	}

 	fclose(arq);//Fecha o arquivo
	return i+1;//Retorna o número de linhas lidas
}

//Sort para ordenar as distancias, da menor para a maior
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