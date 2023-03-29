/* Male zadanie zaliczeniowe na indywidualny projekt programistyczny.
   Autor: Agata Zaleska.

   Program wczytuje wiersze z wejscia i odpowiednio je przetwarza.
   Wynikiem sa uporzadkowane grupy wierszy podobnych (kazda grupa w osobnej linii).
   Podobienstwo wierszy jest okreslone w tresci zadania.

   Program zostal podzielony na 5 modulow:
   similar_lines, read_data_free_memory, group_lines, line_processor, word_processor.
   W pliku definitions.h sa zawarte definicje oraz biblioteki z ktorych korzysta program.*/

#include "group_lines.h"
#include "definitions.h"
#include "read_data_free_memory.h"

int main(void) {
    Tline *lines = NULL;
    int lines_length = read_data(&lines);

    group_lines(lines, lines_length);
    free_lines(lines, lines_length);

    return 0;
}
