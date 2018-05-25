#include "player.h"
#include <string.h>


PtPlayer playerCreate(int id, char* name, char* team, Date bDate, char gender, Statistics statistics)
{
	PtPlayer x = (PtPlayer)malloc(sizeof(Player));

	x->id = id;
	strcpy_s(x->name, strlen(name), name);
	strcpy_s(x->team, strlen(team), team);
	x->birthDate = bDate;
	x->gender = gender;
	x->statistics = statistics;

	return x;
}
