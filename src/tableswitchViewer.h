//
// Created by Henrique Faria on 11/13/16.
//

#ifndef JADIEL_VM_TABLESWITCHVIEWER_H
#define JADIEL_VM_TABLESWITCHVIEWER_H

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
    uint32_t lowBytes;
    uint32_t highBytes;
    uint32_t *jumpOffsets;
    int sizeOfJumpOffsets;
    int totalSize;
} TableswitchData;

TableswitchData makeTableswitchData(uint8_t *src, int pc);
void printTableswitch(TableswitchData data, char *space);


#ifdef __cplusplus
}
#endif


#endif //JADIEL_VM_TABLESWITCHVIEWER_H
