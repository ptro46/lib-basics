#include <stdio.h>
#include <string.h>

#include "console.h"
#include "b_types.h"

static
void color_print_f(unsigned int color, const char* fmt, va_list args) ;

static
void color_string(unsigned int color, char* color_str);

void color_print(unsigned int color, const char* fmt, ...) {
    va_list		args;

    va_start(args, fmt);
    color_print_f(color, fmt, args);
    va_end(args);    
}


void color_set(unsigned int color) {
    char psz_color_string[256];
    color_string( color, psz_color_string);
    printf("%s",psz_color_string);
}

void color_reset(void) {
    printf("\033[0m");
}

static
void color_print_f(unsigned int color, const char* fmt, va_list args) {
    char psz_color_string[256];
    color_string( color, psz_color_string);
    printf("%s",psz_color_string);
    printf(fmt,args);
    printf("\033[0m");
}

#define APPEND_COLOR(opcode, with_semilicon, withou_semilicon) \
    if ( color && opcode ) { \
        if ( wait_semilicon == true ) { \
            strcat(color_str,with_semilicon); \
        } else { \
            strcat(color_str,withou_semilicon); \
        } \
        wait_semilicon = true; \
    } \
    

static
void color_string(unsigned int color, char* color_str) {
    bool wait_semilicon = false ;
    strcpy(color_str, "\033[");


    APPEND_COLOR(BOLD, ";1", "1") ;
    APPEND_COLOR(UNDERLINE, ";4", "4") ;    
    APPEND_COLOR(INVERSE, ";7", "7") ;

    APPEND_COLOR(FG_BLACK, ";30", "30") ;
    APPEND_COLOR(FG_RED, ";31", "31");
    APPEND_COLOR(FG_GREEN, ";32", "32");
    APPEND_COLOR(FG_YELLOW, ";33", "33");
    APPEND_COLOR(FG_BLUE, ";34", "34");
    APPEND_COLOR(FG_MAGENTA, ";35", "35");
    APPEND_COLOR(FG_CYAN, ";36", "36");
    APPEND_COLOR(FG_WHITE, ";37", "37");

    APPEND_COLOR(BG_BLACK, ";40", "40") ;
    APPEND_COLOR(BG_RED, ";41", "41");
    APPEND_COLOR(BG_GREEN, ";42", "42");
    APPEND_COLOR(BG_YELLOW, ";43", "43");
    APPEND_COLOR(BG_BLUE, ";44", "44");
    APPEND_COLOR(BG_MAGENTA, ";45", "45");
    APPEND_COLOR(BG_CYAN, ";46", "46");
    APPEND_COLOR(BG_WHITE, ";47", "47");

    strcat(color_str, "m");
}
