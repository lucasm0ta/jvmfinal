#include <stdio.h>
#include "classLoader.h"
#include "classViewer.h"
#include "instructionMapper.h"
#include "instructions.h"
#include "frame.h"
#include "methodArea.h"

int main(int argc, char **argv){
    char nomeArquivo[69];

    //Argumento - se foi passado como parametro na execucao, utiliza-se do mesmo
    if(argc == 2) {
        strcpy(nomeArquivo, argv[1]);
    }
    
    //Se nome não for especificado
    else {
        printf("Entre com o nome do arquivo:\n> ");
        scanf("%s", nomeArquivo);
    }
    
    //Carrega o .class    
    ClassFile* classFile = carregar_classe(nomeArquivo);
    int opcao;
    
    // Mostra o menu
    printf("Escolha uma opcao :\n");
    printf("1 - Exibir conteudo do .class\n");
    printf("2 - Executar interpretador\n");
    printf("3 - Executar interpretador com saidas para debug\n> ");
    scanf("%d", &opcao);
    switch(opcao){
        case(1):
            initMapper();
            imprimir_classe(classFile);
            break;
        case(2):{
            DEBUG = 0;
            createInstructionsArray();
            Method_info* mainInfo = findMainMethod(classFile);
            empilhar_metodo(classFile, mainInfo);
            executar_frame();
            break;
        }
        case(3):{
            DEBUG = 1;
            initMapper();
            createInstructionsArray();
            Method_info* mainInfo = findMainMethod(classFile);
            empilhar_metodo(classFile, mainInfo);
            executar_frame();
            break;
        }
    }
    
    return 0;
}
