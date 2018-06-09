#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include <Math.h>
#include "averageMVPPlayer.h"
#include "commands.h"
#include "statistics.h"
#include "cluster.h"
#include "float.h"

void load(char *playerFile, char *statsFile, PtList list);
void show(PtList list);
void clear(PtList list);
void sort(PtList list);
void avg(PtList list);
void type(PtList list);
void norm(PtList list);
void checkType(PtList list);
void cluster(PtList list);

char** split(char *str, int nFields, const char *delim);
PtList createClone(PtList list);
Statistics averageCalculation(Statistics stat);
PtList averageStatistics(PtList players);
void calculateMax(PtList list, float* two, float* three, float* assists, float* fouls, float* blocks);
void calculateMin(PtList list, float* two, float* three, float* assists, float* fouls, float* blocks);
float normalizationCalculation(float max, float min, float val);
Statistics statNormalizationCalculation(Statistics stat, float* twoMa, float* threeMa, float* assistsMa, float* foulsMa, float* blocksMa,
	float* twoMi, float* threeMi, float* assistsMi, float* foulsMi, float* blocksMi);
PtList normalizeStatistics(PtList players);
void segmentPlayers(PtList players, PtList allStar, PtList shootingGuard, PtList pointGuard, Statistics media);
Statistics averageAllStats(PtList list);


PtCluster kmeans(PtList list, int k, int maxIteration, float deltaError, float *iterationError);
void calculateClosestsClusters(PtList list, PtClusterList clusters, int k);
float calculateDistance(Cluster cluster, Statistics stat);
void calculateCentroids(PtClusterList clusters, int k); 
float calculateError(PtClusterList clusters, int k);



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
	Player avgPlayer;
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
				avgPlayer = playerCreate(player.id, player.name, player.team, player.birthDate, player.gender, normStats);
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

Statistics averageAllStats(PtList list) {
	Statistics avg = statisticsCreateZeros();
	Statistics aux;
	Player auxP;
	int size;

	listSize(list, &size);
	for (int i = 0; i < size; i++) {
		listGet(list, i, &auxP);
		aux = auxP.statistics;
		avg = statisticsAdd(avg, aux, 0);
	}
	avg.assists = avg.assists / size;
	avg.blocks = avg.blocks / size;
	avg.fouls = avg.fouls / size;
	avg.threePoints = avg.threePoints / size;
	avg.twoPoints = avg.twoPoints / size;


	return avg;
}

void segmentPlayers(PtList players, PtList allStar, PtList shootingGuard, PtList pointGuard, Statistics media) {
	int size;
	int innerSize;
	listSize(players, &size);
	ListElem elem;

	float twoPoints;
	float threePoints;
	float assists;
	float blocks;

	for (int i = 0; i < size; i++) {
		listGet(players, i, &elem);
		twoPoints = elem.statistics.twoPoints;
		threePoints = elem.statistics.threePoints;
		assists = elem.statistics.assists;
		blocks = elem.statistics.blocks;

		if (twoPoints > media.twoPoints && threePoints > media.threePoints && assists > media.assists && blocks > media.blocks) {
			listSize(allStar, &innerSize);
			listAdd(allStar, innerSize, elem);
		}
		else if (twoPoints > media.twoPoints && threePoints > media.threePoints && assists < media.assists && blocks < media.blocks) {
			listSize(shootingGuard, &innerSize);
			listAdd(shootingGuard, innerSize, elem);
		}
		else if (twoPoints < media.twoPoints && threePoints < media.threePoints && assists > media.assists && blocks > media.blocks) {
			listSize(pointGuard, &innerSize);
			listAdd(pointGuard, innerSize, elem);
		}
	}
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

void commandType(PtList list) {
	if (list != NULL) {
		type(list);
	}
	else {
		printf("Erro interno, nao existe uma lista para suportar este comando");
	}
}

void commandCheckType(PtList list) {
	if (list != NULL) {
		checkType(list);
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

	if (size == 0) {
		printf("Nao existe nenhum registo na tabela");
		return;
	}
	printf("           Jogador   ID : NOME                | EQUIPA          | BIRTHDATE  |GENRE| 2POINTS |  3POINTS |  FOULS   | ASSISTS  |BLOCKS    | GAMES  |\n");
	listPrint(list);
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
					if (isSameAge(elem.birthDate, elem2.birthDate) != 0) {
						if (strcmp(elem.name, elem2.name) > 0) {
							listSet(clone, j, elem2, &elem);
							listSet(clone, j + 1, elem, &elem2);
						}
					}

				}
				else if ((equalsStringIgnoreCase(option, games) != 0)) {
					if (elem.statistics.gamesPlayed > elem2.statistics.gamesPlayed) {
						listSet(clone, j, elem2, &elem);
						listSet(clone, j + 1, elem, &elem2);
					}
					if (elem.statistics.gamesPlayed == elem2.statistics.gamesPlayed) {
						if (strcmp(elem.name, elem2.name) > 0) {
							listSet(clone, j, elem2, &elem);
							listSet(clone, j + 1, elem, &elem2);
						}
					}
				}
				else {
					changed = 0;
				}
			}
		}
		if (changed)
			show(clone);
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

		PtList clone = listCreate(size);
		ListElem elem;

		for (int i = 0; i < size; i++) {
			elem = avgMVPList->elements[i].player;
			listAdd(clone, i, elem);
		}

		show(clone);

		listDestroy(&clone);
		mvpPlayerListDestroy(&avgMVPList);
	}
}

