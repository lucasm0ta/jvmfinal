all: instructions instructionMapper classLoader classList objectManager classViewer switchViewer lookupSwitchViewer tableSwitchViewer frame methodArea array main


main: classLoader.o classViewer.o instructionMapper.o methodArea.o array.o instructions.o frame.o classList.o objectManager.o
	gcc main.c -o jvm classViewer.o classLoader.o classList.o methodArea.o objectManager.o frame.o instructionMapper.o array.o instructions.o switchViewer.o tableswitchViewer.o lookupswitchViewer.o -lm -std=c99
classViewer:
	gcc classViewer.c -o classViewer.o -c -std=c99
switchViewer:
	gcc switchViewer.c -o switchViewer.o -c -std=c99
lookupSwitchViewer:
	gcc lookupswitchViewer.c -o lookupswitchViewer.o -c -std=c99
tableSwitchViewer:
	gcc tableswitchViewer.c -o tableswitchViewer.o -c -std=c99
classLoader:
	gcc classLoader.c -o classLoader.o -c -std=c99
instructionMapper:
	gcc instructionMapper.c -o instructionMapper.o -c -std=c99
instructions:
	gcc instructions.c -o instructions.o -c -std=c99
frame:
	gcc frame.c -o frame.o -c -std=c99
methodArea:
	gcc methodArea.c -o methodArea.o -c -std=c99
array:
	gcc array.c -o array.o -c -std=c99
objectManager:
	gcc objectManager.c -o objectManager.o -c -std=c99
classList:
	gcc classList.c -o classList.o -c -std=c99