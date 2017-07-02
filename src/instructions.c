#include "instructions.h"
#include "methodArea.h"
#include "frame.h"
#include "objectManager.h"
#include "tableswitchViewer.h"
#include "lookupswitchViewer.h"
#include "array.h"

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>

extern struct frame* frame_atual;

int16_t read2Bytes(uint8_t* data);
void handlePrintInt();
void handlePrintDouble();
void handlePrintChar();
void handlePrintFloat();
void handlePrintLong();
void handlePrintString();
void handlePrintBoolean();

/**
 * Cria o arrray de instruções para ser acessado
 */
void createInstructionsArray(){

	instruction[0] = nop;
	instruction[1] = aconst_null;
	instruction[2] = iconst_m1;
	instruction[3] = iconst_0;
	instruction[4] = iconst_1;
	instruction[5] = iconst_2;
	instruction[6] = iconst_3;
	instruction[7] = iconst_4;
	instruction[8] = iconst_5;
	instruction[9] = lconst_0;
	instruction[10] = lconst_1;
	instruction[11] = fconst_0;
	instruction[12] = fconst_1;
	instruction[13] = fconst_2;
	instruction[14] = dconst_0;
	instruction[15] = dconst_1;
	instruction[16] = bipush;
	instruction[17] = sipush;
	instruction[18] = ldc;
	instruction[19] = ldc_w;
	instruction[20] = ldc2_w;
	instruction[21] = iload;
	instruction[22] = lload;
	instruction[23] = fload;
	instruction[24] = dload;
	instruction[25] = aload;
	instruction[26] = iload_0;
	instruction[27] = iload_1;
	instruction[28] = iload_2;
	instruction[29] = iload_3;
	instruction[30] = lload_0;
	instruction[31] = lload_1;
	instruction[32] = lload_2;
	instruction[33] = lload_3;
	instruction[34] = fload_0;
	instruction[35] = fload_1;
	instruction[36] = fload_2;
	instruction[37] = fload_3;
	instruction[38] = dload_0;
	instruction[39] = dload_1;
	instruction[40] = dload_2;
	instruction[41] = dload_3;
	instruction[42] = aload_0;
	instruction[43] = aload_1;
	instruction[44] = aload_2;
	instruction[45] = aload_3;
	instruction[46] = iaload;
	instruction[47] = laload;
	instruction[48] = faload;
	instruction[49] = daload;
	instruction[50] = aaload;
	instruction[51] = baload;
	instruction[52] = caload;
	instruction[53] = saload;
	instruction[54] = istore;
	instruction[55] = lstore;
	instruction[56] = fstore;
	instruction[57] = dstore;
	instruction[58] = astore;
	instruction[59] = istore_0;
	instruction[60] = istore_1;
	instruction[61] = istore_2;
	instruction[62] = istore_3;
	instruction[63] = lstore_0;
	instruction[64] = lstore_1;
	instruction[65] = lstore_2;
	instruction[66] = lstore_3;
	instruction[67] = fstore_0;
	instruction[68] = fstore_1;
	instruction[69] = fstore_2;
	instruction[70] = fstore_3;
	instruction[71] = dstore_0;
	instruction[72] = dstore_1;
	instruction[73] = dstore_2;
	instruction[74] = dstore_3;
	instruction[75] = astore_0;
	instruction[76] = astore_1;
	instruction[77] = astore_2;
	instruction[78] = astore_3;
	instruction[79] = iastore;
	instruction[80] = lastore;
	instruction[81] = fastore;
	instruction[82] = dastore;
	instruction[83] = aastore;
	instruction[84] = bastore;
	instruction[85] = castore;
	instruction[86] = sastore;
	instruction[87] = pop;
	instruction[88] = pop2;
	instruction[89] = dup;
	instruction[90] = dup_x1;
	instruction[91] = dup_x2;
	instruction[92] = dup2;
	instruction[93] = dup2_x1;
	instruction[94] = dup2_x2;
	instruction[95] = swap;
	instruction[96] = iadd;
	instruction[97] = ladd;
	instruction[98] = fadd;
	instruction[99] = dadd;
	instruction[100] = isub;
	instruction[101] = lsub;
	instruction[102] = fsub;
	instruction[103] = dsub;
	instruction[104] = imul;
	instruction[105] = lmul;
	instruction[106] = fmul;
	instruction[107] = dmul;
	instruction[108] = idiv;
	instruction[109] = ins_ldiv;
	instruction[110] = fdiv;
	instruction[111] = ddiv;
	instruction[112] = irem;
	instruction[113] = lrem;
	instruction[114] = frem;
	instruction[115] = _drem;
	instruction[116] = ineg;
	instruction[117] = lneg;
	instruction[118] = fneg;
	instruction[119] = dneg;
	instruction[120] = ishl;
	instruction[121] = lshl;
	instruction[122] = ishr;
	instruction[123] = lshr;
	instruction[124] = iushr;
	instruction[125] = lushr;
	instruction[126] = iand;
	instruction[127] = land;
	instruction[128] = ior;
	instruction[129] = lor;
	instruction[130] = ixor;
	instruction[131] = lxor;
	instruction[132] = iinc;
	instruction[133] = i2l;
	instruction[134] = i2f;
	instruction[135] = i2d;
	instruction[136] = l2i;
	instruction[137] = l2f;
	instruction[138] = l2d;
	instruction[139] = f2i;
	instruction[140] = f2l;
	instruction[141] = f2d;
	instruction[142] = d2i;
	instruction[143] = d2l;
	instruction[144] = d2f;
	instruction[145] = i2b;
	instruction[146] = i2c;
	instruction[147] = i2s;
	instruction[148] = lcmp;
	instruction[149] = fcmpl;
	instruction[150] = fcmpg;
	instruction[151] = dcmpl;
	instruction[152] = dcmpg;
	instruction[153] = ifeq;
	instruction[154] = ifne;
	instruction[155] = iflt;
	instruction[156] = ifge;
	instruction[157] = ifgt;
	instruction[158] = ifle;
	instruction[159] = if_icmpeq;
	instruction[160] = if_icmpne;
	instruction[161] = if_icmplt;
	instruction[162] = if_icmpge;
	instruction[163] = if_icmpgt;
	instruction[164] = if_icmple;
	instruction[165] = if_acmpeq;
	instruction[166] = if_acmpne;
	instruction[167] = ins_goto;
	instruction[168] = jsr;
	instruction[169] = ret;
	instruction[170] = tableswitch;
	instruction[171] = lookupswitch;
	instruction[172] = ireturn;
	instruction[173] = lreturn;
	instruction[174] = freturn;
	instruction[175] = dreturn;
	instruction[176] = areturn;
	instruction[177] = void_return;
	instruction[178] = getstatic;
	instruction[179] = putstatic;
	instruction[180] = getfield;
	instruction[181] = putfield;
	instruction[182] = invokevirtual;
	instruction[183] = invokespecial;
	instruction[184] = invokestatic;
	instruction[185] = invokeinterface;

	instruction[187] = ins_new;
	instruction[188] = newarray;
	instruction[189] = anewarray;
	instruction[190] = arraylength;

	instruction[192] = checkcast;
	instruction[193] = instanceof;


	instruction[196] = wide;
	instruction[197] = multianewarray;
	instruction[198] = ifnull;
	instruction[199] = ifnonnull;
	instruction[200] = goto_w;
	instruction[201] = jsr_w;
}
/**
 * fazer nada
 */
void nop(){
	frame_atual->pc++;
}
/**
 * Coloca null na pilha de operandos
 */
void aconst_null(){

	empilhar_operando(0);
	frame_atual->pc++;
}
/**
 * Coloca -1 na pilha
 */
void iconst_m1(){

	empilhar_operando((int32_t) -1);
	frame_atual->pc++;
}
/**
 * Coloca -1 na pilha
 */
void iconst_0(){
	empilhar_operando((int32_t) 0);
	frame_atual->pc++;
}
/**
 * Coloca 1 na pilha
 */
void iconst_1(){

	empilhar_operando((int32_t) 1);
	frame_atual->pc++;
}
/**
 * Coloca 2 na pilha
 */
void iconst_2(){
	empilhar_operando((int32_t) 2);
	frame_atual->pc++;
}
/**
 * Coloca 3 na pilha
 */
void iconst_3(){

	empilhar_operando((int32_t) 3);
	frame_atual->pc++;
}
/**
 * Coloca 4 na pilha
 */
void iconst_4(){

	empilhar_operando((int32_t) 4);
	frame_atual->pc++;
}
/**
 * Coloca 5 na pilha
 */
void iconst_5(){

	empilhar_operando((int32_t) 5);
	frame_atual->pc++;
}
/**
 * Coloca uma constante 0 long na pilha
 */
void lconst_0(){
	empilhar_operando((int32_t) 0);
	empilhar_operando((int32_t) 0);
	frame_atual->pc++;
}
/**
 * Coloca uma constante 1 long na pilha
 */
void lconst_1(){

	empilhar_operando((int32_t) 0);
	empilhar_operando((int32_t) 1);
	frame_atual->pc++;
}
/**
 * Coloca uma constante 0 float na pilha
 */
void fconst_0(){
	float floatValue = 0.0;
	int intValue;
	memcpy(&intValue, &floatValue, sizeof(int32_t));
	empilhar_operando(intValue);
	frame_atual->pc++;
}
/**
 * Coloca uma constante 1 float na pilha
 */
void fconst_1(){
	float floatValue = 1.0;
	int intValue;
	memcpy(&intValue, &floatValue, sizeof(int32_t));
	empilhar_operando(intValue);
	empilhar_operando((int32_t) 1);
	frame_atual->pc++;
}
/**
 * Coloca uma constante 2 float na pilha
 */
void fconst_2(){
	float floatValue = 2.0;
	int intValue;
	memcpy(&intValue, &floatValue, sizeof(int32_t));
	empilhar_operando(intValue);
	frame_atual->pc++;
}
/**
 * Coloca uma constante 0 double na pilha
 */
void dconst_0(){

	empilhar_operando((int32_t) 0);
	empilhar_operando((int32_t) 0);
	frame_atual->pc++;
}
/**
 * Coloca uma constante 1 double na pilha
 */
void dconst_1(){
	double doubleValue = 1.0;
	int64_t intValue;
	memcpy(&intValue, &doubleValue, sizeof(int64_t));
	int32_t high = intValue >> 32;
	int32_t low = intValue & 0xffffffff;
	empilhar_operando(high);
	empilhar_operando(low);
	frame_atual->pc++;
}
/**
 * Coloca um byte na pilha, tirado da area de codigo
 */
void bipush(){

	//push a byte onto the stack as an integer value
    int8_t byte = frame_atual->code[frame_atual->pc+1];
	empilhar_operando((int32_t) byte);
	frame_atual->pc+= 2;
}
/**
 * Coloca um short na pilha, tirado da area de codigo
 */
void sipush(){

	//push a short onto the stack
	int32_t shortValue = read2Bytes((frame_atual->code + frame_atual->pc + 1));
	empilhar_operando((int32_t) shortValue);
	frame_atual->pc += 3;
}
/**
 * Coloca um item na pilha retirado do constant pool
 */
void ldc(){

	// push a constant #index from a constant pool (String, int or float) onto the stack
	int32_t index = frame_atual->code[frame_atual->pc+1];
	uint8_t type = frame_atual->constantPool[index].tag;
	if(type == 8){
		//String
		uint32_t string = frame_atual->constantPool[index].info.string_info->string_index;
		empilhar_operando(string);

	} else if(type == 3){
		//int
		uint32_t bytes = frame_atual->constantPool[index].info.integer_info->bytes;;
		empilhar_operando(bytes);

	} else if(type == 4){
		//float
		uint32_t bytes = frame_atual->constantPool[index].info.float_info->bytes;

		empilhar_operando(bytes);

	}
	frame_atual->pc += 2;
}
/**
 * Coloca um item na pilha retirado do constant pool indice de 16  bits
 */
void ldc_w(){

	//push a constant #index from a constant pool (String, int or float) onto the stack (wide index is constructed as indexbyte1 << 8 + indexbyte2)
	int32_t offset = calculateOffset();
	uint8_t type = frame_atual->constantPool[offset].tag;
	if(type == 8){
		//String
		uint32_t string = frame_atual->constantPool[offset].info.string_info->string_index;
		empilhar_operando(string);

	} else if(type == 3){
		//int
		uint32_t bytes = frame_atual->constantPool[offset].info.integer_info->bytes;;
		empilhar_operando(bytes);

	} else if(type == 4){
		//float
		uint32_t bytes = frame_atual->constantPool[offset].info.float_info->bytes;
		empilhar_operando(bytes);

	}
	frame_atual->pc += 3;
}
/**
 * Coloca um item long ou double na pilha retirado do constant pool indice 16 bits
 */
