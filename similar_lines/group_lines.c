#include "group_lines.h"
#include "line_processor.h"

bool similar_lines(Tline line1, Tline line2){
    if(line1.no_numbers_len != line2.no_numbers_len ||
       line1.numbers_len != line2.numbers_len) return false;

    /*jesli dlugosci tablic sa rowne, sprawdzamy po kolei elementy
      (tablice sa juz posortowane)*/
    int len1 = line1.no_numbers_len;
    for(int i = 0; i < len1; i++) {
        if(strcasecmp(line1.no_numbers[i],line2.no_numbers[i]) != 0) return false;
    }

    int len2 = line1.numbers_len;
    for(int j = 0; j < len2; j++) {
        if(line1.numbers[j] != line2.numbers[j]) return false;
    }
    return true;
}

void group_lines(Tline *lines, int lines_length) {
    int line_index = 0;

    while(line_index < lines_length) { /*przed grupowaniem przetwarzamy linie*/
        set_line_values(&lines[line_index], line_index);
        process_line(&lines[line_index]);
        line_index++;
    }

    for(int i = 0; i < lines_length; i++) {
        while(i < lines_length && !lines[i].comparable) i++;

        if(i == lines_length) return;

        printf("%d", lines[i].number);

        for(int j = i+1; j < lines_length; j++) {
            if(lines[j].comparable) {
                if(similar_lines(lines[i], lines[j])) {
                    printf(" %d", lines[j].number);
                    lines[j].comparable = false;
                }
            }
        }
        printf("\n");
    }
}
