//
// Created by Henrique Faria on 11/13/16.
//

#include "lookupswitchViewer.h"

void imprimir_Lookupswitch(LookupswitchData data, char *space) {
    printf("\n%s     %d: %s {", space, data.position, data.name);
    printf("\n%s           default: %d", space, data.defaultBytes);
    printf("\n%s             count: %d", space, data.amountOfPairs);

    for(int i = 0; i <= data.amountOfPairs; i += 2) {
        printf("\n%s          %*d: %d", space, 8, data.keyOffsetPairs[i], data.keyOffsetPairs[i+1]);
    }

    printf("\n%s     }", space);
}

LookupswitchData montar_lookupswitch_data(uint8_t *src, int pos) {
    const int paddingOffset = makePaddingOffset(pos);
    const int indexOfKeyOffsetPairs = paddingOffset + 8;

    LookupswitchData data;
    data.name = INSTR_LOOKUPSWITCH;
    data.position = pos;
    data.defaultBytes = group_word(src + paddingOffset);
    data.amountOfPairs = group_word(src + paddingOffset + 4);
    data.keyOffsetPairs = group_words(src + indexOfKeyOffsetPairs, data.amountOfPairs * 2);
    data.totalSize = paddingOffset + (2 + (data.amountOfPairs * 2)) * 4;
    return data;
}