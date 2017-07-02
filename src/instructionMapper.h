#ifndef INSTRUCTIONMAPPER_H
#define INSTRUCTIONMAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSTRUCTION_NAME 30
#define INSTRUCTION_SIZE 256
typedef struct decoder {
    //nome da instrucao
    char instruction[INSTRUCTION_NAME];
    //bytes de operandos que ela ocupa
    int bytes;
    int referencesCP;
} decoder;

extern const char *INSTR_TABLESWITCH;
extern const char *INSTR_LOOKUPSWITCH;

// funcao que coloca o nome das strings no decodificador, juntamente com a qtd em bytes
void inicializar_decodificador();
decoder decode[INSTRUCTION_SIZE];

#ifdef __cplusplus
}
#endif


#endif
