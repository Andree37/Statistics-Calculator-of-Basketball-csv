#include <stdlib.h>

#include "statistics.h"


Statistics statisticsCreate(float two, float three, float assists, float fouls, float blocks)
{
	Statistics stats;
	stats.twoPoints = two;
	stats.threePoints = three;
	stats.assists = assists;
	stats.fouls = fouls;
	stats.blocks = blocks;
	stats.gamesPlayed = 0;

	return stats;
}

//Cria uma estatisticas com tudo a zeros
Statistics statisticsCreateZeros()
{
	Statistics stats = statisticsCreate(0,0,0,0,0);

	return stats;
}

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

PtStatisticsList statisticsListCreate(unsigned int capacity) /* funcao 'construtora' da estrutura de dados statisticsList, retorna uma estrutura de dados para guardar estatisticas de jogos */
{
	PtStatisticsList list = (PtStatisticsList)malloc(sizeof(StatisticsList));
	list->capacity = capacity;
	list->size = 0;
	list->elements = (Statistics*)calloc(capacity, sizeof(Statistics));
	return list;
}

void statisticsListAdd(PtStatistics stats, PtStatisticsList list) /* procedimento para adicionar uma nova estatistica de jogos a lista */
{
	if (list->size == list->capacity) {
		list->capacity *= 2;
		list->elements = (Statistics*)realloc(list->elements, list->capacity * sizeof(Statistics));
	}
	list->elements[list->size++] = *stats;
}

void statisticsListDestroy(PtStatisticsList list) /* procedimento que liberta o array e coloca o resto dos atributos num valor nulo */
{
	list->capacity = 0;
	list->size = 0;
	free(list->elements);
}

void statisticsPrint(Statistics stats) {
	printf("| %5.2f   |  %5.2f   |  %5.2f   |  %5.2f   |  %5.2f   |  %4d  |", stats.twoPoints, stats.threePoints, stats.assists, stats.fouls, stats.blocks, stats.gamesPlayed);
}