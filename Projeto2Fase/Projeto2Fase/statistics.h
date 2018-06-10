/* MINI-PROJETO 2 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/

#pragma once

/*Estrutura de dados capaz de guardar as estatisticas de cada jogador*/
typedef struct statistics {
	float twoPoints;	/*total ou media de cestos de dois pontos*/
	float threePoints;	/*total ou media de cestos de 3 pontos*/
	float assists;		/*total ou meida de assitencias*/
	float fouls;		/*total ou media de faltas*/
	float blocks;		/* total ou media de blocos */
	int gamesPlayed;	/*total de jogos disputados*/
	
	float mvp;			/*mvp de cada jogador, nao sendo calculado, comeca a 0*/

}Statistics;

/* tipo definido para ponteiro de Statistics */
typedef Statistics *PtStatistics;

/* definicao de prototipos de funcoes */
Statistics statisticsCreate(float two, float three, float assists, float fouls, float blocks);
Statistics statisticsAdd(Statistics reciever, Statistics giver, int games);
Statistics statisticsCreateZeros();
void statisticsPrint(Statistics stats);


