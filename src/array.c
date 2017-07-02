#include "array.h"

void put_referencia_array(uint32_t *arrayRef, arrayType *array){
    array->reference = (uint32_t)arrayRef;
}

void put_tamanho_array(uint32_t size, arrayType *array){
    array->arraySize = size; 
}

uint32_t get_referencia_array(arrayType *array){
	return array->reference;
}

uint32_t get_tamanho_array(arrayType *array){
	return array->arraySize;
}