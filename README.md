# Similar-lines-detector

## Project description

This is a project task for "Individual programming project" course at University of Warsaw.
The program searches for groups of similar lines in a given text.

Two numbers are similar if they represent the same number, two non-numbers are similar if they represent the same word, in lowercase, uppercase or mix of them. Two lines are similar if they contain identical multisets of non-numbers and numbers.

Program description
The program reads lines from std in. The program ignores does not take into account lines beggining with '#' and empty lines. Each line of the output represents one group of similar lines. The lines are represented by their numbers, the numbers start from one.

Usage:
makefile
./similar_lines
