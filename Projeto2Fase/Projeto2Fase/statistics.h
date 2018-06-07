#pragma once

typedef struct statistics {
	float twoPoints;	/*total ou media de cestos de dois pontos*/
	float threePoints;	/*total ou media de cestos de 3 pontos*/
	float assists;		/*total ou meida de assitencias*/
	float fouls;		/*total ou media de faltas*/
	float blocks;		/* total ou media de blocos */
	int gamesPlayed;	/*toatl de jogos disputados*/
 /* pode acrescentar algum atributo/campo se achar relevante */

}Statistics;

typedef struct statisticList
{
	Statistics *elements;
	unsigned int size;
	unsigned int capacity;
}StatisticsList;

typedef Statistics *PtStatistics;

typedef StatisticsList* PtStatisticsList;

Statistics statisticsCreate(float two, float three, float assists, float fouls, float blocks);
Statistics statisticsAdd(Statistics reciever, Statistics giver, int games);
PtStatisticsList statisticsListCreate(unsigned int capacity);
void statisticsListAdd(PtStatistics stats, PtStatisticsList list);
void statisticsListDestroy(PtStatisticsList list);
Statistics statisticsCreateZeros();
void statisticsPrint(Statistics stats);