void ldc2_w(){

	int32_t offset = calculateOffset();
	uint8_t type = frame_atual->constantPool[offset].tag;
	if(type == 5){
		//Long
		uint32_t high = frame_atual->constantPool[offset].info.long_info->high_bytes;
		uint32_t low = frame_atual->constantPool[offset].info.long_info->low_bytes;
		empilhar_operando(high);
		empilhar_operando(low);

	} else if(type == 6){
		//Double
		uint32_t high = frame_atual->constantPool[offset].info.double_info->high_bytes;
		uint32_t low = frame_atual->constantPool[offset].info.double_info->low_bytes;
		empilhar_operando(high);
		empilhar_operando(low);
	}

	frame_atual->pc += 3;
}
/**
 * Carrega um int na pilha a partir de um indice para as variaveis locais
 */
void iload(){

	int32_t index = frame_atual->code[frame_atual->pc+1];
	int32_t value = frame_atual->fields[index];
	empilhar_operando(value);
	frame_atual->pc += 2;
}
/**
 * load a long value from a local variable #index
 */
void lload(){

	//load a long value from a local variable #index
	int32_t index = frame_atual->code[frame_atual->pc+1];
	int32_t value1 = frame_atual->fields[index];
	int32_t value2 = frame_atual->fields[index+1];

	empilhar_operando(value1);
	empilhar_operando(value2);
	frame_atual->pc += 2;
}
/**
 * load a float value from a local variable #index
 */
void fload(){

	int32_t index = frame_atual->code[frame_atual->pc+1];
	int32_t value = frame_atual->fields[index];
	empilhar_operando(value);
	frame_atual->pc += 2;
}
/**
 * load a double value from a local variable #index
 */
void dload(){

	int32_t index = frame_atual->code[frame_atual->pc+1];
	int32_t value1 = frame_atual->fields[index];
	int32_t value2 = frame_atual->fields[index+1];
	empilhar_operando(value1);
	empilhar_operando(value2);
	frame_atual->pc += 2;
}
/**
 * Retira um indice do area de codigo do frame e com esse indice acha
 * uma variavel local na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void aload(){
	//pega o indice
	int32_t index = frame_atual->code[frame_atual->pc+1];
	// usa o indice para achar a variavel local
	int32_t value = frame_atual->fields[index];

	//coloca na pilha
	empilhar_operando(value);
	frame_atual->pc += 2;
}
/**
 * Com o indice 0 acha
 * uma variavel local inteira na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void iload_0(){
	int32_t value = frame_atual->fields[0];
	empilhar_operando(value);
	frame_atual->pc++;
}
/**
 * Com o indice 1 acha
 * uma variavel local inteira na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void iload_1(){
	int32_t value = frame_atual->fields[1];
	empilhar_operando(value);
	frame_atual->pc++;
}
/**
 * Com o indice 2 acha
 * uma variavel local inteira na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void iload_2(){
	int32_t value = frame_atual->fields[2];
	empilhar_operando(value);
	frame_atual->pc++;
}
/**
 * Com o indice 3 acha
 * uma variavel local inteira na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void iload_3(){

	int32_t value = frame_atual->fields[3];
	empilhar_operando(value);
	frame_atual->pc++;
}
/**
 * Com o indice 0 acha
 * uma variavel local long na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void lload_0(){

    int32_t high = frame_atual->fields[0 + 0];//sendo primeiro zero o indice e o segundo a posição
	empilhar_operando(high);
    int32_t low = frame_atual->fields[0 + 1];//sendo zero o indice e o um a posição
	empilhar_operando(low);

    frame_atual->pc++;
}
/**
 * Com o indice 1 acha
 * uma variavel local long na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void lload_1(){

	int32_t high = frame_atual->fields[1 + 0];//sendo 1 o indice e o zero a posição
	empilhar_operando(high);
    int32_t low = frame_atual->fields[1 + 1];//sendo o primeiro 1 o indice e o segundo a posição
	empilhar_operando(low);
	frame_atual->pc++;
}
/**
 * Com o indice 2 acha
 * uma variavel local long na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void lload_2(){

	int32_t high = frame_atual->fields[2 + 0];//sendo dois o indice e o zero a posição
	empilhar_operando(high);
    int32_t low = frame_atual->fields[2 + 1];//sendo dois o indice e o um a posição
	empilhar_operando(low);

	frame_atual->pc++;
}
/**
 * Com o indice 3 acha
 * uma variavel local long na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void lload_3(){

	int32_t high = frame_atual->fields[3 + 0];//sendo tres o indice e o zero a posição
	empilhar_operando(high);
    int32_t low = frame_atual->fields[3 + 1];//sendo tres o indice e o um a posição
	empilhar_operando(low);
	frame_atual->pc++;
}
/**
 * Com o indice 0 acha
 * uma variavel local float na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void fload_0(){

	int32_t value = frame_atual->fields[0];
	empilhar_operando(value);
	frame_atual->pc++;
}
/**
 * Com o indice 1 acha
 * uma variavel local float na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void fload_1(){

	int32_t value = frame_atual->fields[1];
	empilhar_operando(value);
	frame_atual->pc++;
}
/**
 * Com o indice 2 acha
 * uma variavel local float na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void fload_2(){

	int32_t value = frame_atual->fields[2];
	empilhar_operando(value);
	frame_atual->pc++;
}
/**
 * Com o indice 3 acha
 * uma variavel local float na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void fload_3(){

	int32_t value = frame_atual->fields[3];
	empilhar_operando(value);
	frame_atual->pc++;
}
/**
 * Com o indice 0 acha
 * uma variavel local double na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void dload_0(){

	int32_t high = frame_atual->fields[0 + 0];//sendo primeiro zero o indice e o segundo a posição
	empilhar_operando(high);
    int32_t low = frame_atual->fields[0 + 1];//sendo zero o indice e o um a posição
	empilhar_operando(low);
	frame_atual->pc++;
}
/**
 * Com o indice 1 acha
 * uma variavel local double na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void dload_1(){

	int32_t high = frame_atual->fields[1 + 0];//sendo 1 o indice e o zero a posição
	empilhar_operando(high);
    int32_t low = frame_atual->fields[1 + 1];//sendo o primeiro 1 o indice e o segundo a posição
	empilhar_operando(low);
	frame_atual->pc++;
}
/**
 * Com o indice 2 acha
 * uma variavel local double na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void dload_2(){

	int32_t high = frame_atual->fields[2 + 0];//sendo dois o indice e o zero a posição
	empilhar_operando(high);
    int32_t low = frame_atual->fields[2 + 1];//sendo dois o indice e o um a posição
	empilhar_operando(low);

	frame_atual->pc++;
}
/**
 * Com o indice 3 acha
 * uma variavel local double na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void dload_3(){

	int32_t high = frame_atual->fields[3 + 0];//sendo tres o indice e o zero a posição
	empilhar_operando(high);
    int32_t low = frame_atual->fields[3 + 1];//sendo tres o indice e o um a posição
	empilhar_operando(low);
	frame_atual->pc++;
}
/**
 * Utilizando o indice 0 acha
 * uma variavel local na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void aload_0(){
	// usa o indice para achar a variavel local
	int32_t value = frame_atual->fields[0];

	//coloca na pilha
	empilhar_operando(value);
	frame_atual->pc++;
}
/**
 * Utilizando o indice 1 acha
 * uma variavel local na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void aload_1(){
	// usa o indice para achar a variavel local
	int32_t value = frame_atual->fields[1];

	//coloca na pilha
	empilhar_operando(value);
	frame_atual->pc++;
}

/**
 * Utilizando o indice 2 acha
 * uma variavel local na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void aload_2(){
	// usa o indice para achar a variavel local
	int32_t value = frame_atual->fields[2];

	//coloca na pilha
	empilhar_operando(value);
	frame_atual->pc++;
}
/**
 * Utilizando o indice 3 acha
 * uma variavel local na area de fields, coloca o valor dessa variavel
 * na pilha de operandos
 */
void aload_3(){
	// usa o indice para achar a variavel local
	int32_t value = frame_atual->fields[3];

	//coloca na pilha
	empilhar_operando(value);
	frame_atual->pc++;
}

/**
 * Load int from array e coloca na pilha
 */
void iaload(){
	//Load int from array
	//Pega o indice
	uint32_t index = desempilhar_operando();
	//Pega a estrutura com o array
	arrayType *arrayStruct = (arrayType*) desempilhar_operando();
	//Acha a referencia para o array propriamente dito
	int32_t* arrayRef = (int32_t*) get_referencia_array(arrayStruct);
	//Coloca na pilha h l
	empilhar_operando(arrayRef[index]);

	//atualiza o pc, sem argumentos

	frame_atual->pc++;


}
/**
 * Load long from array e coloca na pilha
 */
void laload(){
	//Load long from array
	//Pega o indice
	uint32_t index = desempilhar_operando();
	//Pega a estrutura com o array
	arrayType *arrayStruct = (arrayType*) desempilhar_operando();
	//Acha a referencia para o array propriamente dito
	uint64_t* arrayRef = (uint64_t*) get_referencia_array(arrayStruct);

	//Divide os 64 bits em duas de 32
	uint32_t highBits = (uint32_t)(arrayRef[index] >> 32);
	uint32_t lowBits = (uint32_t)(arrayRef[index]);

	//Coloca na pilha os 32 bits mais significativos
	empilhar_operando(highBits);
	//Coloca na pilha os 32 bits menos significativos
	empilhar_operando(lowBits);

	//atualiza o pc, sem argumentos

	frame_atual->pc++;
}
/**
 * Load float from array e coloca na pilha
 */
void faload(){
	//Load float from array
	//Pega o indice
	uint32_t index = desempilhar_operando();
	//Pega a estrutura com o array
	arrayType *arrayStruct = (arrayType*) desempilhar_operando();
	//Acha a referencia para o array propriamente dito
	uint32_t* arrayRef = (uint32_t*) get_referencia_array(arrayStruct);
	//Coloca na pilha o float
	empilhar_operando(arrayRef[index]);

	//atualiza o pc, sem argumentos

	frame_atual->pc++;
}
/**
 * Load double from array e coloca na pilha
 */
void daload(){
	//Load double from array
	//Pega o indice
	uint32_t index = desempilhar_operando();
	//Pega a estrutura com o array
	arrayType *arrayStruct = (arrayType*) desempilhar_operando();
	//Acha a referencia para o array propriamente dito da estrutura
	uint64_t* arrayRef = (uint64_t*) get_referencia_array(arrayStruct);

	//Divide os 64 bits do double em duas de 32
	uint32_t highBits = (uint32_t)(arrayRef[index] >> 32);
	uint32_t lowBits = (uint32_t)(arrayRef[index]);

	//Coloca na pilha os 32 bits mais significativos
	empilhar_operando(highBits);
	//Coloca na pilha os 32 bits menos significativos
	empilhar_operando(lowBits);

	//atualiza o pc, sem argumentos

	frame_atual->pc++;
}

/**
 * Tira um index e um array da pilha de operandos e coloca na mesma
 * o valor que se encontra na posicao arrayRef[indice]
 */
void aaload(){
	//tira um index e um array da pilha e coloca na mesma o valor da pposicao
	//Pega o indice da pilha
	uint32_t indice = desempilhar_operando();
	//Pegao array
	arrayType * arrayStruct = (arrayType*) desempilhar_operando();

	//Pega a referencia de dentro da estrutura de array (pois a estrutura soh contem tbm o tamanho)
	uint32_t* arrayRef = (uint32_t*) get_referencia_array(arrayStruct);

	//Coloca na pilha
	empilhar_operando(arrayRef[indice]);
	frame_atual->pc++;
}
/**
 * Tira um index e um array da pilha de operandos e coloca na mesma
 * o byte que se encontra na posicao arrayRef[indice]
 */
void baload(){
	//Load byte from array
	//Pega o indice
	uint32_t index = desempilhar_operando();
	//Pega a estrutura com o array
	arrayType *arrayStruct = (arrayType*) desempilhar_operando();
	//Acha a referencia para o array propriamente dito
	uint8_t* arrayRef = (uint8_t*) get_referencia_array(arrayStruct);
	//Coloca na pilha o byte
	empilhar_operando(arrayRef[index]);

	//atualiza o pc, sem argumentos

	frame_atual->pc++;

}
/**
 * Tira um index e um array da pilha de operandos e coloca na mesma
 * o char que se encontra na posicao arrayRef[indice]
 */
void caload(){
	//Load char from array
	//Pega o indice
	uint32_t index = desempilhar_operando();
	//Pega a estrutura com o array
	arrayType *arrayStruct = (arrayType*) desempilhar_operando();
	//Acha a referencia para o array propriamente dito
	uint16_t* arrayRef = (uint16_t*) get_referencia_array(arrayStruct);
	//Coloca na pilha o char
	empilhar_operando(arrayRef[index]);

	//atualiza o pc, sem argumentos

	frame_atual->pc++;
}
/**
 * Tira um index e um array da pilha de operandos e coloca na mesma
 * o short que se encontra na posicao arrayRef[indice]
 */
