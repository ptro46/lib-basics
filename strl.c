/**
 * \file strl.c
 * \brief size-bounded string copying and concatenation
 * \author open source from apple
 * \author Patrice Trognon
 * \version 1.0
 * \date 30 mars 2022
 */

#include "strl.h"

/**
 * \fn l_strlcpy(char* dst, const char* src, size_t size)
 * \brief The l_strlcpy() function copy strings with the same input parameters and output result
     as snprintf(3).  It's designed to be safer, more consistent, and less error prone replacements for the easily
     misused functions strncpy(3)
 *
 * \param dst destination buffer
 * \param src source buffer
 * \param size buffer max size
 * \return If the return value is >= dstsize, the output string has been truncated.  It is the caller's responsibility to handle this
 */
size_t l_strlcpy(char* dst, const char* src, size_t size) {
    register char *d = dst;
    register const char *s = src;
    register size_t n = size;

    /* Copy as many bytes as will fit */
    if (n != 0 && --n != 0) {
        do {
            if ((*d++ = *s++) == 0) {
                break;
            }
        } while (--n != 0);
    }

    /* Not enough room in dst, add NUL and traverse rest of src */
    if (n == 0) {
        if (size != 0) {
            /* NUL-terminate dst */
            *d = '\0';
        }
        while (*s++) 
            ;
    }

    /* count does not include NUL */
    return(s - src - 1);
}

/**
 * \fn l_strlcat(char* dst, const char* src, size_t size)
 * \brief The l_strlcat() function concatenate strings with the same input parameters and output result
     as snprintf(3).  It's designed to be safer, more consistent, and less error prone replacements for the easily
     misused functions strncat(3)
 *
 * \param dst destination buffer
 * \param src source buffer
 * \param size buffer max size
 * \return If the return value is >= dstsize, the output string has been truncated.  It is the caller's responsibility to handle this
 */
size_t l_strlcat(char* dst, const char* src, size_t size) {
    register char *d = dst;
    register const char *s = src;
    register size_t n = size;
    size_t dlen;

    /* Find the end of dst and adjust bytes left but don't go past end */
    while (n-- != 0 && *d != '\0') {
        d++;
    }
    dlen = d - dst;
    n = size - dlen;

    if (n == 0) {
        return(dlen + strlen(s));
    }
    while (*s != '\0') {
        if (n != 1) {
            *d++ = *s;
            n--;
        }
        s++;
    }
    *d = '\0';

    /* count does not include NUL */
    return(dlen + (s - src));
}
