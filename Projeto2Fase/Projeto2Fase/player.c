#include "player.h"
#include <string.h>


PtPlayer playerCreate(int id, char* name, char* team, Date bDate, char gender , Statistics statistics)
{
	PtPlayer player = (PtPlayer)malloc(sizeof(Player));

	player->id = id;
	strcpy_s(player->name, strlen(name), name);
	strcpy_s(player->team, strlen(team), team);
	player->birthDate = bDate;
	player->gender = gender;
	player->statistics = statistics;

	return player;
}

void playerPlayer(Player player) {

}