void saload(){
	//Load short from array
	//Pega o indice
	uint32_t index = desempilhar_operando();
	//Pega a estrutura com o array
	arrayType *arrayStruct = (arrayType*) desempilhar_operando();
	//Acha a referencia para o array propriamente dito
	uint16_t* arrayRef = (uint16_t*) get_referencia_array(arrayStruct);
	//Coloca na pilha o short
	empilhar_operando(arrayRef[index]);

	//atualiza o pc, sem argumentos

	frame_atual->pc++;
}

/**
 * store int value into variable #index
 */
void istore(){

	//store int value into variable #index
	int32_t value = desempilhar_operando();
	int32_t index = frame_atual->code[frame_atual->pc+1];
	frame_atual->fields[index] = value;
	frame_atual->pc += 2;
}
/**
 * store a long value in a local variable #index
 */
void lstore(){

	//store a long value in a local variable #index
	int32_t low = desempilhar_operando();
	int32_t high = desempilhar_operando();
	int32_t index = frame_atual->code[frame_atual->pc+1];
	int64_t value = high;
	value <<= 32;
	value += low;
	frame_atual->fields[index] = high;
	frame_atual->fields[index+1] = low;
	frame_atual->pc += 2;
}
/**
 * store a float value into a local variable #index
 */
void fstore(){

	//store a float value into a local variable #index
	int32_t value = desempilhar_operando();
	float floatValue;
	memcpy(&floatValue, &value, sizeof(int32_t));
	int32_t index = frame_atual->code[frame_atual->pc+1];
	frame_atual->fields[index] = value;
	frame_atual->pc += 2;
}
/**
 * store a double value into a local variable #index
 */
void dstore(){

	//store a double value into a local variable #index
	int32_t low = desempilhar_operando();
	int32_t high = desempilhar_operando();
	int32_t index = frame_atual->code[frame_atual->pc+1];

	frame_atual->fields[index] = high;
	frame_atual->fields[index+1] = low;

	frame_atual->pc += 2;
}
/**
 * Coloca um valor tirado da pilha em uma posicao do array
 * de fields definida pelo operando tirado da area de codigo
 */
void astore(){
	//pega da pilha o cabeca
	int32_t value = desempilhar_operando();
	// acha o indice para colocar no array
	int32_t index = frame_atual->code[frame_atual->pc+1];

	// usa o indice para achar a posicao que quer do array de variaveis
	frame_atual->fields[index] = value;
	frame_atual->pc += 2;
}
/**
 * store int value into variable indice 0
 */
void istore_0(){

	int32_t value = desempilhar_operando();
	frame_atual->fields[0] = value;
	frame_atual->pc++;
}
/**
 * store int value into variable indice 1
 */
void istore_1(){
	int32_t value = desempilhar_operando();
	frame_atual->fields[1] = value;
	frame_atual->pc++;
}
/**
 * store int value into variable indice 2
 */
void istore_2(){

	int32_t value = desempilhar_operando();
	frame_atual->fields[2] = value;
	frame_atual->pc++;
}
/**
 * store int value into variable indice 3
 */
void istore_3(){

	int32_t value = desempilhar_operando();
	frame_atual->fields[3] = value;
	frame_atual->pc++;
}
/**
 * store a long value in a local variable indice 0
 */
void lstore_0(){

	int32_t low = desempilhar_operando();
	frame_atual->fields[0] = low;
	int32_t high = desempilhar_operando();
	frame_atual->fields[1] = high;
	frame_atual->pc++;
}
/**
 * store a long value in a local variable indice 1
 */
void lstore_1(){

	int32_t low = desempilhar_operando();
	frame_atual->fields[2] = low;
	int32_t high = desempilhar_operando();
	frame_atual->fields[1] = high;
	frame_atual->pc++;
}
/**
 * store a long value in a local variable indice 2
 */
void lstore_2(){


	int32_t low = desempilhar_operando();
	frame_atual->fields[3] = low;
	int32_t high = desempilhar_operando();
	frame_atual->fields[2] = high;
	int64_t value = high;
	value <<= 32;
	value += low;
	frame_atual->pc++;
}
/**
 * store a long value in a local variable indice 3
 */
void lstore_3(){


	int32_t low = desempilhar_operando();

	frame_atual->fields[4] = low;
	int32_t high = desempilhar_operando();
	frame_atual->fields[3] = high;
	frame_atual->pc++;
}
/**
 * store a long value in a local variable indice 0
 */
void fstore_0(){

	int32_t value = desempilhar_operando();
	frame_atual->fields[0] = value;
	frame_atual->pc++;
}
/**
 * store a long value in a local variable indice 1
 */
void fstore_1(){
	int32_t value = desempilhar_operando();
	frame_atual->fields[1] = value;
	frame_atual->pc++;
}
/**
 * store a long value in a local variable indice 2
 */
void fstore_2(){

	int32_t value = desempilhar_operando();
	frame_atual->fields[2] = value;
	frame_atual->pc++;

}
/**
 * store a long value in a local variable indice 3
 */
void fstore_3(){

	int32_t value = desempilhar_operando();
	frame_atual->fields[3] = value;
	frame_atual->pc++;
}
/**
 * store a double value in a local variable indice 0
 */
void dstore_0(){

	int32_t low = desempilhar_operando();
	frame_atual->fields[1] = low;
	int32_t high = desempilhar_operando();
	frame_atual->fields[0] = high;
	frame_atual->pc++;
}
/**
 * store a double value in a local variable indice 1
 */
void dstore_1(){

	int32_t low = desempilhar_operando();
	frame_atual->fields[2] = low;
	int32_t high = desempilhar_operando();
	frame_atual->fields[1] = high;
	frame_atual->pc++;
}
/**
 * store a double value in a local variable indice 2
 */
void dstore_2(){

	int32_t low = desempilhar_operando();
	frame_atual->fields[3] = low;
	int32_t high = desempilhar_operando();
	frame_atual->fields[2] = high;
	frame_atual->pc++;
}
/**
 * store a double value in a local variable indice 3
 */
void dstore_3(){

	int32_t low = desempilhar_operando();
	frame_atual->fields[4] = low;
	int32_t high = desempilhar_operando();
	frame_atual->fields[3] = high;
	frame_atual->pc++;
}
/**
 * store a value in a local variable indice 0
 */
void astore_0(){
	// tira o valor da pilha
	int32_t value = desempilhar_operando();
	//acessa a variavel local e coloca no indice certo o value que estava na pilha
	frame_atual->fields[0] = value;
	frame_atual->pc++;

}
/**
 * store a value in a local variable indice 1
 */
void astore_1(){
	// tira o valor da pilha
	int32_t value = desempilhar_operando();
	//acessa a variavel local e coloca no indice certo o value que estava na pilha
	frame_atual->fields[1] = value;
	frame_atual->pc++;


}
/**
 * store a value in a local variable indice 2
 */
void astore_2(){
	// tira o valor da pilha
	int32_t value = desempilhar_operando();
	//acessa a variavel local e coloca no indice certo o value que estava na pilha
	frame_atual->fields[2] = value;
	frame_atual->pc++;
}
/**
 * store a value in a local variable indice 3
 */
void astore_3(){
	// tira o valor da pilha
	int32_t value = desempilhar_operando();
	//acessa a variavel local e coloca no indice certo o value que estava na pilha
	frame_atual->fields[3] = value;
	frame_atual->pc++;

}
/**
 * tira um inteiro um index e um array da pilha e coloca o valor na posicao definida pelo index
 */
void iastore(){
	//tira um inteiro um index e um array da pilha e coloca o valor na posicao definida pelo index
	//tira o inteiro
	int32_t value = desempilhar_operando();
	//Pega o indice da pilha
	uint32_t index = desempilhar_operando();
	//Pega array
	arrayType * arrayStruct = (arrayType*) desempilhar_operando();

	//Pega a referencia de dentro da estrutura de array (pois a estrutura soh contem tbm o tamanho)
	uint32_t* arrayRef = (uint32_t*) get_referencia_array(arrayStruct);

	//Coloca no vetor
	arrayRef[index] = value;
	frame_atual->pc++;
}
/**
 * tira um long um index e um array da pilha e coloca o valor na posicao definida pelo index
 */
void lastore(){

	//tira um long um index e um array da pilha e coloca o valor na posicao definida pelo index
	//tira o inteiro
	uint32_t lowBits = desempilhar_operando();
	uint32_t highBits = desempilhar_operando();

	uint64_t value = ((uint64_t)highBits << 32) | lowBits;

	//Pega o indice da pilha
	uint32_t index = desempilhar_operando();
	//Pega array
	arrayType * arrayStruct = (arrayType*) desempilhar_operando();

	//Pega a referencia de dentro da estrutura de array (pois a estrutura soh contem tbm o tamanho)
	uint64_t* arrayRef = (uint64_t*) get_referencia_array(arrayStruct);

	//Coloca no vetor
	arrayRef[index] = value;
	frame_atual->pc++;
}
/**
 * tira um float um index e um array da pilha e coloca o valor na posicao definida pelo index
 */
void fastore(){

	//tira um float um index e um array da pilha e coloca o valor na posicao definida pelo index
	//tira o float
	uint32_t value = desempilhar_operando();
	//Pega o indice da pilha
	uint32_t index = desempilhar_operando();
	//Pega array
	arrayType * arrayStruct = (arrayType*) desempilhar_operando();

	//Pega a referencia de dentro da estrutura de array (pois a estrutura soh contem tbm o tamanho)
	uint32_t* arrayRef = (uint32_t*) get_referencia_array(arrayStruct);

	//Coloca no vetor
	arrayRef[index] = value;
	frame_atual->pc++;
}
/**
 * tira um double um index e um array da pilha e coloca o valor na posicao definida pelo index
 */
void dastore(){
	//tira um double um index e um array da pilha e coloca o valor na posicao definida pelo index
	//tira o inteiro
	uint32_t lowBits = desempilhar_operando();
	uint32_t highBits = desempilhar_operando();

	uint64_t value = ((uint64_t)highBits << 32) | lowBits;

	//Pega o indice da pilha
	uint32_t index = desempilhar_operando();
	//Pega array
	arrayType * arrayStruct = (arrayType*) desempilhar_operando();

	//Pega a referencia de dentro da estrutura de array (pois a estrutura soh contem tbm o tamanho)
	uint64_t* arrayRef = (uint64_t*) get_referencia_array(arrayStruct);

	//Coloca no vetor
	arrayRef[index] = value;
	frame_atual->pc++;
}
/**
 * tira um objeto um index e um array da pilha e coloca o valor na posicao definida pelo index
 */
void aastore(){
	//tira um valor um index e um array da pilha e coloca o valor na posicao definida pelo index
	//tira o valor
	uint32_t value = desempilhar_operando();
	//Pega o indice da pilha
	uint32_t indice = desempilhar_operando();
	//Pega array
	arrayType * arrayStruct = (arrayType*) desempilhar_operando();

	//Pega a referencia de dentro da estrutura de array (pois a estrutura soh contem tbm o tamanho)
	uint32_t* arrayRef = (uint32_t*) get_referencia_array(arrayStruct);

	//Coloca no vetor
	arrayRef[indice] = value;
	frame_atual->pc++;

}
/**
 * tira um byte um index e um array da pilha e coloca o valor na posicao definida pelo index
 */
void bastore(){

	//tira um byte um index e um array da pilha e coloca o valor na posicao definida pelo index
	//tira o byte
	uint32_t value = desempilhar_operando();
	//Pega o indice da pilha
	uint32_t index = desempilhar_operando();
	//Pega array
	arrayType * arrayStruct = (arrayType*) desempilhar_operando();

	//Pega a referencia de dentro da estrutura de array (pois a estrutura soh contem tbm o tamanho)
	uint8_t* arrayRef = (uint8_t*) get_referencia_array(arrayStruct);

	//Coloca no vetor
	arrayRef[index] = value;
	frame_atual->pc++;

}
/**
 * tira um char um index e um array da pilha e coloca o valor na posicao definida pelo index
 */
void castore(){

	//tira um float um index e um array da pilha e coloca o valor na posicao definida pelo index
	//tira o float
	uint32_t value = desempilhar_operando();
	//Pega o indice da pilha
	uint32_t index = desempilhar_operando();
	//Pega array
	arrayType * arrayStruct = (arrayType*) desempilhar_operando();

	//Pega a referencia de dentro da estrutura de array (pois a estrutura soh contem tbm o tamanho)
	uint16_t* arrayRef = (uint16_t*) get_referencia_array(arrayStruct);

	//Coloca no vetor
	arrayRef[index] = value;
	frame_atual->pc++;
}
/**
 * tira um short um index e um array da pilha e coloca o valor na posicao definida pelo index
 */
