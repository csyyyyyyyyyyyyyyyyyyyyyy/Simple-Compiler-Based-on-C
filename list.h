#ifndef _LIST_H
#define _LIST_H

//make a token list for every line
#include "token.h"

typedef struct tnode
{
    Token * token;
    struct tnode * nextnode;
    struct tnode * prevnode;
}TNode;

typedef struct tokenlist
{
    TNode * head;
    TNode * tail;
}Tokenlist;

//Tokenlist * add_token(Tokenlist * tklist,Token * token_node);

//Tokenlist * create_list_node(Token * token);
//Tokenlist * append_token(Tokenlist * tklist,Token * token);
//Tokenlist * prepend_token(Tokenlist * tklist, Token * token);
//Tokenlist * insert_tknode_after(Tokenlist * tklist, TNode * somenode,Token * token);
//TNode * find_head(Tokenlist * tklist);
//TNode * find_tail(Tokenlist * tklist);
//TNode * find_token(Tokenlist * tklist,const char * token_target);
//int count(Tokenlist * tklist);
//void print_token_list(Tokenlist * tklist);
//Tokenlist * delete_tknode(Tokenlist * tklist, TNode * someNode);
//void free_token_list(Tokenlist * tklist);

Tokenlist * create_list_node(Token * token);
Tokenlist * append_token(Tokenlist * tklist,Token * token);
void print_token_list(Tokenlist * tklist);


struct node
{
    //int token_number;
    TokenType type;
    char * content;//need malloc twice;//default we set 30 as range
    int linenum;
    struct node * nextnode;
    struct node * prevnode;
};
typedef struct node Node;

struct list
{
    Node * head;
    Node * tail;
};
typedef struct list List;

/*
typedef struct list
{
    int count;
    Node * headnode;
}List;
*/
//void init_list(List *list);
struct node * create_node(Token *token);
Node * find_tail(Node * someNode);
struct node * append_node(struct node* head,Token *token);
void print_list(struct node * Headnode);


List * create_list(Node *headnode);
#endif