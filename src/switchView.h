#ifndef SWITCHVIEWER_H
#define SWITCHVIEWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include "util.h"

u4 *group_words(u1 *src, int size);
u4 group_word(u1 * word);
int iniciar_padding_offset(int pos);

#ifdef __cplusplus
}
#endif


#endif //SWITCHVIEWER_H
