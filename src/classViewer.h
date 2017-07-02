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


void printGeneralInformation(ClassFile* classFile);
void printConstantPool(ClassFile* classFile);
void printInterfaces(ClassFile* classFile);
void printFields(ClassFile* classFile);
void printMethods(ClassFile* classFile);
void printAttributes(Attribute_info* attributes, uint16_t attributes_count, Cp_info* constant_pool, int tab);
void printClass(ClassFile* classfile);
void printCode(Cp_info* constant_pool, Code_attribute* code_attribute, char* space);
int printDefaultInstruction(Cp_info *constant_pool, Code_attribute *codeAttribute, char *space, Mapper opcodeMapper, int instrPos);
void printConstantPoolEntry(int index, Cp_info* constant_pool);

#ifdef __cplusplus
}
#endif


#endif
