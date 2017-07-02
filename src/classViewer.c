#include "classViewer.h"


/**
 * [printGeneralInformation description]
 * @param classFile [description]
 */
void printGeneralInformation(ClassFile* classFile){
	printf("GENERAL INFORMATION :\n\n");
	printf("Magic:                   0x%X\n", classFile->magic);
	printf("Minor Version:           %d\n", classFile->minor_version);
	printf("Major Version:           %d\n", classFile->major_version);
	printf("Constant Pool Count:     %d\n", classFile->constant_pool_count);
	printf("Access flags:            0x%.4X\n", classFile->access_flags);
	printf("This class:              cp_info #%d\n", classFile->this_class);
	printf("Super class:             cp_info #%d\n", classFile->super_class);
	printf("Interfaces count:        %d\n", classFile->interfaces_count);
	printf("Fields count:            %d\n", classFile->fields_count);
	printf("Methods count:           %d\n", classFile->methods_count);
	printf("Attributes count:        %d\n", classFile->attributes_count);
	printf("\n");
}

/**
 * Função que imprime uma string que representa o valor de uma das constantes do Constant Pool
 * @param  index         index da constante no Constant Pool
 * @param  constant_pool ponteiro para um Constant Pool
 * @return               ponteiro para uma string
 */
void printConstantPoolEntry(int index, Cp_info* constant_pool){
	switch(constant_pool[index].tag){
		case CONSTANT_Class:
			printConstantPoolEntry(constant_pool[index].info.class_info->name_index, constant_pool);
			break;
		case CONSTANT_Fieldref:
			printConstantPoolEntry(constant_pool[index].info.fieldref_info->name_and_type_index, constant_pool);
			break;
		case CONSTANT_Methodref:
			printConstantPoolEntry(constant_pool[index].info.methodref_info->name_and_type_index, constant_pool);
			break;
		case CONSTANT_InterfaceMethodref:
			printConstantPoolEntry(constant_pool[index].info.interfaceMethodref_info->name_and_type_index, constant_pool);
			break;
		case CONSTANT_String:
			printConstantPoolEntry(constant_pool[index].info.string_info->string_index, constant_pool);
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
			printConstantPoolEntry(constant_pool[index].info.nameAndType_info->name_index, constant_pool);
			printConstantPoolEntry(constant_pool[index].info.nameAndType_info->descriptor_index, constant_pool);
			break;
		case CONSTANT_Utf8:
			printf("%s", constant_pool[index].info.utf8_info->bytes);
			break;
		case CONSTANT_MethodHandle:
			printConstantPoolEntry(constant_pool[index].info.methodHandle_info->reference_index, constant_pool);
			break;
		case CONSTANT_MethodType:
			printConstantPoolEntry(constant_pool[index].info.methodType_info->descriptor_index, constant_pool);
			break;
		case CONSTANT_InvokeDynamic:
			printConstantPoolEntry(constant_pool[index].info.invokeDynamic_info->name_and_type_index, constant_pool);
			break;
		default:
			printf("invalid constant pool reference\n");
	}
}

/**
 * [printConstantPool description]
 * @param classFile [description]
 */
void printConstantPool(ClassFile* classFile){
	uint16_t i, index;
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
				printConstantPoolEntry(index, constant_pool);
				printf(">\n");
				break;
			case CONSTANT_Fieldref:
				printf("[%.2d] CONSTANT_Fieldref_info:\n", i);
				index = constant_pool[i].info.fieldref_info->class_index;
				printf("     Class name:       cp_info #%d <", index);
				printConstantPoolEntry(index, constant_pool);
				printf(">\n");
				index = constant_pool[i].info.fieldref_info->name_and_type_index;
				printf("     Name and type:    cp_info #%d <", index);
				printConstantPoolEntry(index , constant_pool);
				printf(">\n");
				break;
			case CONSTANT_Methodref:
				printf("[%.2d] CONSTANT_Methodref_info:\n", i);
				index = constant_pool[i].info.methodref_info->class_index;
				printf("     Class name:       cp_info #%d <", index);
				printConstantPoolEntry(index, constant_pool);
				printf(">\n");
				index = constant_pool[i].info.methodref_info->name_and_type_index;
				printf("     Name and type:    cp_info #%d <", index);
				printConstantPoolEntry(index, constant_pool);
				printf(">\n");
				break;
			case CONSTANT_InterfaceMethodref:
				printf("[%.2d] CONSTANT_InterfaceMethodref_info:\n", i);
				index = constant_pool[i].info.interfaceMethodref_info->class_index;
				printf("     Class name:       cp_info #%d <", index);
				printConstantPoolEntry(index, constant_pool);
				printf(">\n");
				index = constant_pool[i].info.interfaceMethodref_info->name_and_type_index;
				printf("     Name and type:    cp_info #%d <", index);
				printConstantPoolEntry(index, constant_pool);
				printf(">\n");
				break;
			case CONSTANT_String:
				printf("[%.2d] CONSTANT_String_info:\n", i);
				index = constant_pool[i].info.string_info->string_index;
				printf("     String:           cp_info #%d <", index);
				printConstantPoolEntry(index, constant_pool);
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
				printConstantPoolEntry(index, constant_pool);
				printf(">\n");
				index = constant_pool[i].info.nameAndType_info->descriptor_index;
				printf("     Descriptor:       cp_info #%d <", index);
				printConstantPoolEntry(index, constant_pool);
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
				printConstantPoolEntry(index, constant_pool);
				printf(">\n");
				break;
			case CONSTANT_MethodType:
				printf("[%.2d] CONSTANT_MethodType_info:\n", i);
				index = constant_pool[i].info.methodType_info->descriptor_index;
				printf("     Descriptor:       cp_info #%d <", index);
				printConstantPoolEntry(index, constant_pool);
				printf(">\n");
				break;
			case CONSTANT_InvokeDynamic:
				printf("[%.2d] CONSTANT_InvokeDynamic_info:\n", i);
				printf("     Bootstrap method: #%d\n", constant_pool[i].info.invokeDynamic_info->bootstrap_method_attr_index);
				index = constant_pool[i].info.invokeDynamic_info->name_and_type_index;
				printf("     Name and type:    cp_info #%d <", index);
				printConstantPoolEntry(index, constant_pool);
				printf(">\n");
				break;
		}
		printf("\n");
	}
}

