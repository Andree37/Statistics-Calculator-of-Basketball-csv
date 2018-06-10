/* MINI-PROJETO 2 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/

#pragma once

/*Estrutura de dados capaz de guardar o tipo, a media do jogador e media geral*/
typedef struct playerType {
	char type[20];

	float avgTwoPoints;
	float allAvgTwoPoints;

	float avgThreePoints;
	float allAvgThreePoints;

	float avgBlocks;
	float allAvgBlocks;

	float avgAssists;
	float allAvgAssists;

	float avgFouls;
	float allAvgFouls;
}PlayerType;

/* tipo definido para ponteiro de playerType */
typedef PlayerType* PtPlayerType;

/* definicao de prototipos de funcoes */
PlayerType playerTypeCreate(char type[20], float avgTwoPoints, float allAvgTwoPoints,float avgThreePoints, float allAvgThreePoints, 
	float avgBlocks, float allAvgBlocks, float avgAssists, float allAvgAssists, float avgFouls, float allAvgFouls);
void playerTypePrint(PlayerType pType);