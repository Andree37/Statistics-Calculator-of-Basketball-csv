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

typedef struct Cluster *PtCluster;

Cluster clusterCreate(Statistics stats);
Cluster clusterAlter(Cluster cluster, Statistics stats);
	

typedef struct clusterList {
	Cluster *elements;
	unsigned int size;
	unsigned int capacity;
}ClusterList;

typedef ClusterList* PtClusterList;

PtClusterList clusterListCreate(unsigned int capacity);
void clusterListAdd(PtClusterList list, Cluster cluster);
void clusterListDestroy(PtClusterList *list);