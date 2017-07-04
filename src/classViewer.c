#include "classViewer.h"

int imprimir_instr_table_switch(const Code_attribute *codeAttribute, const char *space, int i);

int imprimir_instr_lookupswitch(const Code_attribute *codeAttribute, const char *space, int i);

static void acesso_str(int access_flag) {
	printf("[");
	if(access_flag & 0x0001) {
		printf("public; ");
	}
	if(access_flag & 0x0002) {
		printf("private; ");
	}
	if(access_flag & 0x0004) {
		printf("protected; ");
	}
	if(access_flag & 0x0008) {
		printf("static; ");
	}
	if(access_flag & 0x0010) {
		printf("final; ");
	}
	if(access_flag & 0x0020) {
		printf("super; ");
	}
	if(access_flag & 0x0200) {
		printf("interface; ");
	}
	if(access_flag & 0x0400) {
		printf("abstract; ");
	}
	if(access_flag & 0x1000) {
		printf("synthetic; ");
	}
	if(access_flag & 0x2000) {
		printf("annotation; ");
	}
	if(access_flag & 0x4000) {
		printf("enum; ");
	}
	printf("]\n");
}

static void printUtf8String(Cp_info* cp, int index) {
	int tag = cp[index].tag;
	if(tag == 1) {
		printf("<%s>", cp[index].info.utf8_info->bytes);
	}
	if(tag == 7) {
		index = cp[index].info.class_info->name_index;
		printUtf8String(cp, index);
	}
	if(tag == 12) {
		index = cp[index].info.nameAndType_info->name_index;
		printUtf8String(cp, index);
		index = cp[index].info.nameAndType_info->descriptor_index;
		printUtf8String(cp, index);
	}
}

static void versao_java(int versao) {
	switch(versao) {
		case 52:
			printf("[1.8]");
			break;
		case 51:
			printf("[1.7]");
			break;
		case 50:
			printf("[1.6]");
			break;
	}
	printf("\n");
}

void imprimir_informacoes_classe(ClassFile *classFile){
	printf("\nINFORMACOES BASICAS:\n");
	printf("\tMagic Number: 0x%X\n", classFile->magic);
	printf("\tMinor Version: %d\n", classFile->minor_version);
	printf("\tMajor Version: %d ", classFile->major_version);
	versao_java(classFile->major_version);
	printf("\tConstant Pool Count: %d\n", classFile->constant_pool_count);
	printf("\tAccess flags: 0x%.4X ", classFile->access_flags);
	acesso_str(classFile->access_flags);
	printf("\tThis class: cp_info #%d ", classFile->this_class);
	printUtf8String(classFile->constant_pool, classFile->this_class);
	printf("\n");
	printf("\tSuper class: cp_info #%d ", classFile->super_class);
	printUtf8String(classFile->constant_pool, classFile->super_class);
	printf("\n");
	printf("\tInterfaces count: %d\n", classFile->interfaces_count);
	printf("\tFields count: %d\n", classFile->fields_count);
	printf("\tMethods count: %d\n", classFile->methods_count);
	printf("\tAttributes count: %d\n", classFile->attributes_count);
	printf("\n");
}


