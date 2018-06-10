/* MINI-PROJETO 2 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/

/*Bibliotecas importadas*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "statistics.h"

/* definicao de prototipos de funcoes, definidas depois do main() */
void printCommandsMenu();
void stringToUpper(char * str);

/*
* Este e a estrutura responsavel pelo metodo main onde corre o programa em si. Mostra o menu de comandos que o utilizador pode efetuar, de seguida efetua os escolhidos
* O procedimento main chama funcoes para desenvolver a acao pretendida.
*/
int main(int argc, char** argv) {

	/* declaracao de variaveis */
	PtList list= listCreate(300);


	/* interpretador de comandos */
	char command[21];
	int quit = 0;
	while (!quit) {

		system("cls");

		printCommandsMenu();
		fgets(command, sizeof(command), stdin);
		/* descartar 'newline'. Utilizar esta técnica sempre que for lida uma
		* string para ser utilizada, e.g., nome de ficheiro, chave, etc.. */
		command[strlen(command) - 1] = '\0';

		if (equalsStringIgnoreCase(command, "QUIT")) {
			quit = 1; /* vai provocar a saída do interpretador */
		}
		else if (equalsStringIgnoreCase(command, "LOAD")) {
			commandLoad(list);
			system("pause");
		}
		else if (equalsStringIgnoreCase(command, "CLEAR")) {
			commandClear(list);
			system("pause");
		}
		else if (equalsStringIgnoreCase(command, "SHOW")) {
			commandShow(list);
			system("pause");
		}
		else if (equalsStringIgnoreCase(command, "SORT")) {
			commandSort(list);
			system("pause");
		}
		else if (equalsStringIgnoreCase(command, "AVG")) {
			commandAvg(list);
			system("pause");
		}
		else if (equalsStringIgnoreCase(command, "NORM")) {
			commandNorm(list);
			system("pause");

		}
		else if (equalsStringIgnoreCase(command, "TYPE")) {
			commandType(list);
			system("pause");
		}
		else if (equalsStringIgnoreCase(command, "CHECKTYPE")) {
			commandCheckType(list);
			system("pause");
		}
		else if (equalsStringIgnoreCase(command, "KMEANS")) {
			commandKMeans(list);
			system("pause");
		}
		else {
			printf("Comando nao encontrado.\n"); /* Caso nao seja encontrado na cadeia de if-else a cima, e mostrada uma mensagem de erro a dizer que o comando nao foi encontrado */
			system("pause");
		}
	}

	/* libertar memória e apresentar mensagem de saída. */

	listDestroy(&list);

	
	printf("FECHADO COM SUCESSO\n"); /* Mostra uma mensagem de saida */
	return (EXIT_SUCCESS);
}

/*Procedimento que quando e envocado, mostra para a consola algumas opcoes para o utilizador escolher*/
void printCommandsMenu() { /* Menu do utilizador */
	printf("\n===================================================================================");
	printf("\n                          MINI-PROJECT: Basket Scores                              ");
	printf("\n===================================================================================");
	printf("\nA. Info (LOAD, SHOW, CLEAR).");
	printf("\nC. Aggregated info about games and players (SORT, AVG, NORM, TYPE).");
	printf("\nD. Advanced indicator (KMEANS, CHECKTYPE)");
	printf("\nE. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}
