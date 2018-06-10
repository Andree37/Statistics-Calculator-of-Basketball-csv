/* MINI-PROJETO 2 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/

/*Bibliotecas importadas*/
#include "cluster.h"
#include <stdlib.h>

/*Funcao que cria um cluster com as stats iniciais(em cima de uma estatistic ja existente) e devolve o*/
Cluster clusterCreate(Statistics stats)
{
	Cluster c;
	c.meanTwoPoints = stats.twoPoints;
	c.meanThreePoints = stats.threePoints;
	c.meanAssists = stats.assists;
	c.meanFouls = stats.fouls;
	c.meanBlocks = stats.blocks;
	c.members = listCreate(600); //criacao de uma lista (com espaco para 600 para haver seguranca) de membros 

	return c;
}

/*Funcao que alter o cluster para uma nova estatistica*/
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

/*Funcao que cria uma lista de clusters*/
PtClusterList clusterListCreate(unsigned int capacity)
{
	PtClusterList list = (PtClusterList)malloc(sizeof(ClusterList));

	list->capacity = capacity;
	list->size = 0;
	list->elements = (PtCluster)calloc(capacity, sizeof(Cluster));

	return list;
}

/*Procedimento que adiciona um novo cluster a lista de clusters*/
void clusterListAdd(PtClusterList list, Cluster cluster)
{
	list->elements[list->size++] = cluster;
}

/*Procedimento que destroi a lista*/
void clusterListDestroy(PtClusterList * list)
{
	PtClusterList curList = (*list);

	if (curList == NULL) return; //em caso de recebermos um null, retornamos e nao crashamos o programa

	free(curList->elements);
	free(curList);

	(*list) = NULL;
}

