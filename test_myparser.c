#include "tools.h"
#include "myparser.h"
#include "list.h"
#include "automata.h"
//#include "token.h"


int main(int argc,char const *argv[])
{   
    List *token_list=NULL;
    token_list=scan(argv[1]);
    print_list(token_list->head);
    TreeNode * tree;
    currentToken = getToken(token_list);
    //puts("1");
    //lastToken = currentToken;
    tree = declaration_list(token_list);
    //puts("7");
    if(currentToken->type != EOP)
       syntaxError();
       //puts("1");
    tree = print_tree(tree);
    //printf("100\n");
    // if(ERROR)
    // {
    //     printf("Parser Fail!\n");
    // }
    // else
    // {
    //     printf("Parser Success!\n");
    // }
    return 0;
}