/**
 * [printInterfaces description]
 * @param classFile [description]
 */
void printInterfaces(ClassFile* classFile){
	int i;
	printf("INTERFACES :\n\n");
	for (i = 0; i < classFile->interfaces_count; ++i){
		printf("[%.2d] Interface: cp_info #%d <", i, classFile->interfaces[i]);
		printConstantPoolEntry(classFile->interfaces[i], classFile->constant_pool);
		printf(">\n");
	}printf("\n");
}

/**
 * WARNING: GAMBIARRA PARA DAR OS TABS CORRETOS (QUANDO UM ATRIBUTO ESTA DENTRO DO OUTRO)
 * 			POR ISSO QUE TEM UM %s NA FRENTE DE TODOS OS PRINTS
 * @param attributes       [description]
 * @param attributes_count [description]
 * @param constant_pool    [description]
 * @param tab              quantidade de tabs que devem ser dados
 */
void printAttributes(Attribute_info* attributes, uint16_t attributes_count, Cp_info* constant_pool, int tab){
	int i, j, k;
	uint16_t index;
	// Calcula tabs, máximo 2
	char* space = (tab == 1) ? "     " : "";
	space = (tab == 2) ? "          " : space;
	printf("%sATTRIBUTES :\n\n", space);
	for (i = 0; i < attributes_count; ++i){
		printf("%s[%.2d] ", space, i);
		char *str = accessConstantPoolEntry(attributes[i].attribute_name_index, constant_pool);
		printf(":\n");
		printf("%s     Attribute name:   cp_info #%d <", space, attributes[i].attribute_name_index);
		printConstantPoolEntry(attributes[i].attribute_name_index, constant_pool);
		printf(">\n");
		printf("%s     Attribute length: %d\n", space, attributes[i].attribute_length);

		if (strcmp(str, "ConstantValue") == 0){
			index = attributes[i].info.constantValue_attribute->constantvalue_index;
			printf("%s     Constant value:   cp_info #%d <", space, index);
			printConstantPoolEntry(index, constant_pool);
			printf(">\n");
		}
		else if (strcmp(str, "Code") == 0){
			printCode(constant_pool, attributes[i].info.code_attribute, space);
			printf("\n");
			printAttributes(attributes[i].info.code_attribute->attributes, attributes[i].info.code_attribute->attributes_count, constant_pool, tab+1);
		}
		else if (strcmp(str, "Exceptions") == 0){
			printf("%s     Number of exceptions: %d\n", space, attributes[i].info.exceptions_attribute->number_of_exceptions);
			for (j = 0; j < attributes[i].info.exceptions_attribute->number_of_exceptions; ++j){
				index = attributes[i].info.exceptions_attribute->exception_index_table[j];
				printf("%s     [%.2d] Class:        cp_info #%d <", space, j, index);
				printConstantPoolEntry(index, constant_pool);
				printf(">\n");
			}
		}
		else if (strcmp(str, "InnerClasses") == 0){
			for (j = 0; j < attributes[i].info.innerClasses_attribute->number_of_classes; ++j){
				index = attributes[i].info.innerClasses_attribute->classes_ptr[j].inner_class_info_index;
				printf("%s     [%.2d] Inner class:   cp_info #%d <", space, j, index);
				printConstantPoolEntry(index, constant_pool);
				printf(">\n");
				index = attributes[i].info.innerClasses_attribute->classes_ptr[j].outer_class_info_index;
				printf("%s          Outer class:   cp_info #%d <", space, index);
				printConstantPoolEntry(index, constant_pool);
				printf(">\n");
				index = attributes[i].info.innerClasses_attribute->classes_ptr[j].inner_name_index;
				printf("%s          Inner name:    cp_info #%d <", space, index);
				printConstantPoolEntry(index, constant_pool);
				printf(">\n");
				printf("%s          Access flag:   0x%.4X\n", space, attributes[i].info.innerClasses_attribute->classes_ptr[j].inner_class_access_flags);
			}
		}
		else if (strcmp(str, "EnclosingMethod") == 0){
			index = attributes[i].info.enclosingMethod_attribute->class_index;
			printf("%s     Class:            cp_info #%d <", space, index);
			printConstantPoolEntry(index, constant_pool);
			printf(">\n");
			index = attributes[i].info.enclosingMethod_attribute->method_index;
			printf("%s     Method:           cp_info #%d <", space, index);
			printConstantPoolEntry(index, constant_pool);
			printf(">\n");
		}
		else if (strcmp(str, "Synthetic") == 0){
		}
		else if (strcmp(str, "Signature") == 0){
			index = attributes[i].info.signature_attribute->signature_index;
			printf("%s     Signature:        cp_info #%d <", space, index);
			printConstantPoolEntry(index, constant_pool);
			printf(">\n");
		}
		else if (strcmp(str, "SourceFile") == 0){
			index = attributes[i].info.sourceFile_attribute->sourcefile_index;
			printf("%s     Source file name: cp_info #%d <", space, index);
			printConstantPoolEntry(index, constant_pool);
			printf(">\n");
		}
		else if (strcmp(str, "LineNumberTable") == 0){
			printf("%s     Nr.\tStart PC\tLine Number\n", space);
			for (j = 0; j < attributes[i].info.lineNumberTable_attribute->line_number_table_length; ++j){
				printf("%s     %d\t", space , j);
				printf("%d\t\t\t", attributes[i].info.lineNumberTable_attribute->line_number_table_ptr[j].start_pc);
				printf("%d", attributes[i].info.lineNumberTable_attribute->line_number_table_ptr[j].line_number);
				printf("\n");
			}
		}
		else if (strcmp(str, "LocalVariableTable") == 0){
			// attributes[i].info.localVariableTable_attribute->local_variable_table_length = readBytes(2, fp);
			// attributes[i].info.localVariableTable_attribute->local_variable_table_ptr = (local_variable_table*)malloc(attributes[i].info.localVariableTable_attribute->local_variable_table_length*sizeof(local_variable_table));
			// for (j = 0; j < attributes[i].info.localVariableTable_attribute->local_variable_table_length; ++j){
			//     attributes[i].info.localVariableTable_attribute->local_variable_table_ptr[j].start_pc = readBytes(2, fp);
			//     attributes[i].info.localVariableTable_attribute->local_variable_table_ptr[j].length = readBytes(2, fp);
			//     attributes[i].info.localVariableTable_attribute->local_variable_table_ptr[j].name_index = readBytes(2, fp);
			//     attributes[i].info.localVariableTable_attribute->local_variable_table_ptr[j].descriptor_index = readBytes(2, fp);
			//     attributes[i].info.localVariableTable_attribute->local_variable_table_ptr[j].index = readBytes(2, fp);
			// }
		}
		else if (strcmp(str, "LocalVariableTypeTable") == 0){
			// attributes[i].info.localVariableTypeTable_attribute->local_variable_type_table_length = readBytes(2, fp);
			// attributes[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr = (local_variable_type_table*)malloc(attributes[i].info.localVariableTypeTable_attribute->local_variable_type_table_length*sizeof(local_variable_type_table));
			// for (j = 0; j < attributes[i].info.localVariableTypeTable_attribute->local_variable_type_table_length; ++j){
			//     attributes[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr[j].start_pc = readBytes(2, fp);
			//     attributes[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr[j].length = readBytes(2, fp);
			//     attributes[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr[j].name_index = readBytes(2, fp);
			//     attributes[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr[j].signature_index = readBytes(2, fp);
			//     attributes[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr[j].index = readBytes(2, fp);
			// }
		}
		else if (strcmp(str, "Deprecated") == 0){
		}
		else if (strcmp(str, "BootstrapMethods") == 0){
			// attributes[i].info.bootstrapMethods_attribute->num_bootstrap_methods = readBytes(2, fp);
			// attributes[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr = (bootstrap_methods*)malloc(attributes[i].info.bootstrapMethods_attribute->num_bootstrap_methods*sizeof(bootstrap_methods));
			// for (j = 0; j < attributes[i].info.bootstrapMethods_attribute->num_bootstrap_methods; ++j){
			//     attributes[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].bootstrap_method_ref = readBytes(2, fp);
			//     attributes[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].num_bootstrap_arguments = readBytes(2, fp);
			//     attributes[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].bootstrap_arguments = (uint16_t*)malloc(attributes[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].num_bootstrap_arguments*sizeof(uint16_t));
			// 	for (k = 0; k < attributes[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].num_bootstrap_arguments; ++k){
			// 		attributes[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].bootstrap_arguments[k] = readBytes(2, fp);
			// 	}
			// }
		}
		if (i != attributes_count-1 || tab == 0) printf("\n");
	}
}

