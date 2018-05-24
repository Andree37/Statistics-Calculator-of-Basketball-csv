/* MINI-PROJETO 1 ATAD 2018
* Identificacao dos Alunos:
*
*      Numero: 170221006 | Nome: André dos Santos Martins Ribeiro
*      Numero: 170221026 | Nome: Daniel Alexandre Lopes Alves
*
*/
#include "date.h"

/* Esta estrutura e responsavel por criar uma data que sera utilizada na data de nascimento na estrutura jogador */

Date dateCreate(int day, int month, int year) /* funcao 'construtora' da estrutura de dados Date, retorna uma nova data */
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

