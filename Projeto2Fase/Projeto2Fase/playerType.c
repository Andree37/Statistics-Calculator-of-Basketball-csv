/* MINI-PROJETO 2 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/

/*Bibliotecas importadas*/
#include <stdio.h>
#include <string.h>
#include "playerType.h"

/*Funcao responsavel de criar um novo player type*/
PlayerType playerTypeCreate(char type[20], float avgTwoPoints, float allAvgTwoPoints, float avgThreePoints, float allAvgThreePoints, float avgBlocks, float allAvgBlocks, float avgAssists, float allAvgAssists, float avgFouls, float allAvgFouls)
{
	PlayerType pType;

	strcpy_s(pType.type, sizeof(pType.type), type);
	pType.avgTwoPoints = avgTwoPoints;
	pType.allAvgTwoPoints = allAvgTwoPoints;
	pType.avgThreePoints = avgThreePoints;
	pType.allAvgThreePoints = allAvgThreePoints;
	pType.avgBlocks = avgBlocks;
	pType.allAvgBlocks = allAvgBlocks;
	pType.avgAssists = avgAssists;
	pType.allAvgAssists = allAvgAssists;
	pType.avgFouls = avgFouls;
	pType.allAvgFouls = allAvgFouls;

	return pType;
}

/*Procedimento que mostra na consola os valores dos playerType*/
void playerTypePrint(PlayerType pType) {
	printf("%-15s| %5.2f   |  %5.2f   |  %5.2f   |  %5.2f   |  %5.2f   |  %5.2f  |  %5.2f  |  %5.2f  |  %5.2f  |  %5.2f  |",pType.type, pType.avgTwoPoints, pType.allAvgTwoPoints, pType.avgThreePoints, pType.allAvgThreePoints, 
		pType.avgFouls, pType.allAvgFouls, pType.avgAssists, pType.allAvgAssists, pType.avgBlocks, pType.allAvgBlocks);
}