void sastore(){

	//tira um short um index e um array da pilha e coloca o valor na posicao definida pelo index
	//tira o short
	uint32_t value = desempilhar_operando();
	//Pega o indice da pilha
	uint32_t index = desempilhar_operando();
	//Pega array
	arrayType * arrayStruct = (arrayType*) desempilhar_operando();

	//Pega a referencia de dentro da estrutura de array (pois a estrutura soh contem tbm o tamanho)
	uint16_t* arrayRef = (uint16_t*) get_referencia_array(arrayStruct);

	//Coloca no vetor
	arrayRef[index] = value;
	frame_atual->pc++;
}
/**
 * pop operand da pilha
 */
void pop(){

	desempilhar_operando();
	frame_atual->pc++;
}
/**
 * Pop 2 operandos da pilha
 */
void pop2(){

	desempilhar_operando();
	desempilhar_operando();
	frame_atual->pc++;
}
/**
 * Daz um pop e com esse valor faz dois pushs
 */
void dup(){

	int32_t value = desempilhar_operando();
	empilhar_operando(value);
	empilhar_operando(value);
	frame_atual->pc++;
}
/**
 * Duplica o topo da pilha de operandos e insere dois valores
 */
void dup_x1(){

	//TODO
	//FUNÇÃO QUE ATUALIZA PC QUANDO TEM ARGUMENTO
}
/**
 * Duplica o topo da pilha de operandos e insere dois ou tres valores
 */
void dup_x2(){

	//TODO
	//FUNÇÃO QUE ATUALIZA PC QUANDO TEM ARGUMENTO
}
/**
 * Duplica o topo de um ou dois elementos da pilha de operandos
 */
void dup2(){

	int32_t top = desempilhar_operando();
	int32_t sub_top = desempilhar_operando();
	empilhar_operando(sub_top);
	empilhar_operando(top);
	empilhar_operando(sub_top);
	empilhar_operando(top);
	frame_atual->pc++;
}
/**
 * Duplica o topo de um ou dois elementos da pilha de operandos
 * e insere um ou dois valores
 */
void dup2_x1(){

	//TODO
	//FUNÇÃO QUE ATUALIZA PC QUANDO TEM ARGUMENTO
}
/**
 * Duplica o topo de um ou dois elementos da pilha de operandos
 * e insere um ou dois ou três ou quatro valores
 */
void dup2_x2(){

	//TODO
	//FUNÇÃO QUE ATUALIZA PC QUANDO TEM ARGUMENTO
}
/**
 * Troca a ordem dos dois valores no topo da pilha de operandos
 */
void swap(){

	int32_t value1 = desempilhar_operando();
	int32_t value2 = desempilhar_operando();
	empilhar_operando(value1);
	empilhar_operando(value2);
	frame_atual->pc++;
}
/**
 * Soma os dois valores inteiros do topo da pilha e coloca na pilha o resultado
 */
void iadd(){

	int32_t operator1 = desempilhar_operando();
	int32_t operator2 = desempilhar_operando();
	int32_t result = operator1+operator2;
	empilhar_operando(result);
	frame_atual->pc++;
}
/**
 * Soma os dois valores long do topo da pilha e coloca na pilha o resultado
 */
void ladd(){

	//construindo o primeiro operador
	int32_t operator1Low = desempilhar_operando();
	int32_t operator1High = desempilhar_operando();
	int64_t op1;
	op1 = operator1High;
	op1 <<= 32;
	op1 = op1 + operator1Low;

	//construindo o segundo operador
	int32_t operator2Low = desempilhar_operando();
	int32_t operator2High = desempilhar_operando();
	int64_t op2;
	op2 = operator2High;
	op2 <<= 32;
	op2 = op2 + operator2Low;

	//realizando a operação
	int64_t result = op1+op2;

	//coloca os 64 bits em variáveis de 32 bits
	int32_t resultHigh = result >> 32;
	int32_t resultLow = result & 0xffffffff;

	//empilha resultado
	empilhar_operando(resultHigh);
	empilhar_operando(resultLow);

	//atualiza pc
	frame_atual->pc++;

}
/**
 * Soma os dois valores float do topo da pilha e coloca na pilha o resultado
 */
void fadd(){

	int32_t int2 = desempilhar_operando();
	int32_t int1 = desempilhar_operando();
	float floatValue1;
	float floatValue2;
	memcpy(&floatValue1, &int1, sizeof(int32_t));
	memcpy(&floatValue2, &int2, sizeof(int32_t));
	float result = floatValue1 + floatValue2;
	int resultInt;
	memcpy(&resultInt, &result, sizeof(int32_t));
	empilhar_operando(resultInt);
	frame_atual->pc++;
}
/**
 * Soma os dois valores double do topo da pilha e coloca na pilha o resultado
 */
void dadd(){

	//construindo o primeiro operador
	int32_t operator1Low = desempilhar_operando();
	int32_t operator1High = desempilhar_operando();
	int64_t op1;
	op1 = operator1High;
	op1 <<= 32;
	op1 = op1 + operator1Low;

	//construindo o segundo operador
	int32_t operator2Low = desempilhar_operando();
	int32_t operator2High = desempilhar_operando();
	int64_t op2;
	op2 = operator2High;
	op2 <<= 32;
	op2 = op2 + operator2Low;

	//escrevendo em double
	double operator1;
	memcpy(&operator1, &op1, sizeof(int64_t));

	//escrevendo em double
	double operator2;
	memcpy(&operator2, &op2, sizeof(int64_t));

	//realizando a operação

	double resultDouble = operator1+operator2;

	//escrevendo em double
	int64_t result;
	memcpy(&result, &resultDouble, sizeof(int64_t));

	//coloca os 64 bits em variáveis de 32 bits
	int32_t resultHigh = result >> 32;
	int32_t resultLow = result & 0xffffffff;

	//empilha resultado
	empilhar_operando(resultHigh);
	empilhar_operando(resultLow);

	//atualiza pc
	frame_atual->pc++;
}
/**
 * Subtrai os dois valores inteiros do topo da pilha e coloca na pilha o resultado
 */
void isub(){

	int32_t operator2 = desempilhar_operando();
	int32_t operator1 = desempilhar_operando();
	int32_t result = operator1-operator2;
	empilhar_operando(result);
	frame_atual->pc++;
}
/**
 * Subtrai os dois valores long do topo da pilha e coloca na pilha o resultado
 */
void lsub(){

	//construindo o primeiro operador
	int32_t operator1Low = desempilhar_operando();
	int32_t operator1High = desempilhar_operando();

	int64_t op1;
	op1 = operator1High;
	op1 <<= 32;
	op1 = op1 + operator1Low;
	//construindo o segundo operador
	int32_t operator2Low = desempilhar_operando();
	int32_t operator2High = desempilhar_operando();

	int64_t op2;
	op2 = operator2High;
	op2 <<= 32;
	op2 = op2 + operator2Low;
		//realizando a operação
	int64_t result = op2-op1;
	//coloca os 64 bits em variáveis de 32 bits
	int32_t resultHigh = result >> 32;
	int32_t resultLow = result & 0xffffffff;
	//empilha resultado
	empilhar_operando(resultHigh);
	empilhar_operando(resultLow);

	//atualiza pc
	frame_atual->pc++;
}
/**
 * Subtrai os dois valores float do topo da pilha e coloca na pilha o resultado
 */
void fsub(){

	int32_t operator2 = desempilhar_operando();
	int32_t operator1 = desempilhar_operando();
	float op1, op2;
	memcpy(&op1, &operator1, sizeof(int32_t));
	memcpy(&op2, &operator2, sizeof(int32_t));
	float resultFloat = op1-op2;
	int32_t result;
	memcpy(&result, &resultFloat, sizeof(int32_t));
	empilhar_operando(result);
	frame_atual->pc++;
}
/**
 * Subtrai os dois valores double do topo da pilha e coloca na pilha o resultado
 */
void dsub(){

	//construindo o primeiro operador
	int32_t operator1Low = desempilhar_operando();
	int32_t operator1High = desempilhar_operando();

	int64_t op1;
	op1 = operator1High;
	op1 <<= 32;
	op1 = op1 + operator1Low;

	//construindo o segundo operador
	int32_t operator2Low = desempilhar_operando();
	int32_t operator2High = desempilhar_operando();

	int64_t op2;
	op2 = operator2High;
	op2 <<= 32;
	op2 = op2 + operator2Low;

	//escrevendo em double
	double operator1;
	memcpy(&operator1, &op1, sizeof(int64_t));

	//escrevendo em double
	double operator2;
	memcpy(&operator2, &op2, sizeof(int64_t));

	//realizando a operação
	double resultDouble = operator2-operator1;

	//escrevendo em double
	int64_t result;
	memcpy(&result, &resultDouble, sizeof(double));

	//coloca os 64 bits em variáveis de 32 bits
	int32_t resultHigh = result >> 32;
	int32_t resultLow = result & 0xffffffff;

	//empilha resultado
	empilhar_operando(resultHigh);
	empilhar_operando(resultLow);

	//atualiza pc
	frame_atual->pc++;
}
/**
 * Multiplica os dois valores inteiros do topo da pilha e coloca na pilha o resultado
 */
void imul(){

	int32_t operator1 = desempilhar_operando();
	int32_t operator2 = desempilhar_operando();
	int32_t result = operator1*operator2;
	empilhar_operando(result);
	frame_atual->pc++;

}
/**
 * Multiplica os dois valores long do topo da pilha e coloca na pilha o resultado
 */
void lmul(){

	//construindo o primeiro operador
	int32_t operator1Low = desempilhar_operando();
	int32_t operator1High = desempilhar_operando();
	int64_t op1;
	op1 = operator1High;
	op1 <<= 32;
	op1 = op1 + operator1Low;

	//construindo o segundo operador
	int32_t operator2Low = desempilhar_operando();
	int32_t operator2High = desempilhar_operando();
	int64_t op2;
	op2 = operator2High;
	op2 <<= 32;
	op2 = op2 + operator2Low;

	//realizando a operação
	int64_t result = op1*op2;

	//coloca os 64 bits em variáveis de 32 bits
	int32_t resultHigh = result >> 32;
	int32_t resultLow = result & 0xffffffff;

	//empilha resultado
	empilhar_operando(resultHigh);
	empilhar_operando(resultLow);

	//atualiza pc
	frame_atual->pc++;
}
/**
 * Multiplica os dois valores float do topo da pilha e coloca na pilha o resultado
 */
void fmul(){

	int32_t operator2 = desempilhar_operando();
	int32_t operator1 = desempilhar_operando();
	float op1, op2;
	memcpy(&op1, &operator1, sizeof(int32_t));
	memcpy(&op2, &operator2, sizeof(int32_t));
	float resultFloat = op1*op2;
	int32_t result;
	memcpy(&result, &resultFloat, sizeof(int32_t));
	empilhar_operando(result);
	frame_atual->pc++;

}
/**
 * Multiplica os dois valores double do topo da pilha e coloca na pilha o resultado
 */
void dmul(){

	//construindo o primeiro operador
	int32_t operator1Low = desempilhar_operando();
	int32_t operator1High = desempilhar_operando();

	int64_t op1;
	op1 = operator1High;
	op1 <<= 32;
	op1 = op1 + operator1Low;

	//construindo o segundo operador
	int32_t operator2Low = desempilhar_operando();
	int32_t operator2High = desempilhar_operando();
	int64_t op2;
	op2 = operator2High;
	op2 <<= 32;
	op2 = op2 + operator2Low;

	//escrevendo em double
	double operator1;
	memcpy(&operator1, &op1, sizeof(int64_t));

	//escrevendo em double
	double operator2;
	memcpy(&operator2, &op2, sizeof(int64_t));

	//realizando a operação
	double resultDouble = operator1*operator2;

	//escrevendo em double
	int64_t result;
	memcpy(&result, &resultDouble, sizeof(double));

	//coloca os 64 bits em variáveis de 32 bits
	int32_t resultHigh = result >> 32;
	int32_t resultLow = result & 0xffffffff;

	//empilha resultado
	empilhar_operando(resultHigh);
	empilhar_operando(resultLow);

	//atualiza pc
	frame_atual->pc++;
}
/**
 * Divide os dois valores inteiros do topo da pilha e coloca na pilha o resultado
 */
void idiv(){

	int32_t operator2 = desempilhar_operando();
	int32_t operator1 = desempilhar_operando();
	int32_t result = operator1/operator2;
	empilhar_operando(result);
	frame_atual->pc++;
}
/**
 * Divide os dois valores longs do topo da pilha e coloca na pilha o resultado
 */
