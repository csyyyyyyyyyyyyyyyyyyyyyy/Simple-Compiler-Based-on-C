#include "list.h"
#include "tools.h"

/*Create a double linked-list 
Tokenlist * create_list_node(Token * token)
{
    Tokenlist * tklist = (Tokenlist*)malloc(sizeof(Tokenlist));
    TNode * f1_token = (TNode*)malloc(sizeof(TNode));
    tklist->head =f1_token;
    tklist->head->prevnode = NULL;
    tklist->head->nextnode =tklist->tail;
    tklist->tail->token=NULL;
    tklist->tail->prevnode=tklist->head;
    tklist->tail->nextnode=NULL;
    /////////////////////////////////////
    
    strcpy(tklist->head->token->content,token->content);
    tklist->head->token->type= token->type;
    return tklist;
}

Tokenlist * append_token(Tokenlist * tklist,Token * token)
{
    if(tklist->head == NULL)
    {   
        tklist = create_list_node(token);
        return tklist;
    }else if(tklist->tail==NULL)
    {
        strcpy(tklist->tail->token->content,token->content);
        //tklist->tail->token->content=token->content;
        tklist->tail->token->type=token->type;
    }
    else
    {   
        TNode * new_token = (TNode*)malloc(sizeof(TNode));
        new_token->token->type=token->type;
        strcpy(new_token->token->content,token->content);
        tklist->tail->nextnode=new_token;
        tklist->tail->nextnode->prevnode=tklist->tail;
        tklist->tail=new_token;
        tklist->tail->nextnode=NULL;
        /*
        tklist->tail->nextnode = new_token;
        new_token->prevnode = tklist->tail;
        tklist->tail = new_token;
        strcpy(tklist->tail->token->content,token->content);
        tklist->tail->token->type = token->type;
        tklist->tail->nextnode = NULL;   
        
        return tklist;
    }  
}
/*
Tokenlist * prepend_token(Tokenlist * tklist, Token * token)
{
    if(tklist == NULL)
    {   
        tklist = create_list_node(token);
        return tklist;
    }else
    {   
        TNode * new_token = (TNode*)malloc(sizeof(TNode));
        new_token->nextnode = tklist->head;
        tklist->head->prevnode = new_token;
        tklist->head = new_token;
        tklist->head->token = token;
        tklist->head->prevnode = NULL;
        return tklist;
    }  
}

Tokenlist * insert_tknode_after(Tokenlist * tklist, TNode * somenode,Token * token)
{
    TNode * current = tklist->head;
    while(current != somenode)
    {   
        if(current == NULL)
           return NULL;
        current = current->nextnode;
    }
    
    TNode * new_token = (TNode*)malloc(sizeof(TNode));
    new_token ->nextnode = somenode ->nextnode;
    somenode -> nextnode ->prevnode = new_token;
    somenode -> nextnode = new_token;
    new_token -> prevnode = somenode;
    new_token -> token = token;
    return tklist;
}

TNode * find_head(Tokenlist * tklist)
{
    return tklist->head; 
}

TNode * find_tail(Tokenlist * tklist)
{
    return tklist->tail;
}

TNode * find_token(Tokenlist * tklist,const char * token_target)
{
    TNode * current = tklist->head;
    while(current != NULL)
    {
        if(current->token->content == token_target)
           return current;
        current = current->nextnode;
    }
    return NULL;
}

int count(Tokenlist * tklist)
{
    TNode * current = tklist->head;
    int count = 0;
    while(current != NULL)
    {
        count++;
        current = current->nextnode;
    }
    return count;
}


void print_token_list(Tokenlist * tklist)
{
    TNode * current = tklist->head;
    while(current != NULL)
    {
        printf("%s------------->%d",current->token->content,current->token->type);
        current = current->nextnode;
    }
}
/*
Tokenlist * delete_tknode(Tokenlist * tklist, TNode * someNode)
{
    TNode * current = tklist->head;
    if(tklist->head == NULL || someNode == NULL)
       return NULL;
    if(tklist->head == someNode)
    {
       current = someNode -> nextnode;
       current -> prevnode = NULL;
       free(someNode);
       return tklist;
    }  
    while(current != NULL && current ->nextnode != someNode)
    {
        current = current -> nextnode;
    }
    if(current != NULL)
    {
        current ->nextnode = someNode -> nextnode;
        someNode -> nextnode -> prevnode = current;
        free(someNode);
    }
    return tklist;
}

void free_token_list(Tokenlist * tklist)
{
    TNode * current = tklist->head;
    TNode * nextNd = NULL;
    while(current != NULL)
    {
        nextNd = current -> nextnode;
        free(current);
        current = nextNd;
    }
}
*/
/*void init_list(List *list){
    list->count=0;
    list->headnode=NULL;
}*/

Node * create_node(Token *token){
    Node * newnode=(Node *)malloc(sizeof(Node));
    if (newnode!=NULL)
    {
    newnode->content=(char *)calloc(30,sizeof(char));
    //assgin token value to newnode;
    if (token->content!=NULL)
    {
        strcpy(newnode->content,token->content);
    }
    newnode->linenum=token->lineno;
    newnode->type=token->type;
    newnode->prevnode=NULL;
    newnode->nextnode=NULL;
    }
    return newnode;
}

Node * append_node(Node * head,Token * token){
    Node *newnode;
    Node *tempnode;
    newnode=create_node(token);
    if(head==NULL){
        return newnode;//newnode is head
    }
    tempnode=head;
    tempnode=find_tail(head);
    tempnode->nextnode=newnode;
    tempnode->nextnode->prevnode=tempnode;
    return head;
}
void print_list(Node *headnode){
    Node *tempnode;
    tempnode=headnode;
    while(tempnode!=NULL){
        printf("%s----------%d----------line-no:%d  \n",tempnode->content,tempnode->type,tempnode->linenum);
        tempnode=tempnode->nextnode;
    }
}
Node * find_tail(Node * someNode){
    Node * current = someNode;
    while(current != NULL && current -> nextnode != NULL)
        current = current->nextnode;
    return current;
}

Node * get_next_Token(Node * currentNode)
{
    return currentNode->nextnode;
}


List * create_list(Node * headnode){
    List *new_list=(List *)malloc(sizeof(List));
    new_list->head=headnode;
    new_list->tail=find_tail(headnode);
    return new_list;
}