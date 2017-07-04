/*
 * Implementação baseada em:
 *
 * https://docs.oracle.com/javase/specs/jvms/se6/html/Instructions2.doc14.html
 *
 * */

#include "tableswitchViewer.h"

void imprimir_switch_table(TableswitchData data,const char *space) {
    printf("\n%s     %d: %s {", space, data.position, data.name);
    printf("\n%s           default: %d", space, data.defaultBytes);
    printf("\n%s               min: %d", space, data.lowBytes);
    printf("\n%s               max: %d", space, data.highBytes);

    for(int i = 0; i < data.sizeOfJumpOffsets; i++) {
        printf("\n%s                 %d: %d", space, i, data.jumpOffsets[i]);
    }

    printf("\n%s     }", space);
}

TableswitchData montar_switch_table(u1 *src, int pc) {
    const int paddingOffset = iniciar_padding_offset(pc);
    const int indexOfLowBytes = paddingOffset + 4;
    const int indexOfHighBytes = paddingOffset + 8;
    const int indexOfJumpOffsets = paddingOffset + 12;

    TableswitchData data;
    data.name = INSTR_TABLESWITCH;
    data.position = pc;
    data.defaultBytes = group_word(src + paddingOffset);
    data.lowBytes = group_word(src + indexOfLowBytes);
    data.highBytes = group_word(src + indexOfHighBytes);
    data.sizeOfJumpOffsets = data.highBytes - data.lowBytes + 1;
    data.jumpOffsets = group_words(src + indexOfJumpOffsets, data.sizeOfJumpOffsets);
    data.totalSize = paddingOffset + (3 + data.sizeOfJumpOffsets) * 4;
    return data;
}
