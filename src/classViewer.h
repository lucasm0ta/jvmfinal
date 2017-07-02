#ifndef CLASSVIEWER_H
#define CLASSVIEWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "classLoader.h"
#include "instructionMapper.h"
#include "tableswitchViewer.h"
#include "lookupswitchViewer.h"


void imprimir_informacoes_classe(ClassFile *classFile);
void imprimir_constant_pool_completa(ClassFile *classFile);
void imprimir_interfaces(ClassFile *classFile);
void imprimir_fields(ClassFile *classFile);
void imprimir_metodos(ClassFile *classFile);
void imprimir_atributos(Attribute_info *atributos, uint16_t contador_atributos, Cp_info *constant_pool, int tab);
void imprimir_classe(ClassFile *classfile);
void imprimir_code(Cp_info *constant_pool, Code_attribute *code_attribute, char *space);
int imprimir_instrucao_padrao(Cp_info *constant_pool, Code_attribute *code_attribute, char *space, decoder opcode_decod,
                              int instr_pos);
void imprimir_constant_pool_inserida(int index, Cp_info *constant_pool);

#ifdef __cplusplus
}
#endif


#endif
