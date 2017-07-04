#include <stdio.h>
#include "carregador.h"
#include "exibidor.h"
#include "decodificador.h"
#include "instrucoes_base.h"
#include "frame_manager.h"
#include "metodos.h"

void cruzeiro();

int menu (ClassFile* classFile);

int main(int argc, char **argv){
    char nomeArquivo[69];
    cruzeiro();
    //Argumento - se foi passado como parametro na execucao, utiliza-se do mesmo
    if(argc == 2) {
        strcpy(nomeArquivo, argv[1]);
    }

    //Se nome não for especificado
    else {
        printf("Digite o nome do arquivo:\n>> ");
        scanf("%s", nomeArquivo);
    }

    //Carrega o .class
    ClassFile* classFile = carregar_classe(nomeArquivo);
    menu(classFile);

    return 0;
}

void cruzeiro() {
    system("clear || cls");
    printf("\t   _____                    _              _____                                       \n");
    printf("\t  / ____|                  (_)            / ____|                                      \n");
    printf("\t | |     _ __ _   _ _______ _ _ __ ___   | |     __ _ _ __ ___  _ __   ___  __ _  ___  \n");
    printf("\t | |    | '__| | | |_  / _ \\ | '__/ _ \\  | |    / _` | '_ ` _ \\| '_ \\ / _ \\/ _` |/ _ \\ \n");
    printf("\t | |____| |  | |_| |/ /  __/ | | | (_) | | |___| (_| | | | | | | |_) |  __/ (_| | (_) |\n");
    printf("\t  \\_____|_|   \\__,_/___\\___|_|_|  \\___/   \\_____\\__,_|_| |_| |_| .__/ \\___|\\__,_|\\___/ \n");
    printf("\t                                                               | |                     \n");
    printf("\t                                                               |_|                     \n");
    printf("pressione uma tecla para continuar");
    getchar();

    system("clear || cls");
}

int menu (ClassFile* classFile){
    int opt = 0;
    printf("\t===============================================\n");
    printf("\t==================== MENU =====================\n");
    printf("\t===============================================\n");
    printf("\t======= 1) Mostrar conteúdo do .class =========\n");
    printf("\t======= 2) Executar interpretador     =========\n");
    printf("\t===============================================\n");
    printf("\t===============================================\n");
    printf("\t>>");
    scanf("%d",&opt);

    switch(opt){
        case(1):
            inicializar_decodificador();
            imprimir_classe(classFile);
            break;
        case(2):{
            DEBUG = 0;
            criar_array_instrucoes();
            Method_info* metodo_main = buscar_metodo_main(classFile);
            empilhar_metodo(classFile, metodo_main);
            executar_frame();
            break;
        }
    }

}