void norm(PtList list) {

	PtList toNormList = averageStatistics(list);

	PtList normalizedList = normalizeStatistics(toNormList);

	show(normalizedList);

	listDestroy(&toNormList);
	listDestroy(&normalizedList);
}

void type(PtList list) {

	PtList avgList = averageStatistics(list);
	Statistics media = averageAllStats(avgList);

	PtList allStar = listCreate(300);
	PtList shootingGuard = listCreate(300);
	PtList pointGuard = listCreate(300);

	segmentPlayers(avgList, allStar, shootingGuard, pointGuard, media);

	printf("Tipo Shooting-Guard\n");
	listPrint(shootingGuard);
	printf("Tipo Point-Guard\n");
	listPrint(pointGuard);
	printf("Tipo All-Star\n");
	listPrint(allStar);

	listDestroy(&avgList);
	listDestroy(&allStar);
	listDestroy(&shootingGuard);
	listDestroy(&pointGuard);
}

void checkType(PtList list) {

	PtList avgList = averageStatistics(list);
	Statistics media = averageAllStats(avgList);

	PtList allStar = listCreate(300);
	PtList shootingGuard = listCreate(300);
	PtList pointGuard = listCreate(300);

	segmentPlayers(avgList, allStar, shootingGuard, pointGuard, media);

	PtMap map = mapCreate(300); //maximo de jogadores
	PlayerType pType;

	ListElem lElem;

	int size;
	listSize(allStar, &size);
	
	for (int i = 0; i < size; i++) {
		listGet(allStar, i, &lElem);
		pType = playerTypeCreate("all-star", lElem.statistics.twoPoints, media.twoPoints, lElem.statistics.threePoints, media.threePoints,
			lElem.statistics.blocks, media.blocks, lElem.statistics.assists, media.assists, lElem.statistics.fouls, media.fouls);
		mapPut(map, lElem.id, pType);
	}

	listSize(shootingGuard, &size);

	for (int i = 0; i < size; i++) {
		listGet(shootingGuard, i, &lElem);
		pType = playerTypeCreate("shooting-guard", lElem.statistics.twoPoints, media.twoPoints, lElem.statistics.threePoints, media.threePoints,
			lElem.statistics.blocks, media.blocks, lElem.statistics.assists, media.assists, lElem.statistics.fouls, media.fouls);
		mapPut(map, lElem.id, pType);
	}

	listSize(pointGuard, &size);

	for (int i = 0; i < size; i++) {
		listGet(pointGuard, i, &lElem);
		pType = playerTypeCreate("point-guard", lElem.statistics.twoPoints, media.twoPoints, lElem.statistics.threePoints, media.threePoints,
			lElem.statistics.blocks, media.blocks, lElem.statistics.assists, media.assists, lElem.statistics.fouls, media.fouls);
		mapPut(map, lElem.id, pType);
	}

	int intTemp;
	char toInteger[5];
	MapValue value;
	mapSize(map, &size);
	do {
		printf("Introduza uma chave(ID de jogador) para saber informacoes sobre ele ------ Introduza um valor negativo para sair\n");
		gets_s(toInteger, sizeof(toInteger));
		intTemp = atoi(toInteger);

		if((mapContains(map, intTemp) == 0) && intTemp > 0) {
			printf("Valor de chave nao encontrado");
		}
		else if(intTemp > 0){
			mapGet(map, intTemp, &value);

			printf("Key =");
			mapKeyPrint(intTemp);
			mapValuePrint(value);
		}
		printf("\n\n\n");

	} while (intTemp > -1); \

		printf("Byee\n");

	listDestroy(&avgList);
	listDestroy(&allStar);
	listDestroy(&shootingGuard);
	listDestroy(&pointGuard);
	mapDestroy(&map);
}

