/**
 * Contains structures and functions that handle Array objects.
 */

#ifndef ARRAY_H
#define ARRAY_H
#include "util.h"
#include <stdint.h>


/**
 * Structure used to represent an array
 * @arraySize Size of the array
 * @reference Reference to the array itself
 */
typedef struct array{
	u4 arraySize;
	u4 reference;
}arrayType;

/**
 * Puts an Array reference inside an arrayType.
 * @param arrayRef Reference to the array that will be put inside the arrayType
 * @param array    Structure that will receive the new array
 */
void put_referencia_array(u4 *arrayRef, arrayType *array);

/**
 * Puts an array reference inside an arrayType  with it size
 * @param size  Size of the array that will be pyt inside arrayType
 * @param array The array Type
 */
void put_tamanho_array(u4 size, arrayType *array);

/**
 * Given an arrayType structure, returns the pointer to the array itself
 * @param  array Structure to array type
 * @return       Reference to the array itself
 */
u4 get_referencia_array(arrayType *array);

/**
 * Returns arraySize from arrayType. Complexity O(1) since
 * it updates the arraySize for every operation
 *
 * @param  array Structure to array type
 * @return       Array Size
 */
u4 get_tamanho_array(arrayType *array);

#endif
