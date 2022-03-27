/**
 * \file buffer.c
 * \brief management of a buffer with auto-extension of its size 
 * \author Patrice Trognon
 * \version 1.0
 * \date 30 mars 2022
 */
#include <sys/types.h>

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "buffer.h"

/**
 * \brief used by buffer_append_v
 */
#define SIZE_BUF                1024

/**
 * \fn ps_buffer buffer_alloc(size_t initial)
 * \brief alloc struct buffer and call buffer_init with initial size
 *
 * \param initial buffer allocation size
 * \return struct buffer pointer, must be free
 */
ps_buffer
buffer_alloc(size_t initial) {
    ps_buffer buf = NULL ;

    buf = calloc(1,sizeof(s_buffer));
    buffer_init(buf, initial);
    return buf;
}

/**
 * \fn void buffer_init(ps_buffer p_buffer, size_t initial)
 * \brief alloc buffer with initial size
 *
 * \param p_buffer struct buffer pointer
 * \param initial buffer allocation size
 */
void
buffer_init(ps_buffer p_buffer, size_t initial) {
    if ( p_buffer != NULL ) {
        if ( initial > 0 ) {
            p_buffer->data = calloc(initial,sizeof(char));
        } else {
            p_buffer->data = NULL ;
        }
        p_buffer->length = initial;
        p_buffer->offset = 0;
    }
}
    
/**
 * \fn void buffer_free(ps_buffer p_buffer)
 * \brief free buffer data, reset offset and length 
 *
 * \param p_buffer struct buffer pointer
 */
void
buffer_free(ps_buffer p_buffer) {
    if ( p_buffer != NULL ) {
        if ( p_buffer->data != NULL ) {
            free(p_buffer->data);
            p_buffer->length = 0;
            p_buffer->offset = 0;
        }
    }
}

/**
 * \fn void buffer_reset(ps_buffer p_buffer)
 * \brief memset buffer data with 0, and reset offset, data is not free
 *
 * \param p_buffer struct buffer pointer
 */
void
buffer_reset(ps_buffer p_buffer) {
    if ( p_buffer != NULL ) {
        if ( p_buffer->data != NULL ) {
            memset(p_buffer->data, 0, p_buffer->offset);
        }
        p_buffer->offset = 0;       
    }
}

/**
 * \fn void buffer_append(ps_buffer p_buffer, const void* data, size_t len)
 * \brief append the data of size len at the end of the buffer
 *
 * \param p_buffer struct buffer pointer
 * \param data pointer to the data to add
 * \param len size of the data
 */
void
buffer_append(ps_buffer p_buffer, const void* data, size_t len) {
    if ( p_buffer != NULL ) {
        if ( p_buffer->data == NULL ) {
            buffer_init(p_buffer, len + len/2);
        }
        if ( p_buffer->offset + len > p_buffer->length ) {
            p_buffer->length += (len + len/2) ;
            p_buffer->data = realloc(p_buffer->data, p_buffer->length);
            memset(((char*)p_buffer->data) + p_buffer->offset, 0, p_buffer->length - p_buffer->offset);
        }
        memcpy(((char*)p_buffer->data) + p_buffer->offset, data, len);
        p_buffer->offset += len;
    }
}

/**
 * \fn void buffer_append_f(ps_buffer p_buffer, const char* fmt, ...)
 * \brief append format to the data
 *
 * \param p_buffer struct buffer pointer
 * \param fmt format
 * \param ... format parameters
 */
void
buffer_append_f(ps_buffer p_buffer, const char* fmt, ...) {
    va_list		args;

    va_start(args, fmt);
    buffer_append_v(p_buffer, fmt, args);
    va_end(args);
}

/**
 * \fn void buffer_append_v(ps_buffer p_buffer, const char* fmt, va_list args)
 * \brief appand format with va_list to the data
 *
 * \param p_buffer struct buffer pointer
 * \param fmt format
 * \param args va_list
 */
void
buffer_append_v(ps_buffer p_buffer, const char* fmt, va_list args) {
    if ( p_buffer != NULL ) {
        int     l=0;
        va_list copy_args;
        char    *pb=NULL ;
        char    b[SIZE_BUF];

        va_copy(copy_args, args);
        l = vsnprintf(b, sizeof(b), fmt, args) ;
        if ( l > 0 ) {
            if ( ((size_t)l) >= sizeof(b) ) {
                l=vasprintf(&pb, fmt, copy_args);
                if ( l > 0 ) {
                    buffer_append(p_buffer, pb, l);
                    free(pb);
                }
            } else {
                buffer_append(p_buffer, b, l);
            }
        }
        va_end(copy_args);
    }
}

/**
 * \fn void buffer_append_buffer(ps_buffer p_buffer, ps_buffer from)
 * \brief append buffer to the data
 *
 * \param p_buffer struct buffer pointer
 * \param from struct buffer pointer data to by copied
 */
void
buffer_append_buffer(ps_buffer p_buffer, ps_buffer from) {
    if ( p_buffer != NULL && from != NULL && from->data != NULL ) {
        buffer_append(p_buffer, from->data, from->offset) ;
    }
}

/**
 * \fn void buffer_stringify(ps_buffer p_buffer)
 * \brief transform buffer to c string with '\0' at offset
 *
 * \param p_buffer struct buffer pointer
 * \return pointer to c string end with '\0'
 */
char*
buffer_stringify(ps_buffer p_buffer) {
    if ( p_buffer != NULL ) {
        char c = '\0';
        buffer_append(p_buffer, &c, sizeof(c));                      
    }
    return (char*)p_buffer->data ;
}
