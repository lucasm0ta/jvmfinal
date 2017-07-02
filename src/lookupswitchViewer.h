//
// Created by Henrique Faria on 11/13/16.
//

#ifndef JADIEL_VM_LOOKUPSWITCHVIEWER_H
#define JADIEL_VM_LOOKUPSWITCHVIEWER_H

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

#endif //JADIEL_VM_LOOKUPSWITCHVIEWER_H
