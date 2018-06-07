#include "commands.h"
#include "statistics.h"
#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include "input.h"

char** split(char *str, int nFields, const char *delim);
void load(char *playerFile, char *statsFile, PtList list);
void show(PtList list);
void clear(PtList list);
void sort(PtList list);



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

int equalsStringIgnoreCase(char str1[], char str2[]) /* Esta funcao devolve true se as strings que recebem forem iguas, independente do 'case', false se nao */
{
	stringToUpper(str1);
	return (strcmp(str1, str2) == 0);
}

void stringToUpper(char * str) /* transforma a string num 'upper case' da mesma */
{
	char *s = str;
	while (*s) {
		*s = toupper((unsigned char)*s);
		s++;
	}
}

void commandLoad(PtList list) {
	if (list != NULL) {
		char commandP[21];
		char commandS[21];
		printf("Introduza o ficheiro dos jogadores: ");
		gets_s(commandP, sizeof(commandP));
		printf("/nIntroduza o ficheiro dos jogos: ");
		gets_s(commandS, sizeof(commandS));
		printf("\n");

		if (strstr(commandP, "players") != 0 && strstr(commandS, "games") != 0) {
			load(commandP, commandS, list);
		}
		else {
			printf("A introducao dos nomes dos ficheiros esta errada.\n");
		}
	}
	else {
		printf("Erro interno, nao existe uma lista para suportar este comando");
	}
}

void commandShow(PtList list) {
	if (list != NULL) {
		show(list);
	}
	else {
		printf("Erro interno, nao existe uma lista para suportar este comando");
	}
}

void commandClear(PtList list) {
	if (list != NULL) {
		clear(list);
	}
	else {
		printf("Erro interno, nao existe uma lista para suportar este comando");
	}
}

void commandSort(PtList list) {
	if (list != NULL) {
		sort(list);
	}
	else {
		printf("Erro interno, nao existe uma lista para suportar este comando");
	}
}

void load(char *playerFile, char *statsFile, PtList list) {
	FILE *fd;
	FILE *fd2;
	int err = fopen_s(&fd, statsFile, "r");
	int err2 = fopen_s(&fd2, playerFile, "r");

	if (err != 0) {
		printf("Nao foi possivel abrir o ficheiro %s ...\n", statsFile);
		return;
	}
	if (err2 != 0) {
		printf("Nao foi possivel abrir o ficheiro %s ...\n", playerFile);
		return;
	}

	char nextline[1024];

	int countPlayers = 0;
	int countGames = 0;

	while (fgets(nextline, sizeof(nextline), fd2)) {
		if (strlen(nextline) < 1)
			continue;

		char **tokens = split(nextline, 5, ";");

		int playerId = atoi(tokens[0]);
		char* name = tokens[1];

		char* team = tokens[2];

		int day, month, year;
		sscanf_s(tokens[3], "%d/%d/%d", &day, &month, &year);

		char gender = tokens[4][0];

		Date date = dateCreate(day, month, year);

		Statistics stat = statisticsCreateZeros();

		Player player = playerCreate(playerId, name, team, date, gender, stat);

		listAdd(list, countPlayers, player);

		countPlayers++;

		free(tokens);

	}

	fclose(fd2);

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

		Player player;

		int size;
		listSize(list, &size);

		for (int i = 0; i < size; i++) {
			listGet(list, i, &player);
			if (player.id == playerId) {
				Statistics stats = statisticsCreate(two, three, assists, fouls, blocks);
				Statistics newStats;
				newStats = statisticsAdd(player.statistics, stats);
				Player newPlayer = playerCreate(player.id, player.name, player.team, player.birthDate, player.gender, newStats);
				listSet(list, i, newPlayer, &player);
			}
		}

		free(tokens);
		countGames++;


	}
	printf("\n\nForam lidos %d jogadores... \n", countPlayers);
	printf("\nForam lidos %d estatisticas... \n", countGames);

	fclose(fd);

	return list;
}

void show(PtList list) {
	int size;
	listSize(list, &size);
	ListElem elem;

	if (size == 0) {
		printf("Nao existe nenhum registo na tabela");
		return;
	}
	printf("Jogador  ID |         Nome         |   Equipa        |    Data    |Sexo|2Points  | 3Points  | Assists  | Fouls    | Blocks   | Games  |\n");
	for (int i = 0; i < size; i++) {
		listGet(list, i, &elem);
		listElemPrint(elem);
	}
}

void clear(PtList list) {
	listClear(list);
	printf("Lista limpa");
}

void sort(PtList list) {
	int size;
	listSize(list, &size);
	ListElem elem;
	ListElem elem2;

	char* name = "NOME";
	char* date = "DATA";
	char* games = "JOGOS";
	char option[10];

	PtList clone = listCreate(size);

	if (size > 0) {

		for (int i = 0; i < size; i++) {
			listGet(list, i, &elem);
			listAdd(clone, i, elem);
		}

		printf("Escolha a maneira de ordenacao\n\n");
		printf("Nome - para a ordenacao pelo nome\n");
		printf("Data - para a ordenacao pela Data de nascimento\n");
		printf("Jogos - para a ordenacao pelos numeros de jogos jogados\n");

		gets_s(option, sizeof(option));


		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - i - 1; j++) {
				listGet(clone, j, &elem);
				listGet(clone, j + 1, &elem2);
				if ((equalsStringIgnoreCase(option, name) != 0)) {
					if (strcmp(elem.name, elem2.name) > 0) {
						listSet(clone, j, elem2, &elem);
						listSet(clone, j + 1, elem, &elem2);
					}
				}

				if ((equalsStringIgnoreCase(option, date) != 0)) {
					if (isYoungerThan(elem.birthDate, elem2.birthDate)) {
						listSet(clone, j, elem2, &elem);
						listSet(clone, j + 1, elem, &elem2);
					}
				}

				if ((equalsStringIgnoreCase(option, games) != 0)) {
					if (elem.statistics.gamesPlayed > elem2.statistics.gamesPlayed) {
						listSet(clone, j, elem2, &elem);
						listSet(clone, j + 1, elem, &elem2);
					}
				}
			}
		}

		listPrint(clone);
	}
	else {
		printf("Lista sem registos\n");
	}
}


