#include "commands.h"

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

void load(char *playerFile, char *statsFile) {
	PtList list = listCreate(300);
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
	PtStatistics stats;

	PtStatistics newstats;

	int game=0;
	while (fgets(nextline, sizeof(nextline), fd2)) {
		if (strlen(nextline) < 1)
			continue;

		char **tokens = split(nextline, 7, ";");

		int playerId = atoi(tokens[0]);
		char* name = atoi(tokens[1]);//nao faz nada de momento
		strcpy_s(name, strlen(tokens[1]), tokens[1]);

		char* team;//= atof(tokens[2]);
			strcpy_s(team, strlen(tokens[2]), tokens[2]);

		int day = atof(tokens[3]);
		int month = atof(tokens[4]);
		int year = atof(tokens[5]);

		char gender = atof(tokens[6]);

		
		Date d = dateCreate(day, month, year);

		PtPlayer p= playerCreate(playerId, name, team, d, gender, statistics);

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

		if (stats == NULL ) {
			stats = statisticsCreate(two, three, assists, fouls, blocks);
			
		}else
		 newstats = statisticsCreate(two, three, assists, fouls, blocks);

		

		free(tokens);
		//countPlayers++;
		if (game != idGame)
			game = idGame;

	}
	printf("\n\nForam lidos %d jogadores... \n", countPlayers);
	fclose(fd);

	return list;
}

void createStatistics() {

}
