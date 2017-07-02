#include <stdio.h>
#include <string.h>
#include "objectManager.h"
#include "classLoader.h"
#include "methodArea.h"

static Object* objectList;

uint16_t generateObjectFieldCount(ClassFile* classFile);
ObjectField* generateObjectFieldArray(ClassFile* classFile, uint16_t count);
uint16_t generateObjectMethodCount(ClassFile* classFile);
ObjectMethod* generateObjectMethodArray(ClassFile* classFile, uint16_t count);

Object* createObject(ClassFile* classFile){
	Object* object = (Object*)malloc(sizeof(Object));
	object->classFile = classFile; 
	object->fields_count = generateObjectFieldCount(classFile);
	object->fields = generateObjectFieldArray(classFile, object->fields_count);
	object->methods_count = generateObjectMethodCount(classFile);
	object->methods = generateObjectMethodArray(classFile, object->methods_count);
	object->variables_pointers = (uint64_t*)malloc(object->fields_count*sizeof(uint64_t));
	for (int i = 0; i < object->fields_count; ++i){
		object->variables_pointers[i] = 0;
	}
	return object;
}

// Funcoes de metodos do objeto

uint16_t generateObjectMethodCount(ClassFile* classFile){
	uint16_t count = 0;
	do{
		count += classFile->methods_count;
		classFile = getSuperClass(classFile);
	}while(classFile != NULL);
	return count;
}

ObjectMethod generateObjectMethod(ClassFile* classFile, Method_info* method_info){
	ObjectMethod method;
	method.classFile = classFile;
	method.name = classFile->constant_pool[method_info->name_index].info.utf8_info->bytes;
	method.descriptor = classFile->constant_pool[method_info->descriptor_index].info.utf8_info->bytes;
	method.access_flag = method_info->access_flags;
	method.method_info = method_info;
	return method;
}

ObjectMethod* generateObjectMethodArray(ClassFile* classFile, uint16_t count){
	ObjectMethod* methods = (ObjectMethod*)malloc(count*sizeof(ObjectMethod));
	count = 0;
	do{
		for (int i = 0; i < classFile->methods_count; ++i){
			methods[count] = generateObjectMethod(classFile, &(classFile->methods[i]));
			count++;
		}
		classFile = getSuperClass(classFile);
	}while(classFile != NULL);
	return methods;
}

ObjectMethod getObjectMethodByName(Object* object, char* methodName, char* className){
	for (int i = 0; i < object->methods_count; ++i){
		// Procura pela funcao com mesmo nome
		if (strcmp(object->methods[i].name, methodName) == 0){
			if (strcmp("<init>", methodName) == 0){
				// Procura pela classe com mesmo nome
				ClassFile* classFile = object->methods[i].classFile;
				int string_index = classFile->constant_pool[classFile->this_class].info.string_info->string_index;
	    		char * nomeClassept = classFile->constant_pool[string_index].info.utf8_info->bytes;
				if (strcmp(nomeClassept, className) == 0){
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

uint16_t generateObjectFieldCount(ClassFile* classFile){
	uint16_t count = 0;
	do{
		count += classFile->fields_count;
		classFile = getSuperClass(classFile);
	}while(classFile != NULL);
	return count;
}

ObjectField generateObjectField(ClassFile* classFile, Field_info* field_info){
	ObjectField field;
	field.name = classFile->constant_pool[field_info->name_index].info.utf8_info->bytes;
	field.descriptor = classFile->constant_pool[field_info->descriptor_index].info.utf8_info->bytes;
	field.access_flag = field_info->access_flags;
	return field;
}

ObjectField* generateObjectFieldArray(ClassFile* classFile, uint16_t count){
	ObjectField* fields = (ObjectField*)malloc(count*sizeof(ObjectField));
	count = 0;
	do{
		for (int i = 0; i < classFile->fields_count; ++i){
			fields[count] = generateObjectField(classFile, &(classFile->fields[i]));
			count++;
		}
		classFile = getSuperClass(classFile);
	}while(classFile != NULL);
	return fields;
}


uint64_t getObjectFieldValueByName(Object* object, char* name){
	for (int i = 0; i < object->fields_count; ++i){
		if (strcmp(object->fields[i].name, name) == 0){
			return object->variables_pointers[i];
		}
	}	
}

void setObjectFieldValueByName(Object* object, char* name, uint64_t value){
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