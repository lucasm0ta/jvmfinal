#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "carregador.h"
#include "util.h"

typedef struct object_field{
	char* 			name;
	char*			descriptor;
	u2		access_flag;
}object_field;

typedef struct object_method{
	ClassFile* 		classFile;
	char* 			name;
	char*			descriptor;
	u2		access_flag;
	Method_info* 	method_info;
}object_method;

typedef struct Object{
	ClassFile* 		classFile;
	u2        fields_count;
    object_field*    fields;
	u2        methods_count;
    object_method*   methods;
    uint64_t*		variables_pointers;
}Object;

/**
 * Retorna uma instância da classe alocada
 * @param  class_file estrutura do classFile que sera instanciada
 * @return referência para um objeto alocado
 */
Object* criar_objeto(ClassFile *class_file);

/**
 * Retorna o field que possuiu o mesmo nome do parâmetro informado
 * @param  object referência para o objeto
 * @param  name   nome do field desejado
 * @return caso o field for um objeto/array retorna uma referência, ou um valor nos outros casos
 */
uint64_t buscar_object_field_value_por_nome(Object *object, char *name);

/**
 * Atribui o valor passado para um dos fields do objeto
 * @param object referência para o objeto
 * @param name   nome do field a ser modificado
 * @param value  valor a ser atribuido ao field, caso o field seja um objeto/array value é o endereço do objeto
 */
void set_object_field_value_por_nome(Object *object, char *name, uint64_t value);

/**
 * Retorna um método de um objeto
 * @param  object     referência para o objeto
 * @param  method_name nome do método desejado
 * @param  class_name  classe do método desejado (para caso de métodos com mesmo nome, como construtores)
 * @return            refência para um objeto que contém informações do método
 */
object_method buscar_object_method_by_name(Object *object, char *method_name, char *class_name);

#endif
