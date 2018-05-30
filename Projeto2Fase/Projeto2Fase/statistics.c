#include <stdlib.h>

#include "statistics.h"


PtStatistics statisticsCreate(float two, float three, float assists, float fouls, float blocks)
{
	PtStatistics stats = (PtStatistics)malloc(sizeof(Statistics));
	stats->twoPoints = two;
	stats->threePoints = three;
	stats->assists = assists;
	stats->fouls = fouls;
	stats->blocks = blocks;
	stats->gamesPlayed = 0;

	return stats;
}

void statisticsAdd(PtStatistics reciever, PtStatistics giver)
{
	if (reciever == NULL) {
		statisticsCreate(0, 0, 0, 0, 0); //if there is no stats to recieve
	}
	if (giver != NULL && reciever != NULL) {
		reciever->assists += giver->assists;
		reciever->twoPoints += giver->twoPoints;
		reciever->threePoints += giver->threePoints;
		reciever->fouls += giver->fouls;
		reciever->blocks += giver->blocks;
		reciever->gamesPlayed++;
	}
}

PtStatisticsList statisticsListCreate(unsigned int capacity) /* funcao 'construtora' da estrutura de dados statisticsList, retorna uma estrutura de dados para guardar estatisticas de jogos */
{
	PtStatisticsList list = (PtStatistics)malloc(sizeof(Statistics));
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
