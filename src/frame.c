#include "frame.h"
#include "instructions.h"
#include "methodArea.h"
#include "classLoader.h"
#include "instructionMapper.h"


/**
 * Realiza a criacao do frame
 * @param cp     informacao do constantpool
 * @param classe informacao do classfile
 * @param code   atributo de codigo
 */
void createFrame(Cp_info* cp, ClassFile* classe, Code_attribute* code) {
  stackFrame* sf = NULL;
  sf = (stackFrame*) calloc(1, sizeof(stackFrame));

  sf->node = (frame*) calloc(1, sizeof(frame));

  pushFrame(cp, classe, code, sf);
 }

/**
 * Coloca um frame na pilha de frames
 * @param cp     Informação do constantpool
 * @param classe Informação da classe, classfile
 * @param code   Atributo de codigo
 * @param sf     Ponteiro para o frame
 */
void pushFrame(Cp_info* cp, ClassFile* classe, Code_attribute* code, struct stackFrame* sf) {

  sf->next = topo;
	topo = sf;

  //Inicializa o pc.
	topo->node->pc = 0;

  //Inicializa classe constantPool tamanho da pilha tamanho do array de ver local
	//Inicializa bytecodes.
	topo->node->classe = classe;
	topo->node->constantPool = cp;
	topo->node->max_stack = code->max_stack;
	topo->node->max_locals = code->max_locals;
	topo->node->code_length = code->code_length;
	topo->node->code = code->code;

  //Aloca espaço para o array de var local
	topo->node->fields = (uint32_t*) calloc(topo->node->max_locals, sizeof(uint32_t));

  topo->node->operandStack = (operandStack*) calloc(1, sizeof(operandStack));
  topo->node->operandStack->operands = (uint32_t*) calloc(topo->node->max_stack, sizeof(uint32_t));
  topo->node->operandStack->depth = 0; // inicialmente a pilha esta vazia

	//Atualiza o currentFrame para o frame alocado agora.
	currentFrame = topo->node;
}
/**
 * Retira um frame do topo da pilha, libera seu espaço de memoria
 */
void popFrame() {

  if(topo->next != NULL) {
    if(returnFlag == 1) {
      int32_t returnValue = popOperand();
      if(DEBUG) printf("Empilhando retorno cat 1: %d\n", returnValue);
      currentFrame = topo->next->node;
      pushOperand(returnValue);
    } 
    else if(returnFlag == 2) {
      int32_t lowValue = popOperand();
      int32_t highValue = popOperand();
      currentFrame = topo->next->node;
      int64_t value = highValue;
      value <<= 32;
      value += lowValue;
      if(DEBUG) {
        printf("Empilhando retorno cat 2:\n");
        printf("high: %d\n", highValue);
        printf("low: %d\n", lowValue);
        printf("retorno: %lx\n", value);
      } 
      pushOperand(highValue);
      pushOperand(lowValue);
    }
    else{
      currentFrame = topo->next->node;
    }
    returnFlag = 0;
  } else {
    currentFrame = NULL;
  }

  struct stackFrame* aux = topo;
  topo = topo->next;

  free(aux->node->fields);
  free(aux->node->operandStack->operands);
  free(aux->node->operandStack);
  free(aux->node);
  free(aux);
}
/**
 * Coloca um operando na pilha de operandos do frame
 * @param value Valor a ser colocado na pilha
 */
void pushOperand(int32_t value) {

  if(currentFrame->operandStack->depth >= currentFrame->max_stack) {
    printf("Operand stack overflow!\n");
    exit(0);
  }

  // incrementa profundidade da pilha
  currentFrame->operandStack->depth += 1;

  // poe valor no frame - o -1 eh pq o array comeca em 0
  currentFrame->operandStack->operands[currentFrame->operandStack->depth - 1] = value;
}
/**
 * Retira e devolve um valor armazenado na pilha de operandos
 * @return Valor antes armazenado na pilha de operandos
 */
int32_t popOperand() {
  currentFrame->operandStack->depth -= 1;
    if (currentFrame->operandStack->depth < 0){
        printf("profundidade da pilha de operandos negativa: %d\n", currentFrame->operandStack->depth);
    }

    // retorna valor se deve ao fato de ja termos decrementado o topo da pilha
    return currentFrame->operandStack->operands[currentFrame->operandStack->depth];
}
/**
 * Roda os frames 
 */
void runFrame() {
  if(DEBUG) dumpStack(0);
  while ((currentFrame->pc) < currentFrame->code_length){
    if(DEBUG) printf("pc: %d\t%s\n", currentFrame->pc, mapper[currentFrame->code[currentFrame->pc]].instruction);
		instruction[currentFrame->code[currentFrame->pc]]();
	}
  if(DEBUG) dumpStack(1);
  popFrame();
}
/**
 * Chama um metodo criando um frame para ele
 * @param classFile Informação da classe deste método
 * @param method    Informação do metodo
 */
void pushMethod(ClassFile* classFile, Method_info* method) {
  if(DEBUG) printf("\nENTRANDO NO METODO: %s\n", classFile->constant_pool[method->name_index].info.utf8_info->bytes);
  createFrame(classFile->constant_pool, classFile, getCodeAttribute(classFile, method));
}

/**
 * Sai do método
 * @param Flag para saida 
 */
void dumpStack(int i){
  if (topo != NULL){
    ClassFile* classFile = topo->node->classe;
    if (i) printf("\nSAINDO DO METODO\n");
    int string_index = classFile->constant_pool[classFile->this_class].info.string_info->string_index;
    char * nomeClassept = classFile->constant_pool[string_index].info.utf8_info->bytes;
    printf("CLASS NAME:        %s\n",nomeClassept);
    printf("CODE :             %d/%d\n", topo->node->pc,topo->node->code_length);
    printf("NEXT CLASS NAME:   ");
    struct stackFrame* aux = topo;
    while (aux->next != NULL){
      string_index = aux->next->node->classe->constant_pool[aux->next->node->classe->this_class].info.string_info->string_index;
      nomeClassept = aux->next->node->classe->constant_pool[string_index].info.utf8_info->bytes;
      printf("%s -> ",nomeClassept);
      aux = aux->next;
    }
    printf("NULL\n\n");
  }
}
