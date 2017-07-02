#include <stdlib.h>
#include <string.h>
#include "methodArea.h"



int tamanho_tabela;

void redimensionar_hashtable();

TypeInfo ** hashtable;
int data_count = 0;

void inicializar_hashtable(int tamanho_inicial) {
    tamanho_tabela = tamanho_inicial;
    hashtable = (TypeInfo **) malloc(tamanho_tabela * sizeof(TypeInfo *));

    if(hashtable == NULL)
         exit(1);

    for (int i = 0; i < tamanho_tabela; i++)
        hashtable[i] = NULL;
}

void liberar_memoria_Hashtable() {
    for (int i = 0; i < tamanho_tabela; i++) {
        if(hashtable[i] != NULL)
            free(hashtable[i]);
    }
    free(hashtable);
    data_count = 0;
}

void redimensionar_hashtable() {
    int novo_tamanho = tamanho_tabela + (tamanho_tabela * 2) / 3;
    hashtable = (TypeInfo **) realloc(hashtable, novo_tamanho * sizeof(TypeInfo *));

    for (int i = tamanho_tabela; i < novo_tamanho; i++)
        hashtable[i] = NULL;

    tamanho_tabela = novo_tamanho;
}

void inserir(TypeInfo dt) {

    if(data_count == tamanho_tabela)
        redimensionar_hashtable();

    const int index = indexOf(dt);
    hashtable[index] = (TypeInfo *) malloc(sizeof(TypeInfo));

    if(hashtable[index] == NULL)
        exit(1);

    hashtable[index]->name = dt.name;

    data_count++;
}

int indexOf(TypeInfo dt) {
    const int hashValue = hash(dt.name, strlen(dt.name));

    if(hashtable[hashValue] != NULL) {
        int i = (hashValue + 1) % tamanho_tabela;

        while(hashtable[i] != NULL) {
            i = (i + 1) % tamanho_tabela;
        }
        return i;
    } else {
        return hashValue;
    }
}


size_t hash(const char *str, size_t tamanho) {
    unsigned int hash = 5381;
    unsigned int i    = 0;

    for(i = 0; i < tamanho; str++, i++)
    {
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash % tamanho_tabela;
}


TypeInfo *getItem(int index) {
    return hashtable[index];
}


void imprimir_hashtable() {
    printf("\n");
    for(int i = 0; i < tamanho_tabela; i++) {
        if(hashtable[i] != NULL)
            printf("%s\n", hashtable[i]->name);
        else
            printf("-1\n");
    }
    printf("\n");
}

Method_info* buscar_metodo_main(ClassFile *classFile) {

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
ClassFile* super_classe(ClassFile *classFile){
  if (classFile->super_class == 0){
    return NULL;
  }
  return carregar_classe(acessar_constant_pool_entry(classFile->super_class, classFile->constant_pool));
}

Method_info* buscar_metodo(ClassFile *classe_desejada, ClassFile *classe_origem, uint16_t indice) {

    int nome_indice = classe_origem->constant_pool[indice].info.nameAndType_info->name_index;
    int desc_indice = classe_origem->constant_pool[indice].info.nameAndType_info->descriptor_index;
    char* name_origin = classe_origem->constant_pool[nome_indice].info.utf8_info->bytes;
    char* desc_origin = classe_origem->constant_pool[desc_indice].info.utf8_info->bytes;
    char* name_target;
    char* desc_target;

    for(int i = 0; i < classe_desejada->methods_count; i++) {

        name_target = classe_desejada->constant_pool[(classe_desejada->methods[i].name_index)].info.utf8_info->bytes;
        desc_target = classe_desejada->constant_pool[(classe_desejada->methods[i].descriptor_index)].info.utf8_info->bytes;

        if(strcmp(name_origin, name_target) == 0 && strcmp(desc_origin, desc_target) == 0) {
                return &(classe_desejada->methods[i]);
        }

    }
}

char* buscar_nome_classe_por_metodo(Cp_info *constant_pool, int32_t method_index) {
	int32_t class_index = constant_pool[method_index].info.methodref_info->class_index;
  return acessar_constant_pool_entry(class_index, constant_pool);
}

char* buscar_nome_metodo(Cp_info *constant_pool, int16_t nome_type_index) {
  int32_t indice_nome_method = constant_pool[nome_type_index].info.nameAndType_info->name_index;
  return constant_pool[indice_nome_method].info.utf8_info->bytes;
}

char* buscar_descritor_metodo(Cp_info *constant_pool, int16_t nameAndTypeIndex) {
  int32_t methodDescriptorIndex = constant_pool[nameAndTypeIndex].info.nameAndType_info->descriptor_index;
  return constant_pool[methodDescriptorIndex].info.utf8_info->bytes;
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

int32_t contador_de_parametros(char *bytes) {

  int i = 1;
  int contador = 0;
  while(bytes[i] != ')') {
    if(bytes[i] == 'Z' || bytes[i] == 'S' || bytes[i] == 'F' ||
    bytes[i] == 'I' || bytes[i] == 'C' || bytes[i] == 'B') {
      contador++;
    } else if(bytes[i] == 'D' || bytes[i] == 'J') {
      contador+=2;
    } else if(bytes[i] == 'L') {
      while(bytes[i++] != ';');
      contador++;
    }
    i++;
  }

  return contador;
}
