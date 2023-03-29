#include "read_data_free_memory.h"

void free_lines(Tline *lines, int lines_length) {
    for(int i = 0; i < lines_length; i++) {
        free(lines[i].string);

        for(int j = 0; j < lines[i].no_numbers_len; j++) {
            free(lines[i].no_numbers[j]);
        }
        if(lines[i].numbers_len > 0) free(lines[i].numbers);
        if(lines[i].no_numbers_len > 0) free(lines[i].no_numbers);
    }

    free(lines);
}

/*wczytanie linijek z wejsca do tablicy lines
  oraz uzupelnienie tresci i dlugosci linii w strukturze*/
int read_data(Tline **lines) {
    int lines_length = 0;
    char *curr = NULL;
    int i = 0;
    size_t size;

    int line_len = getline(&curr, &size, stdin);
    while(line_len > 0) {
        if(curr == NULL) exit(1);

        if(i == lines_length) {
            *lines = realloc(*lines, (2 * i + 1) * sizeof(**lines));
            if(*lines == NULL) exit(1);
            lines_length = lines_length * 2 + 1;
        }
        (*lines)[i].string = curr;
        (*lines)[i].string_len = line_len;
        curr = NULL;
        i++;
        line_len = getline(&curr, &size, stdin);
    }

    free(curr);
    lines_length = i;
    return lines_length;
}
