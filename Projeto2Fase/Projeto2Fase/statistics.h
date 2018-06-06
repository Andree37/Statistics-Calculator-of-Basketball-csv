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

PtStatistics statisticsCreate(float two, float three, float assists, float fouls, float blocks);
void statisticsAdd(PtStatistics reciever, PtStatistics giver);
PtStatisticsList statisticsListCreate(unsigned int capacity);
void statisticsListAdd(PtStatistics stats, PtStatisticsList list);
void statisticsListDestroy(PtStatisticsList list);
PtStatistics statisticsCreateZeros();


