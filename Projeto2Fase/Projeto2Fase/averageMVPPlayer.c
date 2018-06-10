/* MINI-PROJETO 2 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/

/*Bibliotecas importadas*/
#include "averageMVPPlayer.h"
#include <stdio.h>
#include <stdlib.h>

/*Funcao que devolve um MVPPlayer, recebe um jogador e o seu mvp*/
AvgMVPPlayer avgMVPPlayerCreate(Player player, float avgMvp)
{
	AvgMVPPlayer mvpPlayer;
	mvpPlayer.avgMVP = avgMvp;
	mvpPlayer.player = player;
	return mvpPlayer;
}

/*Funcao que devolve uma lista de jogadores e o seu mvp*/
PtMVPPlayerlist mvpPlayerListCreate(unsigned int capacity)
{
	MVPPlayerList* list = (MVPPlayerList*)malloc(sizeof(MVPPlayerList));

	list->capacity = capacity;
	list->size = 0;
	list->elements = (AvgMVPPlayer*)calloc(capacity, sizeof(AvgMVPPlayer));

	return list;
}

/*Procedimento que adiciona um novo elemento a lista de jogadores/mvp*/
void mvpPLayerListAdd(PtMVPPlayerlist list, AvgMVPPlayer avg) 
{
	if (list->size == list->capacity) { //em caso da capacidade ser igual ao size, ou seja nao haver mais espaco, existe uma realocacao do tamanho do array de elementos
		list->capacity *= 2;
		list->elements = (AvgMVPPlayer*)realloc(list->elements, list->capacity * sizeof(AvgMVPPlayer));
	}
	list->elements[list->size++] = avg;
}

/*Procedimento que imprime todos os jogadores da lista usando o playerPrint*/
void mvpPlayerListPrint(PtMVPPlayerlist list) {
	for (int i = 0; i < list->size; i++) {
		playerPrint(list->elements[i].player);
	}
}

/*Procedimento que destroi a lista*/
void mvpPlayerListDestroy(PtMVPPlayerlist * list)
{
	PtMVPPlayerlist curList = (*list);

	if (curList == NULL) return; //caso recebamos null, returnamos para nao existir erro

	free(curList->elements);
	free(curList);

	(*list) = NULL;
}
