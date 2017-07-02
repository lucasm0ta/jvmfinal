all: instructions instructionMapper classLoader classList objectManager classViewer switchViewer lookupSwitchViewer tableSwitchViewer frame methodArea array main


main: classLoader.o classViewer.o instructionMapper.o methodArea.o array.o instructions.o frame.o classList.o objectManager.o
	gcc main.c -o jvm classViewer.o classLoader.o classList.o methodArea.o objectManager.o frame.o instructionMapper.o array.o instructions.o switchViewer.o tableswitchViewer.o lookupswitchViewer.o -lm -std=c99 -w
classViewer:
	gcc classViewer.c -o classViewer.o -c -std=c99 -w
switchViewer:
	gcc switchViewer.c -o switchViewer.o -c -std=c99 -w
lookupSwitchViewer:
	gcc lookupswitchViewer.c -o lookupswitchViewer.o -c -std=c99 -w
tableSwitchViewer:
	gcc tableswitchViewer.c -o tableswitchViewer.o -c -std=c99 -w
classLoader:
	gcc classLoader.c -o classLoader.o -c -std=c99 -w
instructionMapper:
	gcc instructionMapper.c -o instructionMapper.o -c -std=c99 -w
instructions:
	gcc instructions.c -o instructions.o -c -std=c99 -w
frame:
	gcc frame.c -o frame.o -c -std=c99 -w
methodArea:
	gcc methodArea.c -o methodArea.o -c -std=c99 -w
array:
	gcc array.c -o array.o -c -std=c99 -w
objectManager:
	gcc objectManager.c -o objectManager.o -c -std=c99 -w
classList:
	gcc classList.c -o classList.o -c -std=c99 -w