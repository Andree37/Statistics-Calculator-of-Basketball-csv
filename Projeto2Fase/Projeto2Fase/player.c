#include "player.h"
#include <string.h>


Player playerCreate(int id, char* name, char* team, Date bDate, char gender , Statistics statistics)
{
	Player player;

	player.id = id;
	strcpy_s(player.name, sizeof(player.name), name);
	strcpy_s(player.team, sizeof(player.team), team);
	player.birthDate = bDate;
	player.gender = gender;
	player.statistics = statistics;

	return player;
}

void playerPrint(Player player) {
	printf("Jogador %3d : %-20s | %-15s | %02d/%02d/%04d | %c   ",
		player.id, player.name, player.team, player.birthDate.day, player.birthDate.month, player.birthDate.year, player.gender);
	statisticsPrint(player.statistics);
	printf("\n");
}