void printCode(Cp_info* constant_pool, Code_attribute* codeAttribute, char* space) {
	int i;

	printf("%s     Max stack:        %d\n", space, codeAttribute->max_stack);
	printf("%s     Max locals:       %d\n", space, codeAttribute->max_locals);
	printf("%s     Code length:      %d\n", space, codeAttribute->code_length);

	for(i = 0; i < codeAttribute->code_length; i++) {
		uint8_t opcode = codeAttribute->code[i];
		Mapper opcodeMapper = mapper[opcode];

		if(strcmp(opcodeMapper.instruction, INSTR_TABLESWITCH) == 0) {
			TableswitchData data = makeTableswitchData(codeAttribute->code + i + 1, i);
			printTableswitch(data, space);
			i += data.totalSize;
		}
		else if(strcmp(opcodeMapper.instruction, INSTR_LOOKUPSWITCH) == 0) {
			LookupswitchData data = makeLookupswitchData(codeAttribute->code + i + 1, i);
			printLookupswitch(data, space);
			i += data.totalSize;
		}
		else {
			i = printDefaultInstruction(constant_pool, codeAttribute, space, opcodeMapper, i);
		}
	}
	printf("\n");
}

int printDefaultInstruction(Cp_info *constant_pool, Code_attribute *codeAttribute, char *space, Mapper opcodeMapper, int instrPos) {
	printf("\n%s     %d: %s", space, instrPos, opcodeMapper.instruction);
	int j;
	for(j = 0; j < opcodeMapper.bytes; j++) {
		instrPos++;
		uint8_t opcodeData = codeAttribute->code[instrPos];
		printf(" %d ", opcodeData);
		if(opcodeData != 0 && opcodeMapper.referencesCP) {
			printConstantPoolEntry(opcodeData, constant_pool);
		}
	}

	return instrPos;
}

