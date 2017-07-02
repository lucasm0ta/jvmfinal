/**
 * Contains structures and functions that handle Array objects. 
 */

#ifndef ARRAY_H
#define ARRAY_H

#include <stdint.h>


/**
 * Structure used to represent an array
 * @arraySize Size of the array
 * @reference Reference to the array itself
 */
typedef struct array{	
	uint32_t arraySize;
	uint32_t reference;
}arrayType;

/**
 * Puts an Array reference inside an arrayType.
 * @param arrayRef Reference to the array that will be put inside the arrayType
 * @param array    Structure that will receive the new array
 */
void put_referencia_array(uint32_t *arrayRef, arrayType *array);

/**
 * Puts an array reference inside an arrayType  with it size
 * @param size  Size of the array that will be pyt inside arrayType
 * @param array The array Type
 */
void put_tamanho_array(uint32_t size, arrayType *array);

/**
 * Given an arrayType structure, returns the pointer to the array itself
 * @param  array Structure to array type
 * @return       Reference to the array itself
 */
uint32_t get_referencia_array(arrayType *array);

/**
 * Returns arraySize from arrayType. Complexity O(1) since
 * it updates the arraySize for every operation
 * 
 * @param  array Structure to array type
 * @return       Array Size
 */
uint32_t get_tamanho_array(arrayType *array);

#endif