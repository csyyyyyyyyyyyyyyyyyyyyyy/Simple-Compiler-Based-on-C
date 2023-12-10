#ifndef _TOOLS_H
#define _TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "list.h"

typedef enum
{
  FALSE,
  TRUE
}Boolean;

extern Boolean A_debugAnalyzer;

#define MAX_NUM 10000
#define True 1
#define False 0
//char buffer[10];//store intermediate char_stream
int set_times;
char * Code_stream;
char * read_file(const char *Filename);//read programfile and store it into an char array by lines
void free_code_stream();
int get_file_lines(char *Code_stream);
void print_lines_code(char *Code_stream,int lines,int *table);
char *rtrim(char *str);
char *ltrim(char *str);
char *trim(char *str);
int *get_table(int lines,char *Code_stream);
void filter(char *r,int pProject);
#endif