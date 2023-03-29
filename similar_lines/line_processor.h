#ifndef LINE_PROCESSOR_H
#define LINE_PROCESSOR_H

#include"definitions.h"

/*ustawia poczatkowe/domyslne wartosci parametrow linii*/
extern void set_line_values(Tline *line, int line_index);

/*przetwarza linie slowo po slowie, umieszcza slowa w tablicach
  liczb i nie-liczb oraz je sortuje.
  okresla czy linia jest porownywalna (nie jest: linia pusta, bledna, komentarz)*/
extern void process_line(Tline *line);

#endif /* LINE_PROCESSOR_H */
