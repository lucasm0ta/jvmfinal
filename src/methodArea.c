#include <stdlib.h>
#include <string.h>
#include "methodArea.h"



int tableSize;

void resizeHashtable();

TypeInfo ** hashtable;
int dataCount = 0;

void initHashtable(int initialSize) {
    tableSize = initialSize;
    hashtable = (TypeInfo **) malloc(tableSize * sizeof(TypeInfo *));

    if(hashtable == NULL)
         exit(1);

    for (int i = 0; i < tableSize; i++)
        hashtable[i] = NULL;
}

void freeHashtable() {
    for (int i = 0; i < tableSize; i++) {
        if(hashtable[i] != NULL)
            free(hashtable[i]);
    }
    free(hashtable);
    dataCount = 0;
}

void resizeHashtable() {
    int newSize = tableSize + (tableSize * 2) / 3;
    hashtable = (TypeInfo **) realloc(hashtable, newSize * sizeof(TypeInfo *));

    for (int i = tableSize; i < newSize; i++)
        hashtable[i] = NULL;

    tableSize = newSize;
}

void insert(TypeInfo dt) {

    if(dataCount == tableSize)
        resizeHashtable();

    const int index = indexOf(dt);
    hashtable[index] = (TypeInfo *) malloc(sizeof(TypeInfo));

    if(hashtable[index] == NULL)
        exit(1);

    hashtable[index]->name = dt.name;

    dataCount++;
}

int indexOf(TypeInfo dt) {
    const int hashValue = hash(dt.name, strlen(dt.name));

    if(hashtable[hashValue] != NULL) {
        int i = (hashValue + 1) % tableSize;

        while(hashtable[i] != NULL) {
            i = (i + 1) % tableSize;
        }
        return i;
    } else {
        return hashValue;
    }
}


size_t hash(const char *str, size_t len) {
    unsigned int hash = 5381;
    unsigned int i    = 0;

    for(i = 0; i < len; str++, i++)
    {
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash % tableSize;
}


TypeInfo *getItem(int index) {
    return hashtable[index];
}


void printHashtable() {
    printf("\n");
    for(int i = 0; i < tableSize; i++) {
        if(hashtable[i] != NULL)
            printf("%s\n", hashtable[i]->name);
        else
            printf("-1\n");
    }
    printf("\n");
}

Method_info* findMainMethod(ClassFile* classFile) {

	int i;
	char* nome;
	char* desc;

	for(i = 0; i < classFile->methods_count; i++) {

		nome = classFile->constant_pool[(classFile->methods[i].name_index)].info.utf8_info->bytes;
		desc = classFile->constant_pool[(classFile->methods[i].descriptor_index)].info.utf8_info->bytes;

		if(strcmp("main", nome) == 0 && strcmp("([Ljava/lang/String;)V", desc) == 0) {
				return &(classFile->methods[i]);
		}
	}

  printf("Não foi possível encontrar o método main\n");
  exit(1);
}

/**
 * [getSuperClass description]
 * @param  classFile [description]
 * @return           [description]
 */
ClassFile* getSuperClass(ClassFile* classFile){
  if (classFile->super_class == 0){
    return NULL;
  }
  return carregar_classe(acessar_constant_pool_entry(classFile->super_class, classFile->constant_pool));
}

Method_info* findMethod(ClassFile* targetClass, ClassFile* originClass, uint16_t indice) {

    int indiceName = originClass->constant_pool[indice].info.nameAndType_info->name_index;
    int indiceDescription = originClass->constant_pool[indice].info.nameAndType_info->descriptor_index;
    char* nameOrigin = originClass->constant_pool[indiceName].info.utf8_info->bytes;
    char* descOrigin = originClass->constant_pool[indiceDescription].info.utf8_info->bytes;
    char* nameTarget;
    char* descTarget;

    for(int i = 0; i < targetClass->methods_count; i++) {

        nameTarget = targetClass->constant_pool[(targetClass->methods[i].name_index)].info.utf8_info->bytes;
        descTarget = targetClass->constant_pool[(targetClass->methods[i].descriptor_index)].info.utf8_info->bytes;

        if(strcmp(nameOrigin, nameTarget) == 0 && strcmp(descOrigin, descTarget) == 0) {
                return &(targetClass->methods[i]);
        }

    }
}

char* findClassNameFromMethod(Cp_info* constantPool, int32_t methodIndex) {
	int32_t classIndex = constantPool[methodIndex].info.methodref_info->class_index;
  return acessar_constant_pool_entry(classIndex, constantPool);
}

char* findMethodName(Cp_info* constantPool, int16_t nameAndTypeIndex) {
  int32_t methodNameIndex = constantPool[nameAndTypeIndex].info.nameAndType_info->name_index;
  return constantPool[methodNameIndex].info.utf8_info->bytes;
}

char* findMethodDescriptor(Cp_info* constantPool, int16_t nameAndTypeIndex) {
  int32_t methodDescriptorIndex = constantPool[nameAndTypeIndex].info.nameAndType_info->descriptor_index;
  return constantPool[methodDescriptorIndex].info.utf8_info->bytes;
}

Code_attribute* recuperar_code_attribute(ClassFile *classFile, Method_info *methodInfo) {
  int i = 0;



  for(; i < methodInfo->attributes_count; i++) {

    char * name = classFile->constant_pool[methodInfo->attributes[i].attribute_name_index].info.utf8_info->bytes;
    if(strcmp("Code", name) == 0) {
      return methodInfo->attributes[i].info.code_attribute;
    }
  }

}

int32_t getParamsCount(char* bytes) {

  int i = 1;
  int parametersCount = 0;
  while(bytes[i] != ')') {
    if(bytes[i] == 'Z' || bytes[i] == 'S' || bytes[i] == 'F' ||
    bytes[i] == 'I' || bytes[i] == 'C' || bytes[i] == 'B') {
      parametersCount++;
    } else if(bytes[i] == 'D' || bytes[i] == 'J') {
      parametersCount+=2;
    } else if(bytes[i] == 'L') {
      while(bytes[i++] != ';');
      parametersCount++;
    }
    i++;
  }

  return parametersCount;
}
