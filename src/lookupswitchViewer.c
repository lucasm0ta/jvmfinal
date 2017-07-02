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
    const int padding_Offset = iniciar_padding_offset(pos);
    const int index_ofKey_offset_pairs = padding_Offset + 8;

    LookupswitchData data;
    data.name = INSTR_LOOKUPSWITCH;
    data.position = pos;
    data.defaultBytes = group_word(src + padding_Offset);
    data.amountOfPairs = group_word(src + padding_Offset + 4);
    data.keyOffsetPairs = group_words(src + index_ofKey_offset_pairs, data.amountOfPairs * 2);
    data.totalSize = padding_Offset + (2 + (data.amountOfPairs * 2)) * 4;
    return data;
}
