#ifndef SWITCHVIEWER_H
#define SWITCHVIEWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

uint32_t *group_words(uint8_t *src, int size);
uint32_t group_word(uint8_t * word);
int makePaddingOffset(int pos);

#ifdef __cplusplus
}
#endif


#endif //SWITCHVIEWER_H
