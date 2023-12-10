#ifndef _TOKEN_H
#define _TOKEN_H

/* Maximum number of characters in the source file */
#define MAX_FILE_LEN 10000

/* MAXRESERVED = the number of reserved words/ keywords */
#define MAX_RESERVED 6

/* MAXTOKENLEN is the maximum size of a token */
#define MAX_TOKEN_LEN 100

typedef enum 
{
    NONE,ERROR,/* book-keeping tokens, they are used to label non-final states in the DFA graph.*/
    /* reserved words 
        if else num return void while 
    */
    IF,ELSE,RETURN,VOID,WHILE,
    /* multicharacter tokens */
    ID,NUM,STR,INT,CHAR,/* comment token may can be discarded by scanner */
    NUMC,STRC,INTC,CHARC,// CONSTANT
    BOOL,TRUE,FALSE,//BOOL
    TM,ANY,DECL,RULE,VAR,CONSTANT,EP,EXPORT,IMPORT,
    /* special symbols for 
       operation  + - * / % < <= > >= == != =  |||                  ; , ( ) [ ] { } symbol
    */
    PLUS,MINUS,STAR,OVER,MOD,LT,LTE, GT, GTE, EQ, NEQ, ASSIGN,SEMI, COMMA, LPAR,RPAR, LBR, RBR, LCUR, RCUR,
    /* book-keeping token, representing the EOS (end of stream) signal received at the end of the streamer */
    ARROW, /* for --> */  
    SMILE, /* for :) */
    ENTER, /* end of line, when a new line is met */
    EOP /* end of program */
}TokenType;

typedef struct
{
    char* content;   
    TokenType type;    
    int lineno;  
}Token;

//TokenList scan(const char* fileName);  //把数据读到字符型数组里


#endif