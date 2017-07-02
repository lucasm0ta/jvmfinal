#ifndef CLASSLOADER_H
#define CLASSLOADER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

#define CONSTANT_Class 7
#define CONSTANT_Fieldref 9
#define CONSTANT_Methodref 10
#define CONSTANT_InterfaceMethodref 11
#define CONSTANT_String 8
#define CONSTANT_Integer 3
#define CONSTANT_Float 4
#define CONSTANT_Long 5
#define CONSTANT_Double 6
#define CONSTANT_NameAndType 12
#define CONSTANT_Utf8 1
#define CONSTANT_MethodHandle 15
#define CONSTANT_MethodType 16
#define CONSTANT_InvokeDynamic 18

// Quando tem valor 1 printa saidas de debug
int DEBUG;



typedef struct Class_info {
    u2 name_index;
}Class_info;

typedef struct Fieldref_info {
    u2 class_index;
    u2 name_and_type_index;
}Fieldref_info;

typedef struct Methodref_info {
    u2 class_index;
    u2 name_and_type_index;
}Methodref_info;

typedef struct InterfaceMethodref_info {
    u2 class_index;
    u2 name_and_type_index;
}InterfaceMethodref_info;

typedef struct String_info {
    u2 string_index;
}String_info;

typedef struct Integer_info {
    u4 bytes;
}Integer_info;

typedef struct Float_info {
    u4 bytes;
}Float_info;

typedef struct Long_info {
    u4 high_bytes;
    u4 low_bytes;
}Long_info;

typedef struct Double_info {
    u4 high_bytes;
    u4 low_bytes;
}Double_info;

typedef struct NameAndType_info {
    u2 name_index;
    u2 descriptor_index;
}NameAndType_info;

typedef struct Utf8_info {
    u2 length;
    u1* bytes;
}Utf8_info;

typedef struct MethodHandle_info {
    u1 reference_kind;
    u2 reference_index;
}MethodHandle_info;

typedef struct MethodType_info {
    u2 descriptor_index;
}MethodType_info;

typedef struct InvokeDynamic_info {
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
}InvokeDynamic_info;

typedef union info_pointer {
    Class_info*              class_info;
    Fieldref_info*           fieldref_info;
    Methodref_info*          methodref_info;
    InterfaceMethodref_info* interfaceMethodref_info;
    String_info*             string_info;
    Integer_info*            integer_info;
    Float_info*              float_info;
    Long_info*               long_info;
    Double_info*             double_info;
    NameAndType_info*        nameAndType_info;
    Utf8_info*               utf8_info;
    MethodHandle_info*       methodHandle_info;
    MethodType_info*         methodType_info;
    InvokeDynamic_info*      invokeDynamic_info;
}info_pointer;

// Estrutura principal do Constant Pool
typedef struct Cp_info {
    u1  tag;
    info_pointer info;
}Cp_info;

/***************************************************************************************************
*                                       ATTRIBUTE INFOS                                            *
***************************************************************************************************/

typedef struct Attribute_info Attribute_info;

/**
 * ConstantValue_attribute
 */
typedef struct ConstantValue_attribute {
    u2 constantvalue_index;
}ConstantValue_attribute;

/**
 * Code_attribute
 */
typedef struct exception_table{
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
}exception_table;

typedef struct Code_attribute {
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1*  code;
    u2 exception_table_length;
    exception_table* exception_table_ptr;
    u2 attributes_count;
    Attribute_info* attributes;
}Code_attribute;

/**
 * Exceptions_attribute
 */
typedef struct Exceptions_attribute {
    u2 number_of_exceptions;
    u2* exception_index_table;
}Exceptions_attribute;

/**
 * InnerClasses_attribute
 */
typedef struct Classes{
    u2 inner_class_info_index;
    u2 outer_class_info_index;
    u2 inner_name_index;
    u2 inner_class_access_flags;
}Classes;

typedef struct InnerClasses_attribute {
    u2 number_of_classes;
    Classes* classes_ptr;
}InnerClasses_attribute;

/**
 * EnclosingMethod_attribute
 */
typedef struct EnclosingMethod_attribute {
    u2 class_index;
    u2 method_index;
}EnclosingMethod_attribute;

/**
 * Synthetic_attribute
 */
typedef struct Synthetic_attribute {
}Synthetic_attribute;

/**
 * Signature_attribute
 */
typedef struct Signature_attribute {
    u2 signature_index;
}Signature_attribute;

/**
 * SourceFile_attribute
 */
