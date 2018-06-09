#include "cluster.h"
#include <stdlib.h>

Cluster clusterCreate(Statistics stats)
{
	Cluster c;
	c.meanTwoPoints = stats.twoPoints;
	c.meanThreePoints = stats.threePoints;
	c.meanAssists = stats.assists;
	c.meanFouls = stats.fouls;
	c.meanBlocks = stats.blocks;
	c.members = listCreate(600);

	return c;
}

Cluster clusterAlter(Cluster cluster, Statistics stats)
{
	Cluster c;
	
	c.meanTwoPoints = stats.twoPoints;
	c.meanThreePoints = stats.threePoints;
	c.meanAssists = stats.assists;
	c.meanFouls = stats.fouls;
	c.meanBlocks = stats.blocks;
	c.members = cluster.members;

	return c;
}

PtClusterList clusterListCreate(unsigned int capacity)
{
	PtClusterList list = (PtClusterList)malloc(sizeof(ClusterList));

	list->capacity = capacity;
	list->size = 0;
	list->elements = (PtCluster)calloc(capacity, sizeof(Cluster));

	return list;
}

void clusterListAdd(PtClusterList list, Cluster cluster)
{
	list->elements[list->size++] = cluster;
}

void clusterListDestroy(PtClusterList * list)
{
	PtClusterList curList = (*list);

	if (curList == NULL) return;

	free(curList->elements);
	free(curList);

	(*list) = NULL;
}

