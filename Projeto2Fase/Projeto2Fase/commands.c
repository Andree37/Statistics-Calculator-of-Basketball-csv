#include "commands.h"
#include "statistics.h"
#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include "input.h"

char** split(char *str, int nFields, const char *delim);
void createStatistics();


char** split(char *str, int nFields, const char *delim) {

	char **tokens = malloc(sizeof(char*) * nFields);

	int index = 0;
	char *next_token = NULL;

	char *token = strtok_s(str, delim, &next_token);
	while (token) {
		tokens[index++] = token;
		token = strtok_s(NULL, delim, &next_token);
	}

	return tokens;
}

void commandLoad(PtList list) {
	char commandP[21];
	char commandS[21];
	printf("Introduza o ficheiro dos jogadores\n");
	readCharArray(&commandP, 21);
	printf("Introduza o ficheiro das estatiscas\n");
	readCharArray(&commandS, 21);

	load(commandP, commandS, list);
}


void load(char *playerFile, char *statsFile, PtList list) {
	//PtList list = listCreate(300);
	FILE *fd, *fd2;
	int err = fopen_s(&fd, statsFile, "r");
	int err2 = fopen_s(&fd2, playerFile, "r");

	if (err != 0) {
		printf("Nao foi possivel abrir o ficheiro %s ...\n", statsFile);
		return list;
	}
	if (err2 != 0) {
		printf("Nao foi possivel abrir o ficheiro %s ...\n", statsFile);
		return list;
	}

	char nextline[1024];

	int countStatistics = 0;
	int countPlayers = 0;
	int countGames = 0;
	PtStatistics stats;
	PtStatisticsList statslist = statisticsListCreate(600);
	PtStatistics newstats;


	while (fgets(nextline, sizeof(nextline), fd2)) {
		if (strlen(nextline) < 1)
			continue;

		char **tokens = split(nextline, 7, ";");

		int playerId = atoi(tokens[0]);
		char* name = atoi(tokens[1]);//nao faz nada de momento
		strcpy_s(name, strlen(tokens[1]), tokens[1]);

		char* team=(char*)malloc(sizeof(char))	;//= atof(tokens[2]);
			strcpy_s(team, strlen(tokens[2]), tokens[2]);

		int day = atof(tokens[3]);
		int month = atof(tokens[4]);
		int year = atof(tokens[5]);

		char gender = atof(tokens[6]);

		
		Date d = dateCreate(day, month, year);

		PtStatistics stat = statisticsCreateZeros();

		PtPlayer p= playerCreate(playerId, name, team, d, gender, stat);

		listAdd(list, countPlayers, *p);

		countPlayers++;

		fclose(fd2);
	}


	while (fgets(nextline, sizeof(nextline), fd)) {
		if (strlen(nextline) < 1)
			continue;

		char **tokens = split(nextline, 7, ";");

		int playerId = atoi(tokens[0]);
		int idGame = atoi(tokens[1]);//nao faz nada de momento
		int two = atof(tokens[2]);
		int three = atof(tokens[3]);
		int assists = atof(tokens[4]);
		int fouls = atof(tokens[5]);
		int blocks = atof(tokens[6]);

		PtPlayer p=(PtPlayer)malloc(sizeof(Player));// = playerCreate(0, "", "", NULL, "", NULL);
		int size;
		listSize(list, &size);

		for (int i = 0; i < size; i++) {
			listGet(list, i, p);
			if(p->id == playerId) {
				statisticsAdd(&p->statistics, statisticsCreate(two, three, assists, fouls, blocks));
			}

		}
		
		free(tokens);
		countGames++;
		

	}
	printf("\n\nForam lidos %d jogadores... \n", countPlayers);
	printf("\nForam lidos %d estatisticas... \n", countPlayers);

	fclose(fd);

	return list;
}

void createStatistics() {

}
