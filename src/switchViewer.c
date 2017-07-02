#include "switchViewer.h"

u4 *group_words(u1 *src, int size) {
    static u4 words[256];

    for(int i = 0; i < size; i++) {
        words[i] = group_word(src + (4 * i));
    }

    return words;
}

u4 group_word(u1 *word) {
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
