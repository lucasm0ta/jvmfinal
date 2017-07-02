#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "classLoader.h"

typedef struct ObjectField{
	char* 			name;
	char*			descriptor;
	uint16_t		access_flag;
}ObjectField;

typedef struct ObjectMethod{
	ClassFile* 		classFile;
	char* 			name;
	char*			descriptor;
	uint16_t		access_flag;
	Method_info* 	method_info;
}ObjectMethod;

typedef struct Object{
	ClassFile* 		classFile;
	uint16_t        fields_count;
    ObjectField*    fields;
	uint16_t        methods_count;
    ObjectMethod*   methods;
    uint64_t*		variables_pointers;
}Object;

/**
 * Retorna uma instância da classe do classFile
 * @param  classFile struct do classFile que sera instanciado
 * @return           referência para um objeto alocado
 */
Object* createObject(ClassFile* classFile);

/**
 * Retorna o field com nome "name" de um objeto
 * @param  object referência para o objeto
 * @param  name   nome do field desejado
 * @return        uma referência caso o field for um objeto/array, ou um valor do campo nos outros casos
 */
uint64_t getObjectFieldValueByName(Object* object, char* name);

/**
 * Atribui o valor passado para um dos fields do objeto
 * @param object referência para o objeto
 * @param name   nome do field a ser modificado
 * @param value  valor a ser atribuido ao field, caso o field seja um objeto/array value é o endereço do objeto
 */
void setObjectFieldValueByName(Object* object, char* name, uint64_t value);

/**
 * Retorna um método de um objeto
 * @param  object     referência para o objeto
 * @param  methodName nome do método desejado
 * @param  className  classe do método desejado (para caso de métodos com mesmo nome, como construtores)
 * @return            refência para um objeto que contém informações do método
 */
ObjectMethod getObjectMethodByName(Object* object, char* methodName, char* className);

/**
 * Mostra uma lista do nome dos fields do objeto
 * @param object referênciaa para o objeto
 */
void dumpObjectFields(Object* object);

/**
 * Mostra uma lista do nome dos métodos do objeto
 * @param object referênciaa para o objeto
 */
void dumpObjectMethods(Object* object);

#endif