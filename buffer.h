/**
 * \file buffer.h
 * \brief management of a buffer with auto-extension of its size 
 * \author Patrice Trognon
 * \version 1.0
 * \date 30 mars 2022
 */
#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdarg.h>
#include <stdlib.h>

/**
 * \struct buffer
 * \brief management of a buffer with auto-extension of its size 
 */
struct buffer {
    void*         data;      /*!< buffer data */
    size_t        length;    /*!< buffer total lenght */
    size_t        offset;    /*!< current offset of the space used in the buffer */
} ;

/**
 * \typedef s_buffer
 * \brief buffer
 */
typedef struct buffer s_buffer ;

/**
 * \typedef ps_buffer
 * \brief pointer to buffer
 */
typedef struct buffer *ps_buffer ;

ps_buffer   buffer_alloc(size_t initial);
void        buffer_init(ps_buffer p_buffer, size_t initial);

void        buffer_free(ps_buffer p_buffer);
void        buffer_reset(ps_buffer p_buffer);

void        buffer_append(ps_buffer p_buffer, const void* data, size_t len);
void        buffer_append_f(ps_buffer p_buffer, const char* fmt, ...) ;
void        buffer_append_v(ps_buffer p_buffer, const char* fmt, va_list args) ;
void        buffer_append_buffer(ps_buffer p_buffer, ps_buffer from) ;

char*      buffer_stringify(ps_buffer p_buffer);

#endif /* __BUFFER_H__ */


