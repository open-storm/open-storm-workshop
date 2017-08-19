/**
 * @file strlib.c
 * @brief Functions for parsing c strings.
 * @author Brandon Wong, Ivan Mondragon
 * @version TODO
 * @date 2017-06-19
 */

#include "strlib.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

char *strextract(const char input_str[], char output_str[],
                 const char search_start[], const char search_end[]) {
    if (input_str == NULL) return NULL;
    char *begin, *end = NULL;

    if ((begin = strstr(input_str, search_start))) {
        begin += strlen(search_start);
        if ((end = strstr(begin, search_end))) {
            strncpy(output_str, begin, end - begin);
            output_str[end - begin] = '\0';
        }
    }

    return end;
}

/* [] END OF FILE */
