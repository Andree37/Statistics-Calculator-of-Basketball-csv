#pragma once
#include "player.h"

typedef struct averageMVPPlayer {
	Player player;
	float avgMVP;
}AvgMVPPlayer;

AvgMVPPlayer avgMVPPlayerCreate(Player player, float avgMvp);

typedef struct mvpPlayerList {
	AvgMVPPlayer *elements;
	unsigned int size;
	unsigned int capacity;
}MVPPlayerList;

typedef  MVPPlayerList *PtMVPPlayerlist;

PtMVPPlayerlist mvpPlayerListCreate(unsigned int capacity);
void mvpPLayerListAdd(PtMVPPlayerlist list, AvgMVPPlayer avg);
void mvpPlayerListPrint(PtMVPPlayerlist list);
void mvpPlayerListDestroy(PtMVPPlayerlist *list);