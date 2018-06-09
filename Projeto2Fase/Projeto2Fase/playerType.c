#include <stdio.h>
#include <string.h>
#include "playerType.h"

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

void playerTypePrint(PlayerType pType) {
	printf("| %5.2f   |  %5.2f   |  %5.2f   |  %5.2f   |  %5.2f   |  %5.2f  |  %5.2f  |  %5.2f  |  %5.2f  |  %5.2f  |", pType.avgTwoPoints, pType.allAvgTwoPoints, pType.avgThreePoints, pType.allAvgThreePoints, 
		pType.avgFouls, pType.allAvgFouls, pType.avgAssists, pType.allAvgAssists, pType.avgBlocks, pType.allAvgBlocks);
}