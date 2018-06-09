#pragma once

#include "list.h"

typedef struct cluster {
	float meanTwoPoints;
	float meanThreePoints;
	float meanAssists;
	float meanFouls;
	float meanBlocks;
	PtList members;
}Cluster;

typedef struct Cluster* PtCluster;

PtCluster createCluster(float meanTwoPoints, float meanThreePoints, float meanAssists, float meanFouls, float meanBlocks);
	