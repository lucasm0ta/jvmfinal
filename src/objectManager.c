#include <stdio.h>
#include <string.h>
#include "objectManager.h"
#include "classLoader.h"
#include "methodArea.h"

static Object* objectList;

uint16_t gerar_object_field_count(ClassFile *classFile);
object_field* gerar_object_field_array(ClassFile *class_file, uint16_t count);
uint16_t gerar_object_method_count(ClassFile *class_file);
object_method* gerar_object_method_array(ClassFile *class_file, uint16_t count);

Object* criar_objeto(ClassFile *class_file){
	Object* object = (Object*)malloc(sizeof(Object));
	object->classFile = class_file;
	object->fields_count = gerar_object_field_count(class_file);
	object->fields = gerar_object_field_array(class_file, object->fields_count);
	object->methods_count = gerar_object_method_count(class_file);
	object->methods = gerar_object_method_array(class_file, object->methods_count);
	object->variables_pointers = (uint64_t*)malloc(object->fields_count*sizeof(uint64_t));
	for (int i = 0; i < object->fields_count; ++i){
		object->variables_pointers[i] = 0;
	}
	return object;
}

// Funcoes de metodos do objeto

uint16_t gerar_object_method_count(ClassFile *class_file){
	uint16_t count = 0;
	do{
		count += class_file->methods_count;
		class_file = super_classe(class_file);
	}while(class_file != NULL);
	return count;
}

object_method gerar_object_method(ClassFile *class_file, Method_info *method_info){
	object_method method;
	method.classFile = class_file;
	method.name = class_file->constant_pool[method_info->name_index].info.utf8_info->bytes;
	method.descriptor = class_file->constant_pool[method_info->descriptor_index].info.utf8_info->bytes;
	method.access_flag = method_info->access_flags;
	method.method_info = method_info;
	return method;
}

object_method* gerar_object_method_array(ClassFile *class_file, uint16_t count){
	object_method* methods = (object_method*)malloc(count*sizeof(object_method));
	count = 0;
	do{
		for (int i = 0; i < class_file->methods_count; ++i){
			methods[count] = gerar_object_method(class_file, &(class_file->methods[i]));
			count++;
		}
		class_file = super_classe(class_file);
	}while(class_file != NULL);
	return methods;
}

object_method buscar_object_method_by_name(Object *object, char *method_name, char *class_name){
	for (int i = 0; i < object->methods_count; ++i){
		// Procura pela funcao com mesmo nome
		if (strcmp(object->methods[i].name, method_name) == 0){
			if (strcmp("<init>", method_name) == 0){
				// Procura pela classe com mesmo nome
				ClassFile* classFile = object->methods[i].classFile;
				int string_index = classFile->constant_pool[classFile->this_class].info.string_info->string_index;
	    		char * nomeClassept = classFile->constant_pool[string_index].info.utf8_info->bytes;
				if (strcmp(nomeClassept, class_name) == 0){
					return object->methods[i];
				}
			}
			else{
				return object->methods[i];
			}
		}
	}	
}

void dumpObjectMethods(Object* object){
	printf("Methods Field:\n");
	for (int i = 0; i < object->methods_count; ++i){
		printf("%d : %s\n", i, object->methods[i].name);
	}
}

// Funcoes de fields do objeto

uint16_t gerar_object_field_count(ClassFile *classFile){
	uint16_t count = 0;
	do{
		count += classFile->fields_count;
		classFile = super_classe(classFile);
	}while(classFile != NULL);
	return count;
}

object_field gerar_object_field(ClassFile *class_file, Field_info *field_info){
	object_field field;
	field.name = class_file->constant_pool[field_info->name_index].info.utf8_info->bytes;
	field.descriptor = class_file->constant_pool[field_info->descriptor_index].info.utf8_info->bytes;
	field.access_flag = field_info->access_flags;
	return field;
}

object_field* gerar_object_field_array(ClassFile *class_file, uint16_t count){
	object_field* fields = (object_field*)malloc(count*sizeof(object_field));
	count = 0;
	do{
		for (int i = 0; i < class_file->fields_count; ++i){
			fields[count] = gerar_object_field(class_file, &(class_file->fields[i]));
			count++;
		}
		class_file = super_classe(class_file);
	}while(class_file != NULL);
	return fields;
}


uint64_t buscar_object_field_value_por_nome(Object *object, char *name){
	for (int i = 0; i < object->fields_count; ++i){
		if (strcmp(object->fields[i].name, name) == 0){
			return object->variables_pointers[i];
		}
	}	
}

void set_object_field_value_por_nome(Object *object, char *name, uint64_t value){
	for (int i = 0; i < object->fields_count; ++i){
		if (strcmp(object->fields[i].name, name) == 0){
			object->variables_pointers[i] = value;
			return;
		}
	}	
}

void dumpObjectFields(Object* object){
	printf("Object Field:\n");
	for (int i = 0; i < object->fields_count; ++i){
		printf("%d : %s\n", i, object->fields[i].name);
	}
}