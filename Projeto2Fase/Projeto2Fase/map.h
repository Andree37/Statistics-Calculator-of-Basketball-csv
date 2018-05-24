#pragma once

#pragma once

#define MAP_OK            0
#define MAP_NULL          1
#define MAP_NO_MEMORY     2
#define MAP_EMPTY         3
#define MAP_FULL          4
#define MAP_UNKNOWN_KEY	  5

/* Contem defini��o do tipo a guardar na map */
#include "mapElem.h"

/* Forward declaration do registo (representa��o dos dados)
da map.
Tem de estar definida em concreto num ficheiro *.c aquando
da compila��o do programa.
*/
struct mapImpl;

/* Definicao de refer�ncia para uma inst�ncia de map */
typedef struct mapImpl *PtMap;

/*
Cria uma nova inst�ncia da Map.
Recebe:
initialCapacity - capacidade inicial (se aplic�vel)
Retorno:
refer�ncia da inst�ncia ou;
NULL no caso de inexist�ncia de mem�ria.
*/
PtMap mapCreate(unsigned int initialCapacity);

/*
Destroi uma inst�ncia, libertando a mem�ria associada.
Argumentos:
ptMap - endere�o da refer�ncia da inst�ncia;
Retorno:
MAP_NULL se a refer�ncia recebida for NULL, ou;
MAP_OK em caso de sucesso;
*/
int mapDestroy(PtMap *ptMap);

/*
Adiciona um mapeamento numa dada inst�ncia. Se a chave
j� existir, atualiza o valor mapeado.
Argumentos:
map - refer�ncia da inst�ncia;
key - chave do mapeamento;
value - valor mapeado;
Retorno:
MAP_NULL se a refer�ncia recebida for NULL, ou;
MAP_FULL caso o mapa esteja cheio, ou;
MAP_NO_MEMORY caso nao haja mem�ria para guardar o elemento, ou;
MAP_OK em caso de sucesso;
*/
int mapPut(PtMap map, MapKey key, MapValue value);

/*
Remove um mapeamento de uma dada inst�ncia.
Argumentos:
map - refer�ncia da inst�ncia;
key - chave do mapeamento;
ptValue - valor removido (retorno por refer�ncia);
Retorno:
MAP_NULL se a refer�ncia recebida for NULL, ou;
MAP_EMPTY caso o mapa esteja vazio, ou;
MAP_UNKNOWN_KEY caso a chave n�o exista no mapa, ou;
MAP_OK em caso de sucesso;
*/
int mapRemove(PtMap map, MapKey key, MapValue *ptValue);

/*
Obtem um valor mapeado de uma dada inst�ncia.
Argumentos:
map - refer�ncia da inst�ncia;
key - chave do mapeamento;
ptValue - valor mapeado (retorno por refer�ncia);
Retorno:
MAP_NULL se a refer�ncia recebida for NULL, ou;
MAP_EMPTY caso o mapa esteja vazio, ou;
MAP_UNKNOWN_KEY caso a chave n�o exista no mapa, ou;
MAP_OK em caso de sucesso;
*/
int mapGet(PtMap map, MapKey key, MapValue *ptValue);

/*
Verifica se uma chave faz parte do mapa.
Argumentos:
map - refer�ncia da inst�ncia;
key - chave do mapeamento;
Retorno:
1 se existir a chave;
0 se n�o existir ou o mapa for NULL;
*/
int mapContains(PtMap map, MapKey key);

/*
Quantos elementos est�o armazenados numa inst�ncia.
Argumentos:
map - refer�ncia da inst�ncia;
ptSize - n�mero de elementos (retorno por refer�ncia);
Retorno:
MAP_NULL se a refer�ncia recebida for NULL, ou;
MAP_OK em caso de sucesso;
*/
int mapSize(PtMap map, int *ptSize);

/*
Verifica se a inst�ncia est� vazia (n�o cont�m elementos)
Argumentos:
map - refer�ncia da inst�ncia;
Retorno:
1 caso esteja vazia ou a refer�ncia seja NULL, ou;
0 caso n�o esteja vazia;
*/
int mapIsEmpty(PtMap map);

/*
Limpa uma inst�ncia (remove todos os elementos)
Argumentos:
map - refer�ncia da inst�ncia;
Retorno:
MAP_NULL se a refer�ncia recebida for NULL, ou;
MAP_OK em caso de sucesso;
*/
int mapClear(PtMap map);

/*
Mostra informa��o sobre uma inst�ncia
Argumentos:
map - refer�ncia da inst�ncia;
*/
void mapPrint(PtMap map);


/*

//SEM COMENT�RIOS - USO PEDAG�GICO

#define MAP_OK            0
#define MAP_NULL          1
#define MAP_NO_MEMORY     2
#define MAP_EMPTY         3
#define MAP_FULL          4
#define MAP_UNKNOWN_KEY	  5

#include "mapElem.h"

struct mapImpl;
typedef struct mapImpl *PtMap;

PtMap mapCreate(unsigned int initialCapacity);
int mapDestroy(PtMap *ptMap);
int mapPut(PtMap map, MapKey key, MapValue value);
int mapRemove(PtMap map, MapKey key, MapValue *ptValue);
int mapGet(PtMap map, MapKey key, MapValue *ptValue);
int mapContains(PtMap map, MapKey key);
int mapSize(PtMap map, int *ptSize);
int mapIsEmpty(PtMap map);
int mapClear(PtMap map);
void mapPrint(PtMap map);

*/