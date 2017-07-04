all: instrucoes_base decodificador carregador lista_classe ger_objeto exibidor switchView lookupSwitchView tableSwitchView frame_manager metodos array main


main: carregador.o exibidor.o decodificador.o metodos.o array.o instrucoes_base.o frame_manager.o lista_classe.o ger_objeto.o
	gcc main.c -o jvm exibidor.o carregador.o lista_classe.o metodos.o ger_objeto.o frame_manager.o decodificador.o array.o instrucoes_base.o switchView.o tableswitchView.o lookupswitchView.o -lm -std=c99 -w
exibidor:
	gcc exibidor.c -o exibidor.o -c -std=c99 -w
switchView:
	gcc switchView.c -o switchView.o -c -std=c99 -w
lookupSwitchView:
	gcc lookupswitchView.c -o lookupswitchView.o -c -std=c99 -w
tableSwitchView:
	gcc tableswitchView.c -o tableswitchView.o -c -std=c99 -w
carregador:
	gcc carregador.c -o carregador.o -c -std=c99 -w
decodificador:
	gcc decodificador.c -o decodificador.o -c -std=c99 -w
instrucoes_base:
	gcc instrucoes_base.c -o instrucoes_base.o -c -std=c99 -w
frame_manager:
	gcc frame_manager.c -o frame_manager.o -c -std=c99 -w
metodos:
	gcc metodos.c -o metodos.o -c -std=c99 -w
array:
	gcc array.c -o array.o -c -std=c99 -w
ger_objeto:
	gcc ger_objeto.c -o ger_objeto.o -c -std=c99 -w
lista_classe:
	gcc lista_classe.c -o lista_classe.o -c -std=c99 -w