#include "classLoader.h"
#include "classList.h"
#include "methodArea.h"
#include "instructions.h"
#include "frame.h"
#include "array.h"
#include "objectManager.h"

/**
 * Função para leitura byte a byte do arquivo fp
 * @param  size quantidade de bytes a serem lidos
 * @param  fp   ponteiro para o arquivo
 * @return      Os 4 últimos bytes lidos (variável dde 32 bits)
 */
uint32_t readBytes(int size, FILE* fp){
	uint32_t result = 0;
	int i;
	for (i = 0; i < size; ++i){
		result <<= 8;
		result += getc(fp);
	}
	return result;
}

/**
 * Função que retorna uma string que representa o valor de uma das constantes do Constant Pool
 * @param  index         index da constante no Constant Pool
 * @param  constant_pool ponteiro para um Constant Pool
 * @return               ponteiro para uma string
 */
uint8_t* accessConstantPoolEntry(int index, Cp_info* constant_pool){
	switch(constant_pool[index].tag){
		case CONSTANT_Class:
			return accessConstantPoolEntry(constant_pool[index].info.class_info->name_index, constant_pool);
		case CONSTANT_Fieldref:
			return accessConstantPoolEntry(constant_pool[index].info.fieldref_info->name_and_type_index, constant_pool);
		case CONSTANT_Methodref:
			return accessConstantPoolEntry(constant_pool[index].info.methodref_info->name_and_type_index, constant_pool);
		case CONSTANT_InterfaceMethodref:
			return accessConstantPoolEntry(constant_pool[index].info.interfaceMethodref_info->name_and_type_index, constant_pool);
		case CONSTANT_String:
			return accessConstantPoolEntry(constant_pool[index].info.string_info->string_index, constant_pool);
		case CONSTANT_NameAndType:
			accessConstantPoolEntry(constant_pool[index].info.nameAndType_info->name_index, constant_pool);
			return accessConstantPoolEntry(constant_pool[index].info.nameAndType_info->descriptor_index, constant_pool);
		case CONSTANT_Utf8:
			return constant_pool[index].info.utf8_info->bytes; //Alem de imprimir retorna no caso de ser string
		case CONSTANT_MethodHandle:
			return accessConstantPoolEntry(constant_pool[index].info.methodHandle_info->reference_index, constant_pool);
		case CONSTANT_MethodType:
			return accessConstantPoolEntry(constant_pool[index].info.methodType_info->descriptor_index, constant_pool);
		case CONSTANT_InvokeDynamic:
			return accessConstantPoolEntry(constant_pool[index].info.invokeDynamic_info->name_and_type_index, constant_pool);
		default:
			return "invalid constant pool reference";
	}
}


/**
 * Lê atributos no arquivo .class. É utilizado na função de leitura de outras estruturas, o readFields, readMethods e loadClass
 * @param  length        Quantidade de atributos
 * @param  constant_pool Ponteiro para o Constant Poll
 * @param  fp            Ponteiro para o arquivo, que deve estar apontando para onde começam os atributos
 * @return               Estrutura de atributos
 */
