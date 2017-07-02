#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>
#include <stdlib.h>
#include "classLoader.h"
#include "instructions.h"

typedef struct operandStack {
  // stack depth
  int depth;
  // stack operands represented as an array
  int32_t* operands;
} operandStack;

typedef struct frame {
	int32_t* fields; //Local variables array
	Cp_info* constantPool;
	ClassFile* classe;
	uint16_t max_stack;
	uint16_t max_locals;
	uint32_t code_length;
	uint8_t* code; //Bytecode
	uint32_t pc; //Program counter
	operandStack* operandStack;
}frame;

typedef struct stackFrame{
	frame* node;
	struct pilha_frame* next;
}pilha_frame;


//Flag para empilhar 1 slot ou 2(double e long).
int8_t flag;
int32_t returnValue;
int32_t retHigh,retLow;

struct frame* frame_atual;
//Refencia ao cabeca da pilha de frames. Essencial para Empilhar e desempilhar os frames.
static struct pilha_frame* cabeca = NULL;

/**
 * Realiza a criacao do frame
 * @param cp     informacao do constantpool
 * @param classe informacao do classfile
 * @param code   atributo de codigo
 */
void criar_frame(Cp_info *cp, ClassFile *classe, Code_attribute *code);
/**
 * Coloca um frame na pilha de frames
 * @param cp     Informação do constantpool
 * @param classe Informação da classe, classfile
 * @param code   Atributo de codigo
 * @param sf     Ponteiro para o frame
 */
void empilhar_frame(Cp_info *, ClassFile *, Code_attribute *, struct pilha_frame *);
/**
 * Retira um frame do topo da pilha, libera seu espaço de memoria
 */
void desempilhar_frame();
/**
 * Coloca um operando na pilha de operandos do frame
 * @param value Valor a ser colocado na pilha
 */
void empilhar_operando(int32_t);
/**
 * Retira e devolve um valor armazenado na pilha de operandos
 * @return Valor antes armazenado na pilha de operandos
 */
int32_t desempilhar_operando();

/**
 * Roda os frames 
 */
void executar_frame();
/**
 * Chama um metodo criando um frame para ele
 * @param classFile Informação da classe deste método
 * @param method    Informação do metodo
 */
void empilhar_metodo(ClassFile *classe, Method_info *method);

/**
 * Sai do método
 * @param Flag para saida 
 */
void dumpStack(int i);
#endif
