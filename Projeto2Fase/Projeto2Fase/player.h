#pragma once

#include "date.h"
#include "statistics.h"

typedef struct player {
	int id;
	char name[50];
	char team[50];
	Date birthDate;
	char gender;
	Statistics statistics; /* valores acumulados para todos os jogos disputados */
} Player;

typedef Player *PtPlayer;

Player playerCreate(int id, char* name, char* team, Date bDate, char gender, Statistics statistics);
void playerPrint(Player player);


