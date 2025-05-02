/**
 * @file utils.h
 * @brief Header file for utility functions used in the UDS over CAN project.
 * @author Somen Das
 * @date 2023
 */

#ifndef __UTILS__H__
#define __UTILS__H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"

    /**
     * @brief Convert a string into a 16-bit hexadecimal value.
     * @param string The input string.
     * @return A 16-bit unsigned integer.
     */
    u16 stoh(char *string);

    /**
     * @brief Insert an element into the array.
     * @param array The pointer to the array.
     * @param _data The data to be inserted.
     * @param idx The address of the length of the data.
     * @return void.
     */
    void insertIntoArray(u8 *array, u8 _data, u16 *idx);

    /**
     * @brief Insert an element larger than 1-byte into an array of 1-byte numbers.
     * @param array The pointer to the array.
     * @param _data The pointer to the data to be inserted.
     * @param idx The pointer to the length of the data.
     * @param size Size in bytes of the data.
     * @return void.
     */
    void insertInArraytoByte(u8 *array, u16 *idx, void *_data, size_t size);

#ifdef __cplusplus
}
#endif

#endif // __UTILS__H__