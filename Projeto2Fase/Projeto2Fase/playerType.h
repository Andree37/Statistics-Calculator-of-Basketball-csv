#pragma once

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

typedef PlayerType* PtPlayerType;

PlayerType playerTypeCreate(char type[20], float avgTwoPoints, float allAvgTwoPoints,float avgThreePoints, float allAvgThreePoints, 
	float avgBlocks, float allAvgBlocks, float avgAssists, float allAvgAssists, float avgFouls, float allAvgFouls);
void playerTypePrint(PlayerType pType);