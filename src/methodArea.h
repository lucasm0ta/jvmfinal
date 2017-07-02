//
// Created by Henrique Faria on 11/17/16.
//

#ifndef JADIEL_VM_METHODAREA_H
#define JADIEL_VM_METHODAREA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include "classLoader.h"

typedef struct {
    char *name;

} TypeInfo;

void initHashtable(int initialSize);
void printHashtable();
void freeHashtable();
void insert(TypeInfo dt);
size_t hash(const char *str, size_t len);
int indexOf(TypeInfo dt);


Code_attribute* getCodeAttribute(ClassFile* classFile, Method_info* methodInfo);
Method_info* findMainMethod(ClassFile* classFile);
Method_info* findMethod(ClassFile* targetClass, ClassFile* originClass, uint16_t indice);
char* findClassNameFromMethod(Cp_info* constantPool, int32_t methodIndex);
char* findMethodName(Cp_info* constantPool, int16_t nameAndTypeIndex);
char* findMethodDescriptor(Cp_info* constantPool, int16_t nameAndTypeIndex);
int32_t getParamsCount(char* bytes);
TypeInfo *getItem(int index);
ClassFile* getSuperClass(ClassFile* classFile);



#ifdef __cplusplus
}
#endif


#endif //JADIEL_VM_METHODAREA_H
