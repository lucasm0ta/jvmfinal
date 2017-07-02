#ifndef LOOKUPSWITCHVIEWER_H
#define LOOKUPSWITCHVIEWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include "switchViewer.h"
#include "instructionMapper.h"
#include "util.h"

typedef struct {
    const char *name;
    int position;
    u4 defaultBytes;
    u4 amountOfPairs;
    u4 *keyOffsetPairs;
    int totalSize;
} LookupswitchData;

/*
 * Esta função monta a estrutura LookupswitchData
 * @param fonte dos dados
 * @param posição
 * @return struct com os dados
 */
LookupswitchData montar_lookupswitch_data(u1 *src, int pos);
/*
 * imprime estrutura LookupswitchData
 * @param estrutura LookupswitchData
 * @param space
 */
void imprimir_Lookupswitch(LookupswitchData data, char *space);

#ifdef __cplusplus
}
#endif

#endif //LOOKUPSWITCHVIEWER_H
