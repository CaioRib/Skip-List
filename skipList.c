/*****************************************
Trabalho 2 - Algoritmos e Estruturas de Dados
Aluno: Caio Ribeiro de Olibeira Ribeiro
nUSP = 10262839
******************************************/

#include "skipList.h"

/*Inicializacao da Skip List, criando um header pro nivel 0*/
void inicializeSkipList(t_skipList* sL){

		(*sL) = NULL;
		createNewLevel(sL);

}

/*Funcao que cria um header que determina um novo nivel para a skip List*/
void createNewLevel(t_skipList* sL){

	t_node* new = (t_node*)malloc(sizeof(t_node) * 1);
	
	if((*sL) == NULL){
		new->lvl = 0;
		new->next = NULL;
		new->down = NULL;
		new->item.index = NULL;
		new->item.meaning = NULL;
		*sL = new;
	}

	else{
		new->next = NULL;
		new->down = *sL;
		new->lvl = ((*sL)->lvl) + 1;
		new->item.index = NULL;
		new->item.meaning = NULL;
		*sL = new;
	}
}
/*Funcao que determina em quantos niveis serao colocados o novo elemento
a ser inserido, limitando para 20 niveis para que a insercao nao se torne
muito demorada. */
int flipCoin(int max){

	if(max >= 21) max = 20;
	/*Numero randomico entre 0 e (max + 1)*/
	return (rand() % (max + 2));
}

/*Funcao que insere um elemento na Skip List, inserindo em todos os niveis <= ao nivel mais alto
determinado pela flipCoin. Insere em ordem alfabetica e interliga os nos iguais, de forma que o
um no que esta em um nivel > 0 tem um no igual a ele em um nivel inferir, e pode-se acessa-lo por
meio do ponteiro node->down.	*/
void insertElement(t_skipList* sL, t_item item){

	int maxlvl;
	int lvl = flipCoin((*sL)->lvl);
	t_pointer aux = (*sL);
	t_pointer* aux2 = NULL;
	t_node** new;
	int a;

	if(search(sL, item) != NULL){
		printf("OPERACAO INVALIDA\n");
		return;
	}

	/*Alocacao dos nodes*/
	new = (t_node**)malloc(sizeof(t_node*) * (lvl + 1));
	
	for(a = 0; a <= lvl; a++){
		new[a] = (t_node*)malloc(sizeof(t_node) * 1);
	}

	/*Copia do conteudo da entrada para o no*/
	for(a = 0; a <= lvl; a++){
		new[a]->item.index = malloc(sizeof(char) * strlen(item.index) + 1);
		strcpy(new[a]->item.index, item.index);

		new[a]->item.meaning = malloc(sizeof(char) * strlen(item.meaning) + 1);
		strcpy(new[a]->item.meaning, item.meaning);
	}


	/*Cria novo nivel*/
	if(lvl > (*sL)->lvl){
		createNewLevel(sL);
		aux = (*sL);
	}

	/*Desce ate o nivel que deve comecar a insercao, avancando na skip list para
	reduzir o tempo de procura*/
	maxlvl = aux->lvl;
	while(lvl < maxlvl){
		while(aux->next != NULL && strcmp(aux->next->item.index, item.index) < 0){
			aux = aux->next;
		}
		aux = aux->down;
		maxlvl--;
	}


	for(a = 0; a <= lvl; a++){
		/*Avanca ate posicao desejada ou fim da lista*/
		while(aux->next != NULL && strcmp(aux->next->item.index, item.index) < 0) aux = aux->next;

		/*Insercao propriamente dita*/
		if(aux2 != NULL) *aux2 = new[a];
		new[a]->next = aux->next;
		aux->next = new[a];
		aux2 = &(new[a]->down);
		if(a == lvl) aux->down = NULL;
		if(a != lvl) aux = aux->down;

	}
	free(new);
}

/*Funcao que busca um no na skip list a partir de seu t_item, de forma a retornar NULL caso nao o
encontre, ou retornando um ponteiro para o no encontrado.	*/
t_pointer search(t_skipList* sL, t_item item){

	t_pointer aux = (*sL);
	int maxlvl = (*sL)->lvl;

	while(maxlvl >= 0){
		/*Anda para a direita na skip list, procurando o elemento*/
		while(aux->next != NULL && strcmp(aux->next->item.index, item.index) < 0) aux = aux->next;
			
		/*Caso nao o encontre em um nivel, desce*/
		if(aux->next == NULL || strcmp(aux->next->item.index, item.index) != 0){
			aux = aux->down;
			maxlvl--;
		}

		/*Retorno do no encontrado*/
		else if(aux->next != NULL && strcmp(aux->next->item.index, item.index) == 0){
			return aux->next;
		}
	}

	/*Caso nao tenha sido achado, retorna NULL*/
	return NULL;
	
}

