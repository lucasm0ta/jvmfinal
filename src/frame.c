#include "frame.h"
#include "instructions.h"
#include "methodArea.h"
#include "classLoader.h"
#include "instructionMapper.h"


pilha_frame* criar_frame(Cp_info *cp, ClassFile *classe, Code_attribute *code) {
    pilha_frame* pf = NULL;
    pf = (pilha_frame*) calloc(1, sizeof(pilha_frame));

    pf->node = (frame*) calloc(1, sizeof(frame));
    return pf;
}


void empilhar_frame(Cp_info *cp, ClassFile *classe, Code_attribute *code, struct pilha_frame *pf) {
    pf->next = cabeca;
    cabeca = pf;

    frame* new_frame = cabeca->node;
    frame_atual = cabeca->node;

    new_frame->pc = 0;

    new_frame->classe = classe;
    new_frame->constantPool = cp;
    new_frame->max_stack = code->max_stack;
    new_frame->max_locals = code->max_locals;
    new_frame->code_length = code->code_length;
    new_frame->code = code->code;

    new_frame->fields = (uint32_t*) calloc(new_frame->max_locals, sizeof(uint32_t));

    new_frame->operandStack = (operandStack*) calloc(1, sizeof(operandStack));
    new_frame->operandStack->operands = (uint32_t*) calloc(new_frame->max_stack, sizeof(uint32_t));
    new_frame->operandStack->depth = 0;
}
/**
* Retira um frame do topo da pilha, libera seu espaço de memoria
*/
void desempilhar_frame() {

    if(cabeca->next != NULL) {
        if(flag == 1) {
            int32_t valor_retorno = desempilhar_operando();
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

    cabeca = cabeca->next;
}

void free_frame(struct pilha_frame* pf) {
    if(pf != NULL && pf->node != NULL) {
        if(pf->node->fields != NULL) {
            free(pf->node->fields);
        }
        if(pf->node->operandStack != NULL) {
            free(pf->node->operandStack->operands);
            free(pf->node->operandStack);
        }
            free(pf->node);
            free(pf);
    }
}

void empilhar_operando(int32_t value) {

    if(frame_atual->operandStack->depth >= frame_atual->max_stack) {
        printf("Erro, stack overflow\n");
    }

    frame_atual->operandStack->depth += 1;

    frame_atual->operandStack->operands[frame_atual->operandStack->depth - 1] = value;
}


int32_t desempilhar_operando() {
    frame_atual->operandStack->depth -= 1;
    if (frame_atual->operandStack->depth < 0){
        printf("Erro ao desempilhar: Stack Frame vazia");
    }

    return frame_atual->operandStack->operands[frame_atual->operandStack->depth];
}


void executar_frame() {
    while ((frame_atual->pc) < frame_atual->code_length){
        instrucao[frame_atual->code[frame_atual->pc]]();
    }
    desempilhar_frame();
}


void empilhar_metodo(ClassFile *classFile, Method_info *method) {
    pilha_frame* new_frame = criar_frame(classFile->constant_pool, classFile, recuperar_code_attribute(classFile, method));
    empilhar_frame(classFile->constant_pool, classFile, recuperar_code_attribute(classFile, method), new_frame);
}