void ins_ldiv(){
	// 	divide two longs
		//construindo o primeiro operador
	int32_t operator1Low = desempilhar_operando();
	int32_t operator1High = desempilhar_operando();
	int64_t op1;
	op1 = operator1High;
	op1 <<= 32;
	op1 = op1 + operator1Low;

	//construindo o segundo operador
	int32_t operator2Low = desempilhar_operando();
	int32_t operator2High = desempilhar_operando();
	int64_t op2;
	op2 = operator2High;
	op2 <<= 32;
	op2 = op2 + operator2Low;

	//realizando a operação
	int64_t result = op2/op1;

	//coloca os 64 bits em variáveis de 32 bits
	int32_t resultHigh = result >> 32;
	int32_t resultLow = result & 0xffffffff;

	//empilha resultado
	empilhar_operando(resultHigh);
	empilhar_operando(resultLow);

	//atualiza pc
	frame_atual->pc++;

}
/**
 * Divide os dois valores float do topo da pilha e coloca na pilha o resultado
 */
void fdiv(){

	int32_t operator2 = desempilhar_operando();
	int32_t operator1 = desempilhar_operando();
	float op1, op2;
	memcpy(&op1, &operator1, sizeof(int32_t));
	memcpy(&op2, &operator2, sizeof(int32_t));
	float resultFloat = op1/op2;
	int32_t result;
	memcpy(&result, &resultFloat, sizeof(int32_t));
	empilhar_operando(result);
	frame_atual->pc++;

}
/**
 * Divide os dois valores doble do topo da pilha e coloca na pilha o resultado
 */
void ddiv(){

	//construindo o primeiro operador
	int32_t operator1Low = desempilhar_operando();
	int32_t operator1High = desempilhar_operando();
	int64_t op1;
	op1 = operator1High;
	op1 <<= 32;
	op1 = op1 + operator1Low;

	//construindo o segundo operador
	int32_t operator2Low = desempilhar_operando();
	int32_t operator2High = desempilhar_operando();
	int64_t op2;
	op2 = operator2High;
	op2 <<= 32;
	op2 = op2 + operator2Low;

	//escrevendo em double
	double operator1;
	memcpy(&operator1, &op1, sizeof(int64_t));

	//escrevendo em double
	double operator2;
	memcpy(&operator2, &op2, sizeof(int64_t));

	//realizando a operação
	double resultDouble = operator2/operator1;

	//escrevendo em double
	int64_t result;
	memcpy(&result, &resultDouble, sizeof(double));

	//coloca os 64 bits em variáveis de 32 bits
	int32_t resultHigh = result >> 32;
	int32_t resultLow = result & 0xffffffff;

	//empilha resultado
	empilhar_operando(resultHigh);
	empilhar_operando(resultLow);

	//atualiza pc
	frame_atual->pc++;

}
/**
 * Calcula o resto da divisao de dois inteiros
 */
void irem(){

	int32_t operator2 = desempilhar_operando();
	int32_t operator1 = desempilhar_operando();
	int32_t result = operator1%operator2;
	empilhar_operando(result);
	frame_atual->pc++;

}
/**
 * Calcula o resto da divisao de dois longs
 */
void lrem(){

	int32_t operator1Low = desempilhar_operando();
	int32_t operator1High = desempilhar_operando();
	int64_t op1 = operator1High;
	op1 = op1 >> 32;
	op1 = op1 + operator1Low;

	int32_t operator2Low = desempilhar_operando();
	int32_t operator2High = desempilhar_operando();
	int64_t op2 = operator1High;
	op2 = op2 << 32;
	op2 = op2 + operator2Low;

	int64_t resultLong = op2%op1;

	int32_t resultHigh = resultLong >> 32;
	int32_t resultLow = resultLong & 0xffffffff;

	empilhar_operando(resultHigh);
	empilhar_operando(resultLow);

	frame_atual->pc++;

}
/**
 * Calcula o resto da divisao de dois floats
 */
void frem(){

	int32_t operator2 = desempilhar_operando();
	int32_t operator1 = desempilhar_operando();
	float op1, op2;
	memcpy(&op1, &operator1, sizeof(int32_t));
	memcpy(&op2, &operator2, sizeof(int32_t));
	float resultFloat = fmodf(op1,op2);
	int32_t result;
	memcpy(&result, &resultFloat, sizeof(int32_t));
	empilhar_operando(result);
	frame_atual->pc++;

}
/**
 * Calcula o resto da divisao de dois doubles
 */
void _drem(){

	int32_t operator1Low = desempilhar_operando();
	int32_t operator1High = desempilhar_operando();
	int64_t op1 = operator1High;
	op1 <<= 32;
	op1 = op1 + operator1Low;


	int32_t operator2Low = desempilhar_operando();
	int32_t operator2High = desempilhar_operando();
	int64_t op2 = operator2High;
	op2 <<= 32;
	op2 = op2 + operator2Low;

	double double1;
	double double2;
	memcpy(&double1, &op1, sizeof(int64_t));
	memcpy(&double2, &op2, sizeof(int64_t));
	double resultDouble = fmod(double2, double1);
	int64_t result;
	memcpy(&result, &resultDouble, sizeof(int64_t));

	int32_t resultHigh = result >> 32;
	int32_t resultLow = result & 0xffffffff;

	empilhar_operando(resultHigh);
	empilhar_operando(resultLow);

	frame_atual->pc++;

}
/**
 * Calcula o valor negativo do inteiro
 */
void ineg(){

	int32_t operator = desempilhar_operando();
	int32_t result = -operator;
	empilhar_operando(result);
	frame_atual->pc++;

}
/**
 * Calcula o valor negativo do long
 */
void lneg(){

	int32_t operatorLow = desempilhar_operando();
	int32_t operatorHigh = desempilhar_operando();
	int64_t operator = operatorHigh;
	operator = operator << 32;
	operator |= operatorLow;

	//escrevendo em long
	long op;
	memcpy(&op, &operator, sizeof(int64_t));

	long resultLong = -op;

	//escrevendo em long
	int64_t result;
	memcpy(&result, &resultLong, sizeof(int64_t));

	int32_t high = result >> 32;
	int32_t low = result & 0xffffffff;

	empilhar_operando(high);
	empilhar_operando(low);
	frame_atual->pc++;

}
/**
 * Calcula o valor negativo do float
 */
void fneg(){

	int32_t operator = desempilhar_operando();
	float valueFloat;
	memcpy(&valueFloat, &operator, sizeof(int32_t));
	float resultFloat = -(valueFloat);
	int32_t result;
	memcpy(&result, &resultFloat, sizeof(int32_t));
	empilhar_operando(result);
	frame_atual->pc++;

}
/**
 * Calcula o valor negativo do double
 */
void dneg(){

	int32_t low = desempilhar_operando();
	int32_t high = desempilhar_operando();
	//escrevendo em double
	int64_t intValue = high;
	intValue <<= 32;
	intValue += low;
	double value;
	memcpy(&value, &intValue, sizeof(int64_t));

	value = - value;
	memcpy(&intValue, &value, sizeof(int64_t));

	high = intValue >> 32;
	low = intValue & 0xffffffff;
	//escrevendo em double

	empilhar_operando(high);
	empilhar_operando(low);
	frame_atual->pc++;

}
/**
 * Calcula o valor do shift left do int
 */
void ishl(){

	//int shift left
	int32_t shift = desempilhar_operando();
	int32_t shifted = shift5Bits(shift);
	int32_t value = desempilhar_operando();
	int32_t result = value << shifted;
	empilhar_operando(result);
	frame_atual->pc++;

}
/**
 * Calcula o valor do shift left do long
 */
void lshl(){

	//long shift left
	int32_t shift = desempilhar_operando();
	shift6Bits(shift);
	//desempilhando parte alta e baixa
	int32_t low = desempilhar_operando();
	int32_t high = desempilhar_operando();
	//construção do resultado
	int64_t resultLong = high;
	resultLong = resultLong << 32;
	resultLong = resultLong + low;
	//realizando a operação
	resultLong = resultLong << shift;
	//dividindo o resultado em int32
	int32_t result1 = resultLong >> 32;
	int32_t result2 = resultLong & 0xffffffff;
	//empilhando os resultados
	empilhar_operando(result1);
	empilhar_operando(result2);
	frame_atual->pc++;

}
/**
 * Calcula o valor do shift right do int
 */
void ishr(){

	//int shift right
	int32_t shift = desempilhar_operando();
	int32_t shifted = shift5Bits(shift);
	int32_t value = desempilhar_operando();
	int32_t result = value >> shifted;
	empilhar_operando(result);
	frame_atual->pc++;

}

/**
 * Calcula o valor do shift right do long
 */
void lshr(){

	//long shift left
	int32_t shift = desempilhar_operando();
	shift6Bits(shift);
	//desempilhando parte alta e baixa
	int32_t low = desempilhar_operando();
	int32_t high = desempilhar_operando();
	//construção do resultado
	int64_t resultLong = high;
	resultLong = resultLong << 32;
	resultLong = resultLong + low;
	//realizando a operação
	resultLong = resultLong >> shift;
	//dividindo o resultado em int32
	int32_t result1 = resultLong >> 32;
	int32_t result2 = resultLong & 0xffffffff;
	//empilhando os resultados
	empilhar_operando(result1);
	empilhar_operando(result2);
	frame_atual->pc++;

}
/**
 * Calcula o valor do shift right logico do int
 */
void iushr(){

	//int shift right
	int32_t shift = desempilhar_operando();
	int32_t shifted = shift5Bits(shift);
	int32_t value = desempilhar_operando();
	int32_t result = value >> shifted;
	empilhar_operando(result);
	frame_atual->pc++;

}

/**
 * Calcula o valor do shift right logico do long
 */
void lushr(){

	//long shift left
	int32_t shift = desempilhar_operando();
	shift6Bits(shift);
	//desempilhando parte alta e baixa
	int32_t high = desempilhar_operando();
	int32_t low = desempilhar_operando();
	//construção do resultado
	int64_t resultLong = high;
	resultLong = resultLong << 32;
	resultLong = resultLong + low;
	//realizando a operação
	resultLong = resultLong >> shift;
	//dividindo o resultado em int32
	int32_t result1 = resultLong >> 32;
	int32_t result2 = resultLong & 0xffffffff;
	//empilhando os resultados
	empilhar_operando(result1);
	empilhar_operando(result2);
	frame_atual->pc++;

}
/**
 * Calcula o valor da operação logica and entre inteiros
 */
void iand(){

	int32_t operator1 = desempilhar_operando();
	int32_t operator2 = desempilhar_operando();
	int32_t result = operator1&operator2;
	empilhar_operando(result);
	frame_atual->pc++;
}
/**
 * Calcula o valor da operação logica and entre longs
 */
void land(){

	int32_t operator1Low = desempilhar_operando();
	int32_t operator1High = desempilhar_operando();
	int64_t op1 = operator1High;
	op1 = op1 >> 32;
	op1 = op1 + operator1Low;

	int32_t operator2Low = desempilhar_operando();
	int32_t operator2High = desempilhar_operando();
	int64_t op2 = operator1High;
	op2 = op2 << 32;
	op2 = op2 + operator2Low;

	int64_t resultLong = op1&op2;

	int32_t resultHigh = resultLong >> 32;
	int32_t resultLow = resultLong & 0xffffffff;

	empilhar_operando(resultHigh);
	empilhar_operando(resultLow);
	frame_atual->pc++;

}
/**
 * Calcula o valor da operação logica or entre inteiros
 */
void ior(){

	int32_t operator1 = desempilhar_operando();
	int32_t operator2 = desempilhar_operando();
	int32_t result = operator1|operator2;
	empilhar_operando(result);
	frame_atual->pc++;
}

/**
 * Calcula o valor da operação logica or entre longs
 */
void lor(){

	int32_t operator1Low = desempilhar_operando();
	int32_t operator1High = desempilhar_operando();
	int64_t op1 = operator1High;
	op1 = op1 >> 32;
	op1 = op1 + operator1Low;

	int32_t operator2Low = desempilhar_operando();
	int32_t operator2High = desempilhar_operando();
	int64_t op2 = operator1High;
	op2 = op2 << 32;
	op2 = op2 + operator2Low;

	int64_t resultLong = op1|op2;

	int32_t resultHigh = resultLong >> 32;
	int32_t resultLow = resultLong & 0xffffffff;

	empilhar_operando(resultHigh);
	empilhar_operando(resultLow);
	frame_atual->pc++;

}
/**
 * Calcula o valor da operação logica xor entre interos
 */
void ixor(){

	int32_t operator1 = desempilhar_operando();
	int32_t operator2 = desempilhar_operando();
	int32_t result = operator1^operator2;
	empilhar_operando(result);
	frame_atual->pc++;
}
/**
 * Calcula o valor da operação logica xor entre longs
 */
