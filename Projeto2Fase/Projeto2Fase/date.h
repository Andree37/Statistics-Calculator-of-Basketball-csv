/* MINI-PROJETO 2 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/
#pragma once

/* Estrutura de dados que guarda um dia, mes e ano */
typedef struct date {
	unsigned int day, month, year;
}Date;

/* tipo definido para ponteiro de data */
typedef Date* PtDate;

/* definicao de prototipos de funcoes */
Date dateCreate(int day, int month, int year);
int isYoungerThan(Date date1, Date date2);
int isSameAge(Date date1, Date date2);
