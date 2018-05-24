#pragma once

/* definicao do tipo da chave */
typedef int MapKey;
/* definicao do tipo do valor*/
typedef int MapValue;

void mapKeyPrint(MapKey key);
void mapValuePrint(MapValue value);

/* funcao de comparacao de chaves */
int mapKeyEquals(MapKey key1, MapKey key2);