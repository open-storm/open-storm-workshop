/**
 * @file strlib.h
 * @brief Functions for parsing c strings.
 * @author Brandon Wong, Ivan Mondragon
 * @version TODO
 * @date 2017-06-19
 */

#ifndef STRLIB_H
#define STRLIB_H
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Searches for the left-most c string in between @p search_start and @p
 * search_end and stores it in @p output_str
 *
 * @param input_str[] C string to be searched
 * @param output_str[] Buffer to store the resulting c string
 * @param search_start[] Leading c string in the query
 * @param search_end[] Ending c string in the query
 *
 * @return Pointer to first occurance of @p search_end after @p search_start or
 * NULL if extraction fails.
 */
char* strextract(const char input_str[], char output_str[],
                 const char search_start[], const char search_end[]);

#endif
/* [] END OF FILE */
