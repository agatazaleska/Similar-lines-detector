CC       = gcc
CPPFLAGS =
CFLAGS   = -Wall -Wextra -std=c11 -O2
LDFLAGS  =

.PHONY: all clean

all: similar_lines

similar_lines: similar_lines.o group_lines.o line_processor.o word_processor.o read_data_free_memory.o

line_processor.o: line_processor.c line_processor.h definitions.h

word_processor.o: word_processor.c word_processor.h definitions.h

group_lines.o: group_lines.c group_lines.h definitions.h

read_data_free_memory.o: read_data_free_memory.c read_data_free_memory.c definitions.h

similar_lines.o: similar_lines.c group_lines.h read_data_free_memory.h definitions.h

clean:
	rm -f *.o similar_lines
