#ifndef READ_DATA_FREE_MEMORY_H
#define READ_DATA_FREE_MEMORY_H

#include "definitions.h"

/*zwalnia wszystkie tablice w poszczegolnych liniach oraz tablice linii*/
extern void free_lines(Tline *lines, int lines_length);

/*wczytuje dane za pomoca getline, zwraca dlugosc tablicy linii*/
extern int read_data(Tline **lines);

#endif /* READ_DATA_FREE_MEMORY_H */
