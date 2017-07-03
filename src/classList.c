#include <stdbool.h>
#include <wchar.h>
#include "classList.h"

static lista_classe* g_classList;

char *get_nome_classe(const lista_classe *classListAux, int stringIndex);

bool existe_proximo_elemento(const lista_classe *aux_lista_classe);

lista_classe* criar_lista_classe(){
	lista_classe* aux = (lista_classe*)malloc(sizeof(lista_classe));
	aux->classFile = NULL;
	aux->next = NULL;
	return aux;
}

void iniciar_lista_classe(){
	if (g_classList == NULL) g_classList = criar_lista_classe();
}

ClassFile* buscar_classe(char *name){ 
    iniciar_lista_classe();
	lista_classe* aux_lista_classe = g_classList;
	int stringIndex;
	char *className;
	while(existe_proximo_elemento(aux_lista_classe)){
		if(strcmp(get_nome_classe(aux_lista_classe, stringIndex), name) == 0){
			return aux_lista_classe->classFile;
		}
		aux_lista_classe = aux_lista_classe->next;
	}
	return NULL;
}

bool existe_proximo_elemento(const lista_classe *aux_lista_classe) { return aux_lista_classe->next != NULL; }

char *get_nome_classe(const lista_classe *classListAux, int stringIndex) {
	char *className;
	stringIndex = classListAux->classFile->constant_pool[classListAux->classFile->this_class].info.string_info->string_index;
	className = classListAux->classFile->constant_pool[stringIndex].info.utf8_info->bytes;
	return className;
}

void empilhar_classe(ClassFile *classFile){
    iniciar_lista_classe();
	lista_classe* aux_lista_classe = g_classList;
	while(existe_proximo_elemento(aux_lista_classe)){
		aux_lista_classe = aux_lista_classe->next;
	}
	aux_lista_classe->classFile = classFile;
	aux_lista_classe->next = criar_lista_classe();
}
