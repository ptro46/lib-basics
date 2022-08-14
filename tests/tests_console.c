#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"

#include "console.h"

#define test_foreground(mask, text) \
    color_print(mask , text); \
    strcpy(b,"bold "); \
    color_print(BOLD + mask , strcat(b,text)); \
    strcpy(b,"underline "); \
    color_print(UNDERLINE + mask , strcat(b,text)); \
    strcpy(b,"inverse "); \
    color_print(INVERSE + mask , strcat(b,text)); \
    strcpy(b,"bold underline "); \
    color_print(BOLD + UNDERLINE + mask , strcat(b,text));
    

#define test_background(mask, text) \
    color_print(mask , text); \
    strcpy(b,"bold "); \
    color_print(BOLD + mask , strcat(b,text)); \
    strcpy(b,"underline "); \
    color_print(UNDERLINE + mask , strcat(b,text)); \
    strcpy(b,"bold underline "); \
    color_print(BOLD + UNDERLINE + mask , strcat(b,text));

void     test_console(void) {
    char b[256];

    test_foreground(FG_RED, "FG_RED\n");
    test_foreground(FG_GREEN, "FG_GREEN\n");
    test_foreground(FG_YELLOW, "FG_YELLOW\n");
    test_foreground(FG_BLUE, "FG_BLUE\n");
    test_foreground(FG_MAGENTA, "FG_MAGENTA\n");
    test_foreground(FG_CYAN, "FG_CYAN\n");
    test_foreground(FG_WHITE, "FG_WHITE\n");

    test_background(BG_RED, "BG_RED\n");
    test_background(BG_GREEN, "BG_GREEN\n");
    test_background(BG_YELLOW, "BG_YELLOW\n");
    test_background(BG_BLUE, "BG_BLUE\n");
    test_background(BG_MAGENTA, "BG_MAGENTA\n");
    test_background(BG_CYAN, "BG_CYAN\n");
    test_background(BG_WHITE, "BG_WHITE\n");
}
