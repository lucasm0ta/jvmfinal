/**
 * Functions used to print the class structure information.
 */

#ifndef CLASSVIEWER_H
#define CLASSVIEWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "classLoader.h"
#include "instructionMapper.h"
#include "tableswitchViewer.h"
#include "lookupswitchViewer.h"

/**
 * Imprime as informacoes basicas da classe como magic_number e tamanho das estruturas
 * @param  classFile Estrutura que guarda informacoes do .class
 */
void imprimir_informacoes_classe(ClassFile *classFile);

/**
 * Imprime as informacoes da constantPool do .class.
 * @param classFile Estrutura que guarda informacoes do .class
 */
void imprimir_constant_pool_completa(ClassFile *classFile);

/**
 * Imprime as informacoes das interfaces do .class
 * @param classFile Estrutura que guarda informacoes do .class
 */
void imprimir_interfaces(ClassFile *classFile);

/**
 * Imprime as informacoes dos fields do .class
 * @param classFile Estrutura que guarda informacoes do .class
 */
void imprimir_fields(ClassFile *classFile);

/**
 * Imprime as informacoes dos metodos do .class
 * @param classFile Estrutura que guarda informacoes do .class
 */
void imprimir_metodos(ClassFile *classFile);

/**
 * WARNING: GAMBIARRA PARA DAR OS TABS CORRETOS (QUANDO UM ATRIBUTO ESTA DENTRO DO OUTRO)
 *          POR ISSO QUE TEM UM %s NA FRENTE DE TODOS OS PRINTS
 * @param atributos       [description]
 * @param contador_atributos [description]
 * @param constant_pool    [description]
 * @param tab              quantidade de tabs que devem ser dados
 */
void imprimir_atributos(Attribute_info *atributos, uint16_t contador_atributos, Cp_info *constant_pool, int tab);

/**
 * Função que realiza os prints de acordo com cada item do Byte code Viewer
 * @param classFile [description]
 */
void imprimir_classe(ClassFile *classfile);

/**
 * Imprime as informacoes do code attribute. Ele usa a constant_pool para
 * imprimir as informacoes das entradas do constant_pool que estao no code
 * @param constant_pool  Ponteiro para constant_pool q o code usa
 * @param code_attribute Codigo que tera sua informacao impressaq
 */
void imprimir_code(Cp_info *constant_pool, Code_attribute *code_attribute, char *space);

/**
 * Imprime as instrucoes padrao do java
 * @param  constant_pool  Ponteiro para a constant_pool
 * @param  code_attribute O codigo que vai ser usado
 * @param  opcode_decod   decodificador usado para achar o nome dai nstrucao
 * @param  instr_pos      Posicao da instrucao
 * @return                retorna posicao da instrucao
 */
int imprimir_instrucao_padrao(Cp_info *constant_pool, Code_attribute *code_attribute, char *space, decoder opcode_decod,
                              int instr_pos);

/**
 * Imprime a entrada em index da constant_pool
 * @param index         Index da entrada da constant_pool q sera impressa
 * @param constant_pool Ponteiro para a constant_pool
 */
void imprimir_constant_pool_inserida(int index, Cp_info *constant_pool);

#ifdef __cplusplus
}
#endif


#endif
