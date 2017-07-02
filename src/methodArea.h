#ifndef METHODAREA_H
#define METHODAREA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include "classLoader.h"

typedef struct {
    char *name;
} TypeInfo;

void inicializar_hashtable(int tamanho_inicial);
void imprimir_hashtable();
void liberar_memoria_Hashtable();
void inserir(TypeInfo dt);
size_t hash(const char *str, size_t tamanho);
int indexOf(TypeInfo dt);

Code_attribute* recuperar_code_attribute(ClassFile *classFile, Method_info *methodInfo);

Method_info* buscar_metodo_main(ClassFile *classFile);
Method_info* buscar_metodo(ClassFile *classe_desejada, ClassFile *classe_origem, uint16_t indice);
char* buscar_nome_classe_por_metodo(Cp_info *constant_pool, int32_t method_index);
char* buscar_nome_metodo(Cp_info *constant_pool, int16_t nome_type_index);
char* buscar_descritor_metodo(Cp_info *constant_pool, int16_t nameAndTypeIndex);
int32_t contador_de_parametros(char *bytes);
TypeInfo *getItem(int index);
ClassFile* super_classe(ClassFile *classFile);

#ifdef __cplusplus
}
#endif

#endif //METHODAREA_H