void lxor(){

	int32_t operator1Low = desempilhar_operando();
	int32_t operator1High = desempilhar_operando();
	int64_t op1 = operator1High;
	op1 = op1 >> 32;
	op1 = op1 + operator1Low;

	int32_t operator2Low = desempilhar_operando();
	int32_t operator2High = desempilhar_operando();
	int64_t op2 = operator1High;
	op2 = op2 << 32;
	op2 = op2 + operator2Low;

	int64_t resultLong = op1^op2;

	int32_t resultHigh = resultLong >> 32;
	int32_t resultLow = resultLong & 0xffffffff;

	empilhar_operando(resultHigh);
	empilhar_operando(resultLow);
	frame_atual->pc++;

}
/**
 * Incrementa variavel local em uma constante
 */
void iinc(){
	uint8_t index = frame_atual->code[frame_atual->pc+1];
	int8_t value = frame_atual->code[frame_atual->pc+2];
	frame_atual->fields[index]+=value;
	frame_atual->pc+=3;
}
/**
 * Converte int para long
 */
void i2l(){

	// 	convert an int into a long
	int32_t integer = desempilhar_operando();
	long valueLong = (long)integer;
	int64_t value;

	memcpy(&value, &valueLong, sizeof(int64_t));

	int32_t high = value >> 32;
	int32_t low  = value & 0xffffffff;

	empilhar_operando(high);
	empilhar_operando(low);
	frame_atual->pc++;


}
/**
 * Converte int para float
 */
void i2f(){

	//convert an int into a float
	int32_t integer = desempilhar_operando();
	float toFloat = (float) integer;
	memcpy(&integer, &toFloat, sizeof(int32_t));
	empilhar_operando(integer);
	frame_atual->pc++;

}
/**
 * Converte int para double
 */
void i2d(){

	int32_t integer = desempilhar_operando();
	double valueDouble = (double)integer;

	int64_t value;

	memcpy(&value, &valueDouble, sizeof(int64_t));

	int32_t high = value >> 32;
	int32_t low  = value & 0xffffffff;

	empilhar_operando(high);
	empilhar_operando(low);
	frame_atual->pc++;

}
/**
 * Converte long para int
 */
void l2i(){

	int32_t low = desempilhar_operando();
	int32_t high  = desempilhar_operando();
	int64_t op = high;
	op <<=32;
	op |= low;
	int32_t result = (int32_t)op;
	empilhar_operando(result);
	frame_atual->pc++;

}
/**
 * Converte long para float
 */
void l2f(){

	int32_t low = desempilhar_operando();
	int32_t high = desempilhar_operando();

	float valueFloat = (float)low;
	int32_t value;

	memcpy(&value, &valueFloat, sizeof(int32_t));

	empilhar_operando(value);
	frame_atual->pc++;

}
/**
 * Converte long para double
 */
void l2d(){

	int32_t low = desempilhar_operando();
	int32_t high = desempilhar_operando();
	int64_t valueLong = high;
	valueLong = valueLong <<32;
	valueLong = valueLong + low;
	double valueDouble = (double) valueLong;
	int64_t value;
	memcpy(&value, &valueDouble, sizeof(int64_t));
	empilhar_operando(value);
	frame_atual->pc++;

}
/**
 * Converte float para inteiro
 */
void f2i(){

	//convert an float into a int
	int32_t integer = desempilhar_operando();
	float toFloat;
	memcpy(&toFloat, &integer, sizeof(int32_t));
	int32_t result = (int32_t) toFloat;
	empilhar_operando(result);
	frame_atual->pc++;

}
/**
 * Converte float para long
 */
void f2l(){

	int32_t intValue = desempilhar_operando();
	float floatValue;
	memcpy(&floatValue, &intValue, sizeof(int32_t));
	long valueLong = (long) floatValue;
	int64_t value;
	memcpy(&value, &valueLong, sizeof(int64_t));
	int32_t high = value >> 32;
	int32_t low = value & 0xffffffff;
	empilhar_operando(high);
	empilhar_operando(low);
	frame_atual->pc++;

}
/**
 * Converte float para double
 */
void f2d(){

	int32_t intValue = desempilhar_operando();
	float floatValue;
	memcpy(&floatValue, &intValue, sizeof(int32_t));
	double valueDouble = (double) floatValue;
	int64_t value;
	memcpy(&value, &valueDouble, sizeof(int64_t));
	int32_t high = value >> 32;
	int32_t low = value & 0xffffffff;
	empilhar_operando(high);
	empilhar_operando(low);
	frame_atual->pc++;
}
/**
 * COnverte double para inteiro
 */
void d2i(){

	int32_t low = desempilhar_operando();
	int32_t high = desempilhar_operando();
	int64_t intValue = high;
	intValue <<= 32;
	intValue += low;
	double doubleValue;
	memcpy(&doubleValue, &intValue, sizeof(int64_t));
	int32_t value = (int) doubleValue;
	empilhar_operando(value);
	frame_atual->pc++;

}
/**
 * Converte double para long
 */
void d2l(){

	int32_t low = desempilhar_operando();
	int64_t high = desempilhar_operando();
	int64_t intValue = high;
	intValue = intValue << 32;
	intValue += low;
	double doubleValue;
	memcpy(&doubleValue, &intValue, sizeof(int64_t));
	int64_t valueLong = (long) doubleValue;
	int32_t highValue = valueLong >> 32;
	int32_t lowValue = valueLong & 0xffffffff;
	empilhar_operando(highValue);
	empilhar_operando(lowValue);
	frame_atual->pc++;

}
/**
 * COnverte double para float
 */
void d2f(){

	int32_t low = desempilhar_operando();
	int32_t high = desempilhar_operando();
	double doubleValue;
	int64_t intValue;
	intValue = high;
	intValue <<= 32;
	intValue += low;
	memcpy(&doubleValue, &intValue, sizeof(int64_t));
	float valueFloat = (float)doubleValue;
	int32_t value;
	memcpy(&value, &valueFloat, sizeof(int32_t));
	empilhar_operando(value);
	frame_atual->pc++;

}
/**
 * COnverte int para byte
 */
void i2b(){

	int32_t integer = desempilhar_operando();
	int8_t byte = (int8_t) integer;
	empilhar_operando(byte);
	frame_atual->pc++;

}
/**
 * COnverte int para char
 */
void i2c(){

	int32_t integer = desempilhar_operando();
	uint8_t character = (uint8_t) integer;
	empilhar_operando((int32_t) character);
	frame_atual->pc++;

}
/**
 * COnverte int para sshort
 */
void i2s(){

	int32_t integer = desempilhar_operando();
	short valueShort = (short) integer;
	int16_t value;
	memcpy(&value, &valueShort, sizeof(int16_t));
	empilhar_operando((int32_t) value);
	frame_atual->pc++;

}
/**
 * COmpra longs
 */
void lcmp(){

	//push 0 if the two longs are the same, 1 if value1 is greater than value2, -1 otherwise
	//long 1
	int32_t long1Low = desempilhar_operando();
	int32_t long1High = desempilhar_operando();
	//contrucao do long
	int64_t long1 = long1High;
	long1 = long1 >> 32;
	long1 = long1 + long1Low;

	//long 2
	int32_t long2Low = desempilhar_operando();
	int32_t long2High = desempilhar_operando();

	//contrucao do long
	int64_t long2 = long2High;
	long2 = long2 >> 32;
	long2 = long2 + long2Low;

	long value1Long;
	memcpy(&value1Long, &long1, sizeof(int64_t));
	long value2Long;
	memcpy(&value2Long, &long2, sizeof(int64_t));
	verifyLongs(value1Long, value2Long);

	frame_atual->pc++;

}
/**
 * Compara dois floats (menor)
 */
void fcmpl(){

	//compare two floats
	//desempilhando dois valores da pilha
	int32_t value1 = desempilhar_operando();
	int32_t value2 = desempilhar_operando();
	float value1Float;
	float value2Float;
	//transformando int32 em float
	memcpy(&value1Float, &value1, sizeof(int32_t));
	memcpy(&value2Float, &value2, sizeof(int32_t));
	//comparando os floats
	verifyFloats(value1Float, value2Float);
	//atualizando pc
	frame_atual->pc++;

}
/**
 * COmpara floats (maior)
 */
void fcmpg(){

	//compare two floats
	//desempilhando dois valores da pilha
	int32_t value1 = desempilhar_operando();
	int32_t value2 = desempilhar_operando();
	float value1Float;
	float value2Float;
	//transformando int32 em float
	memcpy(&value1Float, &value1, sizeof(int32_t));
	memcpy(&value2Float, &value2, sizeof(int32_t));
	//comparando os floats
	verifyFloats(value1Float, value2Float);
	//atualizando pc
	frame_atual->pc++;

}
/**
 * Compara longs (menor)
 */
void dcmpl(){

	//double 1
	int32_t double1Low = desempilhar_operando();
	int32_t double1High = desempilhar_operando();
	//contrucao do double
	int64_t double1 = double1High;
	double1 = double1 << 32;
	double1 = double1 + double1Low;

	//double 2
	int32_t double2Low = desempilhar_operando();
	int32_t double2High = desempilhar_operando();

	//contrucao do double
	int64_t double2 = double2High;
	double2 = double2 << 32;
	double2 = double2 + double2Low;

	double value1Double;
	memcpy(&value1Double, &double1, sizeof(int64_t));
	double value2Double;
	memcpy(&value2Double, &double2, sizeof(int64_t));
	verifyDoubles(value1Double, value2Double);

	frame_atual->pc++;

}
/**
 * Compara doubles (maior)
 */
void dcmpg(){

	//double 1
	int32_t double1High = desempilhar_operando();
	int32_t double1Low = desempilhar_operando();
	//contrucao do double
	int64_t double1 = double1High;
	double1 = double1 >> 32;
	double1 = double1 + double1Low;

	//double 2
	int32_t double2High = desempilhar_operando();
	int32_t double2Low = desempilhar_operando();

	//contrucao do double
	int64_t double2 = double2High;
	double2 = double2 >> 32;
	double2 = double2 + double2Low;

	double value1Double;
	memcpy(&value1Double, &double1, sizeof(int64_t));
	double value2Double;
	memcpy(&value2Double, &double2, sizeof(int64_t));

	verifyDoubles(value1Double, value2Double);

	frame_atual->pc++;

}
/**
 * Se o valor for zero vai para instrução no branchoffset
 */
void ifeq(){

	//if value is 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)
	int32_t value = desempilhar_operando();
	int32_t branchOffset = calculateOffset();
	if (value == 0)
	{
		frame_atual->pc = frame_atual->pc + branchOffset;
	} else {
		frame_atual->pc += 3;
	}
}
/**
 * Se o valor for diferente de zero vai para instrução no branchoffset
 */
void ifne(){

	//if value is not 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)
	int32_t value = desempilhar_operando();
	int32_t branchOffset = calculateOffset();
	if (value != 0)
	{
		frame_atual->pc = frame_atual->pc + branchOffset;
	} else {
		frame_atual->pc += 3;
	}
}
/**
 * Se o valor for menor que zero vai para instrução no branchoffset
 */
void iflt(){

	//if value is less than 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)
	int32_t value = desempilhar_operando();
	int32_t branchOffset = calculateOffset();
	if (value < 0)
	{
		frame_atual->pc = frame_atual->pc + branchOffset;
	} else {
		frame_atual->pc += 3;
	}
}
/**
 * Se o valor for maior que zero vai para instrução no branchoffset
 */
void ifge(){

	//if value is greater or equal than 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)
	int32_t value = desempilhar_operando();
	int32_t branchOffset = calculateOffset();
	if (value >= 0)
	{
		frame_atual->pc = frame_atual->pc + branchOffset;
	} else {
		frame_atual->pc += 3;
	}

}
/**
 * Se o valor for maior igual a zero vai para instrução no branchoffset
 */
void ifgt(){

	//if value is greater than 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)
	int32_t value = desempilhar_operando();
	int32_t branchOffset = calculateOffset();
	if (value > 0)
	{
		frame_atual->pc = frame_atual->pc + branchOffset;
	} else {
		frame_atual->pc += 3;
	}

}
/**
 * Se o valor for menor igual a zero vai para instrução no branchoffset
 */
void ifle(){

	//if value is less or equal than 0, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)
	int32_t value = desempilhar_operando();
	int32_t branchOffset = calculateOffset();
	if (value <= 0)
	{
		frame_atual->pc = frame_atual->pc + branchOffset;
	} else {
		frame_atual->pc += 3;
	}

}
/**
 * Realiza o salto se value1 = value2
 */
void if_icmpeq(){

	//if ints are equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)
	int32_t value1 = desempilhar_operando();
	int32_t value2 = desempilhar_operando();
	int32_t branchOffset = calculateOffset();
	if (value1 == value2 )
	{
		frame_atual->pc = frame_atual->pc + branchOffset;
	} else {
		frame_atual->pc += 3;
	}
}
/**
 * Realiza o salto se value1 != value2
 */
