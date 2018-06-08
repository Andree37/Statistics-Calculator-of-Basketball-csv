#include "commands.h"
#include "statistics.h"
#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include "input.h"
#include "averageMVPPlayer.h"


void commandNorm(PtList list);
void commandAvg(PtList list);

char** split(char *str, int nFields, const char *delim);
void load(char *playerFile, char *statsFile, PtList list);
void show(PtList list);
void clear(PtList list);
void sort(PtList list);
PtList createClone(PtList list);
Statistics averageCalculation(Statistics stat);
PtList averageStatistics(PtList players);

void calculateMax(PtList list, float* two, float* three, float* assists, float* fouls, float* blocks);
void calculateMin(PtList list, float* two, float* three, float* assists, float* fouls, float* blocks);
float normalizationCalculation(float max, float min, float val);
Statistics statNormalizationCalculation(Statistics stat, float* twoMa, float* threeMa, float* assistsMa, float* foulsMa, float* blocksMa,
	float* twoMi, float* threeMi, float* assistsMi, float* foulsMi, float* blocksMi);
void norm(PtList list);
PtList normalizeStatistics(PtList players);


Statistics averageAllStats(PtList list);

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

PtList createClone(PtList list) {
	int size;
	listSize(list, &size);
	ListElem elem;

	if (size > 0) {

		PtList clone = listCreate(size);

		for (int i = 0; i < size; i++) {
			listGet(list, i, &elem);
			listAdd(clone, i, elem);
		}
		return clone;
	}
	return NULL;
}

PtList averageStatistics(PtList players) {
	Player player;
	Player avgPlayer;
	Statistics avgStats;
	int size;
	int index = 0;
	listSize(players, &size);
	PtList avgList = listCreate(size);

	if (players != NULL) {

		for (int i = 0; i < size; i++) {
			listGet(players, i, &player);
			if (player.statistics.gamesPlayed > 0) {

				avgStats = statisticsAdd(statisticsCreateZeros(), averageCalculation(player.statistics), player.statistics.gamesPlayed);
				avgPlayer = playerCreate(player.id, player.name, player.team, player.birthDate, player.gender, avgStats);
				listAdd(avgList, index++, avgPlayer);
			}
		}
	}
	return avgList;
}

Statistics averageCalculation(Statistics stat) {
	Statistics avg;
	int games = stat.gamesPlayed;
	if (games != 0) {
		avg.twoPoints = stat.twoPoints / games;
		avg.threePoints = stat.threePoints / games;
		avg.assists = stat.assists / games;
		avg.fouls = stat.fouls / games;
		avg.blocks = stat.blocks / games;
		avg.gamesPlayed = games;
	}

	return avg;
}

