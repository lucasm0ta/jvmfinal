/**
 *  Contains the structure and functions that handle the loaded class files
 */

#ifndef CLASSLIST_H
#define CLASSLIST_H

#include "classLoader.h"
#include <stdlib.h>

/**
 * List that holds all of the loaded .class files
 */
typedef struct ClassList{
    ClassFile*			classFile;
    struct lista_classe*	next;
}lista_classe;

/**
 * Shows the list of classes. Used for debugging
 */
void dumpClassList();

/**
 * Puts a new classList in the classFile list
 * @param classFile classFile reference
 */
void empilhar_classe(ClassFile *classFile);

/**
 * Gets a loaded classFile based on its name
 * @param  name ClassFile name
 * @return      struct para class solicitada, NULL caso não encontre a class
 */
ClassFile* buscar_classe(char *name);

#endif 