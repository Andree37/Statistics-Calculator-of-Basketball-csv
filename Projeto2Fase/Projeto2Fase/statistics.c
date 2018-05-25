#include "statistics.h"

PtStatistics statisticsCreate(float two, float three, float assists, float fouls, float games)
{
	PtStatistics x = (PtStatistics)malloc(sizeof(Statistics));
	x->twoPoints = two;
	x->threePoints = three;
	x->assists = assists;
	x->fouls = fouls;
	x->gamesPlayed = games;

	return x;
}
