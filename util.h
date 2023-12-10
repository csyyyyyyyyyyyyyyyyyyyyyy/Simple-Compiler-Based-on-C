/****************************************************/
/* File: util.h                                     */
/* The interface of general tools for the           */
/* C-Minus compiler                                 */
/* Programming designed by Zhiyao Liang             */
/* MUST                                             */
/****************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_


typedef enum{
  FALSE,
  TRUE
}Boolean;


/* Print the message msg, then wait for the user to hit the enter/return key.
 * The input queue is cleared before this function returns.
 */
void pause_msg(const char * msg);

/* <Parameter:>
 * str:  a character string.
 * <Return:>
 * A copy (a clone) of the input string str, including the ending '\0'. The space of the clone does not overlap with the space of str.
 * */
char * string_clone(const char* str);

/* clear the input queue of stdin. This should be done after the previous input and before the next input. */
void clear_input_queue(void);

/* same as malloc(), but when unsuccessful,  print some error message. */
void * checked_malloc(int len);


/* read all characters from a file stream into a character array, which contains arrayLength elements. 
at  most arrayLength - 1 characters can be read into array, because a '\0' will be appended into */
int read_file_to_char_array( char * array, int arrayLength, FILE * stream);

/* given a string str, create a new string which contains the characters in str from (including) index begin, to index (including) end */
char *  clone_string_section(const char * str, int begin, int end);

#endif
