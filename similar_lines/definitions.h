#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define NO_NUMBER          1001
#define INVALID            1002
#define NUMBER             1003

#define HEX_IDENT_SMALL    'x'
#define HEX_IDENT_CAPITAL  'X'
#define CHAR_ZERO          '0'
#define CHAR_PLUS          '+'
#define CHAR_MINUS         '-'
#define COMMENT_PREF       '#'

#define HEXADECIMAL        16
#define OCTAL              8

#define FIRST_VALID_CHAR   33
#define LAST_VALID_CHAR    126

struct line {
    int number;
    char *string;
    int string_len;
    long double *numbers;
    int numbers_len;
    char **no_numbers;
    int no_numbers_len;
    bool comparable;
};
typedef struct line Tline;

#endif /* DEFINITIONS_H */
