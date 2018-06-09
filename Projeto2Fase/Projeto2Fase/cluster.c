#include "cluster.h"

Cluster createCluster(Statistics stats)
{
	//PtCluster c = (PtCluster)malloc(sizeof(Cluster));
	Cluster c;
	c.meanTwoPoints = stats.twoPoints;
	c.meanThreePoints = stats.threePoints;
	c.meanAssists = stats.assists;
	c.meanFouls = stats.fouls;
	c.meanBlocks = stats.blocks;
	c.members = listCreate(600);

	return c;
}

Cluster alterCluster(Cluster cluster, Statistics stats)
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
