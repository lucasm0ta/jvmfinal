#ifndef ARRAY_H
#define ARRAY_H

#include <stdint.h>


/**
 * estrutura para o array, serve para salvar tbm o tamanho do array
 */
typedef struct array{	
	uint32_t arraySize;
	uint32_t reference;
}arrayType;

/**
 * Dada uma referencia para arrayType devolve o ponteiro para o array propriamente dita
 * @param  array Estrutura a qual a referencia se encontra
 * @return       Referencia para o array
 */
uint32_t get_referencia_array(arrayType *array);

/**
 * Dada uma referencia para arrayType devolve o tamanho do array
 * @param  array Estrutura a qual a referencia se encontra
 * @return       Tamanho do array
 */
uint32_t get_tamanho_array(arrayType *array);

/**
 * Dada um ponteiro para um array e um para a estrutura de array coloca-o na estrutura
 * @param arrayRef Referencia a ser posta
 * @param array    Estrutura a ser posta a referencia
 */
void put_referencia_array(uint32_t *arrayRef, arrayType *array);

/**
 * //Dada um tamanho int um ponteiro para a estrutura de array coloca-o na estrutura	
 * @param size  Tamanho a ser posto na estrutura
 * @param array Estrutura a ser posto o tamanho
 */
void put_tamanho_array(uint32_t size, arrayType *array);

#endif