void imprimir_constant_pool_inserida
		(int index, Cp_info *constant_pool){
	switch(constant_pool[index].tag){
		case CONSTANT_Class:
			imprimir_constant_pool_inserida(constant_pool[index].info.class_info->name_index, constant_pool);
			break;
		case CONSTANT_Fieldref:
			imprimir_constant_pool_inserida(constant_pool[index].info.fieldref_info->name_and_type_index, constant_pool);
			break;
		case CONSTANT_Methodref:
			imprimir_constant_pool_inserida(constant_pool[index].info.methodref_info->name_and_type_index,
											constant_pool);
			break;
		case CONSTANT_InterfaceMethodref:
			imprimir_constant_pool_inserida(constant_pool[index].info.interfaceMethodref_info->name_and_type_index,
											constant_pool);
			break;
		case CONSTANT_String:
			imprimir_constant_pool_inserida(constant_pool[index].info.string_info->string_index, constant_pool);
			break;
		case CONSTANT_Integer:
			printf("%d", constant_pool[index].info.integer_info->bytes);
			break;
		case CONSTANT_Float:
			printf("%f", constant_pool[index].info.float_info->bytes);
			break;
		case CONSTANT_Long:
			printf("0x%.8X", constant_pool[index].info.long_info->high_bytes);
			printf("%.8X", constant_pool[index].info.long_info->low_bytes);
			break;
		case CONSTANT_Double:
			printf("0x%.8X", constant_pool[index].info.double_info->high_bytes);
			printf("%.8X", constant_pool[index].info.double_info->low_bytes);
			break;
		case CONSTANT_NameAndType:
			imprimir_constant_pool_inserida(constant_pool[index].info.nameAndType_info->name_index, constant_pool);
			imprimir_constant_pool_inserida(constant_pool[index].info.nameAndType_info->descriptor_index, constant_pool);
			break;
		case CONSTANT_Utf8:
			printf("%s", constant_pool[index].info.utf8_info->bytes);
			break;
		case CONSTANT_MethodHandle:
			imprimir_constant_pool_inserida(constant_pool[index].info.methodHandle_info->reference_index, constant_pool);
			break;
		case CONSTANT_MethodType:
			imprimir_constant_pool_inserida(constant_pool[index].info.methodType_info->descriptor_index, constant_pool);
			break;
		case CONSTANT_InvokeDynamic:
			imprimir_constant_pool_inserida(constant_pool[index].info.invokeDynamic_info->name_and_type_index,
											constant_pool);
			break;
		default:
			printf("invalid constant pool reference\n");
	}
}


