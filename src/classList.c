#include "classList.h"

static ClassList* g_classList;

ClassList* createClassList(){
	ClassList* aux = (ClassList*)malloc(sizeof(ClassList));
	aux->classFile = NULL;
	aux->next = NULL;
	return aux;
}

void initClassList(){
	if (g_classList == NULL) g_classList = createClassList();
}

void pushClass(ClassFile *classFile){
	initClassList();
	ClassList* classListAux = g_classList;
	while(classListAux->next != NULL){
		classListAux = classListAux->next;
	}
	classListAux->classFile = classFile;
	classListAux->next = createClassList();
}

ClassFile* searchClass(char *name){
	initClassList();
	ClassList* classListAux = g_classList;
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

void dumpClassList(){
	initClassList();
	ClassList* classListAux = g_classList;	
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