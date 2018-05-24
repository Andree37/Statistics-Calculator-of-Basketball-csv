/* MINI-PROJETO 2 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "commands.h"

/* definicao de prototipos de funcoes, definidas depois do main() */
void printCommandsMenu();

/*
* Este e a estrutura responsavel pelo metodo main onde corre o programa em si. Mostra o menu de comandos que o utilizador pode efetuar, de seguida efetua os escolhidos
* O procedimento main chama funcoes para desenvolver a acao pretendida.
*/
int main(int argc, char** argv) {

	/* declaracao de variaveis */
	//PlayerList playerList = playerListCreate(300);
	//StatisticsList statsList = statisticsListCreate(300);


	/* interpretador de comandos */
	char command[21];
	int quit = 0;
	while (!quit) {

		printCommandsMenu();
		fgets(command, sizeof(command), stdin);
		/* descartar 'newline'. Utilizar esta técnica sempre que for lida uma
		* string para ser utilizada, e.g., nome de ficheiro, chave, etc.. */
		command[strlen(command) - 1] = '\0';

		if (equalsStringIgnoreCase(command, "QUIT")) {
			quit = 1; /* vai provocar a saída do interpretador */
		}
		else if (equalsStringIgnoreCase(command, "LOAD")) {
			//commandloadG(&statsList); /* chama a funcao LoadG depois de passar por algumas verificacoes */
		}
		else if (equalsStringIgnoreCase(command, "CLAER")) {
			//commandloadP(&playerList); /* chama a funcao LoadP depois de passar por algumas verificacoes */
		}
		else if (equalsStringIgnoreCase(command, "SHOW")) {
			//commandShowP(&playerList); /* chama a funcao ShowP depois de passar por algumas verificacoes, tal como ver se o playerList tem jogadores para mostrar */
		}
		else if (equalsStringIgnoreCase(command, "SEARCH")) {
			//commandSearch(&playerList); /* chama a funcao commandLoadP depois de passar por algumas verificacoes */
		}
		else if (equalsStringIgnoreCase(command, "SORT")) {
			//commandMFoulG(&statsList); /* chama a funcao MFoulG depois de passar por algumas verificacoes */
		}
		else if (equalsStringIgnoreCase(command, "AVG")) {
			//commandMFoulP(&statsList, &playerList); /* chama a funcao MFoulP depois de passar por algumas verificacoes */
		}
		else if (equalsStringIgnoreCase(command, "NORM")) {
			//commandFairPlay(&statsList, &playerList); /* chama a funcao FairPlay depois de passar por algumas verificacoes, tal como ambas as listas, statsList e playersList terem jogadores e estatisticas */
		}
		else if (equalsStringIgnoreCase(command, "TYPE")) {
			//commandIdealTeam(&statsList, &playerList); /* chama a funcao IdealTeam depois de passar por algumas verificacoes, tal como ambas as listas, statsList e playersList terem jogadores e estatisticas */
		}
		else if (equalsStringIgnoreCase(command, "CHECHTYPE")) {
			//commandIdealTeam(&statsList, &playerList); /* chama a funcao IdealTeam depois de passar por algumas verificacoes, tal como ambas as listas, statsList e playersList terem jogadores e estatisticas */
		}
		else if (equalsStringIgnoreCase(command, "KMEANS")) {
			//commandIdealTeam(&statsList, &playerList); /* chama a funcao IdealTeam depois de passar por algumas verificacoes, tal como ambas as listas, statsList e playersList terem jogadores e estatisticas */
		}
		else {
			printf("Comando nao encontrado.\n"); /* Caso nao seja encontrado na cadeia de if-else a cima, e mostrada uma mensagem de erro a dizer que o comando nao foi encontrado */
		}
	}

	/* libertar memória e apresentar mensagem de saída. */
	//playerListDestroy(&playerList); /*Liberta o espaco do playerList*/
	//statisticsListDestroy(&statsList); /*Liberta o espaco do statsList*/


	printf("FECHADO COM SUCESSO\n"); /* Mostra uma mensagem de saida */
	return (EXIT_SUCCESS);
}


//FALTA UPDATE
void printCommandsMenu() { /* Menu do utilizador */
	printf("\n===================================================================================");
	printf("\n                          MINI-PROJECT: Basket Scores                              ");
	printf("\n===================================================================================");
	printf("\nA. Info about players (LOADP, SHOWP, TABLE, SEARCH).");
	printf("\nB. Specific info about players' performance during the games (LOADG, SEARCHG, MVP).");
	printf("\nC. Aggregated info about games and players (MFOULP, MFOULG, FAIRPLAY).");
	printf("\nD. Advanced indicator (IDEALTEAM)");
	printf("\nE. Exit (QUIT)\n\n");
	printf("COMMAND> ");
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

char** split(char *str, int nFields, const char *delim) { /* Esta funcao e responsavel pela separacao de registos, depois utilizada no loadp e loadg*/

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
