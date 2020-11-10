/*****************************************
Trabalho 2 - Algoritmos e Estruturas de Dados
Aluno: Caio Ribeiro de Olibeira Ribeiro
nUSP = 10262839
******************************************/

#include "skipList.h"
#include "T2_lib.h"

int main(){

	/*Variaveis: */
	int flag = 0, i;
	char** string = NULL;
	t_skipList sL;
	t_pointer x;

	t_item b;
	b.index = NULL;
	b.meaning = NULL;

	/*inicicializacao da skip list*/
	inicializeSkipList(&sL);

	/*loop para quando a leitura chega ao EOF*/
	while(flag == 0){	
		/*leitura da entrada*/
		string = readLine(&flag);

		if(string != NULL){
			/*Operacao de insercao*/
			if(strcmp(string[0], "insercao") == 0){
				b.index = string[1];
				b.meaning = string[2];			
				insertElement(&sL, b);
			}
			
			/*Operacao de remocao*/
			if(strcmp(string[0], "remocao") == 0){
				b.index = string[1];
				removeSkipList(&sL, b);
			}
		
			/*Operacao de busca*/
			if(strcmp(string[0], "busca") == 0){
				b.index = string[1];
				x  = search(&sL, b);
				if(x == NULL) printf("OPERACAO INVALIDA\n");
				else if(x != NULL){
					printf("%s ", x->item.index);
					printf("%s\n", x->item.meaning);
				}
			}

			/*Operacao de impressao*/
			if(strcmp(string[0], "impressao") == 0){
				printLSkipList(sL, string[1]);
			}

			/*Operacao de alteracao*/
			if(strcmp(string[0], "alteracao") == 0){
				b.index = NULL;
				b.index = string[1];
				b.meaning = NULL;
				b.meaning = string[2];
				changeSkipList(&sL, b);

			}
				
			/*Free na entrada, para que possa ser feita a leitura de uma nova linha*/
			for(i = 0; i < 3; i++){
				free(string[i]);
				string[i] = NULL;
			}
		}
		free(string);
		string = NULL;


	}

 	destroySkipList(&sL);
	
	return 0;

}