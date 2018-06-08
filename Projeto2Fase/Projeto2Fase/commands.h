#pragma once

#include <stdio.h>
#include<stdlib.h>

#include "list.h"
#include "player.h"

int equalsStringIgnoreCase(char str1[], char str2[]);
void stringToUpper(char * str);

void commandLoad(PtList list);
void commandShow(PtList list);
void commandClear(PtList list);
void commandSort(PtList list);
void commandAvg(PtList list);
void commandNorm(PtList list);

