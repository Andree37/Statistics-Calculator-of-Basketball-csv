/* MINI-PROJETO 2 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/

/*Bibliotecas importadas*/
#include "player.h"
#include <string.h>

/*Funcao que devolve um novo jogador com os seus campos e as estatisticas*/
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

/*Procedimento que mostra na consola a informacao do jogador*/
void playerPrint(Player player) {
	printf("Jogador %3d : %-20s | %-15s | %02d/%02d/%04d | %c   ",
		player.id, player.name, player.team, player.birthDate.day, player.birthDate.month, player.birthDate.year, player.gender);
	statisticsPrint(player.statistics); // e chamado o procedimento que ira mostrar as estatisticas do jogador
	printf("\n");
}
