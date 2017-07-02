#ifndef CLASSLIST_H
#define CLASSLIST_H

#include "classLoader.h"
#include <stdlib.h>

typedef struct ClassList{
    ClassFile*			classFile;
    struct ClassList*	next;
}ClassList; 

/**
 * Insere um classFile na lista de classFiles ja carregados
 * @param classFile referência para a estrutura classFile
 */
void pushClass(ClassFile *classFile);

/**
 * Procura um classFile já carregado na lista de classFiles
 * @param  name nome da classe
 * @return      struct para class solicitada, NULL caso não encontre a class
 */
ClassFile* searchClass(char *name);

/**
 * Mostra a lista de classes ja carregadas
 */
void dumpClassList();

#endif 