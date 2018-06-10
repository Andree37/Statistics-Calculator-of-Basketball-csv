/* MINI-PROJETO 2 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/

#pragma once

/*Bibliotecas importadas*/
#include <stdio.h>
#include<stdlib.h>

#include "list.h"
#include "player.h"
#include "map.h"

/* definicao de prototipos de funcoes*/
int equalsStringIgnoreCase(char str1[], char str2[]);
void stringToUpper(char * str);

void commandLoad(PtList list);
void commandShow(PtList list);
void commandClear(PtList list);
void commandSort(PtList list);
void commandAvg(PtList list);
void commandNorm(PtList list);
void commandType(PtList list);
void commandCheckType(PtList list);
void commandKMeans(PtList list);