/**
 * [printFields description]
 * @param classFile [description]
 */
void printFields(ClassFile* classFile){
	uint16_t i, index;
	Field_info* fields = classFile->fields;
	printf("FIELDS :\n\n");
	for (i = 0; i < classFile->fields_count; ++i){
		printf("[%.2d] Name:              cp_info #%d <", i, fields[i].name_index);
		printConstantPoolEntry(fields[i].name_index, classFile->constant_pool);
		printf(">\n");
		printf("     Descriptor:        cp_info #%d <", fields[i].descriptor_index);
		printConstantPoolEntry(fields[i].descriptor_index, classFile->constant_pool);
		printf(">\n");
		printf("     Access flags:      0x%.4X\n", fields[i].access_flags);
		if (fields[i].attributes_count > 0){
			printf("\n");
			printAttributes(fields[i].attributes, fields[i].attributes_count, classFile->constant_pool, 1);
		}
		printf("\n");
	}
}

/**
 * [printMethods description]
 * @param classFile [description]
 */
void printMethods(ClassFile* classFile){
	uint16_t i, index;
	Method_info* methods = classFile->methods;
	printf("METHODS :\n\n");
	for (i = 0; i < classFile->methods_count; ++i){
		printf("[%.2d] Name:              cp_info #%d <", i, methods[i].name_index);
		printConstantPoolEntry(methods[i].name_index, classFile->constant_pool);
		printf(">\n");
		printf("     Descriptor:        cp_info #%d <", methods[i].descriptor_index);
		printConstantPoolEntry(methods[i].descriptor_index, classFile->constant_pool);
		printf(">\n");
		printf("     Access flags:      0x%.4X\n", methods[i].access_flags);
		if (methods[i].attributes_count > 0){
			printf("\n");
			printAttributes(methods[i].attributes, methods[i].attributes_count, classFile->constant_pool, 1);
		}
		printf("\n");
	}
}

/**
 * Função que realiza os prints de acordo com cada item do Byte code Viewer
 * @param classFile [description]
 */
void printClass(ClassFile* classFile){
	printGeneralInformation(classFile);
	printConstantPool(classFile);
	printInterfaces(classFile);
	printFields(classFile);
	printMethods(classFile);
	printAttributes(classFile->attributes, classFile->attributes_count, classFile->constant_pool, 0);
}
