#pragma once
#include "playerType.h"

/* definicao do tipo da chave */
typedef int MapKey;
/* definicao do tipo do valor*/
typedef PlayerType MapValue; // O value, neste projeto, foi definido como um PlayerType

void mapKeyPrint(MapKey key);
void mapValuePrint(MapValue value);

/* funcao de comparacao de chaves */
int mapKeyEquals(MapKey key1, MapKey key2);