/* MINI-PROJETO 2 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/

/*Bibliotecas importadas*/
#include <stdlib.h>
#include "statistics.h"

/*Funcao que devolve uma nova estatistica criada com os jogos a 0*/
Statistics statisticsCreate(float two, float three, float assists, float fouls, float blocks)
{
	Statistics stats;
	stats.twoPoints = two;
	stats.threePoints = three;
	stats.assists = assists;
	stats.fouls = fouls;
	stats.blocks = blocks;
	stats.gamesPlayed = 0;
	stats.mvp = 0;

	return stats;
}

/*Funcao que devolve uma estatistica criada com tudo a 0*/
Statistics statisticsCreateZeros()
{
	Statistics stats = statisticsCreate(0,0,0,0,0);

	return stats;
}

/*Funcao que devolve uma estatistica com a soma entre a estatistica doadora e a que recebe*/
Statistics statisticsAdd(Statistics reciever, Statistics giver, int games)
{
	if (games != 0) {
		reciever.gamesPlayed = games;
	}else
		reciever.gamesPlayed++;

		reciever.assists += giver.assists;
		reciever.twoPoints += giver.twoPoints;
		reciever.threePoints += giver.threePoints;
		reciever.fouls += giver.fouls;
		reciever.blocks += giver.blocks;
		

		return reciever;
}

/*Procedimento que mostra na consola as estatisticas*/
void statisticsPrint(Statistics stats) {
	printf("| %5.2f   |  %5.2f   |  %5.2f   |  %5.2f   |  %5.2f   |  %4d  |", stats.twoPoints, stats.threePoints, stats.fouls, stats.assists, stats.blocks, stats.gamesPlayed);
}