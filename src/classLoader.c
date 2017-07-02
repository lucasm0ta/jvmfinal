#include "classLoader.h"
#include "classList.h"
#include "methodArea.h"
#include "instructions.h"
#include "frame.h"
#include "array.h"
#include "objectManager.h"

/**
 * \brief Função para leitura byte a byte do arquivo fp
 * \param size quantidade de bytes a serem lidos
 * \param fp ponteiro para o arquivo
 * \return Os 4 últimos bytes lidos (variável dde 32 bits)
 */
uint32_t ler_bytes(int size, FILE *fp){
	uint32_t retorno = 0;
	int i;
	for (i = 0; i < size; ++i){
		retorno <<= 8;
		retorno += getc(fp);
	}
	return retorno;
}

/**
 * \brief Função que retorna uma string que representa o valor de uma das constantes do Constant Pool
 * \param index Index da constante no Constant Pool
 * \param constant_pool Ponteiro para um Constant Pool
 * \return Ponteiro para uma string
 */
uint8_t* acessar_constant_pool_entry(int index, Cp_info *constant_pool){
	switch(constant_pool[index].tag){
		case CONSTANT_Class:
			return acessar_constant_pool_entry(constant_pool[index].info.class_info->name_index, constant_pool);
		case CONSTANT_Fieldref:
			return acessar_constant_pool_entry(constant_pool[index].info.fieldref_info->name_and_type_index,
											   constant_pool);
		case CONSTANT_Methodref:
			return acessar_constant_pool_entry(constant_pool[index].info.methodref_info->name_and_type_index,
											   constant_pool);
		case CONSTANT_InterfaceMethodref:
			return acessar_constant_pool_entry(constant_pool[index].info.interfaceMethodref_info->name_and_type_index,
											   constant_pool);
		case CONSTANT_String:
			return acessar_constant_pool_entry(constant_pool[index].info.string_info->string_index, constant_pool);
		case CONSTANT_NameAndType:
			acessar_constant_pool_entry(constant_pool[index].info.nameAndType_info->name_index, constant_pool);
			return acessar_constant_pool_entry(constant_pool[index].info.nameAndType_info->descriptor_index,
											   constant_pool);
		case CONSTANT_Utf8:
			return constant_pool[index].info.utf8_info->bytes; //Alem de imprimir retorna no caso de ser string
		case CONSTANT_MethodHandle:
			return acessar_constant_pool_entry(constant_pool[index].info.methodHandle_info->reference_index,
											   constant_pool);
		case CONSTANT_MethodType:
			return acessar_constant_pool_entry(constant_pool[index].info.methodType_info->descriptor_index,
											   constant_pool);
		case CONSTANT_InvokeDynamic:
			return acessar_constant_pool_entry(constant_pool[index].info.invokeDynamic_info->name_and_type_index,
											   constant_pool);
		default:
			return "invalid constant pool reference";
	}
}

/**
 * Lê atributos no arquivo .class. É utilizado na função de leitura de outras estruturas, o readFields, readMethods e loadClass
 * \param length Quantidade de atributos
 * \param constant_pool Ponteiro para o Constant Poll
 * \param fp Ponteiro para o arquivo, que deve estar apontando para onde começam os atributos
 * \return Estrutura de atributos
 */
