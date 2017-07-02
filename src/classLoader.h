#ifndef CLASSLOADER_H
#define CLASSLOADER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/***************************************************************************************************
*                                       CONSTANT POOL                                              *
***************************************************************************************************/

typedef struct Class_info {
    uint16_t name_index;
}Class_info;

typedef struct Fieldref_info {
    uint16_t class_index;
    uint16_t name_and_type_index;
}Fieldref_info;

typedef struct Methodref_info {
    uint16_t class_index;
    uint16_t name_and_type_index;
}Methodref_info;

typedef struct InterfaceMethodref_info {
    uint16_t class_index;
    uint16_t name_and_type_index;
}InterfaceMethodref_info;

typedef struct String_info {
    uint16_t string_index;
}String_info;

typedef struct Integer_info {
    uint32_t bytes;
}Integer_info;

typedef struct Float_info {
    uint32_t bytes;
}Float_info;

typedef struct Long_info {
    uint32_t high_bytes;
    uint32_t low_bytes;
}Long_info;

typedef struct Double_info {
    uint32_t high_bytes;
    uint32_t low_bytes;
}Double_info;

typedef struct NameAndType_info {
    uint16_t name_index;
    uint16_t descriptor_index;
}NameAndType_info;

typedef struct Utf8_info {
    uint16_t length;
    uint8_t* bytes;
}Utf8_info;

typedef struct MethodHandle_info {
    uint8_t reference_kind;
    uint16_t reference_index;
}MethodHandle_info;

typedef struct MethodType_info {
    uint16_t descriptor_index;
}MethodType_info;

typedef struct InvokeDynamic_info {
    uint16_t bootstrap_method_attr_index;
    uint16_t name_and_type_index;
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
    uint8_t  tag;
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
    uint16_t constantvalue_index;
}ConstantValue_attribute;

/**
 * Code_attribute
 */
typedef struct exception_table{
    uint16_t start_pc;
    uint16_t end_pc;
    uint16_t handler_pc;
    uint16_t catch_type;
}exception_table;

typedef struct Code_attribute {
    uint16_t max_stack;
    uint16_t max_locals;
    uint32_t code_length;
    uint8_t*  code;
    uint16_t exception_table_length;
    exception_table* exception_table_ptr;
    uint16_t attributes_count;
    Attribute_info* attributes;
}Code_attribute;

/**
 * Exceptions_attribute
 */
typedef struct Exceptions_attribute {
    uint16_t number_of_exceptions;
    uint16_t* exception_index_table;
}Exceptions_attribute;

/**
 * InnerClasses_attribute
 */
typedef struct Classes{
    uint16_t inner_class_info_index;
    uint16_t outer_class_info_index;
    uint16_t inner_name_index;
    uint16_t inner_class_access_flags;
}Classes;

typedef struct InnerClasses_attribute {
    uint16_t number_of_classes;
    Classes* classes_ptr;
}InnerClasses_attribute;

/**
 * EnclosingMethod_attribute
 */
typedef struct EnclosingMethod_attribute {
    uint16_t class_index;
    uint16_t method_index;
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
    uint16_t signature_index;
}Signature_attribute;

/**
 * SourceFile_attribute
 */
typedef struct SourceFile_attribute {
    uint16_t sourcefile_index;
}SourceFile_attribute;

/**
 * SourceDebugExtension_attribute
 */
typedef struct SourceDebugExtension_attribute {
    uint8_t* debug_extension;
}SourceDebugExtension_attribute;

/**
 * LineNumberTable_attribute
 */
typedef struct line_number_table{
    uint16_t start_pc;
    uint16_t line_number;
}line_number_table;

typedef struct LineNumberTable_attribute {
    uint16_t line_number_table_length;
    line_number_table* line_number_table_ptr;
}LineNumberTable_attribute;

/**
 * LocalVariableTable_attribute
 */
typedef struct local_variable_table{
    uint16_t start_pc;
    uint16_t length;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t index;
}local_variable_table;

typedef struct LocalVariableTable_attribute {
    uint16_t local_variable_table_length;
    local_variable_table* local_variable_table_ptr;
}LocalVariableTable_attribute;

/**
 * LocalVariableTypeTable_attribute
 */
typedef struct local_variable_type_table{
    uint16_t start_pc;
    uint16_t length;
    uint16_t name_index;
    uint16_t signature_index;
    uint16_t index;
}local_variable_type_table;

typedef struct LocalVariableTypeTable_attribute {
    uint16_t local_variable_type_table_length;
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
    uint16_t bootstrap_method_ref;
    uint16_t num_bootstrap_arguments;
    uint16_t* bootstrap_arguments;
}bootstrap_methods;

typedef struct BootstrapMethods_attribute {
    uint16_t num_bootstrap_methods;
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
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    attribute_pointer info;
};

/***************************************************************************************************
*                                                                                                  *
***************************************************************************************************/

typedef struct Field_info {
    uint16_t        access_flags;
    uint16_t        name_index;
    uint16_t        descriptor_index;
    uint16_t        attributes_count;
    Attribute_info* attributes;
}Field_info;

typedef struct Method_info {
    uint16_t        access_flags;
    uint16_t        name_index;
    uint16_t        descriptor_index;
    uint16_t        attributes_count;
    Attribute_info* attributes;
}Method_info;

// Estrutura que armazena o .class inteiro
typedef struct ClassFile {
    uint32_t        magic;
    uint16_t        minor_version;
    uint16_t        major_version;
    uint16_t        constant_pool_count;
    Cp_info*        constant_pool;
    uint16_t        access_flags;
    uint16_t        this_class;
    uint16_t        super_class;
    uint16_t        interfaces_count;
    uint16_t*       interfaces;
    uint16_t        fields_count;
    Field_info*     fields;
    uint16_t        methods_count;
    Method_info*    methods;
    uint16_t        attributes_count;
    Attribute_info* attributes;
} ClassFile;

ClassFile* carregar_classe(char *className);
uint8_t* acessar_constant_pool_entry(int index, Cp_info *constant_pool);
void verificar_magic_number(ClassFile *classFile);
void verificar_nome_classe_artigo(ClassFile *classFile, char *nomeArquivo);
void verificar_versao(ClassFile *classFile);

#ifdef __cplusplus
}
#endif


#endif