void cluster(PtList list){

	PtList toNormList = averageStatistics(list);

	PtList norm = normalizeStatistics(toNormList);

	char command[25];
	int k;
	int maxIteration;
	float deltaError;
	PtClusterList clusters;
	PtClusterList bestCluster;
	


	printf("Quantos cluster quer usar?");
	gets_s(command, sizeof(command));
	k = atoi(command);
	printf("Quantas iteracoes quer efetuar");
	gets_s(command, sizeof(command));
	maxIteration = atoi(command);
	printf("Qual a varicao minima do erro entre iteracoes");
	gets_s(command, sizeof(command));
	deltaError = atoi(command);
	
	float iterationError;
	float bestError = FLT_MAX;

	int repetitionMax = 100;


	for (int i = 0; i < repetitionMax; i++) {
		clusters = kmeans(norm, k, maxIteration, deltaError, &iterationError);
		if (iterationError < bestError) {
			bestError = iterationError;
			bestCluster = clusters;
		}
	}
	
	printf("Best error=%.2f\n", bestError);
	for (int i = 0; i < k; i++) {
		printf("Cluster %d ----", i+1);
		listPrint(bestCluster->elements[i].members);
	}

	listDestroy(&toNormList);
	listDestroy(&norm);

	//destroy cluster lists
	
}

PtCluster kmeans(PtList list, int k, int maxIteration, float deltaError, float *iterationError) {
	//kmeans
	PtClusterList clusters = clusterListCreate(600);
	Player p;
	Statistics stat;
	int size;
	listSize(list, &size);
	int random;
	Cluster toAdd;

	for (int i = 0; i < k; i++) {
		////buscar umas stats de um jogador random
		random = (rand() % size);
		listGet(list, random ,&p);
		stat = p.statistics;
		toAdd = clusterCreate(stat);
		clusterListAdd(clusters, toAdd);
	}

	int iterationNumber = 1;
	float prevError = FLT_MAX;
	*iterationError = FLT_MAX;

	do {
		if (iterationNumber > 1)
			prevError = *iterationError;

		//Atribuir 
		calculateClosestsClusters(list, clusters,  k);
		//Reclacular os centroides
		calculateCentroids(clusters, k, &stat);
		//Calcular o erro
		*iterationError=calculateError(clusters, k);

		iterationNumber++;
	} while ((iterationNumber < maxIteration) && (fabs(prevError - *iterationError) > deltaError));

	return clusters;
}

void calculateClosestsClusters(PtList list, PtClusterList clusters, int k) {
	int sizeList;
	int sizeCluster;
	float distance;
	float closestDistance;
	int closestCluster;
	Player player;
	Statistics stat;
	
	for (int i = 0; i < k; i++) {
		listClear(clusters->elements[i].members);
	}
	
	listSize(list, &sizeList);
	for (int i = 0; i < sizeList; i++) {
		listGet(list, i, &player);
		stat = player.statistics;
		for (int j = 0; j < k; j++) {
			distance =calculateDistance(clusters->elements[j], stat);
			if (j== 0||distance < closestDistance) {
				closestCluster = j;
				closestDistance = distance;
			}
		}
		listSize(clusters->elements[closestCluster].members, &sizeCluster);
		listAdd(clusters->elements[closestCluster].members, sizeCluster, player);
		
	}

}

float calculateDistance(Cluster cluster, Statistics stat){
	float clustAssists = cluster.meanAssists - stat.assists;
	float clustTwoPoints = cluster.meanTwoPoints - stat.twoPoints;
	float clustThreePoints = cluster.meanThreePoints - stat.threePoints;
	float clustFouls = cluster.meanFouls - stat.fouls;
	float clustBlocks = cluster.meanBlocks - stat.blocks;

	float ass = pow((clustAssists),2.0);
	float two = pow((clustTwoPoints),2.0);
	float three = pow((clustThreePoints),2.0);
	float fouls = pow((clustFouls),2.0);
	float blocks = pow((clustBlocks),2.0);


	return sqrt(ass+two+three+fouls+blocks);
}

void calculateCentroids(PtClusterList clusters, int k){ 
	Statistics stat;
	Statistics avgStats;
	
	for (int i = 0; i < k; i++) {
		avgStats = averageAllStats(clusters->elements[i].members);
		clusters->elements[i] = clusterAlter(clusters->elements[i],  avgStats);

	}

}


float calculateError(PtClusterList clusters, int k) {
	int size;
	float total = 0;
	float distance;
	Player p;
	Statistics s;
	PtList l;

	for (int i = 0; i < k; i++) {
		l = clusters->elements[i].members;
		listSize(l, &size);
		for (int j = 0; j < size; j++) {
			listGet(l, j, &p);
			s = p.statistics;
			distance = calculateDistance(clusters->elements[i],s);
			total += pow(distance,2.0);
		}
	}
	return total;
}