/* MINI-PROJETO 1 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/
#include <stdio.h>

#include "input.h"

/* Estrutura que e responsavel pela leitura do input do utilizador, fornecida pelo professor*/

void readInteger(int * ptVal) /* procedimento que le um inteiro e devolve-o por ponteiro */
{
	char line[20];
	fgets(line, sizeof(line), stdin);
	(*ptVal) = atoi(line);
}

void readDouble(int * ptVal) /* procedimento que le um double e devolve-o por ponteiro */
{
	char line[20];
	fgets(line, sizeof(line), stdin);
	(*ptVal) = atof(line);
}

void readCharArray(char *charArr, unsigned int maxChars) { /* procedimento que le um array de char e devolve-o por ponteiro */
	fgets(charArr, maxChars, stdin);
	int len = strlen(charArr);
	if (len > 0 && charArr[len - 1] == '\n') {
		charArr[len - 1] = '\0';
	}
}
