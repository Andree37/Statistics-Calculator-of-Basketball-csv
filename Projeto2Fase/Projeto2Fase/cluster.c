#include "cluster.h"

PtCluster createCluster(float meanTwoPoints, float meanThreePoints, float meanAssists, float meanFouls, float meanBlocks)
{
	//PtCluster c = (PtCluster)malloc(sizeof(Cluster));
	Cluster c;
	c.meanTwoPoints = meanTwoPoints;
	c.meanThreePoints = meanThreePoints;
	c.meanAssists = meanAssists;
	c.meanFouls = meanFouls;
	c.meanBlocks = meanBlocks;
	c.members = listCreate(600);
}