void commandLoad(PtList list) {
	if (list != NULL) {
		char commandP[21];

		char commandS[21];


		printf("Introduza o ficheiro dos jogadores: ");
		gets_s(commandP, sizeof(commandP));
		printf("Introduza o ficheiro dos jogos: ");
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

void commandAvg(PtList list) {
	if (list != NULL) {
		avg(list);
	}
	else {
		printf("Erro interno, nao existe uma lista para suportar este comando");
	}
}

void commandNorm(PtList list) {
	if (list != NULL) {
		norm(list);
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
				Statistics stats = statisticsCreate(two, three, fouls, assists, blocks);
				Statistics newStats;
				newStats = statisticsAdd(player.statistics, stats, 0);
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
	printf("Jogador  ID |         Nome         |   Equipa        |    Data    |Sexo|2Points  | 3Points  |   Fouls  | Assists  | Blocks   | Games  |\n");
	for (int i = 0; i < size; i++) {
		listGet(list, i, &elem);
		listElemPrint(elem);
		printf("\n");
	}
}

void clear(PtList list) {
	listClear(list);
	printf("Lista limpa");
}

void sort(PtList list) {
	int changed = 1;

	ListElem elem;
	ListElem elem2;

	char* name = "NOME";
	char* date = "DATA";
	char* games = "JOGOS";
	char option[10];

	PtList clone = createClone(list);

	int size;
	listSize(clone, &size);

	if (clone != NULL) {




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
				else if ((equalsStringIgnoreCase(option, date) != 0)) {
					if (isYoungerThan(elem.birthDate, elem2.birthDate)) {
						listSet(clone, j, elem2, &elem);
						listSet(clone, j + 1, elem, &elem2);
					}
				}
				else if ((equalsStringIgnoreCase(option, games) != 0)) {
					if (elem.statistics.gamesPlayed > elem2.statistics.gamesPlayed) {
						listSet(clone, j, elem2, &elem);
						listSet(clone, j + 1, elem, &elem2);
					}
				}
				else {
					changed = 0;
				}
			}
		}
		if (changed)
			listPrint(clone);
		else {
			printf("Input invalido. Por favor insira Nome, Jogos ou Data.");
		}
	}
	else {
		printf("Lista sem registos\n");
	}
	listDestroy(&clone);
}

void avg(PtList list) {
	PtList avgList = averageStatistics(list);
	Player player;
	Statistics avgStats;
	float avgMVP;
	int size;
	listSize(avgList, &size);

	PtMVPPlayerlist avgMVPList = mvpPlayerListCreate(size);
	AvgMVPPlayer playerAVG;

	if (size > 0) {
		for (int i = 0; i < size; i++) {
			listGet(avgList, i, &player);
			avgStats = player.statistics;
			avgMVP = 3 * avgStats.threePoints + 2 * avgStats.twoPoints + avgStats.assists + 2 * avgStats.blocks - (3 * avgStats.fouls);
			playerAVG = avgMVPPlayerCreate(player, avgMVP);
			mvpPLayerListAdd(avgMVPList, playerAVG);
		}

		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - i - 1; j++) {
				if (avgMVPList->elements[j].avgMVP < avgMVPList->elements[j + 1].avgMVP) {
					AvgMVPPlayer aux = avgMVPList->elements[j];
					avgMVPList->elements[j] = avgMVPList->elements[j + 1];
					avgMVPList->elements[j + 1] = aux;
				}
			}
		}
		printf("Jogador  ID |         Nome         |   Equipa        |    Data    |Sexo|2Points  | 3Points  | Assists  | Fouls    | Blocks   | Games  |\n");

		mvpPlayerListPrint(avgMVPList);
	}
}

void norm(PtList list) {

	PtList toNormList = averageStatistics(list);

	PtList normalizedList = normalizeStatistics(toNormList);

	listPrint(normalizedList);
	listDestroy(&toNormList);

	listDestroy(&normalizedList);

}

void calculateMax(PtList list, float* two, float* three, float* assists, float* fouls, float* blocks) {
	int size;
	listSize(list, &size);
	Player player;
	listGet(list, 0, &player);

	Statistics stat = player.statistics;

	*two = stat.twoPoints;
	*three = stat.threePoints;
	*assists = stat.assists;
	*fouls = stat.fouls;
	*blocks = stat.blocks;

	for (int i = 1; i < size; i++) {
		listGet(list, i, &player);
		stat = player.statistics;
		if (stat.gamesPlayed > 0) {
			if (*two < stat.twoPoints)
				*two = stat.twoPoints;

			if (*three < stat.threePoints)
				*three = stat.threePoints;

			if (*assists < stat.assists)
				*assists = stat.assists;

			if (*fouls < stat.fouls)
				*fouls = stat.fouls;

			if (*blocks < stat.blocks)
				*blocks = stat.blocks;
		}
	}
}

