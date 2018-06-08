#include "averageMVPPlayer.h"
#include <stdio.h>
#include <stdlib.h>

AvgMVPPlayer avgMVPPlayerCreate(Player player, float avgMvp)
{
	AvgMVPPlayer mvpPlayer;
	mvpPlayer.avgMVP = avgMvp;
	mvpPlayer.player = player;
	return mvpPlayer;
}

PtMVPPlayerlist mvpPlayerListCreate(unsigned int capacity)
{
	MVPPlayerList* list = (MVPPlayerList*)malloc(sizeof(MVPPlayerList));
	if (list == NULL) printf("1");
	list->capacity = capacity;
	list->size = 0;
	list->elements = (AvgMVPPlayer*)calloc(capacity, sizeof(AvgMVPPlayer));

	return list;
}

void mvpPLayerListAdd(PtMVPPlayerlist list, AvgMVPPlayer avg) 
{
	if (list->size == list->capacity) {
		list->capacity *= 2;
		list->elements = (AvgMVPPlayer*)realloc(list->elements, list->capacity * sizeof(AvgMVPPlayer));
	}
	list->elements[list->size++] = avg;
}

void mvpPlayerListPrint(PtMVPPlayerlist list) {
	for (int i = 0; i < list->size; i++) {
		playerPrint(list->elements[i].player);
	}
}
