//
// Created by Henrique Faria on 11/13/16.
//

#ifndef JADIEL_VM_SWITCHVIEWER_H
#define JADIEL_VM_SWITCHVIEWER_H

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


#endif //JADIEL_VM_SWITCHVIEWER_H
