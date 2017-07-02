#include "classList.h"

static lista_classe* g_classList;


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
	lista_classe* classListAux = g_classList;
	int stringIndex;
	char *className;
	while(classListAux->next != NULL){
		stringIndex = classListAux->classFile->constant_pool[classListAux->classFile->this_class].info.string_info->string_index;
		className = classListAux->classFile->constant_pool[stringIndex].info.utf8_info->bytes;
		if(strcmp(className, name) == 0){
			return classListAux->classFile;
		}
		classListAux = classListAux->next;
	}
	return NULL;
}

void empilhar_classe(ClassFile *classFile){
    iniciar_lista_classe();
	lista_classe* aux_lista_classe = g_classList;
	while(aux_lista_classe->next != NULL){
		aux_lista_classe = aux_lista_classe->next;
	}
	aux_lista_classe->classFile = classFile;
	aux_lista_classe->next = criar_lista_classe();
}


void dumpClassList(){
    iniciar_lista_classe();
	lista_classe* classListAux = g_classList;
	int stringIndex;
	char *className;
	printf("Dump Class List : \n");
	for (int i = 0; classListAux->next != NULL; ++i){
		stringIndex = classListAux->classFile->constant_pool[classListAux->classFile->this_class].info.string_info->string_index;
		className = classListAux->classFile->constant_pool[stringIndex].info.utf8_info->bytes;
		printf("%d : %s\n", i, className);
		classListAux = classListAux->next;
	}
}