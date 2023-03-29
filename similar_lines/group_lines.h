#ifndef GROUP_LINES_H
#define GROUP_LINES_H

#include"definitions.h"

/*przetwarza po kolei linie - okresla czy sa porownywalne,
  uzupelnia i sortuje tablice liczb i nieliczb.
  Potem szuka i wypisuje grupy lini
  uwzgledniajac tylko linie porownywalne*/
extern void group_lines(Tline *lines, int lines_length);

#endif /* GROUP_LINES_H */
