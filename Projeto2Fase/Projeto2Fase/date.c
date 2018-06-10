/* MINI-PROJETO 2 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/

/*Bibliotecas importadas*/
#include "date.h"

/*Funcao que devolve uma nova data*/
Date dateCreate(int day, int month, int year) 
{
	Date newDate;
	if (day < 0 || day > 31) {
		day == 0;
	}
	newDate.day = day;
	if (month < 1 || month > 12) {
		month == 1;
	}
	newDate.month = month;
	if (year < 0) {
		year = 0;
	}
	newDate.year = year;
	return newDate;
}

/*Funcao que retorna true(1) se for mais novo, false(0) se nao for*/
int isYoungerThan(Date date1, Date date2) {
	if (date1.year > date2.year) {
		return 1;
	}
	else if (date1.year == date2.year) {
		if (date1.month > date2.month) {
			return 1;
		}
		if (date1.month == date2.month) {
			if (date1.day > date2.day) {
				return 1;
			}
		}
	}

	return 0;
}

/*Funcao que retorna true(1) se for da mesma idade, false(0) se nao for*/
int isSameAge(Date date1, Date date2) {
	if (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day) return 1;
	return 0;
}

