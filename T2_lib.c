/*****************************************
Trabalho 2 - Algoritmos e Estruturas de Dados
Aluno: Caio Ribeiro de Olibeira Ribeiro
nUSP = 10262839
******************************************/

#include "T2_lib.h"
#include "skipList.h"

/*Funcao que le a entrada, tratando caracteres insesejaveis ao fim de
cada leitura. Retorna um char** contendo 2 ou 3 strings, dependendo da
operacao escolhida. Alem disso, possui uma flag que verifica se chegou
ao fim do arquivo, sendo modificada para 1 se sim, ou permanecendo 0 caso
contrario.	*/
char** readLine(int* flag){
	int count = 0;
	char c;
	char** string = (char**)malloc(3 * sizeof(char*));
	int i, j;
	int debug[] = {32, 10, -1, 13};

	/*Inicializacao*/
	for(i = 0; i < 3; i++) string[i] = NULL;

	/*Loop que le as duas primeiras palavras*/
	for(i = 0; i < 2; i++){
		count = 0;
		do{
			count++;
			string[i] = realloc(string[i], sizeof(char) * (count + 1));
			c = getchar();
			string[i][count - 1] = c;

		}while(c != EOF && c != ' ' && c != '\n');

		/*Flag que indica fim da leitura*/
		if(c == EOF){
			if(i == 1) free(string[1]);
			free(string[0]);
			free(string);
			*flag = 1;
			return NULL;
		}

		/*Tratamento de caracteres indesejaveis ao fim da string, sendo eles: ' ', '\n', '\r' e
		o caractere indefinido dado por -1*/
		for(j = 0; j < 4; j++){
			if(string[i][count - 1] == debug[j]){
				string[i] = realloc(string[i], sizeof(char) * count);
				string[i][count - 1] = '\0';
				j = 4;
			}	
		}

		for(j = 0; j < 4; j++){
			if(strlen(string[i]) >= 2){
				if(string[i][count - 2] == debug[j]){
					string[i] = realloc(string[i], sizeof(char) * (count - 1));
					string[i][count - 2] = '\0';
					j = 4;
				}
			}
		}
	}

	/*Caso em que e necessario uma terceira string, nos casos de insercao e alteracao*/
	if(strcmp(string[0], "insercao") == 0 || strcmp(string[0], "alteracao") == 0){

		i = 2;
		count = 0;


		do{
			count++;
			string[i] = realloc(string[i], sizeof(char) * (count + 1));
			c = getchar();
			string[i][count - 1] = c;

		}while(c != EOF && c != '\n');

		/*Fim do arquivo*/
		if(c == EOF){
			for(j = 0; j < 3; j++) free(string[j]);
			free(string);
			*flag = 1;
			return NULL;
		}

		/*Tratamento de caracteres indesejaveis ao fim da string, sendo eles: ' ', '\n', '\r' e
		o caractere indefinido dado por -1*/
		for(j = 0; j < 4; j++){
			if(string[2][count - 1] == debug[j]){
				string[2] = realloc(string[2], sizeof(char) * count);
				string[2][count - 1] = '\0';
				j = 4;
			}
		}

		for(j = 0; j < 4; j++){
			if(strlen(string[2]) >= 2){
				if(string[2][count - 2] == debug[j]){
					string[2] = realloc(string[2], sizeof(char) * (count - 1));
					string[2][count - 2] = '\0';
					j = 4;
				}
			}
		}

		if(strlen(string[2]) >= 3){
			if(string[2][count - 3] == debug[0]){
				string[2] = realloc(string[2], sizeof(char) * (count - 1));
				string[2][count - 3] = '\0';
			}
		}
	}

	return string;
}

