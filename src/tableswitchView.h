#ifndef TABLESWITCHVIEWER_H
#define TABLESWITCHVIEWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include "switchView.h"
#include "decodificador.h"
#include "util.h"

typedef struct {
    const char *name;
    int position;
    u4 defaultBytes;
    u4 lowBytes;
    u4 highBytes;
    u4 *jumpOffsets;
    int sizeOfJumpOffsets;
    int totalSize;
} TableswitchData;

TableswitchData montar_switch_table(u1 *src, int pc);
void imprimir_switch_table(TableswitchData data, const char *space);

#ifdef __cplusplus
}
#endif

#endif //TABLESWITCHVIEWER_H
