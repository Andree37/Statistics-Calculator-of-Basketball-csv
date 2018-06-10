/* MINI-PROJETO 2 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/

#pragma once

/*Bibliotecas importadas*/
#include "list.h"

/*Estrutura de dados que guarda um cluster e os seus membros numa numa Lista*/
typedef struct cluster {
	float meanTwoPoints;
	float meanThreePoints;
	float meanAssists;
	float meanFouls;
	float meanBlocks;
	PtList members;
}Cluster;

/*Tipo definido ponteiro para o cluster*/
typedef struct Cluster *PtCluster;

/* definicao de prototipos de funcoes*/
Cluster clusterCreate(Statistics stats);
Cluster clusterAlter(Cluster cluster, Statistics stats);
	
/*Estrutura de dados de uma lista de clusters*/
typedef struct clusterList {
	Cluster *elements;
	unsigned int size;
	unsigned int capacity;
}ClusterList;

/*Tipo definido ponteiro para a lista de clusters*/
typedef ClusterList* PtClusterList;

/* definicao de prototipos de funcoes*/
PtClusterList clusterListCreate(unsigned int capacity);
void clusterListAdd(PtClusterList list, Cluster cluster);
void clusterListDestroy(PtClusterList *list);