Attribute_info* readAttributes(int length, Cp_info* constant_pool, FILE* fp){
	int i, j, k;
	Attribute_info* result = (Attribute_info*)malloc(length*sizeof(Attribute_info));
	for (i = 0; i < length; ++i){
		result[i].attribute_name_index = readBytes(2, fp);
		result[i].attribute_length = readBytes(4, fp);
		char* str = (constant_pool[result[i].attribute_name_index]).info.utf8_info->bytes;
		if (strcmp(str, "ConstantValue") == 0){
			result[i].info.constantValue_attribute = (ConstantValue_attribute*)malloc(sizeof(ConstantValue_attribute));
    		result[i].info.constantValue_attribute->constantvalue_index = readBytes(2, fp);
		}
		else if (strcmp(str, "Code") == 0){
			result[i].info.code_attribute = (Code_attribute*)malloc(sizeof(Code_attribute));
			result[i].info.code_attribute->max_stack = readBytes(2, fp);
			result[i].info.code_attribute->max_locals = readBytes(2, fp);
			result[i].info.code_attribute->code_length = readBytes(4, fp);
			result[i].info.code_attribute->code = (uint8_t*)malloc(result[i].info.code_attribute->code_length*sizeof(uint8_t));
			for (j = 0; j < result[i].info.code_attribute->code_length; ++j){
				result[i].info.code_attribute->code[j] = readBytes(1, fp);
			}
			result[i].info.code_attribute->exception_table_length = readBytes(2, fp);
			result[i].info.code_attribute->exception_table_ptr = (exception_table*)malloc(result[i].info.code_attribute->exception_table_length*sizeof(exception_table));
			for (j = 0; j < result[i].info.code_attribute->exception_table_length; ++j){
			    result[i].info.code_attribute->exception_table_ptr[j].start_pc = readBytes(2, fp);
			    result[i].info.code_attribute->exception_table_ptr[j].end_pc = readBytes(2, fp);
			    result[i].info.code_attribute->exception_table_ptr[j].handler_pc = readBytes(2, fp);
			    result[i].info.code_attribute->exception_table_ptr[j].catch_type = readBytes(2, fp);
			}
			result[i].info.code_attribute->attributes_count = readBytes(2, fp);
			result[i].info.code_attribute->attributes = readAttributes(result[i].info.code_attribute->attributes_count, constant_pool, fp);
		}
		else if (strcmp(str, "Exceptions") == 0){
			result[i].info.exceptions_attribute = (Exceptions_attribute*)malloc(sizeof(Exceptions_attribute));
			result[i].info.exceptions_attribute->number_of_exceptions = readBytes(2, fp);
			result[i].info.exceptions_attribute->exception_index_table = (uint16_t*)malloc(result[i].info.exceptions_attribute->number_of_exceptions*sizeof(uint16_t));
			for (j = 0; j < result[i].info.exceptions_attribute->number_of_exceptions; ++j){
				result[i].info.exceptions_attribute->exception_index_table[j] = readBytes(2, fp);
			}
		}
		else if (strcmp(str, "InnerClasses") == 0){
			result[i].info.innerClasses_attribute = (InnerClasses_attribute*)malloc(sizeof(InnerClasses_attribute));
			result[i].info.innerClasses_attribute->number_of_classes = readBytes(2, fp);
			result[i].info.innerClasses_attribute->classes_ptr = (Classes*)malloc(result[i].info.innerClasses_attribute->number_of_classes*sizeof(Classes));
			for (j = 0; j < result[i].info.innerClasses_attribute->number_of_classes; ++j){
			    result[i].info.innerClasses_attribute->classes_ptr[j].inner_class_info_index = readBytes(2, fp);
			    result[i].info.innerClasses_attribute->classes_ptr[j].outer_class_info_index = readBytes(2, fp);
			    result[i].info.innerClasses_attribute->classes_ptr[j].inner_name_index = readBytes(2, fp);
			    result[i].info.innerClasses_attribute->classes_ptr[j].inner_class_access_flags = readBytes(2, fp);
			}
		}
		else if (strcmp(str, "EnclosingMethod") == 0){
			result[i].info.enclosingMethod_attribute = (EnclosingMethod_attribute*)malloc(sizeof(EnclosingMethod_attribute));
   			result[i].info.enclosingMethod_attribute->class_index = readBytes(2, fp);
   			result[i].info.enclosingMethod_attribute->method_index = readBytes(2, fp);
		}
		else if (strcmp(str, "Synthetic") == 0){
			result[i].info.synthetic_attribute = (Synthetic_attribute*)malloc(sizeof(Synthetic_attribute));
		}
		else if (strcmp(str, "Signature") == 0){
			result[i].info.signature_attribute = (Signature_attribute*)malloc(sizeof(Signature_attribute));
			result[i].info.signature_attribute->signature_index = readBytes(2, fp);
		}
		else if (strcmp(str, "SourceFile") == 0){
			result[i].info.sourceFile_attribute = (SourceFile_attribute*)malloc(sizeof(SourceFile_attribute));
			result[i].info.sourceFile_attribute->sourcefile_index = readBytes(2, fp);
		}
		else if (strcmp(str, "SourceDebugExtension") == 0){
			result[i].info.sourceDebugExtension_attribute = (SourceDebugExtension_attribute*)malloc(sizeof(SourceDebugExtension_attribute));
			readBytes(result[i].attribute_length, fp);
		}
		else if (strcmp(str, "LineNumberTable") == 0){
			result[i].info.lineNumberTable_attribute = (LineNumberTable_attribute*)malloc(sizeof(LineNumberTable_attribute));
			result[i].info.lineNumberTable_attribute->line_number_table_length = readBytes(2, fp);
			result[i].info.lineNumberTable_attribute->line_number_table_ptr = (line_number_table*)malloc(result[i].info.lineNumberTable_attribute->line_number_table_length*sizeof(line_number_table));
			for (j = 0; j < result[i].info.lineNumberTable_attribute->line_number_table_length; ++j){
			    result[i].info.lineNumberTable_attribute->line_number_table_ptr[j].start_pc = readBytes(2, fp);
			    result[i].info.lineNumberTable_attribute->line_number_table_ptr[j].line_number = readBytes(2, fp);
			}
		}
		else if (strcmp(str, "LocalVariableTable") == 0){
			result[i].info.localVariableTable_attribute = (LocalVariableTable_attribute*)malloc(sizeof(LocalVariableTable_attribute));
			result[i].info.localVariableTable_attribute->local_variable_table_length = readBytes(2, fp);
			result[i].info.localVariableTable_attribute->local_variable_table_ptr = (local_variable_table*)malloc(result[i].info.localVariableTable_attribute->local_variable_table_length*sizeof(local_variable_table));
			for (j = 0; j < result[i].info.localVariableTable_attribute->local_variable_table_length; ++j){
			    result[i].info.localVariableTable_attribute->local_variable_table_ptr[j].start_pc = readBytes(2, fp);
			    result[i].info.localVariableTable_attribute->local_variable_table_ptr[j].length = readBytes(2, fp);
			    result[i].info.localVariableTable_attribute->local_variable_table_ptr[j].name_index = readBytes(2, fp);
			    result[i].info.localVariableTable_attribute->local_variable_table_ptr[j].descriptor_index = readBytes(2, fp);
			    result[i].info.localVariableTable_attribute->local_variable_table_ptr[j].index = readBytes(2, fp);
			}
		}
		else if (strcmp(str, "LocalVariableTypeTable") == 0){
			result[i].info.localVariableTypeTable_attribute = (LocalVariableTypeTable_attribute*)malloc(sizeof(LocalVariableTypeTable_attribute));
			result[i].info.localVariableTypeTable_attribute->local_variable_type_table_length = readBytes(2, fp);
			result[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr = (local_variable_type_table*)malloc(result[i].info.localVariableTypeTable_attribute->local_variable_type_table_length*sizeof(local_variable_type_table));
			for (j = 0; j < result[i].info.localVariableTypeTable_attribute->local_variable_type_table_length; ++j){
			    result[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr[j].start_pc = readBytes(2, fp);
			    result[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr[j].length = readBytes(2, fp);
			    result[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr[j].name_index = readBytes(2, fp);
			    result[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr[j].signature_index = readBytes(2, fp);
			    result[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr[j].index = readBytes(2, fp);
			}
		}
		else if (strcmp(str, "Deprecated") == 0){
			result[i].info.deprecated_attribute = (Deprecated_attribute*)malloc(sizeof(Deprecated_attribute));
		}
		else if (strcmp(str, "BootstrapMethods") == 0){
			result[i].info.bootstrapMethods_attribute = (BootstrapMethods_attribute*)malloc(sizeof(BootstrapMethods_attribute));
			result[i].info.bootstrapMethods_attribute->num_bootstrap_methods = readBytes(2, fp);
			result[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr = (bootstrap_methods*)malloc(result[i].info.bootstrapMethods_attribute->num_bootstrap_methods*sizeof(bootstrap_methods));
			for (j = 0; j < result[i].info.bootstrapMethods_attribute->num_bootstrap_methods; ++j){
			    result[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].bootstrap_method_ref = readBytes(2, fp);
			    result[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].num_bootstrap_arguments = readBytes(2, fp);
			    result[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].bootstrap_arguments = (uint16_t*)malloc(result[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].num_bootstrap_arguments*sizeof(uint16_t));
				for (k = 0; k < result[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].num_bootstrap_arguments; ++k){
					result[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].bootstrap_arguments[k] = readBytes(2, fp);
				}
			}
		}
		else{
			readBytes(result[i].attribute_length, fp);
		}
	}
	return result;
}

/**
 * Lê o Pool de constantes no arquivo .class.
 * @param  length Quantidade de contantes
 * @param  fp     Ponteiro para o arquivo, que deve estar apontando para onde começa o pool de constantes
 * @return        Referência para uma estrutura Pool de Constantes
 */
Cp_info* readConstantPool(int length, FILE* fp){
	int i, j;
	Cp_info* result = (Cp_info*)malloc(length*sizeof(Cp_info));
	for (i = 1; i < length; ++i){
		result[i].tag = readBytes(1, fp);
		switch(result[i].tag){
			case CONSTANT_Class:
				result[i].info.class_info = (Class_info*)malloc(sizeof(Class_info));
				result[i].info.class_info->name_index = readBytes(2, fp);
				break;
			case CONSTANT_Fieldref:
				result[i].info.fieldref_info = (Fieldref_info*)malloc(sizeof(Fieldref_info));
				result[i].info.fieldref_info->class_index = readBytes(2, fp);
				result[i].info.fieldref_info->name_and_type_index = readBytes(2, fp);
				break;
			case CONSTANT_Methodref:
				result[i].info.methodref_info = (Methodref_info*)malloc(sizeof(Methodref_info));
				result[i].info.methodref_info->class_index = readBytes(2, fp);
				result[i].info.methodref_info->name_and_type_index = readBytes(2, fp);
				break;
			case CONSTANT_InterfaceMethodref:
				result[i].info.interfaceMethodref_info = (InterfaceMethodref_info*)malloc(sizeof(InterfaceMethodref_info));
				result[i].info.interfaceMethodref_info->class_index = readBytes(2, fp);
				result[i].info.interfaceMethodref_info->name_and_type_index =readBytes(2, fp);
				break;
			case CONSTANT_String:
				result[i].info.string_info = (String_info*)malloc(sizeof(String_info));
				result[i].info.string_info->string_index = readBytes(2, fp);
				break;
			case CONSTANT_Integer:
				result[i].info.integer_info = (Integer_info*)malloc(sizeof(Integer_info));
				result[i].info.integer_info->bytes = readBytes(4, fp);
				break;
			case CONSTANT_Float:
				result[i].info.float_info = (Float_info*)malloc(sizeof(Float_info));
				result[i].info.float_info->bytes = readBytes(4, fp);
				break;
			case CONSTANT_Long:
				result[i].info.long_info = (Long_info*)malloc(sizeof(Long_info));
				result[i].info.long_info->high_bytes = readBytes(4, fp);
				result[i].info.long_info->low_bytes = readBytes(4, fp);
				i++;
				break;
			case CONSTANT_Double:
				result[i].info.double_info = (Double_info*)malloc(sizeof(Double_info));
				result[i].info.double_info->high_bytes = readBytes(4, fp);
				result[i].info.double_info->low_bytes = readBytes(4, fp);
				i++;
				break;
			case CONSTANT_NameAndType:
				result[i].info.nameAndType_info = (NameAndType_info*)malloc(sizeof(NameAndType_info));
				result[i].info.nameAndType_info->name_index = readBytes(2, fp);
				result[i].info.nameAndType_info->descriptor_index = readBytes(2, fp);
				break;
			case CONSTANT_Utf8:
				result[i].info.utf8_info = (Utf8_info*)malloc(sizeof(Utf8_info));
				result[i].info.utf8_info->length = readBytes(2, fp);
				result[i].info.utf8_info->bytes = (uint8_t*)malloc((result[i].info.utf8_info->length+1)*sizeof(uint8_t));
				for (j = 0; j < result[i].info.utf8_info->length; ++j){
					result[i].info.utf8_info->bytes[j] = readBytes(1, fp);
				}
				result[i].info.utf8_info->bytes[j] = 0; // Concatenar esse zero pode dar ruim? facilita bastante o print
				                                        // No arquivo de .class esse zero não existe
				break;
			case CONSTANT_MethodHandle:
				result[i].info.methodHandle_info = (MethodHandle_info*)malloc(sizeof(MethodHandle_info));
				result[i].info.methodHandle_info->reference_kind = readBytes(1, fp);
				result[i].info.methodHandle_info->reference_index = readBytes(2, fp);
				break;
			case CONSTANT_MethodType:
				result[i].info.methodType_info = (MethodType_info*)malloc(sizeof(MethodType_info));
				result[i].info.methodType_info->descriptor_index = readBytes(2, fp);
				break;
			case CONSTANT_InvokeDynamic:
				result[i].info.invokeDynamic_info = (InvokeDynamic_info*)malloc(sizeof(InvokeDynamic_info));
				result[i].info.invokeDynamic_info->bootstrap_method_attr_index = readBytes(2, fp);
				result[i].info.invokeDynamic_info->name_and_type_index = readBytes(2, fp);
				break;
			default:
				break;
		}
	}
	return result;
}

/**
 * Lê do arquivo .class os indices do contant pool que representam as interfaces da classe.
 * @param  length Quantidade de interfaces
 * @param  fp     Ponteiro para o arquivo, que deve estar apontando para onde começam os indices
 * @return        Referência para um vetor de indices do constant pool
 */
uint16_t* readInterfaces(int length, FILE* fp){
	int i;
	uint16_t* result = (uint16_t*)malloc(length*sizeof(uint16_t));
	for (i = 0; i < length; ++i){
		result[i] = readBytes(2, fp);
	}
	return result;
}

/**
 * Lê os fields de um arquivo .class.
 * @param  length        Quantidade de Fields
 * @param  constant_pool Referência para o constant pool da class que esta sendo lida
 * @param  fp            Ponteiro para o arquivo, que deve estar apontando para onde começam os fields
 * @return               Referência para um vetor de estruturas dos fields
 */
Field_info* readFields(int length, Cp_info* constant_pool, FILE* fp){
	int i;
	Field_info* result = (Field_info*)malloc(length*sizeof(Field_info));
	for (i = 0; i < length; ++i){
		result[i].access_flags = readBytes(2, fp);
		result[i].name_index = readBytes(2, fp);
		result[i].descriptor_index = readBytes(2, fp);
		result[i].attributes_count = readBytes(2, fp);
		result[i].attributes = readAttributes(result[i].attributes_count, constant_pool, fp);
	}
	return result;
}

/**
 * Lê os métodos de um arquivo .class.
 * @param  length        Quantidade de métodos
 * @param  constant_pool Referência para o constant pool da class que esta sendo lida
 * @param  fp            Ponteiro para o arquivo, que deve estar apontando para onde começam os métodos
 * @return               Referência para um vetor de estruturas dos métodos
 */
Method_info* readMethods(int length, Cp_info* constant_pool, FILE* fp){
	int i;
	Method_info* result = (Method_info*)malloc(length*sizeof(Method_info));
	for (i = 0; i < length; ++i){
		result[i].access_flags = readBytes(2, fp);
		result[i].name_index = readBytes(2, fp);
		result[i].descriptor_index = readBytes(2, fp);
		result[i].attributes_count = readBytes(2, fp);
		result[i].attributes = readAttributes(result[i].attributes_count, constant_pool, fp);
	}
	return result;
}

/**
 * Função principal que chama todas as outras funções de leitura para ler o .class inteiro
 * Caso o .class solicitado já foi carregado anteriormente, retorna uma referência para a estrutura já carregada
 * @param  className Nome da classe a ser lida
 * @return           Referência para uma struct ClassFile
 */
ClassFile* loadClass(char* className){
	// Veifica se o arquivo ja foi carregado alguma vez
	ClassFile* classFile = buscar_classe(className);
	if (classFile != NULL)	return classFile;

	// Concatena o .class no final do nome
	char name[80];
	strcpy(name, className);
	strcat(name, ".class");

	// Abre o arquivo
	FILE* fp = NULL;
	fp = fopen(name, "rb");

	// Checa corretude nome do arquivo
	if(!fp){
		printf("Classe %s nao encontrada\n", className);
		exit(1);
	}

	classFile = (ClassFile*)malloc(sizeof(ClassFile));
	classFile->magic = readBytes(4, fp); // TODO verificacao do valor do magic
	classFile->minor_version = readBytes(2, fp);
	classFile->major_version = readBytes(2, fp);
	classFile->constant_pool_count = readBytes(2, fp);
	classFile->constant_pool = readConstantPool(classFile->constant_pool_count, fp);
    classFile->access_flags = readBytes(2, fp);
    classFile->this_class = readBytes(2, fp);
    classFile->super_class = readBytes(2, fp);
    classFile->interfaces_count = readBytes(2, fp);
    classFile->interfaces = readInterfaces(classFile->interfaces_count, fp);
    classFile->fields_count = readBytes(2, fp);
	classFile->fields = readFields(classFile->fields_count, classFile->constant_pool, fp);
	classFile->methods_count = readBytes(2, fp);
	classFile->methods = readMethods(classFile->methods_count, classFile->constant_pool, fp);
	classFile->attributes_count = readBytes(2, fp);
	classFile->attributes = readAttributes(classFile->attributes_count, classFile->constant_pool, fp);

	fclose(fp);
	// Verifica se o arquivo eh um .class
	classFormatchecker(classFile);
	// Verifica se o nome do arquivo é o mesmo da classe
	classNameChecker(classFile, className);
	// Verifica se a versao do .class é suportada pelo java 2
	versionChecker(classFile);
	// Guarda a classe no vetor global de classes
    empilhar_classe(classFile);
	return classFile;
}

/**
 * Função verificacao, verificar se o arquivo se trata de um .class verificando o campo magic
 * @param 	classFile 	Ponteiro para os dados do suposto .class
 * @return    1 para .class e 0 para nao .class
 */
void classFormatchecker(ClassFile* classFile){
	if(classFile->magic != 0xCAFEBABE){
		printf("Arquivo nao eh um .class.\n");
		exit(1);
	}
}

/**
 * Função verificacao, verificar se o nome da classe do .class bate com o do arquivo
 * @param 	classFile 	Ponteiro para os dados do .class
 * @param 	nomeArquivo 	Ponteiro o nome do arquivo
 * @return    1 para confere e 0 para nao confere
 */
void classNameChecker(ClassFile* classFile, char* nomeArquivo){
	int i = 0;
	int string_index = classFile->constant_pool[classFile->this_class].info.string_info->string_index;
	char * nomeClassept = classFile->constant_pool[string_index].info.utf8_info->bytes;

	//Verifica se nome da classe eh igual ao nome do arquivo
	if(strcmp(nomeClassept, nomeArquivo)){
		printf("Nome da classe (%s) e do arquivo (%s) nao conferem.\n", nomeClassept, nomeArquivo);
		exit(1);//Nomes diferentes
	}
}

/**
 * Função verificacao, verificar se a major version do .class é suportada pelo java 2
 * @param 	classFile 	Ponteiro para os dados do .class
 * @return    1 para suportada e 0 para nao .suportada
 */
void versionChecker(ClassFile* classFile){
//	if(classFile->major_version != 0x2e){
//		printf("Versao nao suportada pelo java 2.\n");
//		exit(1);
//	}
}
