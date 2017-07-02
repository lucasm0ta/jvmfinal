#ifndef TABLESWITCHVIEWER_H
#define TABLESWITCHVIEWER_H

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

TableswitchData montar_switch_table(uint8_t *src, int pc);
void imprimir_switch_table(TableswitchData data, char *space);

#ifdef __cplusplus
}
#endif

#endif //TABLESWITCHVIEWER_H
