/* MINI-PROJETO 2 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/

#pragma once

/*Bibliotecas importadas*/
#include "player.h"

/*Estrutura de dados que guarda um jogador e o seu MVP*/
typedef struct averageMVPPlayer {
	Player player;
	float avgMVP;
}AvgMVPPlayer;

/* definicao de prototipos de funcoes*/
AvgMVPPlayer avgMVPPlayerCreate(Player player, float avgMvp);

/*Estrutura de dados de uma lista de jogadores e o seu MVP*/
typedef struct mvpPlayerList {
	AvgMVPPlayer *elements;
	unsigned int size;
	unsigned int capacity;
}MVPPlayerList;

/*Tipo definido ponteiro para a lista*/
typedef  MVPPlayerList *PtMVPPlayerlist;

/* definicao de prototipos de funcoes*/
PtMVPPlayerlist mvpPlayerListCreate(unsigned int capacity);
void mvpPLayerListAdd(PtMVPPlayerlist list, AvgMVPPlayer avg);
void mvpPlayerListPrint(PtMVPPlayerlist list);
void mvpPlayerListDestroy(PtMVPPlayerlist *list);