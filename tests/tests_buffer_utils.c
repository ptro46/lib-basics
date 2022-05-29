#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"

void    buffer_dump(ps_buffer p_buffer) {
    printf("buffer:data(%p) offset(%zu) length(%zu)\n\t%s\n",p_buffer->data, p_buffer->offset, p_buffer->length, (char*)p_buffer->data);
}