void if_icmpne(){

	//if ints are not equal, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)
	int32_t value1 = desempilhar_operando();
	int32_t value2 = desempilhar_operando();
	int32_t branchOffset = calculateOffset();
	if (value1 != value2 )
	{
		frame_atual->pc = frame_atual->pc + branchOffset;
	} else {
		frame_atual->pc += 3;
	}

}
/**
 * Realiza o salto se value1 < value2
 */
void if_icmplt(){

	//if value1 are less than value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)
	int32_t value1 = desempilhar_operando();
	int32_t value2 = desempilhar_operando();
	int32_t branchOffset = calculateOffset();
	if (value1 < value2 )
	{
		frame_atual->pc = frame_atual->pc + branchOffset;
	} else {
		frame_atual->pc += 3;
	}

}
/**
 * Realiza o salto se value1 >= value2
 */
void if_icmpge(){

	//if value1 are greater or equal than value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)
	int32_t value1 = desempilhar_operando();
	int32_t value2 = desempilhar_operando();
	int32_t branchOffset = calculateOffset();
	if (value1 <= value2 )
	{
		frame_atual->pc = frame_atual->pc + branchOffset;
	} else {
		frame_atual->pc += 3;
	}

}
/**
 * Realiza o salto se value1 > value2
 */
void if_icmpgt(){

	//if value1 are greater than value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)
	int32_t value1 = desempilhar_operando();
	int32_t value2 = desempilhar_operando();
	int32_t branchOffset = calculateOffset();
	if (value2 > value1 )
	{
		frame_atual->pc = frame_atual->pc + branchOffset;
	} else {
		frame_atual->pc += 3;
	}

}
/**
 * Realiza o salto se value1 <= value2
 */
void if_icmple(){

	//if value1 are less or equal than value2, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)
	int32_t value1 = desempilhar_operando();
	int32_t value2 = desempilhar_operando();
	int32_t branchOffset = calculateOffset();
	if (value2 <= value1) {
		frame_atual->pc = frame_atual->pc + branchOffset;
	} else {
		frame_atual->pc += 3;
	}

}

void if_acmpeq(){

}

void if_acmpne(){

}
/**
 * Realiza o salto para dado offset
 */
void ins_goto(){

	int32_t branchOffset = calculateOffset();
	frame_atual->pc = frame_atual->pc + branchOffset;

}
/**
 * Realiza o salto para dado offset e coloca endereco de retorno na pilha
 */
void jsr(){

	//jump to subroutine at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2) and place the return address on the stack
	int32_t branchOffset = calculateOffset();
	int32_t returnAdress = frame_atual->pc+3;
	empilhar_operando(returnAdress);
	frame_atual->pc = frame_atual->pc + branchOffset;
}
/**
 * Continuar execucao a partir de um endereço encontrado em uma variavel local
 */
void ret(){

	//continue execution from address taken from a local variable #index (the asymmetry with jsr is intentional)
	int32_t index = frame_atual->code[frame_atual->pc+1];
	int32_t offset = frame_atual->fields[index];
	frame_atual->pc = frame_atual->pc+offset;
	frame_atual->pc += 2;
}
/**
 * Acessar a tabela de saltos pelo indice e realizar salto
 */
void tableswitch() {
    int compValue = desempilhar_operando();

	uint8_t *src = frame_atual->code + frame_atual->pc + 1;
	TableswitchData dt = montar_switch_table(src, frame_atual->pc);

	if(compValue >= dt.lowBytes && compValue <= dt.highBytes) {
		for(int i = 0; i < dt.sizeOfJumpOffsets; i++) {
			if(compValue == i) {
				frame_atual->pc += dt.jumpOffsets[i];
				return;
			}
		}
	}

	frame_atual->pc += dt.defaultBytes;
}
/**
 * Acessar tabela de salto por chave e realizar salto
 */
void lookupswitch() {
  int compValue = desempilhar_operando();

    uint8_t *src = frame_atual->code + frame_atual->pc + 1;
    LookupswitchData dt = montar_lookupswitch_data(src, frame_atual->pc);

    for(int i = 0; i <= dt.amountOfPairs; i += 2) {
        if(compValue == dt.keyOffsetPairs[i]) {
            frame_atual->pc += dt.keyOffsetPairs[i+1];
            return;
        }
    }

    frame_atual->pc += dt.defaultBytes;
}
/**
 * Retornar int de um metodo
 */
void ireturn(){
	frame_atual->pc = frame_atual->code_length;
	flag = 1;
}
/**
 * Retornar long de um metodo
 */
void lreturn(){
	frame_atual->pc = frame_atual->code_length;
	flag = 2;
}
/**
 * Retornar float de um metodo
 */
void freturn(){
	frame_atual->pc = frame_atual->code_length;
	flag = 1;
}
/**
 * Retornar double de um metodo
 */
void dreturn(){
	frame_atual->pc = frame_atual->code_length;
	flag = 2;
}
/**
 * Retornar objeto de um metodo
 */
void areturn(){
	frame_atual->pc = frame_atual->code_length;
    flag = 1;
}
/**
 * Retornar void de um metodo
 */
void void_return(){
	frame_atual->pc = frame_atual->code_length;
	flag = 0;
}
/**
 * Pegar um campo estatico a partir de uma classe
 */
void getstatic(){
	frame_atual->pc+=3;
}

/**
 * Colocar um campo estatico a partir de uma classe
 */
void putstatic(){

	//Acha indices para o constant pool
	uint8_t indexByte1 = frame_atual->code[frame_atual->pc+1];
	uint8_t indexByte2 = frame_atual->code[frame_atual->pc+2];

	//junta os dois para encontrar o indice desejado
	uint16_t index = (indexByte1 << 8) | indexByte2;

	int indexField = frame_atual->constantPool[index].info.fieldref_info->name_and_type_index;

	desempilhar_operando();

	frame_atual->pc +=3;


}
/**
 * Achar um campo a partir de um objeto
 */
void getfield(){
	uint16_t index = read2Bytes((frame_atual->code + frame_atual->pc + 1));
	// get name and type for field index
	index = frame_atual->constantPool[index].info.fieldref_info->name_and_type_index;

	Object* object = (Object*) desempilhar_operando();

	char* descriptor = findMethodDescriptor(frame_atual->constantPool, index);
	uint64_t value = getObjectFieldValueByName(object, findMethodName(frame_atual->constantPool, index));

	switch(descriptor[0]){
		// variaveis normais
		case 'C': case 'F': case 'B': case 'I': case 'S': case 'Z': case 'L': case '[': {
			uint32_t aux = value & 0xffffffff;
			empilhar_operando(aux);
			break;
		}
		// variaveis categoria 2
		case 'J': case 'D':{
			uint32_t resultHigh;
			resultHigh = value >> 32;
			uint32_t resultLow;
			resultLow = value & 0xffffffff;
			//empilha resultado
			empilhar_operando(resultHigh);
			empilhar_operando(resultLow);
			break;
		}
	}

	frame_atual->pc += 3;
}
/**
 * Setar campo de objeto
 */
void putfield(){
	uint16_t index = read2Bytes((frame_atual->code + frame_atual->pc + 1));
	// get name and type for field index
	index = frame_atual->constantPool[index].info.fieldref_info->name_and_type_index;

	char* descriptor = findMethodDescriptor(frame_atual->constantPool, index);

	switch(descriptor[0]){
		// variaveis normais
		case 'C': case 'F': case 'B': case 'I': case 'S': case 'Z': case 'L': case '[': {
			uint32_t value = desempilhar_operando();
			Object* object = (Object*) desempilhar_operando();
			setObjectFieldValueByName(object, findMethodName(frame_atual->constantPool, index), value);
			break;
		}
		// variaveis categoria 2
		case 'J': case 'D': {
			uint32_t resultLow = desempilhar_operando();
			uint32_t resultHigh = desempilhar_operando();
			Object* object = (Object*) desempilhar_operando();
			uint64_t aux = resultHigh;
			aux <<= 32;
			aux += resultLow;
			setObjectFieldValueByName(object, findMethodName(frame_atual->constantPool, index), aux);
			break;
		}
	}
	frame_atual->pc += 3;
}
/**
 * Chamar metodo despachar baseado na classe
 */
void invokevirtual(){
	int i;
	uint16_t index = read2Bytes((frame_atual->code + frame_atual->pc + 1));
	//pega o nome da classe
	char* className = findClassNameFromMethod(frame_atual->constantPool, index);

	int32_t nameAndTypeIndex = frame_atual->constantPool[index].info.methodref_info->name_and_type_index;
	char* methodName = findMethodName(frame_atual->constantPool, nameAndTypeIndex);
	char* methodDescriptor = findMethodDescriptor(frame_atual->constantPool, nameAndTypeIndex);
	if((strcmp(className, "java/io/PrintStream") == 0) && (strcmp(methodName,"println") == 0)) {
		if (DEBUG) printf("SYSTEM OUT : ");
		if(strcmp(methodDescriptor,"()V") == 0) {
			printf("\n");
		} else {
			if (methodDescriptor[1] == 'I') {
				handlePrintInt();
			} else if (methodDescriptor[1] == 'F') {
				handlePrintFloat();
			} else if (methodDescriptor[1] == 'Z') {
				handlePrintBoolean();
			} else if (methodDescriptor[1] == 'D') {
				handlePrintDouble();
			} else if(methodDescriptor[1] == 'C') {
				handlePrintChar();
			} else if(methodDescriptor[1] == 'J') {
				handlePrintLong();
			} else {
				handlePrintString();
			}
		}
	} else {
		// Calcula quantidade total de parametros na pilha
		int32_t paramsCount = getParamsCount(methodDescriptor);
		// Armazena os argumentos da pilha em um Array
		uint32_t fieldsArray[paramsCount+1];
		for(i = 0; i < paramsCount; fieldsArray[paramsCount-(i++)] = desempilhar_operando());
		Object* object = (Object*) desempilhar_operando();
		fieldsArray[0] = (uint32_t) object;
		// Retorna um estrutura de metodo do objeto para criar um frame
		ObjectMethod method = getObjectMethodByName(object, methodName, className);
		ClassFile* classFile = method.classFile;
		Method_info* method_info = method.method_info;
		empilhar_metodo(classFile, method_info);
		// Copia os argumentos para as variaveis locais do novo frame
		for (int i = 0; i <= paramsCount; ++i){
			frame_atual->fields[i] = fieldsArray[i];
		}
		executar_frame();
	}
	frame_atual->pc+=3;
}
/**
 * Invoca metodo com tratamento especial para superclass privite e metodos de incializacao de instancia
 */
void invokespecial(){
	uint16_t index = read2Bytes((frame_atual->code + frame_atual->pc + 1));
	//pega o nome da classe
	char* className = findClassNameFromMethod(frame_atual->constantPool, index);
	int32_t nameAndTypeIndex = frame_atual->constantPool[index].info.methodref_info->name_and_type_index;
	char* methodName = findMethodName(frame_atual->constantPool, nameAndTypeIndex);
	char* methodDescriptor = findMethodDescriptor(frame_atual->constantPool, nameAndTypeIndex);
	// Calcula quantidade total de parametros na pilha
	int32_t paramsCount = getParamsCount(methodDescriptor);
	// Armazena os argumentos da pilha em um Array
	uint32_t fieldsArray[paramsCount+1];
	for(int i = 0; i < paramsCount; fieldsArray[paramsCount-(i++)] = desempilhar_operando());
	Object* object = (Object*) desempilhar_operando();
	fieldsArray[0] = (uint32_t) object;
	// Retorna um estrutura de metodo do objeto para criar um frame
	ObjectMethod method = getObjectMethodByName(object, methodName, className);
	ClassFile* classFile = method.classFile;
	Method_info* method_info = method.method_info;
	empilhar_metodo(classFile, method_info);
	// Copia os argumentos para as variaveis locais do novo frame
	for (int i = 0; i <= paramsCount; ++i){
		frame_atual->fields[i] = fieldsArray[i];
	}
	executar_frame();
	frame_atual->pc += 3;
}
/**
 * Invocar uma metodo estático de uma classe
 */
void invokestatic(){
	int i;
	uint16_t index = read2Bytes((frame_atual->code + frame_atual->pc + 1));
	//pega o nome da classe
	char* className = findClassNameFromMethod(frame_atual->constantPool, index);

	int32_t nameAndTypeIndex = frame_atual->constantPool[index].info.methodref_info->name_and_type_index;

	ClassFile* classFile = carregar_classe(className);
	Method_info* invokedMethod = findMethod(classFile, frame_atual->classe,nameAndTypeIndex);
	int32_t paramsCount = getParamsCount(classFile->constant_pool[invokedMethod->descriptor_index].info.utf8_info->bytes);
	uint32_t fieldsArray[paramsCount];

	for(i = 0; i < paramsCount; fieldsArray[i++] = desempilhar_operando());

	empilhar_metodo(classFile, invokedMethod);
	for(i = 0; i < paramsCount; i++) {
		frame_atual->fields[i] = fieldsArray[paramsCount - i - 1];
	}
	executar_frame();

	frame_atual->pc += 3;
}
/**
 * Invocar interface metodo
 */
