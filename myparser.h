/************************
Homework 3 : Parser 
Compiler 2022 Fall MUST

myparser.h:  
For each non-trivial rule of the grammar that you designed, design a grammar function, and put the prototype and needed comments here. 

Please read the document of this homework, and provide the needed content in this file. 
*************************/  


/*************************
Names of the group members  (English and/or Chinese)
Member 1:  Pang Weicong 
Member 2:  He Yuchen
Member 3:  Chen Siyi
**************************/

#ifndef _MYPARSER_H
#define _MYPARSER_H

#include "token.h"
#include "tools.h"
#include "list.h"
#include "automata.h"
//#include "tools.h"
//#include <stdlib.h>
#define MAX_CHILDREN 20
#define MAX_ID_NUM 20
List * token_list_scan;
 
Node * currentToken ;  
Node * lastToken ;


//19 types of nodes 
//分别表示int、id、void、char、num、str、数值、变量声明、数组声明、函数声明、函数声明参数列表、
//函数声明参数、复合语句体、if、while、return、赋值、运算、数组元素、函数调用、
//函数调用参数列表、未知节点
typedef enum {IntK, IdK, VoidK,CharK,NumK,StrK,ConstK, Var_DeclK, Arry_DeclK, FunK, 
ParamsK, ParamK, CompK, Selection_StmtK, Iteration_StmtK, 
Return_StmtK, AssignK, OpK, Arry_ElemK, CallK, ArgsK, UnkownK} Nodekind;

typedef enum {Void,Integer} ExpType;

typedef struct treeNode
{
   struct treeNode * child[MAX_CHILDREN];
   struct treeNode * sibling;
   int line_no;  //所处行号
   Nodekind nodekind; //节点类型
   union     //属性
   {
       TokenType op;
       int val;
       char name[MAX_ID_NUM];
   }Attribute;
   ExpType type;    //表达式返回类型
}TreeNode;

TreeNode * syntaxTree;
int step;



//与目标Token类型ex匹配，若匹配成功则获取下一个Token
void match(TokenType ex,List * token_list);
void syntaxError();
TreeNode * print_tree(TreeNode * t);
Node * getToken(List * token_list);
TreeNode * newNode(Nodekind kind);
TreeNode * declaration_list(List * token_list);
TreeNode * declaration(List * token_list);
TreeNode * params(List * token_list);
TreeNode * param_list(TreeNode * k,List * token_list);
TreeNode * param(TreeNode * k,List * token_list);
TreeNode * compound_stmt(List * token_list);
TreeNode * local_declarations(List * token_list);
TreeNode * statement_list(List * token_list);
TreeNode * statement(List * token_list);
TreeNode * expression_stmt(List * token_list);
TreeNode * selection_stmt(List * token_list);
TreeNode * iteration_stmt(List * token_list);
TreeNode * return_stmt(List * token_list);
TreeNode * expression(List * token_list);
TreeNode * var(List * token_list);
TreeNode * simple_expression(TreeNode * k,List * token_list);
TreeNode * additive_expression(TreeNode * k,List * token_list);
TreeNode * term(TreeNode * k,List * token_list);
TreeNode * factor(TreeNode * k,List * token_list);
TreeNode * call(TreeNode * k,List * token_list);
TreeNode * args(List * token_list);

#endif
