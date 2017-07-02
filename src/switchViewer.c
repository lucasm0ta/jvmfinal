#include "switchViewer.h"

uint32_t *group_words(uint8_t *src, int size) {
    static uint32_t words[256];

    for(int i = 0; i < size; i++) {
        words[i] = group_word(src + (4 * i));
    }

    return words;
}

uint32_t group_word(uint8_t *word) {
    return word[0] << 24 | word[1] << 16 | word[2] << 8 | word[3];
}

int iniciar_padding_offset(int pos) {
    int mod = pos % 4;

    switch(mod) {
        case 0:
            return 3;
        case 1:
            return 2;
        case 2:
            return 1;
        case 3:
            return 0;
        default:
            return -1;
    }

}