void invokeinterface(){
	uint16_t index = read2Bytes((frame_atual->code + frame_atual->pc + 1));
	//pega o nome da classe
	char* className = findClassNameFromMethod(frame_atual->constantPool, index);
	int32_t nameAndTypeIndex = frame_atual->constantPool[index].info.methodref_info->name_and_type_index;
	char* methodName = findMethodName(frame_atual->constantPool, nameAndTypeIndex);
	char* methodDescriptor = findMethodDescriptor(frame_atual->constantPool, nameAndTypeIndex);
	// Calcula quantidade total de parametros na pilha
	int32_t paramsCount = getParamsCount(methodDescriptor);
	// Armazena os argumentos da pilha em um Array
	uint32_t fieldsArray[paramsCount+1];
	for(int i = 0; i < paramsCount; fieldsArray[paramsCount-(i++)] = desempilhar_operando());
	Object* object = (Object*) desempilhar_operando();
	fieldsArray[0] = (uint32_t) object;
	// Retorna um estrutura de metodo do objeto para criar um frame
	ObjectMethod method = getObjectMethodByName(object, methodName, className);
	ClassFile* classFile = method.classFile;
	Method_info* method_info = method.method_info;
	empilhar_metodo(classFile, method_info);
	// Copia os argumentos para as variaveis locais do novo frame
	for (int i = 0; i <= paramsCount; ++i){
		frame_atual->fields[i] = fieldsArray[i];
	}
	executar_frame();
	frame_atual->pc += 5;
}
/**
 * Carregar objeto na pilha utilizando de um indice para o constant pool como operando
 */
void ins_new(){

	uint16_t index = frame_atual->code[frame_atual->pc + 1];
	// shifta pq sao 2 bytes de index
	index <<= 8;
	index += frame_atual->code[frame_atual->pc + 2];

	index = frame_atual->constantPool[index].info.class_info->name_index;

	ClassFile* classFile = carregar_classe(frame_atual->constantPool[index].info.utf8_info->bytes);
	Object* object = createObject(classFile);
	empilhar_operando((int32_t) object);

	frame_atual->pc += 3;
}
/**
 * Cria um novo array podendo ser de todos os possíveis tipos
 */
void newarray(){
	//instrucao que cria um novo array e coloca a referencia para a mesma na pilha

	//Pega o parametro que define o tipo
	uint32_t type = frame_atual->code[frame_atual->pc + 1];
	//Numero de elementos para o array
	uint32_t count = desempilhar_operando();

	//variavel para salvar o tamanho de cada elemento do array
	uint16_t typeSize = 0;

	//Define o tamanho do tipo
	switch(type){
		case 4 : //boolean
			typeSize = 1;
		break;
		case 5 : //char
			typeSize = 2;
		break;
		case 6 : //float
			typeSize = 4;
		break;
		case 7 : //double
			typeSize = 8;
		break;
		case 8 : //Byte
			typeSize = 1;
		break;
		case 9 : //Short
			typeSize = 2;
		break;
		case 10 : //int
			typeSize = 4;
		break;
		case 11 : //Longyy
			typeSize = 8;
		break;
	}

	//Realiza a alocacao

	// Coloca o tamanho
	arrayType* array;
	array = (arrayType *) malloc(sizeof(arrayType));
	put_tamanho_array(count, array);

	// Aloca o espaco de dados
	put_referencia_array(calloc(count, typeSize), array);

	// Coloca a referencia na pilha de operandos
    int32_t arrayTypeRef;
    memcpy(&arrayTypeRef, &array , sizeof(int32_t));
	empilhar_operando((uint32_t) array);
	//Incrementa o PC
	frame_atual->pc += 2;
}
/**
 * Cria um novo array objeto
 */
void anewarray(){

	//retira da pilha o valor que vai corresponder ao tamanho do array a ser criado
	uint32_t count = desempilhar_operando();

	//Acha indices para o constant pool
	uint8_t indexByte1 = frame_atual->code[frame_atual->pc+1];
	uint8_t indexByte2 = frame_atual->code[frame_atual->pc+2];

	//junta os dois para encontrar o indice desejado
	uint16_t index = (indexByte1 << 8) | indexByte2;

	//TODO definir que tipo o array vai ser e pegar o tamanho desse tipo para a alocacao
	//Na descricao eh dito para acessar o constant pool na posicao index e verificar se eh uma
	//classe, array ou interface.
	uint16_t sizeBytes = sizeof(frame_atual->constantPool[index]);

	// Aloca o array

	// Coloca o tamanho
	arrayType* array;
	array = (arrayType *) malloc(sizeof(arrayType));
	put_tamanho_array(count, array);

	// Aloca o espaco de dados
	put_referencia_array(calloc(count, sizeBytes), array);

	// Coloca a referencia na pilha de operandos
	empilhar_operando((uint32_t) array);

	//Atualiza o pc
	frame_atual->pc+=3;
}
/**
 * Devolve o tamanho de dado array
 */
void arraylength(){
	//Encontra o tamanho do array que está na pilha

	//Pega a referecia para o array.
	arrayType* array = (arrayType*) desempilhar_operando();

	uint32_t size = get_tamanho_array(array);

	// Coloca o tamanho na pilha
	empilhar_operando(size);

	// // Atualiza o PC
	frame_atual->pc++;

}

void checkcast(){

}

void instanceof(){

}

void wide(){

}
/**
 * Cria arrays multidimencionais de todos os possíveis tipos
 */
void multianewarray(){


	//Acha o numero de dimensoes
	uint8_t dimensions = frame_atual->code[frame_atual->pc+3];

	//cria um array para armazenar os valores do tamanho das dimencoes
	uint32_t count[dimensions + 1];

	//pega os counts (tamanho da dimensao) correspondente ao numero de dimencoes
	for (int i = dimensions; i > 0; --i){
		//retira da pilha o valor que vai corresponder ao tamanho do array a ser criado
		count[i] = desempilhar_operando();
	}

	//Acha indices para o constant pool
	uint8_t indexByte1 = frame_atual->code[frame_atual->pc+1];
	uint8_t indexByte2 = frame_atual->code[frame_atual->pc+2];

	//junta os dois para encontrar o indice desejado
	uint16_t index = (indexByte1 << 8) | indexByte2;

	//Tamanho de cada elemento
	uint16_t sizeBytes = 0;

	//pega o indice para o utf8
	index = frame_atual->constantPool[index].info.string_info->string_index;
	//acha a descricao do tipo
	uint8_t* bytes = frame_atual->constantPool[index].info.utf8_info->bytes;

	//boOlean
	if(strstr(bytes, "Z") != NULL) sizeBytes = 1;
	//char
	if(strstr(bytes, "C") != NULL) sizeBytes = 2;
	//float
	if(strstr(bytes, "F") != NULL) sizeBytes = 4;
	//double
	if(strstr(bytes, "D") != NULL) sizeBytes = 8;
	//Byte
	if(strstr(bytes, "B") != NULL) sizeBytes = 1;
	//Short
	if(strstr(bytes, "S") != NULL) sizeBytes = 2;
	//int
	if(strstr(bytes, "I") != NULL) sizeBytes = 4;
    //Long
	if(strstr(bytes, "J") != NULL) sizeBytes = 8;


	// Aloca o array multidimencoes
	//Aloca o array de ponteiros
	uint32_t *mArrayRef = (uint32_t *)calloc(dimensions, sizeof(uint32_t*));

	// Aloca o corpo do array multidimensoes
	for(int i = 0; i < dimensions; i++){
		if(count[i+1]){
			mArrayRef[i] = (uint32_t )calloc(count[i+1], sizeBytes);
		}else{ //caso o count seja 0 nenhuma nova dimencao eh alocada
			break;
		}
	}


	// Coloca o tamanho
	arrayType* array;
	array = (arrayType *) malloc(sizeof(arrayType));
	put_tamanho_array(dimensions, array);

	// Aloca o espaco de dados
	put_referencia_array(mArrayRef, array);

	// Coloca a referencia na pilha de operandos
	empilhar_operando((uint32_t) array);

	//Atualiza o pc
	frame_atual->pc+=3;
}
/**
 * Realiza salto se o valor na pilha de operandos for nulo
 */
void ifnull(){

	//if value is null, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)
	int32_t offset = calculateOffset();
	int32_t value = desempilhar_operando();
	if(value == 0){
		frame_atual->pc = frame_atual->pc + offset;
	} else{
		frame_atual->pc++;
	}
}
/**
 * Realiza salto se o valor na pilha de operandos não for nulo
 */
void ifnonnull(){

	//if value is not null, branch to instruction at branchoffset (signed short constructed from unsigned bytes branchbyte1 << 8 + branchbyte2)
	int32_t offset = calculateOffset();
	int32_t value = desempilhar_operando();
	if(value != 0){
		frame_atual->pc = frame_atual->pc + offset;
	} else{
		frame_atual->pc++;
	}
}

void goto_w(){

}

void jsr_w(){

}
/**
 * Devolve apenas os 5 bytes menos significativos
 * @param  shift
 * @return shift       5 bytes menos significativos
 */
int32_t shift5Bits(int32_t shift){
	shift = shift & 0x1f;
	return shift;
}
/**
 * Devolve apenas os 5 bytes menos significativos
 * @param  shift
 * @return shift       6 bytes menos significativos
 */
void shift6Bits(int32_t shift){
	shift = shift & 0x3f;
}
/**
 * Verifica dois longs para igualdade, maioridade e menororidade
 * @param long1
 * @param long2
 */
void verifyLongs(long long1,long long2){
	if(long1 == long2){
		empilhar_operando((int32_t) 0);
	} else if(long2 > long1){
		empilhar_operando((int32_t) 1);
	} else {
		empilhar_operando((int32_t) -1);
	}
}
/**
 * Verifica dois floats para igualdade, maioridade e menororidade
 * @param float1
 * @param float2
 */
void verifyFloats(float float1,float float2){
	if(float1 == float2){
		empilhar_operando((int32_t) 0);
	} else if(float2 > float1){
		empilhar_operando((int32_t) 1);
	} else {
		empilhar_operando((int32_t) -1);
	}
}
/**
 * Verifica dois doubles para igualdade, maioridade e menororidade
 * @param double1
 * @param double2
 */
void verifyDoubles(double double1,double double2){
	if(double1 == double2){
		empilhar_operando((int32_t) 0);
	} else if(double2 > double1){
		empilhar_operando((int32_t) 1);
	} else {
		empilhar_operando((int32_t) -1);
	}
}
/**
 * Calcula um offset a partir de dois 8bits retirados da area de codigo
 * @return Offset montado
 */
int32_t calculateOffset(){

	//calcula offset para salto
	uint8_t branchOffset1 = frame_atual->code[frame_atual->pc + 1];
	uint8_t branchOffset2 = frame_atual->code[frame_atual->pc + 2];
	int16_t branchOffset = branchOffset1;
	branchOffset <<= 8;
	branchOffset += branchOffset2;
	return branchOffset;

}
/**
 * Junta dois bytes a partir de um array
 * @param  data array de entrada
 * @return      valor 16bits
 */
int16_t read2Bytes(uint8_t* data) {
	int16_t value = data[0];
	value <<= 8;
	value += data[1];
	return value;
}
/**
 * Printa um inteiro
 */
void handlePrintInt() {
	printf("%d\n", desempilhar_operando());
}
/**
 * Printa um Long
 */
void handlePrintLong() {

	uint64_t value;
	int32_t lowValue = desempilhar_operando();
	int32_t highValue = desempilhar_operando();

	value = highValue;
	value <<= 32;
	value |= lowValue;
	printf("%ld\n", value);
}
/**
 * Printa um Char
 */
void handlePrintChar() {
	char value = (char) desempilhar_operando();
	printf("%c\n", value);
}
/**
 * Printa um Float
 */
void handlePrintFloat() {
	float floatValue;
	int value = desempilhar_operando();
	memcpy(&floatValue, &value, sizeof(int32_t));
	printf("%.2f\n", floatValue);
}
/**
 * Printa um String
 */
void handlePrintString() {
	printf("%s\n", frame_atual->constantPool[desempilhar_operando()].info.utf8_info->bytes);
}
/**
 * Printa um Boolean
 */
void handlePrintBoolean() {
	int value = desempilhar_operando();
	value ? printf("TRUE\n") : printf("FALSE\n");
}
/**
 * Printa um Double
 */
void handlePrintDouble() {
    double doubleValue;
    uint64_t low = desempilhar_operando();
    uint64_t high = desempilhar_operando();
		int64_t value;
		value = high;
		value <<=32;
		value += low;
		memcpy(&doubleValue, &value, sizeof(int64_t));
    printf("%.2lf\n", doubleValue);
}