void calculateMin(PtList list, float* two, float* three, float* assists, float* fouls, float* blocks) {
	int size;
	listSize(list, &size);
	Player player;
	listGet(list, 0, &player);

	Statistics stat = player.statistics;

	*two = stat.twoPoints;
	*three = stat.threePoints;
	*assists = stat.assists;
	*fouls = stat.fouls;
	*blocks = stat.blocks;

	for (int i = 1; i < size; i++) {
		listGet(list, i, &player);
		stat = player.statistics;
		if (stat.gamesPlayed > 0) {
			if (*two > stat.twoPoints)
				*two = stat.twoPoints;

			if (*three > stat.threePoints)
				*three = stat.threePoints;

			if (*assists > stat.assists)
				*assists = stat.assists;

			if (*fouls > stat.fouls)
				*fouls = stat.fouls;

			if (*blocks > stat.blocks)
				*blocks = stat.blocks;
		}
	}
}

PtList normalizeStatistics(PtList players) {

	float twoMax, twoMin;
	float threeMax, threeMin;
	float assistsMax, assistsMin;
	float foulsMax, foulsMin;
	float blocksMax, blocksMin;


	int size;
	listSize(players, &size);

	calculateMax(players, &twoMax, &threeMax, &assistsMax, &foulsMax, &blocksMax);
	calculateMin(players, &twoMin, &threeMin, &assistsMin, &foulsMin, &blocksMin);


	Player player;
	PtList normList = listCreate(size);
	Statistics normStats;
	Statistics stats;
	int index = 0;
	if (players != NULL) {

		for (int i = 0; i < size; i++) {
			listGet(players, i, &player);
			if (player.statistics.gamesPlayed > 0) {
				stats = statNormalizationCalculation(player.statistics, &twoMax, &threeMax, &assistsMax, &foulsMax, &blocksMax,
					&twoMin, &threeMin, &assistsMin, &foulsMin, &blocksMin);
				normStats = statisticsAdd(statisticsCreateZeros(), stats, player.statistics.gamesPlayed);
				Player avgPlayer = playerCreate(player.id, player.name, player.team, player.birthDate, player.gender, normStats);
				listAdd(normList, index++, avgPlayer);
			}
		}
	}
	return normList;
}

float normalizationCalculation(float max, float min, float val) {

	return (val - min) / (max - min);

}

Statistics statNormalizationCalculation(Statistics stat, float* twoMa, float* threeMa, float* assistsMa, float* foulsMa, float* blocksMa,
	float* twoMi, float* threeMi, float* assistsMi, float* foulsMi, float* blocksMi) {

	Statistics norm;
	int games = stat.gamesPlayed;
	if (games != 0) {
		norm.twoPoints = normalizationCalculation(*twoMa, *twoMi, stat.twoPoints);
		norm.threePoints = normalizationCalculation(*threeMa, *threeMi, stat.threePoints);
		norm.assists = normalizationCalculation(*assistsMa, *assistsMi, stat.assists);
		norm.fouls = normalizationCalculation(*foulsMa, *foulsMi, stat.fouls);
		norm.blocks = normalizationCalculation(*blocksMa, *blocksMi, stat.blocks);
		norm.gamesPlayed = games;
	}

	return norm;

}



void type(PtList list) {
	Statistics media= averageAllStats(list);
	float twoPoints;
	float threePoints;	
	float assists;		
	float fouls;		
	float blocks;




	PtList allStar;
	PtList shootingGuard;
	PtList pointGuard;

}


Statistics averageAllStats(PtList list) {
	Statistics avg = statisticsCreateZeros();
	Statistics aux;
	Player auxP;
	int size;
	//int total;
	listSize(list,&size);
	for (int i = 0; i < size; i++) {
		listGet(list, i, &auxP);
		aux = auxP.statistics;
		statisticsAdd(avg, aux, 0);
	}
	aux.assists = aux.assists / size;
	aux.blocks = aux.blocks / size;
	aux.fouls = aux.fouls / size;
	aux.threePoints = aux.threePoints / size;
	aux.twoPoints = aux.twoPoints / size;


	return aux;
}