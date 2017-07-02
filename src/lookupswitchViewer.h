#ifndef LOOKUPSWITCHVIEWER_H
#define LOOKUPSWITCHVIEWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include "switchViewer.h"
#include "instructionMapper.h"

typedef struct {
    const char *name;
    int position;
    uint32_t defaultBytes;
    uint32_t amountOfPairs;
    uint32_t *keyOffsetPairs;
    int totalSize;
} LookupswitchData;

LookupswitchData montar_lookupswitch_data(uint8_t *src, int pos);
void imprimir_Lookupswitch(LookupswitchData data, char *space);

#ifdef __cplusplus
}
#endif

#endif //LOOKUPSWITCHVIEWER_H
