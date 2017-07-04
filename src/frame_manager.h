#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>
#include <stdlib.h>
#include "carregador.h"
#include "instrucoes_base.h"
#include "util.h"

/**
 * Pilha de operandos. Cada frame tera um desses que sera usado
 * por algumas instrucoes, principalmente as que fazem operacoes.
 *
 * @depth Tamanho do frame. Aponta para o ultimo elemento adicionado
 * @operands O vetor de operandos que representa a pilha
 */
typedef struct operandStack {
  int depth;
  int32_t* operands;
} operandStack;

/**
 * Estrutura do frame. Contem um vetor de varaveis locais, um ponteiro
 * para a constant_pool, um pilha de operandos e o codigo em si. Possui alguns
 * outros elementos que sao usados no seu funcionamento.
 */
typedef struct frame {
	int32_t* fields; //Local variables array
	Cp_info* constantPool;
	ClassFile* classe;
	u2 max_stack;
	u2 max_locals;
	u4 code_length;
	u1* code; //Bytecode
	u4 pc; //Program counter
	operandStack* operandStack;
}frame;

/**
 * Estrutura usada para empilhar frames
 */
typedef struct pilha_frame{
	frame* node;
	struct pilha_frame* next;
}pilha_frame;


// Flags usadas para saber se o novo valor ocupa 1 ou 2 slots
int8_t flag;
int32_t returnValue;
int32_t retHigh,retLow;

// Ponteiro pro primeiro frame da pilha
struct frame* frame_atual;
static struct pilha_frame* cabeca = NULL;

/**
 * Cria a estrutura do frame e faz empilha ela
 * @param cp     Ponteiro para o constant_pool
 * @param classe Estrutura do classFile
 * @param code   Ponteiro para a estrutura do codigo
 */
pilha_frame* criar_frame(Cp_info *cp, ClassFile *classe, Code_attribute *code);

/**
 * Empilha um frame na pilha
 * @param cp     Ponteiro para o constant_pool
 * @param classe Estrutura do classFile
 * @param code   Ponteiro para a estrutura do codigo
 * @param sf     Ponteiro para a pilha de frames
 */
void empilhar_frame(Cp_info *, ClassFile *, Code_attribute *, struct pilha_frame *);

/**
 * Desempilha um frame, liberando toda a memoria usada por esse frame
 */
void desempilhar_frame();

/**
 * Empilha um operando na pilha de openrados do frame atual
 * @param value Valor que sera colocado na pilha
 */
void empilhar_operando(int32_t);

/**
 * Desempilha o valor da pilha e retorna esse valor
 * @return Valor que foi desempilhado
 */
int32_t desempilhar_operando();

/**
 * Executa o codigo do atributo Code do frame
 */
void executar_frame();

/**
 * Cria um novo frame para o metodo chamado
 * @param classFile Ponteiro para a estrutura da classe
 * @param method    Ponteiro para o atributo metodo
 */
void empilhar_metodo(ClassFile *classe, Method_info *method);

/**
 * Libera a memoria usada por um frame
 * @param frame Ponteiro para frame
 */
void free_frame(struct pilha_frame* pf);

#endif
