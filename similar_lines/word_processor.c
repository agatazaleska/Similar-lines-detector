#include "word_processor.h"

int set_type(char *end) {
    if(*end == 0) return NUMBER;
    else return NO_NUMBER;
}

/*sprawdza czy slowo zaczyna sie od "0X" lub "0x"*/
bool check_0x(char *word) {
    if(strlen(word) < 2) return false;
    else if(word[0] == CHAR_ZERO && (word[1] == HEX_IDENT_SMALL ||
                                     word[1] == HEX_IDENT_CAPITAL)) return true;
    else return false;
}

/*przetwarza slowa zaczynajace sie na "0" lub "0x/0X"
  number - liczba o docelowym formacie, w ktorym bedzie przechowywana*/
int process_non_decimal(char *word, long double *number, int base) {
    char *end;
    unsigned long int_number;

    if(base == HEXADECIMAL) {
        if(strlen(word) == 2) { /*liczba ma postac "0x" lub "0X"*/
            *number = 0;
            return NUMBER;
        }
        int_number = strtoul(word, &end, HEXADECIMAL);
        if(*end == 0) {
            *number = (long double)int_number;
            return NUMBER;
        }
        else return NO_NUMBER;
    }
    else {
        int_number = strtoul(word, &end, 0);
        if(*end != 0) { /*liczba zaczynajaca sie od 0 moze byc zmiennoprzecinkowa*/
            *number = strtold(word, &end);
            return set_type(end);
        }
        else {
            *number = (long double)int_number;
             return NUMBER;
        }
    }
}

bool is_invalid(char *word) {
    int word_size = strlen(word);
    char current;

    for(int i = 0; i < word_size; i++) {
        current = word[i];
        if(!(current >= FIRST_VALID_CHAR && current <= LAST_VALID_CHAR)) {
            return true;
        }
    }
    return false;
}

/*dodaje do odpowiedniej tablicy slowo (w przypadku typu NO_NUMBER)
  lub przekonwertowana na long double liczbe (w przypadku typu NUMBER)*/
void add_to_array(char *word, int type, Tline *line, long double number) {
    if(type == NUMBER) {
        line->numbers = realloc(line->numbers,
                        (unsigned)(line->numbers_len + 1) * sizeof(*(line->numbers)));
        if(line->numbers == NULL) exit(1);

        line->numbers[line->numbers_len] = number;
        line->numbers_len += 1;
    }
    else if(type == NO_NUMBER) {
        line->no_numbers = realloc(line->no_numbers,
                           (unsigned)(line->no_numbers_len + 1) * sizeof(*(line->no_numbers)));
        if(line->no_numbers == NULL) exit(1);

        line->no_numbers[line->no_numbers_len] = word;
        line->no_numbers_len += 1;
    }
}

int process_word(char *word, Tline *line) {
    long double number;
    char *end;
    char first_char = word[0];
    int type;

    if(is_invalid(word)) return INVALID;

    else {
        if(first_char == CHAR_ZERO) { /*liczba moze byc osemkowa/szesnastkowa*/
            char second_char = word[1];
            if(second_char == 0) {
                number = 0;
                type = NUMBER;
            }
            else if(second_char == HEX_IDENT_SMALL || second_char == HEX_IDENT_CAPITAL) {
                type = process_non_decimal(word, &number, HEXADECIMAL);
            }
            else type = process_non_decimal(word, &number, OCTAL);
        }
        /*liczby szesnastkowe i osemkowe nie zaczynaja sie od +/-*/
        else if(first_char == CHAR_MINUS || first_char == CHAR_PLUS) {
            if(check_0x(word + 1)) type = NO_NUMBER;
            else {
                number = strtold(word, &end);
                type = set_type(end);
            }
        }
        else {
            number = strtold(word, &end);
            if(isnan(number)) type = NO_NUMBER;
            else type = set_type(end);
        }
    }

    add_to_array(word, type, line, number);
    return type;
}
