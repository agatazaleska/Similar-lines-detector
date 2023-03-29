#include "line_processor.h"
#include "word_processor.h"

void set_line_values(Tline *line, int line_index) {
    line->comparable = true;
    line->number = line_index + 1;
    line->no_numbers = NULL;
    line->no_numbers_len = 0;
    line->numbers = NULL;
    line->numbers_len = 0;
}

/*porownanie liczb w sposob jakiego wymaga qsort*/
int compare(const void *arg1, const void *arg2) {
    long double a = *((long double *)arg1);
    long double b = *((long double *)arg2);

    if(a < b) return -1;
    else if(a == b) return 0;
    else return 1;
}

/*porownanie slow w sposob jakiego wymaga qsort*/
int compare_str(const void *arg1, const void *arg2) {
    char *a = *(char **)arg1;
    char *b = *(char **)arg2;
    return strcasecmp(a, b);
}

/*pomija w napisie jedno slowo (slowa sa oddzielone bialymi znakami) oraz biale znaki po nim,
  zwraca indeks na ktorym rozpoczyna sie nowe slowo lub indeks konca napisu*/
int make_jump(char *str) {
    int i = 0;
    while(isspace(str[i]) && str[i] != 0) i++;
    if(str[i] == 0) return i;
    while(isspace(str[i]) == 0 && str[i] != 0) i++;
    return i;
}

void process_line(Tline *line) {
    char *line_s = line->string;

    if(line_s[0] == COMMENT_PREF) {
        line->comparable = false;
        return;
    }
    if((unsigned)line->string_len != strlen(line->string)) { /*wychwytuje /0 w srodku linii*/
        line->comparable = false;
        fprintf(stderr, "ERROR %d\n", line->number);
        return;
    }

    /*zmienna okreslajaca pozycje w linii, od ktorej sacanf ma zaczac wczytywanie*/
    int jump = 0;
    int type;
    char *curr_word;

    /*slowo po slowie przetwarza, identyfikuje i przydziela do tablicy. wywala z petli jak blad.*/
    while(sscanf(line_s + jump, "%ms", &curr_word) >= 0) {
        if(curr_word == NULL ) exit(1);

        type = process_word(curr_word, line);
        if(type == INVALID) {
            line->comparable = false;
            fprintf(stderr, "ERROR %d\n", line->number);
            free(curr_word);
            return;
        }
        if(type == NUMBER) free(curr_word); /*zwalniamy niepotrzebna liczbe zapisana jako (char*)*/
        else curr_word = NULL; /*zerujemy wskaznik na slowo znajdujace sie teraz w tablicy slow*/
        jump += make_jump(line_s + jump); /*przeskakujemy przetworzone slowo*/
    }
    free(curr_word);

    if(line->numbers_len == 0 && line->no_numbers_len == 0) {
        line->comparable = false; /*linia pusta*/
    }
    else {
        if(line->numbers_len > 0) qsort(line->numbers, line->numbers_len, sizeof(long double), compare);
        if(line->no_numbers_len > 0) qsort(line->no_numbers, line->no_numbers_len, sizeof(char*), compare_str);
    }
}
