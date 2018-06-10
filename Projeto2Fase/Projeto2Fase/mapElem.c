#include "mapElem.h"

void mapKeyPrint(MapKey key) {
	printf("%d \n", key); //a key e um int por isso podemos fazer print assim
}

void mapValuePrint(MapValue value) {
	playerTypePrint(value); //procedimento encarregue de fazer print do valor, sendo ele um PlayerType
}

/* funcao de comparacao de chaves */
int mapKeyEquals(MapKey key1, MapKey key2) {
	//no caso de MapKey == int. Alterar de acordo
	//com o tipo efetivo
	return (key1 == key2);
}