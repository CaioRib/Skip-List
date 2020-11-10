/*****************************************
Trabalho 2 - Algoritmos e Estruturas de Dados
Aluno: Caio Ribeiro de Olibeira Ribeiro
nUSP = 10262839
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SKIPLIST_H
#define SKIPLIST_H

/*Definicao da skip lIst, composta por nos com ponteiro para frente e para baixo.*/
typedef struct{

	char* index;
	char* meaning;

}t_item;

struct node{
	
	t_item item;
	int lvl;
	struct node* next;
	struct node* down;

};

typedef struct node t_node;
typedef t_node* t_pointer;
typedef t_pointer t_skipList;

/*Funcoes de manipulacao da skip list*/
void inicializeSkipList(t_skipList* sL);
void createNewLevel(t_skipList* sL);
int flipCoin(int max);
void insertElement(t_skipList* sL, t_item newItem);
t_pointer search(t_skipList* sL, t_item item);
t_pointer removeSkipList(t_skipList* sL, t_item item);
void printAllSkipList(t_skipList sL);
void printLSkipList(t_skipList sL, char* letter);
void destroySkipList(t_skipList*  sL);
void changeSkipList(t_skipList* sL, t_item new);

#endif