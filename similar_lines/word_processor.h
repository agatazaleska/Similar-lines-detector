#ifndef WORD_PROCESSOR_H
#define WORD_PROCESSOR_H

#include "definitions.h"

/*przetwarza słowo - określa i zwraca typ oraz
  umieszcza je w odpowiednej tablicy w strukturze linii*/
extern int process_word(char *word, Tline *lines);

#endif /* WORD_PROCESSOR_H */