/*Funcao que remove um no da skip list a partir do t_item dado como parametro. Retorna um ponteiro para o no
eliminado.	*/
t_pointer removeSkipList(t_skipList* sL, t_item item){

	int maxlvl     = (*sL)->lvl;
	t_pointer aux  = (*sL);
	t_pointer rm   = NULL;
	t_pointer down = NULL;

	/*Busca a posicao do primeiro no com a chave procurada*/
	while(maxlvl >= 0){
		rm = NULL;

		/*Anda para a direita*/
		while(aux->next != NULL && strcmp(aux->next->item.index, item.index) < 0) aux = aux->next;

		/*Anda para baixo*/
		if(aux->next == NULL || strcmp(aux->next->item.index, item.index) != 0){
			aux = aux->down;
			maxlvl--;
		}

		/*Caso em que no foi encontrado. */
		else if(strcmp(aux->next->item.index, item.index) == 0){
			rm = aux;
			break;
		}
	}

	if(rm == NULL){
		printf("OPERACAO INVALIDA\n");
	}

	aux = rm;
	/*Remocao propriamente dita*/
	if(aux != NULL){
		while(maxlvl >= 0){
			while(aux->next != NULL && strcmp(aux->next->item.index, item.index) < 0) aux = aux->next;

			/*Remove guardando o ponteiro para baixo do no eliminado, para poder descer na Skip List depois
			da remocao deste.	*/
			if(maxlvl > 0) down = aux->down;
			rm = aux->next;
			aux->next = aux->next->next;
			if(maxlvl > 0) aux = down;
			free(rm->item.index);
			free(rm->item.meaning);
			free(rm);
			maxlvl--;
		}
	}

	return NULL;
}

/*	FUNCAO AUXILIAR UTILIZADA APENAS PARA DEBUG
Imprime todos os niveis da Skip List com seus respectivos elementos.	*/
void printAllSkipList(t_skipList sL){

	t_pointer aux = sL;
	t_pointer down = sL;
	int lvl = (sL->lvl);
	int a;


	for(a = 0; a <= lvl; a++){
		printf("(Linha %d) -> ", lvl - a);
	

			aux = aux->next;
			if(aux == NULL){
				printf("Vazia");
			}


			while(aux != NULL){
				printf("%s ", aux->item.index);
				aux = aux->next;
			}
		

	down = down->down;
	aux = down;
	}


}

/*Funcao que imprime todos os elementos comecados com uma letra definida pelo usuario
na leitura.*/
void printLSkipList(t_pointer sL, char* letter){
	
	t_pointer aux = sL;

	/*Desce ate o nivel 0 da skip list*/
	while(aux->down != NULL) aux = aux->down;

	/*Procura o primeiro elemento que possua primeira letra igual*/
	while(aux->next != NULL && aux->next->item.index[0] != letter[0])
		aux = aux->next;

	/*Caso em que nao ha nenhum elemento comecado pela letra desejada*/
	if(aux->next == NULL || aux->next->item.index[0] != letter[0]){
		printf("NAO HA PALAVRAS INICIADAS POR %c\n", letter[0]);
		return;
	}

	/*Caso contrario, printa todos os elementos e respectivos significados*/
	while(aux->next != NULL && aux->next->item.index[0] == letter[0]){
		printf("%s ", aux->next->item.index);
		printf("%s\n", aux->next->item.meaning);
		aux = aux->next;
	}
}

/*	Funcao que libera toda a memoria alocada para a Skip List, eliminando todos os nos
e strings destes.	*/
void destroySkipList(t_skipList*  sL){

	t_pointer aux = (*sL);
	t_pointer rm = (*sL);
	t_pointer down = (*sL);
	int lvl = (*sL)->lvl;
	int a;


	while(aux != NULL){
		if(aux->next != NULL) aux = aux->next;

		/*Elimina todos os elementos*/
		while(aux != NULL){
			rm = aux;
			if(aux != NULL) aux = aux->next;
			free(rm->item.index);
			free(rm->item.meaning);
			free(rm);
			rm = NULL;
		}

		down = down->down;
		aux = down;

	}

	aux = (*sL);
	rm = (*sL);
	aux = aux->down;

	free(rm);
	rm = NULL;

	/*Elimina todos os headers*/
	for(a = 0; a < lvl; a++){
		rm = aux;
		aux = aux->down;
		free(rm);
		rm = NULL;
	}	
}

/*	Funcao que altera o significado de determinada palavra determinada pelo usuario*/
void changeSkipList(t_skipList* sL, t_item new){


	int maxlvl     = (*sL)->lvl;
	t_pointer aux  = (*sL);
	t_pointer alt   = NULL;
	t_pointer down = NULL;

	/*Busca:	*/
	while(maxlvl >= 0){
		alt = NULL;

		while(aux->next != NULL && strcmp(aux->next->item.index, new.index) < 0) aux = aux->next;
		if(aux->next == NULL || strcmp(aux->next->item.index, new.index) != 0){
			aux = aux->down;
			maxlvl--;
		}

		else if(strcmp(aux->next->item.index, new.index) == 0){
			alt = aux;
			break;
		}
	}

	/*Caso em que a palavra nao foi encontrada*/
	if(alt == NULL){
		printf("OPERACAO INVALIDA\n");
	}

	aux = alt;

	/*	Mudanca do significado de todos os nos iguais*/
	if(aux != NULL){
		while(maxlvl >= 0){
			while(aux->next != NULL && strcmp(aux->next->item.index, new.index) < 0) aux = aux->next;

			if(strcmp(aux->next->item.index, new.index) == 0){

				free(aux->next->item.index);
				aux->next->item.index = NULL;
				aux->next->item.index = (char*)malloc(sizeof(char) * strlen(new.index) + 1);
				strcpy(aux->next->item.index, new.index);


				free(aux->next->item.meaning);
				aux->next->item.meaning = NULL;
				aux->next->item.meaning = (char*)malloc(sizeof(char) * strlen(new.meaning) + 1);
				strcpy(aux->next->item.meaning, new.meaning);

				if(maxlvl > 0) down = aux->down;
				if(maxlvl > 0) aux = down;
				maxlvl--;
			}
		}
	}
}