Attribute_info* ler_atributos(int length, Cp_info *constant_pool, FILE *fp){
	int i, j, k;
	Attribute_info* retorno = (Attribute_info*)malloc(length*sizeof(Attribute_info));
	for (i = 0; i < length; ++i){
		retorno[i].attribute_name_index = ler_bytes(2, fp);
		retorno[i].attribute_length = ler_bytes(4, fp);
		char* str = (constant_pool[retorno[i].attribute_name_index]).info.utf8_info->bytes;
		if (strcmp(str, "ConstantValue") == 0){
			retorno[i].info.constantValue_attribute = (ConstantValue_attribute*)malloc(sizeof(ConstantValue_attribute));
    		retorno[i].info.constantValue_attribute->constantvalue_index = ler_bytes(2, fp);
		} else if (strcmp(str, "Code") == 0){
			retorno[i].info.code_attribute = (Code_attribute*)malloc(sizeof(Code_attribute));
			retorno[i].info.code_attribute->max_stack = ler_bytes(2, fp);
			retorno[i].info.code_attribute->max_locals = ler_bytes(2, fp);
			retorno[i].info.code_attribute->code_length = ler_bytes(4, fp);
			retorno[i].info.code_attribute->code = (uint8_t*)malloc(retorno[i].info.code_attribute->code_length*sizeof(uint8_t));
			for (j = 0; j < retorno[i].info.code_attribute->code_length; ++j){
				retorno[i].info.code_attribute->code[j] = ler_bytes(1, fp);
			}
			retorno[i].info.code_attribute->exception_table_length = ler_bytes(2, fp);
			retorno[i].info.code_attribute->exception_table_ptr = (exception_table*)malloc(retorno[i].info.code_attribute->exception_table_length*sizeof(exception_table));
			for (j = 0; j < retorno[i].info.code_attribute->exception_table_length; ++j){
			    retorno[i].info.code_attribute->exception_table_ptr[j].start_pc = ler_bytes(2, fp);
			    retorno[i].info.code_attribute->exception_table_ptr[j].end_pc = ler_bytes(2, fp);
			    retorno[i].info.code_attribute->exception_table_ptr[j].handler_pc = ler_bytes(2, fp);
			    retorno[i].info.code_attribute->exception_table_ptr[j].catch_type = ler_bytes(2, fp);
			}
			retorno[i].info.code_attribute->attributes_count = ler_bytes(2, fp);
			retorno[i].info.code_attribute->attributes = ler_atributos(retorno[i].info.code_attribute->attributes_count,
																	  constant_pool, fp);
		} else if (strcmp(str, "Exceptions") == 0){
			retorno[i].info.exceptions_attribute = (Exceptions_attribute*)malloc(sizeof(Exceptions_attribute));
			retorno[i].info.exceptions_attribute->number_of_exceptions = ler_bytes(2, fp);
			retorno[i].info.exceptions_attribute->exception_index_table = (uint16_t*)malloc(retorno[i].info.exceptions_attribute->number_of_exceptions*sizeof(uint16_t));
			for (j = 0; j < retorno[i].info.exceptions_attribute->number_of_exceptions; ++j){
				retorno[i].info.exceptions_attribute->exception_index_table[j] = ler_bytes(2, fp);
			}
		} else if (strcmp(str, "InnerClasses") == 0){
			retorno[i].info.innerClasses_attribute = (InnerClasses_attribute*)malloc(sizeof(InnerClasses_attribute));
			retorno[i].info.innerClasses_attribute->number_of_classes = ler_bytes(2, fp);
			retorno[i].info.innerClasses_attribute->classes_ptr = (Classes*)malloc(retorno[i].info.innerClasses_attribute->number_of_classes*sizeof(Classes));
			for (j = 0; j < retorno[i].info.innerClasses_attribute->number_of_classes; ++j){
			    retorno[i].info.innerClasses_attribute->classes_ptr[j].inner_class_info_index = ler_bytes(2, fp);
			    retorno[i].info.innerClasses_attribute->classes_ptr[j].outer_class_info_index = ler_bytes(2, fp);
			    retorno[i].info.innerClasses_attribute->classes_ptr[j].inner_name_index = ler_bytes(2, fp);
			    retorno[i].info.innerClasses_attribute->classes_ptr[j].inner_class_access_flags = ler_bytes(2, fp);
			}
		} else if (strcmp(str, "EnclosingMethod") == 0){
			retorno[i].info.enclosingMethod_attribute = (EnclosingMethod_attribute*)malloc(sizeof(EnclosingMethod_attribute));
   			retorno[i].info.enclosingMethod_attribute->class_index = ler_bytes(2, fp);
   			retorno[i].info.enclosingMethod_attribute->method_index = ler_bytes(2, fp);
		} else if (strcmp(str, "Synthetic") == 0){
			retorno[i].info.synthetic_attribute = (Synthetic_attribute*)malloc(sizeof(Synthetic_attribute));
		} else if (strcmp(str, "Signature") == 0){
			retorno[i].info.signature_attribute = (Signature_attribute*)malloc(sizeof(Signature_attribute));
			retorno[i].info.signature_attribute->signature_index = ler_bytes(2, fp);
		} else if (strcmp(str, "SourceFile") == 0){
			retorno[i].info.sourceFile_attribute = (SourceFile_attribute*)malloc(sizeof(SourceFile_attribute));
			retorno[i].info.sourceFile_attribute->sourcefile_index = ler_bytes(2, fp);
		} else if (strcmp(str, "SourceDebugExtension") == 0){
			retorno[i].info.sourceDebugExtension_attribute = (SourceDebugExtension_attribute*)malloc(sizeof(SourceDebugExtension_attribute));
			ler_bytes(retorno[i].attribute_length, fp);
		} else if (strcmp(str, "LineNumberTable") == 0){
			retorno[i].info.lineNumberTable_attribute = (LineNumberTable_attribute*)malloc(sizeof(LineNumberTable_attribute));
			retorno[i].info.lineNumberTable_attribute->line_number_table_length = ler_bytes(2, fp);
			retorno[i].info.lineNumberTable_attribute->line_number_table_ptr = (line_number_table*)malloc(retorno[i].info.lineNumberTable_attribute->line_number_table_length*sizeof(line_number_table));
			for (j = 0; j < retorno[i].info.lineNumberTable_attribute->line_number_table_length; ++j){
			    retorno[i].info.lineNumberTable_attribute->line_number_table_ptr[j].start_pc = ler_bytes(2, fp);
			    retorno[i].info.lineNumberTable_attribute->line_number_table_ptr[j].line_number = ler_bytes(2, fp);
			}
		} else if (strcmp(str, "LocalVariableTable") == 0){
			retorno[i].info.localVariableTable_attribute = (LocalVariableTable_attribute*)malloc(sizeof(LocalVariableTable_attribute));
			retorno[i].info.localVariableTable_attribute->local_variable_table_length = ler_bytes(2, fp);
			retorno[i].info.localVariableTable_attribute->local_variable_table_ptr = (local_variable_table*)malloc(retorno[i].info.localVariableTable_attribute->local_variable_table_length*sizeof(local_variable_table));
			for (j = 0; j < retorno[i].info.localVariableTable_attribute->local_variable_table_length; ++j){
			    retorno[i].info.localVariableTable_attribute->local_variable_table_ptr[j].start_pc = ler_bytes(2, fp);
			    retorno[i].info.localVariableTable_attribute->local_variable_table_ptr[j].length = ler_bytes(2, fp);
			    retorno[i].info.localVariableTable_attribute->local_variable_table_ptr[j].name_index = ler_bytes(2, fp);
			    retorno[i].info.localVariableTable_attribute->local_variable_table_ptr[j].descriptor_index = ler_bytes(2,
																													  fp);
			    retorno[i].info.localVariableTable_attribute->local_variable_table_ptr[j].index = ler_bytes(2, fp);
			}
		} else if (strcmp(str, "LocalVariableTypeTable") == 0){
			retorno[i].info.localVariableTypeTable_attribute = (LocalVariableTypeTable_attribute*)malloc(sizeof(LocalVariableTypeTable_attribute));
			retorno[i].info.localVariableTypeTable_attribute->local_variable_type_table_length = ler_bytes(2, fp);
			retorno[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr = (local_variable_type_table*)malloc(retorno[i].info.localVariableTypeTable_attribute->local_variable_type_table_length*sizeof(local_variable_type_table));
			for (j = 0; j < retorno[i].info.localVariableTypeTable_attribute->local_variable_type_table_length; ++j){
			    retorno[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr[j].start_pc = ler_bytes(
						2, fp);
			    retorno[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr[j].length = ler_bytes(2,
																													 fp);
			    retorno[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr[j].name_index = ler_bytes(
						2, fp);
			    retorno[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr[j].signature_index = ler_bytes(
						2, fp);
			    retorno[i].info.localVariableTypeTable_attribute->local_variable_type_table_ptr[j].index = ler_bytes(2,
																													fp);
			}
		} else if (strcmp(str, "Deprecated") == 0){
			retorno[i].info.deprecated_attribute = (Deprecated_attribute*)malloc(sizeof(Deprecated_attribute));
		} else if (strcmp(str, "BootstrapMethods") == 0){
			retorno[i].info.bootstrapMethods_attribute = (BootstrapMethods_attribute*)malloc(sizeof(BootstrapMethods_attribute));
			retorno[i].info.bootstrapMethods_attribute->num_bootstrap_methods = ler_bytes(2, fp);
			retorno[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr = (bootstrap_methods*)malloc(retorno[i].info.bootstrapMethods_attribute->num_bootstrap_methods*sizeof(bootstrap_methods));
			for (j = 0; j < retorno[i].info.bootstrapMethods_attribute->num_bootstrap_methods; ++j){
			    retorno[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].bootstrap_method_ref = ler_bytes(2,
																													 fp);
			    retorno[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].num_bootstrap_arguments = ler_bytes(
						2, fp);
			    retorno[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].bootstrap_arguments = (uint16_t*)malloc(retorno[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].num_bootstrap_arguments*sizeof(uint16_t));
				for (k = 0; k < retorno[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].num_bootstrap_arguments; ++k){
					retorno[i].info.bootstrapMethods_attribute->bootstrap_methods_ptr[j].bootstrap_arguments[k] = ler_bytes(
							2, fp);
				}
			}
		} else {
			ler_bytes(retorno[i].attribute_length, fp);
		}
	}
	return retorno;
}

/**
 * \brief Lê o Pool de constantes no arquivo .class.
 * \param length Quantidade de contantes
 * \param fp Ponteiro para o arquivo, que deve estar apontando para onde começa o pool de constantes
 * \return Referência para uma estrutura Pool de Constantes
 */
Cp_info* ler_constant_pool(int length, FILE *fp){
	int i, j;
	Cp_info* retorno = (Cp_info*)malloc(length*sizeof(Cp_info));
	for (i = 1; i < length; ++i){
		retorno[i].tag = ler_bytes(1, fp);
		switch(retorno[i].tag){
			case CONSTANT_Class:
				retorno[i].info.class_info = (Class_info*)malloc(sizeof(Class_info));
				retorno[i].info.class_info->name_index = ler_bytes(2, fp);
				break;
			case CONSTANT_Fieldref:
				retorno[i].info.fieldref_info = (Fieldref_info*)malloc(sizeof(Fieldref_info));
				retorno[i].info.fieldref_info->class_index = ler_bytes(2, fp);
				retorno[i].info.fieldref_info->name_and_type_index = ler_bytes(2, fp);
				break;
			case CONSTANT_Methodref:
				retorno[i].info.methodref_info = (Methodref_info*)malloc(sizeof(Methodref_info));
				retorno[i].info.methodref_info->class_index = ler_bytes(2, fp);
				retorno[i].info.methodref_info->name_and_type_index = ler_bytes(2, fp);
				break;
			case CONSTANT_InterfaceMethodref:
				retorno[i].info.interfaceMethodref_info = (InterfaceMethodref_info*)malloc(sizeof(InterfaceMethodref_info));
				retorno[i].info.interfaceMethodref_info->class_index = ler_bytes(2, fp);
				retorno[i].info.interfaceMethodref_info->name_and_type_index = ler_bytes(2, fp);
				break;
			case CONSTANT_String:
				retorno[i].info.string_info = (String_info*)malloc(sizeof(String_info));
				retorno[i].info.string_info->string_index = ler_bytes(2, fp);
				break;
			case CONSTANT_Integer:
				retorno[i].info.integer_info = (Integer_info*)malloc(sizeof(Integer_info));
				retorno[i].info.integer_info->bytes = ler_bytes(4, fp);
				break;
			case CONSTANT_Float:
				retorno[i].info.float_info = (Float_info*)malloc(sizeof(Float_info));
				retorno[i].info.float_info->bytes = ler_bytes(4, fp);
				break;
			case CONSTANT_Long:
				retorno[i].info.long_info = (Long_info*)malloc(sizeof(Long_info));
				retorno[i].info.long_info->high_bytes = ler_bytes(4, fp);
				retorno[i].info.long_info->low_bytes = ler_bytes(4, fp);
				i++;
				break;
			case CONSTANT_Double:
				retorno[i].info.double_info = (Double_info*)malloc(sizeof(Double_info));
				retorno[i].info.double_info->high_bytes = ler_bytes(4, fp);
				retorno[i].info.double_info->low_bytes = ler_bytes(4, fp);
				i++;
				break;
			case CONSTANT_NameAndType:
				retorno[i].info.nameAndType_info = (NameAndType_info*)malloc(sizeof(NameAndType_info));
				retorno[i].info.nameAndType_info->name_index = ler_bytes(2, fp);
				retorno[i].info.nameAndType_info->descriptor_index = ler_bytes(2, fp);
				break;
			case CONSTANT_Utf8:
				retorno[i].info.utf8_info = (Utf8_info*)malloc(sizeof(Utf8_info));
				retorno[i].info.utf8_info->length = ler_bytes(2, fp);
				retorno[i].info.utf8_info->bytes = (uint8_t*)malloc((retorno[i].info.utf8_info->length+1)*sizeof(uint8_t));
				for (j = 0; j < retorno[i].info.utf8_info->length; ++j){
					retorno[i].info.utf8_info->bytes[j] = ler_bytes(1, fp);
				}
				retorno[i].info.utf8_info->bytes[j] = 0; // Concatenar esse zero pode dar ruim? facilita bastante o print
				                                        // No arquivo de .class esse zero não existe
				break;
			case CONSTANT_MethodHandle:
				retorno[i].info.methodHandle_info = (MethodHandle_info*)malloc(sizeof(MethodHandle_info));
				retorno[i].info.methodHandle_info->reference_kind = ler_bytes(1, fp);
				retorno[i].info.methodHandle_info->reference_index = ler_bytes(2, fp);
				break;
			case CONSTANT_MethodType:
				retorno[i].info.methodType_info = (MethodType_info*)malloc(sizeof(MethodType_info));
				retorno[i].info.methodType_info->descriptor_index = ler_bytes(2, fp);
				break;
			case CONSTANT_InvokeDynamic:
				retorno[i].info.invokeDynamic_info = (InvokeDynamic_info*)malloc(sizeof(InvokeDynamic_info));
				retorno[i].info.invokeDynamic_info->bootstrap_method_attr_index = ler_bytes(2, fp);
				retorno[i].info.invokeDynamic_info->name_and_type_index = ler_bytes(2, fp);
				break;
			default:
				break;
		}
	}
	return retorno;
}

/**
 * \brief Lê do arquivo .class os indices do contant pool que representam as interfaces da classe.
 * \param length Quantidade de interfaces
 * \param fp Ponteiro para o arquivo, que deve estar apontando para onde começam os indices
 * \return Referência para um vetor de indices do constant pool
 */
uint16_t* ler_interfaces(int length, FILE *fp){
	int i;
	uint16_t* retorno = (uint16_t*)malloc(length*sizeof(uint16_t));
	for (i = 0; i < length; ++i){
		retorno[i] = ler_bytes(2, fp);
	}
	return retorno;
}

/**
 * \brief Lê os fields de um arquivo .class.
 * \param length Quantidade de Fields
 * \param constant_pool Referência para o constant pool da class que esta sendo lida
 * \param fp Ponteiro para o arquivo, que deve estar apontando para onde começam os fields
 * \return Referência para um vetor de estruturas dos fields
 */
Field_info* ler_fields(int length, Cp_info *constant_pool, FILE *fp){
	int i;
	Field_info* retorno = (Field_info*)malloc(length*sizeof(Field_info));
	for (i = 0; i < length; ++i){
		retorno[i].access_flags = ler_bytes(2, fp);
		retorno[i].name_index = ler_bytes(2, fp);
		retorno[i].descriptor_index = ler_bytes(2, fp);
		retorno[i].attributes_count = ler_bytes(2, fp);
		retorno[i].attributes = ler_atributos(retorno[i].attributes_count, constant_pool, fp);
	}
	return retorno;
}

/**
 * \brief Lê os métodos de um arquivo .class.
 * \param length Quantidade de métodos
 * \param constant_pool Referência para o constant pool da class que esta sendo lida
 * \param fp Ponteiro para o arquivo, que deve estar apontando para onde começam os métodos
 * \return Referência para um vetor de estruturas dos métodos
 */
Method_info* ler_metodos(int length, Cp_info *constant_pool, FILE *fp){
	int i;
	Method_info* result = (Method_info*)malloc(length*sizeof(Method_info));
	for (i = 0; i < length; ++i){
		result[i].access_flags = ler_bytes(2, fp);
		result[i].name_index = ler_bytes(2, fp);
		result[i].descriptor_index = ler_bytes(2, fp);
		result[i].attributes_count = ler_bytes(2, fp);
		result[i].attributes = ler_atributos(result[i].attributes_count, constant_pool, fp);
	}
	return result;
}

/**
 * \brief Função principal que chama todas as outras funções de leitura para ler o .class inteiro
 * Caso o .class solicitado já foi carregado anteriormente, retorna uma referência para a estrutura já carregada
 * \param className Nome da classe a ser lida
 * \return Referência para uma struct ClassFile
 */
ClassFile* carregar_classe(char *className){
	// Veifica se o arquivo ja foi carregado alguma vez
	ClassFile* classFile = buscar_classe(className);
	if (classFile != NULL)	return classFile;

	// Concatena o .class no final do nome
	char name[80];
	strcpy(name, className);

	// Abre o arquivo
	FILE* fp = NULL;
	fp = fopen(name, "rb");

	// Checa corretude nome do arquivo
	if(!fp){
		printf("Classe %s nao encontrada\n", className);
		exit(1);
	}

	classFile = (ClassFile*)malloc(sizeof(ClassFile));
	classFile->magic = ler_bytes(4, fp); // TODO verificacao do valor do magic
	classFile->minor_version = ler_bytes(2, fp);
	classFile->major_version = ler_bytes(2, fp);
	classFile->constant_pool_count = ler_bytes(2, fp);
	classFile->constant_pool = ler_constant_pool(classFile->constant_pool_count, fp);
    classFile->access_flags = ler_bytes(2, fp);
    classFile->this_class = ler_bytes(2, fp);
    classFile->super_class = ler_bytes(2, fp);
    classFile->interfaces_count = ler_bytes(2, fp);
    classFile->interfaces = ler_interfaces(classFile->interfaces_count, fp);
    classFile->fields_count = ler_bytes(2, fp);
	classFile->fields = ler_fields(classFile->fields_count, classFile->constant_pool, fp);
	classFile->methods_count = ler_bytes(2, fp);
	classFile->methods = ler_metodos(classFile->methods_count, classFile->constant_pool, fp);
	classFile->attributes_count = ler_bytes(2, fp);
	classFile->attributes = ler_atributos(classFile->attributes_count, classFile->constant_pool, fp);

	fclose(fp);
	// Verifica se o arquivo eh um .class
	verificar_magic_number(classFile);
	// Verifica se o nome do arquivo é o mesmo da classe
	verificar_nome_classe_artigo(classFile, className);
	// Verifica se a versao do .class é suportada pelo java 2
	verificar_versao(classFile);
	// Guarda a classe no vetor global de classes
    empilhar_classe(classFile);
	return classFile;
}

/**
 * \brief Função verificacao, verificar se o arquivo se trata de um .class verificando o campo magic
 * \param classFile Ponteiro para os dados do suposto .class
 * \return 1 para .class e 0 para nao .class
 */
void verificar_magic_number(ClassFile *classFile){
	if(classFile->magic != 0xCAFEBABE){
		printf("Nao e .class.\n");
		exit(1);
	}
}

/**
 * \brief Função verificacao, verificar se o nome da classe do .class bate com o do arquivo
 * \param classFile Ponteiro para os dados do .class
 * \param nomeArquivo Ponteiro o nome do arquivo
 * \return 1 para confere e 0 para nao confere
 */
void verificar_nome_classe_artigo(ClassFile *classFile, char *nomeArquivo){
	int i = 0;
	int string_index = classFile->constant_pool[classFile->this_class].info.string_info->string_index;
	char *nomeClassept = classFile->constant_pool[string_index].info.utf8_info->bytes;

	//Verifica se nome da classe eh igual ao nome do arquivo
	int pos = 0;
	int last = 0;
	while(nomeArquivo[pos] != '\0') {
		if(nomeArquivo[pos] == '/')
			last = pos;
		pos++;
	}
	int size = pos - last - 7;
	char *buff1 = malloc(sizeof(char) * size);
	memcpy(buff1, &nomeArquivo[last+1], size);
	buff1[size] = '\0';

	pos = 0;
	last = 0;
	while(nomeClassept[pos] != '\0') {
		if(nomeClassept[pos] == '/')
			last = pos;
		pos++;
	}
	if (last) last++;
	size = pos - last;
	char *buff2 = malloc(sizeof(char) * size);
	memcpy(buff2, &nomeClassept[last], size);
	buff2[size] = '\0';
	if (strcmp(buff1, buff2)) {
		printf("Nome da classe (%s) e do arquivo (%s) diferentes.\n", buff1, buff2);
		exit(1);//Nomes diferentes
	}
}

/**
 * \brief Função verificacao, verificar se a major version do .class é suportada pelo java 2
 * \param classFile Ponteiro para os dados do .class
 * \return 1 para suportada e 0 para nao .suportada
 */
void verificar_versao(ClassFile *classFile) {
//	if(classFile->major_version != 0x2e){
//		printf("Versao nao suportada pelo java 2.\n");
//		exit(1);
//	}
}