void imprimir_constant_pool_completa(ClassFile *classFile){
	u2 i, index;
	int64_t aux;
	Cp_info* constant_pool = classFile->constant_pool;
	printf("CONSTANT POOL :\n\n");
	for (i = 1; i < classFile->constant_pool_count; ++i){
		aux = 0;
		switch(constant_pool[i].tag){
			case CONSTANT_Class:
				printf("[%.2d] CONSTANT_Class_info:\n", i);
			    index = constant_pool[i].info.class_info->name_index;
				printf("     Class name:       cp_info #%d <", index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
				break;
			case CONSTANT_Fieldref:
				printf("[%.2d] CONSTANT_Fieldref_info:\n", i);
				index = constant_pool[i].info.fieldref_info->class_index;
				printf("     Class name:       cp_info #%d <", index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
				index = constant_pool[i].info.fieldref_info->name_and_type_index;
				printf("     Name and type:    cp_info #%d <", index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
				break;
			case CONSTANT_Methodref:
				printf("[%.2d] CONSTANT_Methodref_info:\n", i);
				index = constant_pool[i].info.methodref_info->class_index;
				printf("     Class name:       cp_info #%d <", index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
				index = constant_pool[i].info.methodref_info->name_and_type_index;
				printf("     Name and type:    cp_info #%d <", index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
				break;
			case CONSTANT_InterfaceMethodref:
				printf("[%.2d] CONSTANT_InterfaceMethodref_info:\n", i);
				index = constant_pool[i].info.interfaceMethodref_info->class_index;
				printf("     Class name:       cp_info #%d <", index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
				index = constant_pool[i].info.interfaceMethodref_info->name_and_type_index;
				printf("     Name and type:    cp_info #%d <", index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
				break;
			case CONSTANT_String:
				printf("[%.2d] CONSTANT_String_info:\n", i);
				index = constant_pool[i].info.string_info->string_index;
				printf("     String:           cp_info #%d <", index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
				break;
			case CONSTANT_Integer:
				printf("[%.2d] CONSTANT_Integer_info:\n", i);
				printf("     Bytes:            0x%.8X\n", constant_pool[i].info.integer_info->bytes);
				printf("     Integer:          %d\n", constant_pool[i].info.integer_info->bytes);
				break;
			case CONSTANT_Float:
				printf("[%.2d] CONSTANT_Float_info:\n", i);
				printf("     Bytes:            0x%.8X\n", constant_pool[i].info.float_info->bytes);
				printf("     Float:            %f\n", constant_pool[i].info.float_info->bytes);
				break;
			case CONSTANT_Long:
				printf("[%.2d] CONSTANT_Long_info:\n", i);
				printf("     High bytes:       0x%.8X\n", constant_pool[i].info.long_info->high_bytes);
				printf("     Low bytes:        0x%.8X\n", constant_pool[i].info.long_info->low_bytes);
			    aux |= constant_pool[i].info.long_info->high_bytes;
			    aux <<= 32;
			    aux |= constant_pool[i].info.long_info->low_bytes;
				printf("     Long:             %d\n", aux);
				printf("\n");
				printf("[%.2d] (large numeric continued)\n", ++i);
				break;
			case CONSTANT_Double:
				printf("[%.2d] CONSTANT_Double_info:\n", i);
				printf("     High bytes:       0x%.8X\n", constant_pool[i].info.double_info->high_bytes);
				printf("     Low bytes:        0x%.8X\n", constant_pool[i].info.double_info->low_bytes);
			    aux |= constant_pool[i].info.long_info->high_bytes;
			    aux <<= 32;
			    aux |= constant_pool[i].info.long_info->low_bytes;
				printf("     Double:           %lf\n", aux);
				printf("\n");
				printf("[%.2d] (large numeric continued)\n", ++i);
				break;
			case CONSTANT_NameAndType:
				printf("[%.2d] CONSTANT_NameAndType_info:\n", i);
				index = constant_pool[i].info.nameAndType_info->name_index;
				printf("     Name:             cp_info #%d <", index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
				index = constant_pool[i].info.nameAndType_info->descriptor_index;
				printf("     Descriptor:       cp_info #%d <", index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
				break;
			case CONSTANT_Utf8:
				printf("[%.2d] CONSTANT_Utf8_info:\n", i);
				printf("     Length of array:  %d\n", constant_pool[i].info.utf8_info->length);
				// TODO printar length of string corretamente
				printf("     Length of string: %d\n", constant_pool[i].info.utf8_info->length);
				printf("     String:           %s\n", constant_pool[i].info.utf8_info->bytes);
				break;
			case CONSTANT_MethodHandle:
				printf("[%.2d] CONSTANT_MethodHandle_info:\n", i);
				printf("     Reference kind:   %d\n", constant_pool[i].info.methodHandle_info->reference_kind);
				index = constant_pool[i].info.methodHandle_info->reference_index;
				printf("     Reference:        cp_info #%d <",index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
				break;
			case CONSTANT_MethodType:
				printf("[%.2d] CONSTANT_MethodType_info:\n", i);
				index = constant_pool[i].info.methodType_info->descriptor_index;
				printf("     Descriptor:       cp_info #%d <", index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
				break;
			case CONSTANT_InvokeDynamic:
				printf("[%.2d] CONSTANT_InvokeDynamic_info:\n", i);
				printf("     Bootstrap method: #%d\n", constant_pool[i].info.invokeDynamic_info->bootstrap_method_attr_index);
				index = constant_pool[i].info.invokeDynamic_info->name_and_type_index;
				printf("     Name and type:    cp_info #%d <", index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
				break;
		}
		printf("\n");
	}
}


void imprimir_interfaces(ClassFile *classFile){
	int i;
	printf("INTERFACES :\n\n");
	for (i = 0; i < classFile->interfaces_count; ++i){
		printf("[%.2d] Interface: cp_info #%d <", i, classFile->interfaces[i]);
		imprimir_constant_pool_inserida(classFile->interfaces[i], classFile->constant_pool);
		printf(">\n");
	}printf("\n");
}


void imprimir_atributos(Attribute_info *atributos, u2 contador_atributos, Cp_info *constant_pool, int tab){
	int i, j, k;
	u2 index;
	// Calcula tabs, máximo 2
	char* space = (tab == 1) ? "     " : "";
	space = (tab == 2) ? "          " : space;
	printf("%sATTRIBUTES :\n\n", space);
	for (i = 0; i < contador_atributos; ++i){
		printf("%s[%.2d] \n", space, i);
		printf("%s     Generic Info:\n", space);
		char *str = acessar_constant_pool_entry(atributos[i].attribute_name_index, constant_pool);
		printf(":\n");
		printf("%s     Attribute name:   cp_info #%d <", space, atributos[i].attribute_name_index);
		imprimir_constant_pool_inserida(atributos[i].attribute_name_index, constant_pool);
		printf(">\n");
		printf("%s     Attribute length: %d\n\n", space, atributos[i].attribute_length);

		printf("%s     Specific Info:\n", space);
		if (strcmp(str, "ConstantValue") == 0){
			index = atributos[i].info.constantValue_attribute->constantvalue_index;
			printf("%s     Constant value:   cp_info #%d <", space, index);
			imprimir_constant_pool_inserida(index, constant_pool);
			printf(">\n");
		}
		else if (strcmp(str, "Code") == 0){
			imprimir_code(constant_pool, atributos[i].info.code_attribute, space);
			printf("\n");
			imprimir_atributos(atributos[i].info.code_attribute->attributes,
							   atributos[i].info.code_attribute->attributes_count, constant_pool, tab + 1);
		}
		else if (strcmp(str, "Exceptions") == 0){
			printf("%s     Number of exceptions: %d\n", space, atributos[i].info.exceptions_attribute->number_of_exceptions);
			for (j = 0; j < atributos[i].info.exceptions_attribute->number_of_exceptions; ++j){
				index = atributos[i].info.exceptions_attribute->exception_index_table[j];
				printf("%s     [%.2d] Class:        cp_info #%d <", space, j, index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
			}
		}
		else if (strcmp(str, "InnerClasses") == 0){
			for (j = 0; j < atributos[i].info.innerClasses_attribute->number_of_classes; ++j){
				index = atributos[i].info.innerClasses_attribute->classes_ptr[j].inner_class_info_index;
				printf("%s     [%.2d] Inner class:   cp_info #%d <", space, j, index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
				index = atributos[i].info.innerClasses_attribute->classes_ptr[j].outer_class_info_index;
				printf("%s          Outer class:   cp_info #%d <", space, index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
				index = atributos[i].info.innerClasses_attribute->classes_ptr[j].inner_name_index;
				printf("%s          Inner name:    cp_info #%d <", space, index);
				imprimir_constant_pool_inserida(index, constant_pool);
				printf(">\n");
				printf("%s          Access flag:   0x%.4X", space, atributos[i].info.innerClasses_attribute->classes_ptr[j].inner_class_access_flags);
				acesso_str(atributos[i].info.innerClasses_attribute->classes_ptr[j].inner_class_access_flags);
			}
		}
		else if (strcmp(str, "EnclosingMethod") == 0){
			index = atributos[i].info.enclosingMethod_attribute->class_index;
			printf("%s     Class:            cp_info #%d <", space, index);
			imprimir_constant_pool_inserida(index, constant_pool);
			printf(">\n");
			index = atributos[i].info.enclosingMethod_attribute->method_index;
			printf("%s     Method:           cp_info #%d <", space, index);
			imprimir_constant_pool_inserida(index, constant_pool);
			printf(">\n");
		}
		else if (strcmp(str, "Synthetic") == 0){
		}
		else if (strcmp(str, "Signature") == 0){
			index = atributos[i].info.signature_attribute->signature_index;
			printf("%s     Signature:        cp_info #%d <", space, index);
			imprimir_constant_pool_inserida(index, constant_pool);
			printf(">\n");
		}
		else if (strcmp(str, "SourceFile") == 0){
			index = atributos[i].info.sourceFile_attribute->sourcefile_index;
			printf("%s     Source file name: cp_info #%d <", space, index);
			imprimir_constant_pool_inserida(index, constant_pool);
			printf(">\n");
		}
		else if (strcmp(str, "LineNumberTable") == 0){
			printf("%s     Nr.\tStart PC\tLine Number\n", space);
			for (j = 0; j < atributos[i].info.lineNumberTable_attribute->line_number_table_length; ++j){
				printf("%s     %d\t", space , j);
				printf("%d\t\t\t", atributos[i].info.lineNumberTable_attribute->line_number_table_ptr[j].start_pc);
				printf("%d", atributos[i].info.lineNumberTable_attribute->line_number_table_ptr[j].line_number);
				printf("\n");
			}
		}
		if (i != contador_atributos-1 || tab == 0) printf("\n");
	}
}

void imprimir_code(Cp_info *constant_pool, Code_attribute *codeAttribute, char *space) {
	int i;

	printf("%s     Max stack:        %d\n", space, codeAttribute->max_stack);
	printf("%s     Max locals:       %d\n", space, codeAttribute->max_locals);
	printf("%s     Code length:      %d\n", space, codeAttribute->code_length);

	for(i = 0; i < codeAttribute->code_length; i++) {
		u1 opcode = codeAttribute->code[i];
		decoder opcode_decod = decode[opcode];

		if(strcmp(opcode_decod.instruction, INSTR_TABLESWITCH) == 0) {
			i = imprimir_instr_table_switch(codeAttribute, space, i);
		} else if(strcmp(opcode_decod.instruction, INSTR_LOOKUPSWITCH) == 0) {
			i = imprimir_instr_lookupswitch(codeAttribute, space, i);
		} else {
			i = imprimir_instrucao_padrao(constant_pool, codeAttribute, space, opcode_decod, i);
		}
	}
	printf("\n");
}

int imprimir_instr_lookupswitch(const Code_attribute *codeAttribute, const char *space, int i) {
	LookupswitchData data = montar_lookupswitch_data(codeAttribute->code + i + 1, i);
	imprimir_Lookupswitch(data, space);
	i += data.totalSize;
	return i;
}

int imprimir_instr_table_switch(const Code_attribute *codeAttribute, const char *space, int i) {
	TableswitchData data = montar_switch_table(codeAttribute->code + i + 1, i);
	imprimir_switch_table(data, space);
	i += data.totalSize;
	return i;
}

int imprimir_instrucao_padrao(Cp_info *constant_pool, Code_attribute *code_attribute, char *space, decoder opcode_decod,
							  int instr_pos) {
	printf("\n%s     %d: %s", space, instr_pos, opcode_decod.instruction);
	int j;
	for(j = 0; j < opcode_decod.bytes; j++) {
		instr_pos++;
		u1 opcodeData = code_attribute->code[instr_pos];
		printf(" %d ", opcodeData);
		if(opcodeData != 0 && opcode_decod.referencesCP) {
			imprimir_constant_pool_inserida(opcodeData, constant_pool);
		}
	}

	return instr_pos;
}


void imprimir_fields(ClassFile *classFile){
	u2 i, index;
	Field_info* fields = classFile->fields;
	printf("FIELDS :\n\n");
	for (i = 0; i < classFile->fields_count; ++i){
		printf("[%.2d] Name:              cp_info #%d <", i, fields[i].name_index);
		imprimir_constant_pool_inserida(fields[i].name_index, classFile->constant_pool);
		printf(">\n");
		printf("     Descriptor:        cp_info #%d <", fields[i].descriptor_index);
		imprimir_constant_pool_inserida(fields[i].descriptor_index, classFile->constant_pool);
		printf(">\n");
		printf("     Access flags:      0x%.4X\n", fields[i].access_flags);
		if (fields[i].attributes_count > 0){
			printf("\n");
			imprimir_atributos(fields[i].attributes, fields[i].attributes_count, classFile->constant_pool, 1);
		}
		printf("\n");
	}
}


void imprimir_metodos(ClassFile *classFile){
	u2 i, index;
	Method_info* methods = classFile->methods;
	printf("METHODS :\n\n");
	for (i = 0; i < classFile->methods_count; ++i){
		printf("[%.2d] Name:              cp_info #%d <", i, methods[i].name_index);
		imprimir_constant_pool_inserida(methods[i].name_index, classFile->constant_pool);
		printf(">\n");
		printf("     Descriptor:        cp_info #%d <", methods[i].descriptor_index);
		imprimir_constant_pool_inserida(methods[i].descriptor_index, classFile->constant_pool);
		printf(">\n");
		printf("     Access flags:      0x%.4X", methods[i].access_flags);
		acesso_str(methods[i].access_flags);
		if (methods[i].attributes_count > 0){
			printf("\n");
			imprimir_atributos(methods[i].attributes, methods[i].attributes_count, classFile->constant_pool, 1);
		}
		printf("\n");
	}
}

static void limpar_buffer() {
	int c;
	while((c = getchar()) != '\n' && c != EOF);
}

void imprimir_classe(ClassFile *classFile){
	imprimir_informacoes_classe(classFile);
	limpar_buffer();
	getchar();
	imprimir_constant_pool_completa(classFile);
	getchar();
	imprimir_interfaces(classFile);
	getchar();
	imprimir_fields(classFile);
	getchar();
	imprimir_metodos(classFile);
	getchar();
	imprimir_atributos(classFile->attributes, classFile->attributes_count, classFile->constant_pool, 0);
	getchar();
}
