/* MINI-PROJETO 2 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/

#pragma once

/*Bibliotecas importadas*/
#include "date.h"
#include "statistics.h"

/*Estrutura de dados capaz de guardar informacoes sobre o jogador e as suas estatisticas*/
typedef struct player {
	int id;
	char name[50];
	char team[50];
	Date birthDate;
	char gender;
	Statistics statistics; /* valores acumulados para todos os jogos disputados */
} Player;

/* tipo definido para ponteiro de jogador */
typedef Player *PtPlayer;

/* definicao de prototipos de funcoes */
Player playerCreate(int id, char* name, char* team, Date bDate, char gender, Statistics statistics);
void playerPrint(Player player);


