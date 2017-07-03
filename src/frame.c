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
void criar_frame(Cp_info *cp, ClassFile *classe, Code_attribute *code) {
  pilha_frame* pf = NULL;
  pf = (pilha_frame*) calloc(1, sizeof(pilha_frame));

  pf->node = (frame*) calloc(1, sizeof(frame));

  empilhar_frame(cp, classe, code, pf);
 }

/**
 * Coloca um frame na pilha de frames
 * @param cp Informação do constantpool
 * @param classe Informação da classe, classfile
 * @param code Atributo de codigo
 * @param pf Ponteiro para o frame
 */
void empilhar_frame(Cp_info *cp, ClassFile *classe, Code_attribute *code, struct pilha_frame *pf) {
  pf->next = cabeca;
  cabeca = pf;

  //Inicializa o pc.
  cabeca->node->pc = 0;

  //Inicializa classe constantPool tamanho da pilha tamanho do array de ver local
  //Inicializa bytecodes.
  cabeca->node->classe = classe;
  cabeca->node->constantPool = cp;
  cabeca->node->max_stack = code->max_stack;
  cabeca->node->max_locals = code->max_locals;
  cabeca->node->code_length = code->code_length;
  cabeca->node->code = code->code;

  //Aloca espaço para o array de var local
  cabeca->node->fields = (u4*) calloc(cabeca->node->max_locals, sizeof(u4));

  cabeca->node->operandStack = (operandStack*) calloc(1, sizeof(operandStack));
  cabeca->node->operandStack->operands = (u4*) calloc(cabeca->node->max_stack, sizeof(u4));
  cabeca->node->operandStack->depth = 0; // inicialmente a pilha esta vazia

  //Atualiza o frame_atual para o frame alocado agora.
  frame_atual = cabeca->node;
}
/**
 * Retira um frame do topo da pilha, libera seu espaço de memoria
 */
void desempilhar_frame() {

  if(cabeca->next != NULL) {
    if(flag == 1) {
      int32_t valor_retorno = desempilhar_operando();
      if(DEBUG) printf("Empilhando retorno cat 1: %d\n", valor_retorno);
      frame_atual = cabeca->next->node;
      empilhar_operando(valor_retorno);
    }
    else if(flag == 2) {
      int32_t lowValue = desempilhar_operando();
      int32_t highValue = desempilhar_operando();
      frame_atual = cabeca->next->node;
      int64_t value = highValue;
      value <<= 32;
      value += lowValue;
      if(DEBUG) {
        printf("Empilhando retorno cat 2:\n");
        printf("high: %d\n", highValue);
        printf("low: %d\n", lowValue);
        printf("retorno: %lx\n", value);
      }
      empilhar_operando(highValue);
      empilhar_operando(lowValue);
    }
    else{
      frame_atual = cabeca->next->node;
    }
    flag = 0;
  } else {
    frame_atual = NULL;
  }

  struct pilha_frame* aux = cabeca;
  cabeca = cabeca->next;

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
void empilhar_operando(int32_t value) {

  if(frame_atual->operandStack->depth >= frame_atual->max_stack) {
    printf("Operand stack overflow!\n");
    exit(0);
  }

  // incrementa profundidade da pilha
  frame_atual->operandStack->depth += 1;

  // poe valor no frame - o -1 eh pq o array comeca em 0
  frame_atual->operandStack->operands[frame_atual->operandStack->depth - 1] = value;
}
/**
 * Retira e devolve um valor armazenado na pilha de operandos
 * @return Valor antes armazenado na pilha de operandos
 */
int32_t desempilhar_operando() {
  frame_atual->operandStack->depth -= 1;
    if (frame_atual->operandStack->depth < 0){
        printf("profundidade da pilha de operandos negativa: %d\n", frame_atual->operandStack->depth);
    }

    // retorna valor se deve ao fato de ja termos decrementado o cabeca da pilha
    return frame_atual->operandStack->operands[frame_atual->operandStack->depth];
}
/**
 * Roda os frames
 */
void executar_frame() {
  if(DEBUG) dumpStack(0);
  while ((frame_atual->pc) < frame_atual->code_length){
    if(DEBUG) printf("pc: %d\t%s\n", frame_atual->pc, decode[frame_atual->code[frame_atual->pc]].instruction);
    instrucao[frame_atual->code[frame_atual->pc]]();
  }
  if(DEBUG) dumpStack(1);
  desempilhar_frame();
}
/**
 * Chama um metodo criando um frame para ele
 * @param classFile Informação da classe deste método
 * @param method    Informação do metodo
 */
void empilhar_metodo(ClassFile *classFile, Method_info *method) {
  if(DEBUG) printf("\nENTRANDO NO METODO: %s\n", classFile->constant_pool[method->name_index].info.utf8_info->bytes);
  criar_frame(classFile->constant_pool, classFile, recuperar_code_attribute(classFile, method));
}

/**
 * Sai do método
 * @param Flag para saida
 */
void dumpStack(int i){
  if (cabeca != NULL){
    ClassFile* classFile = cabeca->node->classe;
    if (i) printf("\nSAINDO DO METODO\n");
    int string_index = classFile->constant_pool[classFile->this_class].info.string_info->string_index;
    char * nome_classept = classFile->constant_pool[string_index].info.utf8_info->bytes;
    printf("CLASS NAME:        %s\n",nome_classept);
    printf("CODE :             %d/%d\n", cabeca->node->pc,cabeca->node->code_length);
    printf("NEXT CLASS NAME:   ");
    struct pilha_frame* aux = cabeca;
    while (aux->next != NULL){
      string_index = aux->next->node->classe->constant_pool[aux->next->node->classe->this_class].info.string_info->string_index;
      nome_classept = aux->next->node->classe->constant_pool[string_index].info.utf8_info->bytes;
      printf("%s -> ",nome_classept);
      aux = aux->next;
    }
    printf("NULL\n\n");
  }
}
