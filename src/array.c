#include "array.h"


/**
 * Dada uma referencia para arrayType devolve o ponteiro para o array propriamente dita
 * @param  array Estrutura a qual a referencia se encontra
 * @return       Referencia para o array
 */
uint32_t get_referencia_array(arrayType *array){
	return array->reference;
}

/**
 * Dada uma referencia para arrayType devolve o tamanho do array
 * @param  array Estrutura a qual a referencia se encontra
 * @return       Tamanho do array
 */
uint32_t get_tamanho_array(arrayType *array){
	return array->arraySize;
}

/**
 * Dada um ponteiro para um array e um para a estrutura de array coloca-o na estrutura
 * @param arrayRef Referencia a ser posta
 * @param array    Estrutura a ser posta a referencia
 */
void put_referencia_array(uint32_t *arrayRef, arrayType *array){
	array->reference = (uint32_t)arrayRef;
}

/**
 * //Dada um tamanho int um ponteiro para a estrutura de array coloca-o na estrutura	
 * @param size  Tamanho a ser posto na estrutura
 * @param array Estrutura a ser posto o tamanho
 */
void put_tamanho_array(uint32_t size, arrayType *array){
	array->arraySize = size; 
}