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

		

		free(tokens);
		countPlayers++;


	}
	printf("\n\nForam lidos %d jogadores... \n", countPlayers);
	fclose(fd);

	return list;
}

void createStatistics() {

}
