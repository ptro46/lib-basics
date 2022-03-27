/**
 * \file strl.h
 * \brief size-bounded string copying and concatenation
 * \author open source from apple
 * \author Patrice Trognon
 * \version 1.0
 * \date 30 mars 2022
 */
#ifndef __STRL_H__
#define __STRL_H__

#include <sys/types.h>
#include <string.h>

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
size_t l_strlcpy(char* dst, const char* src, size_t size);

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
size_t l_strlcat(char* dst, const char* src, size_t size) ;

#endif /* __STRL_H__ */