typedef struct SourceFile_attribute {
    u2 sourcefile_index;
}SourceFile_attribute;

/**
 * SourceDebugExtension_attribute
 */
typedef struct SourceDebugExtension_attribute {
    u1* debug_extension;
}SourceDebugExtension_attribute;

/**
 * LineNumberTable_attribute
 */
typedef struct line_number_table{
    u2 start_pc;
    u2 line_number;
}line_number_table;

typedef struct LineNumberTable_attribute {
    u2 line_number_table_length;
    line_number_table* line_number_table_ptr;
}LineNumberTable_attribute;

/**
 * LocalVariableTable_attribute
 */
typedef struct local_variable_table{
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
}local_variable_table;

typedef struct LocalVariableTable_attribute {
    u2 local_variable_table_length;
    local_variable_table* local_variable_table_ptr;
}LocalVariableTable_attribute;

/**
 * LocalVariableTypeTable_attribute
 */
typedef struct local_variable_type_table{
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 signature_index;
    u2 index;
}local_variable_type_table;

typedef struct LocalVariableTypeTable_attribute {
    u2 local_variable_type_table_length;
    local_variable_type_table* local_variable_type_table_ptr;
}LocalVariableTypeTable_attribute;

/**
 * Deprecated_attribute
 */
typedef struct Deprecated_attribute {
}Deprecated_attribute;

/**
 * BootstrapMethods_attribute
 */
typedef struct bootstrap_methods{
    u2 bootstrap_method_ref;
    u2 num_bootstrap_arguments;
    u2* bootstrap_arguments;
}bootstrap_methods;

typedef struct BootstrapMethods_attribute {
    u2 num_bootstrap_methods;
    bootstrap_methods* bootstrap_methods_ptr;
}BootstrapMethods_attribute;

/**
 * Attribute_info
 */
typedef union attribute_pointer {
    BootstrapMethods_attribute*         bootstrapMethods_attribute;
    Deprecated_attribute*               deprecated_attribute;
    LocalVariableTypeTable_attribute*   localVariableTypeTable_attribute;
    LocalVariableTable_attribute*       localVariableTable_attribute;
    LineNumberTable_attribute*          lineNumberTable_attribute;
    SourceDebugExtension_attribute*     sourceDebugExtension_attribute;
    SourceFile_attribute*               sourceFile_attribute;
    Signature_attribute*                signature_attribute;
    Synthetic_attribute*                synthetic_attribute;
    EnclosingMethod_attribute*          enclosingMethod_attribute;
    InnerClasses_attribute*             innerClasses_attribute;
    Exceptions_attribute*               exceptions_attribute;
    Code_attribute*                     code_attribute;
    ConstantValue_attribute*            constantValue_attribute;
}attribute_pointer;

// Estrutura principal dos atributos
// Typedef dessa estrutura esta la em cima
struct Attribute_info {
    u2 attribute_name_index;
    u4 attribute_length;
    attribute_pointer info;
};

/***************************************************************************************************
*                                                                                                  *
***************************************************************************************************/

typedef struct Field_info {
    u2        access_flags;
    u2        name_index;
    u2        descriptor_index;
    u2        attributes_count;
    Attribute_info* attributes;
}Field_info;

typedef struct Method_info {
    u2        access_flags;
    u2        name_index;
    u2        descriptor_index;
    u2        attributes_count;
    Attribute_info* attributes;
}Method_info;

// Estrutura que armazena o .class inteiro
typedef struct ClassFile {
    u4        magic;
    u2        minor_version;
    u2        major_version;
    u2        constant_pool_count;
    Cp_info*        constant_pool;
    u2        access_flags;
    u2        this_class;
    u2        super_class;
    u2        interfaces_count;
    u2*       interfaces;
    u2        fields_count;
    Field_info*     fields;
    u2        methods_count;
    Method_info*    methods;
    u2        attributes_count;
    Attribute_info* attributes;
} ClassFile;

ClassFile* carregar_classe(char *className);

/**
 * Entra na constant_pool e pega o valor de uma das entradas.
 * @param  index         Index da entrada da constant_pool
 * @param  constant_pool Ponteiro para a constant_pool
 * @return               Valor de uma entrada da constant_pool como string
 */
u1* acessar_constant_pool_entry(int index, Cp_info *constant_pool);
void verificar_magic_number(ClassFile *classFile);
void verificar_nome_classe_artigo(ClassFile *classFile, char *nomeArquivo);
void verificar_versao(ClassFile *classFile);

#ifdef __cplusplus
}
#endif


#endif
