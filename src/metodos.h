#ifndef METHODAREA_H
#define METHODAREA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include "carregador.h"
#include "util.h"

/**
 * Guarda o tipo da informacao em uma string
 */
typedef struct {
    char *name;
} TypeInfo;


/**
 * Pega a a rea de code de um determinado metodo
 * @param  classFile  Estrutura do classFile
 * @param  methodInfo Estrutura do metodo q sera procurado
 * @return            Ponteiro para estrutura de codigo 
 */
Code_attribute* recuperar_code_attribute(ClassFile *classFile, Method_info *methodInfo);

/**
 * Acha o metodo main na estrutura do classFile 
 * @param  classFile Ponteiro para estrutura do classFile
 * @return           Retorna um ponteiro para uma estrutura Method_info contendo o metodo main
 */
Method_info* buscar_metodo_main(ClassFile *classFile);

/**
 * Acha um metodo de uma estrutura de classe em outra estrutura de classe
 * @param  classe_desejada Classe onde o metodo sera procurado
 * @param  classe_origem   A classe que contem o metodo
 * @param  indice          Indice do metodo
 * @return                 Retorna o metodo encontrado na outra classe
 */
Method_info* buscar_metodo(ClassFile *classe_desejada, ClassFile *classe_origem, u2 indice);

/**
 * Retorna o nome da classe que contem o metodo pelo indice dele
 * @param  constant_pool Ponteiro para constantPool da classe
 * @param  method_index  Indice do metodo que tera seu nome buscado
 * @return               Retorna ponteiro para a string que contem o nome do metodo
 */
char* buscar_nome_classe_por_metodo(Cp_info *constant_pool, int32_t method_index);

/**
 * Busca o nome do metodo pelo Indice
 * @param  constant_pool   Ponteiro para a constant_pool 
 * @param  nome_type_index indice que sera buscado
 * @return                 Nome do metodo como ponteiro para char
 */
char* buscar_nome_metodo(Cp_info *constant_pool, int16_t nome_type_index);

/**
 * Busca o descritor para o metodo na constant_pool
 * @param  constant_pool    Ponteiro para a constantPool da classe
 * @param  nameAndTypeIndex indice que sera buscado
 * @return                  Descritor do metodo
 */
char* buscar_descritor_metodo(Cp_info *constant_pool, int16_t nameAndTypeIndex);

/**
 * Conta quantos parametros tem
 * @param  bytes bytes que serao analisados
 * @return       Retorna o numero de parametros
 */
int32_t contador_de_parametros(char *bytes);

TypeInfo *getItem(int index);

/**
 * Retorna um ponteiro para estrutura da classe pai
 * @param  classFile Ponteiro para a classe que tera seu pai buscado
 * @return           Retorna ponteiro para a estrutura da classe pai
 */
ClassFile* super_classe(ClassFile *classFile);

#ifdef __cplusplus
}
#endif

#endif //METHODAREA_H
