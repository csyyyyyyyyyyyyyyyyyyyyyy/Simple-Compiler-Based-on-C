#ifndef AUTOMATA_H
#define AUTOMATA_H
#include "tools.h"
#include "token.h"
#include "list.h"
#define KEYWORD_TABLE_NUM 16
Token* automata(char * code_stream);//return a token 
int is_symbol(char ch);
int is_keyword(char buffer []);//declaration like INT CHAR etc.
//void assgin_ch(char ch1,char ch2);
extern int num;

List* scan (const char*filename);
//int is_space();
//is_upper
//is_lower
#endif