#include "myparser.h"

void match(TokenType ex,List * token_list)
{   
    if (ex== EOP)
    {
        return;
    }

    if(currentToken->type == ex)
    {   
        //puts("31");
        getToken(token_list);
    }
    else
    {   
        //puts("32");
        syntaxError();
    }
}

void syntaxError()
{
    printf("Syntax error at line: %d, token: %s, token type: %d\n",currentToken->linenum,currentToken->content,currentToken->type);
}

Node * getToken(List * token_list)   //get the next token
{
    if(currentToken == NULL && lastToken == NULL)
    {
        currentToken = token_list->head;
        lastToken = token_list->head;
    }
    else
    {
        lastToken = currentToken;
        currentToken = currentToken->nextnode;
    }
    return currentToken;
}

TreeNode * newNode(Nodekind kind)
{
    TreeNode * new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if(new_node == NULL)
    {
       printf("Malloc Failed.\n");
    }
    else
    {
       int i;
       for(i=0;i<MAX_CHILDREN;i++)
       {   
           new_node->child[i] = NULL;
       } 
       //printf("total number of i is %d\n",i);
       new_node->sibling = NULL;
       new_node->nodekind = kind;
       new_node->line_no = currentToken->linenum;
       if(kind == OpK || kind == IntK || kind == IdK)
          new_node->type = Integer;
       if(kind == IdK)
          strcpy(new_node->Attribute.name,"");
          //new_node->Attribute.name = "";
       if(kind == ConstK)
          new_node->Attribute.val = 0;
    }
    return new_node;
}

void printSpace(int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("   ");
    }
}

TreeNode * print_tree(TreeNode * t)
{
    int i;
    while(t != NULL)
    {
        printSpace(step);
        switch(t->nodekind)
        {
            case IntK:
                 printf("IntK\n");
                 break;
            case IdK:
                 printf("IdK: %s\n",t->Attribute.name);
                 break;
            case VoidK:
                 printf("VoidK\n");
                 break;
            case CharK:
                 printf("CharK\n");
                 break;
            case NumK:
                 printf("NumK\n");
                 break;
            case StrK:
                 printf("StrK\n");
                 break;
            case ConstK:
                 printf("ConstK: %d\n",t->Attribute.val);
                 break;
            case Var_DeclK:
                 printf("Var_DeclK\n");
                 break;
            case Arry_DeclK:
                 printf("Arry_DeclK\n");
                 break;
            case FunK:
                 printf("FunK\n");
                 break;
            case ParamK:
                 printf("ParamK\n");
                 break;
            case ParamsK:
                 printf("ParamsK\n");
                 break;
            case CompK:
                 printf("CompK\n");
                 break;
            case Selection_StmtK:
                 printf("If\n");
                 break;
            case Iteration_StmtK:
                 printf("While\n");
                 break;
            case Return_StmtK:
                 //puts("50");
                 printf("Return\n");
                 break;
            case AssignK:
                 printf("Assign\n");
                 break;
            case OpK:  //should be fixed
                 printf("Op:\n");
                 break;
            case Arry_ElemK:
                 printf("Arry_ElemK\n");
                 break;
            case CallK:
                 printf("CallK\n");
                 break;
            case ArgsK:
                 printf("ArgsK\n");
                 break;
                 
            default:
                 printf("UnknownK: UnKnown exp kind\n");
                 break;
        }    
        
        step++;
        
        for(i=0;i<MAX_CHILDREN;i++)
        {   
            if(t->child[i] != NULL)
            {   
                //puts("56");
                print_tree(t->child[i]);
            }
        }
        
        step--;
        t = t -> sibling;
        
    }
    return t;
    // printf("%s %d\n",currentToken->content,currentToken->type);
}

TreeNode * declaration_list(List * token_list)
{
    
    TreeNode * t = declaration(token_list);
    //puts("1");
    TreeNode * p = t;
    //printf("%s %d\n",currentToken->content,currentToken->type);
    //puts("5");
    
    /*Find int and void types when syntax analysis is wrong at the beginning, 
      filter out all Tokens before int and void, and prevent one error followed 
      by a hundred errors at the beginning*/
      //puts("9");
      /*
      if (currentToken==NULL)
        {
            puts("currentToken is NULL\n");
        }
       */ 
    while((currentToken->type != INT) && (currentToken->type != VOID) && (currentToken->type != NUM)
    &&(currentToken->type != CHAR) && (currentToken->type != STR) && (currentToken->type != EOP))
    {
        puts("12");
        if (currentToken==NULL)
        {
            break;
        }
        
        syntaxError();
        //puts("13");

        getToken(token_list);
        //puts("10");
        if(currentToken->type == EOP)
           break;
    }
    
    //printf("%s %d\n",currentToken->content,currentToken->type);
    while((currentToken->type == INT) || (currentToken->type == VOID) || (currentToken->type == NUM) ||
          (currentToken->type == CHAR) || (currentToken->type == STR))
    {   
        //printf("%s %d\n",currentToken->content,currentToken->type);
        //puts("11");
        TreeNode * q = declaration(token_list);
        if(q != NULL)
        {
            if(t == NULL)
                t = p = q;
            else
            {
                p->sibling = q;
                p = q;
            }
        }
    }
    match(EOP,token_list);
    return t;
}


TreeNode * declaration(List * token_list)
{   
    //puts("22");
    TreeNode * t = NULL;
    TreeNode * p = NULL;
    TreeNode * q = NULL;
    TreeNode * s = NULL;
    if(currentToken->type == INT)
    {
        //puts("1");
        p = newNode(IntK);
        match(INT,token_list);
        //puts("2");
    }
    else if(currentToken->type == VOID)
    {
        p = newNode(VoidK);
        match(VOID,token_list);
    }
    else if(currentToken->type == CHAR)
    {
        p = newNode(CharK);
        match(CHAR,token_list);
    }
    else if(currentToken->type == NUM)
    {
        p = newNode(NumK);
        match(NUM,token_list);
    }
    else if(currentToken->type == STR)
    {
        p = newNode(StrK);
        match(STR,token_list);
    }
    else if(currentToken->type == WHILE)
    {
        p = newNode(Iteration_StmtK);
        match(WHILE,token_list);
    }
    else
    {
        syntaxError();
    }
    
    if((p != NULL) && (currentToken->type == ID))
    {
        //q->Attribute.name=(char *)calloc(20,sizeof(char));
        //puts("4");
        q = newNode(IdK);
        //puts("5");
        strcpy(q->Attribute.name,currentToken->content);
        //puts("6");
        //puts(q->Attribute.name);
        match(ID,token_list);
    
    
        if(currentToken->type == LPAR)      // '(' declaration of function
        {
            t = newNode(FunK);
            t->child[0] = p;
            t->child[1] = q;
            match(LPAR,token_list);
            t->child[2] = params(token_list);
            match(RPAR,token_list);
            //puts("50");
            t->child[3] = compound_stmt(token_list);
        }
        else if(currentToken->type == LBR)   // '[' declaration of array
        {
            t = newNode(Var_DeclK);
            TreeNode * m = newNode(Arry_DeclK);
            match(LBR,token_list);
            match(NUM,token_list);
            s = newNode(ConstK);
            s->Attribute.val = atoi(lastToken->content);
            m->child[0] = q;
            m->child[1] = s;
            t->child[0] = p;
            t->child[1] = m;
            match(RBR,token_list);
            match(SEMI,token_list);
        }
        else if(currentToken->type == SEMI)  // end with ';'
        {
            //puts("3");
            t = newNode(Var_DeclK);
            t->child[0] = p;
            t->child[1] = q;
            match(SEMI,token_list);
           //puts("4");
        }
        else
        {
            syntaxError();
        }
    }
    else
    {
        syntaxError();
    }
    return t;
}

TreeNode * params(List * token_list)
{
    TreeNode * t = newNode(ParamsK);
    TreeNode * p = NULL;
    TreeNode * s = NULL;
    if(currentToken->type == VOID)
    {
        p = newNode(VoidK);
        match(VOID,token_list);
        if(currentToken->type == RPAR)   //the parameter list is (void)
        {
            if(t != NULL)
               t->child[0] = p;
        }
        else  // the parameter list is (void id,[......])
        {
            t->child[0] = param_list(p,token_list);
        }
    }
    else if(currentToken->type == INT || currentToken->type == CHAR || currentToken->type == NUM || currentToken->type == STR)  
    {
        t->child[0] = param_list(p,token_list);
    }
    else if(currentToken->type == STRC)
    {
        p = newNode(StrK);
        match(STRC,token_list);
        match(COMMA,token_list);
        s = newNode(currentToken->type);
        t->child[0] = p;
        t->child[1] = s;
        match(currentToken->type,token_list);
    }
    else
    {
        syntaxError();
    }
    return t;
}

TreeNode * param(TreeNode * k,List * token_list)
{
    TreeNode * t = newNode(ParamK);
    TreeNode * p = NULL;
    TreeNode * q = NULL;
    
    if(k == NULL && currentToken->type == INT)
    {
        p = newNode(IntK);
        match(INT,token_list);
    }
    else if(k!=NULL)
    {
        p = k;
    }
    if(p != NULL)
    {
        t->child[0] = p;
        if(currentToken->type == ID)
        {
            q = newNode(IdK);
            strcpy(q->Attribute.name,currentToken->content);
            t->child[1] = q;
            match(ID,token_list);
        }
        else
        {
            syntaxError();
        }
        
        if((currentToken->type == LBR) && (t->child[1] != NULL))
        {
            match(LBR,token_list);
            t->child[2] = newNode(IdK);
            match(RBR,token_list);
        }
        else
        {
            return t;
        }
    }
    else
    {
        syntaxError();
    }
    return t;
}

TreeNode * param_list(TreeNode * k,List * token_list)
{
    TreeNode * t = param(k,token_list);
    TreeNode * p = t;
    k = NULL;
    while(currentToken->type == COMMA)
    {
        TreeNode * q = NULL;
        match(COMMA,token_list);
        q = param(k,token_list);
        if(q != NULL)
        {
            if(t == NULL)
            {
                t = p = q;
            }
            else
            {
                p -> sibling = q;
                p = q;
            }
        }
    }
    return t;    
}

TreeNode * compound_stmt(List * token_list)
{
    TreeNode * t = newNode(CompK);
    //printf("current token: %s %d\n",currentToken->content,currentToken->type); //correct
    match(LCUR,token_list);
    //printf("current token: %s %d\n",currentToken->content,currentToken->type); //correct
    //puts("30");
    t->child[0] = local_declarations(token_list);
    //printf("%s %d\n",currentToken->content,currentToken->type);
    t->child[1] = statement_list(token_list);
    //puts("101");
    match(RCUR,token_list);
    //printf("%s %d\n",currentToken->content,currentToken->type);
    return t;
}

TreeNode * local_declarations(List * token_list)
{   
    //printf("%s %d\n",currentToken->content,currentToken->type);
    TreeNode * t = NULL;
    TreeNode * q = NULL;
    TreeNode * p = NULL;
    
    while(currentToken->type == INT || currentToken->type == VOID || currentToken->type == CHAR || currentToken->type == NUM)
    {   
        //printf("current token: %s %d\n",currentToken->content,currentToken->type); 
        p = newNode(Var_DeclK);
        if(currentToken->type == INT)
        {
            TreeNode * q1 = newNode(IntK);
            p->child[0] = q1;
            match(INT,token_list);
        }
        else if(currentToken->type == VOID)
        {
            TreeNode * q1 = newNode(VoidK);
            p->child[0] = q1;
            match(VOID,token_list);
        }
        else if(currentToken->type == CHAR)
        {
            TreeNode * q1 = newNode(CharK);
            p->child[0] = q1;
            match(CHAR,token_list);
        }
        else if(currentToken->type == NUM)
        {
            TreeNode * q1 = newNode(NumK);
            p->child[0] = q1;
            match(NUM,token_list);
        }
        
        if((p!=NULL) && (currentToken->type == ID))
        {
            TreeNode * q2 = newNode(IdK);
            strcpy(q2->Attribute.name,currentToken->content);
            p->child[1] = q2;
            match(ID,token_list);
            
            if(currentToken->type == LBR)
            {
                TreeNode * q3 = newNode(Var_DeclK);
                p->child[3] = q3;
                match(LBR,token_list);
                match(RBR,token_list);
                match(SEMI,token_list);
            }
            else if(currentToken->type == SEMI)
            {
                match(SEMI,token_list);
            }
            else
            {
                match(SEMI,token_list);
            }
        }
        else
        {
            syntaxError();
        }
        
        if(p!= NULL)
        {
            if(t==NULL)
              t = q = p;
            else
            {
                q->sibling = p;
                q = p;
            }
        }
    }
    
    return t;
}

TreeNode * statement_list(List * token_list)
{   
    //printf("current token: %s %d\n",currentToken->content,currentToken->type); 
    TreeNode * t = statement(token_list);
    TreeNode * p = t;
    //printf("current token: %s %d\n",currentToken->content,currentToken->type);
    while(currentToken->type == IF || currentToken->type == LCUR || currentToken->type == ID || 
          currentToken->type == WHILE || currentToken->type == RETURN || currentToken->type == SEMI
          || currentToken->type == LPAR || currentToken->type == INTC)
    {   
        //puts("48");
        TreeNode * q;
        q = statement(token_list);
        if(q != NULL)
        {
            if(t == NULL)
            {
                t = p = q;
            }
            else
            {
                p->sibling = q;
                p = q;
            }
        }
    }
    return t;
}

TreeNode * statement(List * token_list)
{
    TreeNode * node = NULL;
    //printf("%s %d\n",currentToken->content,currentToken->type);
    switch(currentToken->type)
    {
        // case IF:
        //     node = selection_stmt(token_list);
        //     break;
        // case WHILE:
        //     node = iteration_stmt(token_list);
        //     break;
        // case RETURN:
        //     puts("49");
        //     node = return_stmt(token_list);
        //     break;
        case LCUR:
            //puts("46");
            node = compound_stmt(token_list);
            break;
        case ID:
            if(strcmp(currentToken->content,"while") == 0)   /*tokentype of while is ID, not while*/
            {
                node = iteration_stmt(token_list);
            }
            else if(strcmp(currentToken->content,"return") == 0) /*tokentype of return is ID, nor return*/
            {   
                //puts("49");
                node = return_stmt(token_list); 
            }
            else if(strcmp(currentToken->content,"if") == 0)
            {
                node = selection_stmt(token_list);
            }  
            else
            {
                //puts("41");
                node = expression_stmt(token_list);
            }
            break;
        case SEMI:
            node = expression_stmt(token_list);
            break;
        case LPAR:
            node = expression_stmt(token_list);
            break;
        case INTC:
            node = expression_stmt(token_list);
            break;
        default:
            syntaxError();
            currentToken = getToken(token_list);
            break;       
    }
    return node;
}

TreeNode * selection_stmt(List * token_list)
{
    TreeNode * node = newNode(Selection_StmtK);
    match(ID,token_list);
    match(LPAR,token_list);
    
    if(node != NULL)
       node->child[0] = expression(token_list);
       
    match(RPAR,token_list);
    node->child[1] = statement(token_list);
    
    if(currentToken->type == ELSE)
    {
        match(ELSE,token_list);
        if(node != NULL)
          node->child[2] = statement(token_list);
    }
    
    return node;
}

TreeNode * iteration_stmt(List * token_list)
{   
    //printf("%s %d\n",currentToken->content,currentToken->type);
    TreeNode * node = newNode(Iteration_StmtK);
    match(ID,token_list);
    match(LPAR,token_list);
    //printf("%s %d\n",currentToken->content,currentToken->type);
    if(node != NULL)
    {  
       //puts("41");
       node->child[0] = expression(token_list);
    }
    
    match(RPAR,token_list);
    //printf("%s %d\n",currentToken->content,currentToken->type);
    if(node != NULL)
    {  
       //puts("60");
       node->child[1] = statement(token_list); 
    }
    //printf("%s %d\n",currentToken->content,currentToken->type);
    return node;
}

TreeNode * return_stmt(List * token_list)
{
    TreeNode * node = newNode(Return_StmtK);
    match(ID,token_list);
    //printf("%s %d\n",currentToken->content,currentToken->type);
    if(currentToken->type == SEMI)
    {
        match(SEMI,token_list);
        return node;
    }
    else
    {   
        if(node != NULL)
           node->child[0] = expression(token_list);
    //     printf("%s %d\n",currentToken->content,currentToken->type);
    }
    match(SEMI,token_list);
    return node;
}

TreeNode * expression_stmt(List * token_list)
{
    TreeNode * t = NULL;
    if(currentToken->type == SEMI)
    {
        match(SEMI,token_list);
        return t;
    }
    else
    {
        t = expression(token_list);
        match(SEMI,token_list);
    }
    return t;
}

TreeNode * expression(List * token_list)
{
    TreeNode * t = var(token_list);
    if(t == NULL)
    {
        t = simple_expression(t,token_list);
    }
    else
    {   
        //puts("43");
        TreeNode * p = NULL;
        if(currentToken->type == ASSIGN)
        {   
            p = newNode(AssignK);
            //printf("%s %d\n",currentToken->content,currentToken->type);
            // printf("%s %d\n",lastToken->content,lastToken->type);
            strcpy(p->Attribute.name,lastToken->content);
            match(ASSIGN,token_list);
            p->child[0] = t;
            // if(p->child[0] != NULL)
            // {
            //     puts("52");
            // }
            p->child[1] = expression(token_list);
            // if(p->child[1] != NULL)
            // {
            //     puts("53");
            // }
            return p;
        }
        else
        {   
            //puts("47");+
            t = simple_expression(t,token_list);   //var and call types in simple_expression
        }
    }
    return t;
}

TreeNode * simple_expression(TreeNode * k,List * token_list)
{   
    //puts("45");
    TreeNode * node = additive_expression(k,token_list);
    k=NULL;
    if(EQ == currentToken->type || GT == currentToken->type
    || GTE == currentToken->type || LT == currentToken->type ||
    LTE == currentToken->type || NEQ == currentToken->type)
    {
        TreeNode * qnode = newNode(OpK);
        qnode->Attribute.op = currentToken->type;
        qnode->child[0]=node;
        node=qnode;
        match(currentToken->type,token_list);
        node->child[1]=additive_expression(k,token_list);
        //return node;
    }
    return node;
}

TreeNode * additive_expression(TreeNode * k,List * token_list){
    TreeNode * node = term(k,token_list);
    k = NULL;
    while((currentToken->type==PLUS)||(currentToken->type==MINUS)){   //we are here now +
        TreeNode * qnode = newNode(OpK);
        qnode->Attribute.op = currentToken->type;
        qnode->child[0] = node;
        match(currentToken->type,token_list);
        //printf("%s %d\n",currentToken->content,currentToken->type);
        qnode->child[1] = term(k,token_list);
        node = qnode;
    }
    return node;
}

TreeNode * term(TreeNode * k,List * token_list)
{
    TreeNode * node= factor(k,token_list);
    k= NULL;
    while((currentToken->type==STAR)||(currentToken->type==OVER))
    {
        TreeNode * qnode= newNode(OpK);
        qnode->Attribute.op = currentToken->type;
        qnode->child[0]=node;
        node=qnode;
        match(currentToken->type,token_list);
        qnode->child[1]=factor(k,token_list);
    }
    return node;
}

TreeNode * factor(TreeNode * k,List * token_list)
{
    TreeNode * node=NULL;
    if(k!=NULL){
        if(currentToken->type == LPAR && k->nodekind != Arry_ElemK)
        {
            node=call(k,token_list);
        }
        else
        {
            node=k;
        }
        }
    else
    {
        switch(currentToken->type)
        {
            case LPAR:
                match(LPAR,token_list);
                node=expression(token_list);
                match(RPAR,token_list);
                break;
            case ID:
                k=var(token_list);
                if(LPAR == currentToken->type && k->nodekind != Arry_ElemK)
                {
                    node=call(k,token_list);
                }
                break;
            case INTC:
                node = newNode(ConstK);
                if((node!=NULL) && (currentToken->type==INTC))
                {   
                    //printf("Now the token's content is %s\n",currentToken->content);
                    node->Attribute.val = atoi(currentToken->content); //convert string to integer
                    //printf("value is %d\n",node->Attribute.val);
                }
                match(INTC,token_list);
                break;
            default:
                syntaxError();
                currentToken=getToken(token_list);
                break;
        }
    }
    return node;
}

TreeNode * var(List * token_list)
{
    TreeNode * node=NULL;
    TreeNode * pnode=NULL;
    TreeNode * qnode=NULL;
    //printf("%s %d\n",currentToken->content,currentToken->type);
    if(currentToken->type==ID)
    {
        pnode=newNode(IdK);
        //printf("%s %d\n",currentToken->content,currentToken->type);
        strcpy(pnode->Attribute.name,currentToken->content);
        //pnode->attr.name=currentToken.tokenString.c_str();
        //printf("%s\n",pnode->Attribute.name);
        match(ID,token_list);
        if(currentToken->type == LBR)   //array
        {
            match(LBR,token_list);
            qnode=expression(token_list);
            match(RBR,token_list);
            node=newNode(Arry_ElemK);
            node->child[0]=pnode;
            node->child[1]=qnode;
        }
        else if(currentToken->type == LPAR)
        {   
            qnode = newNode(FunK);
            qnode->child[0] = pnode;
            match(LPAR,token_list);
            qnode->child[1] = params(token_list);
            match(RPAR,token_list);
            match(SEMI,token_list);
        }
        else
        {
            node=pnode;
        }
    }
    return node;
}

TreeNode * call(TreeNode *k,List * token_list)
{
    TreeNode *node =newNode(CallK);
    if(k!=NULL)
        node->child[0]=k;
    match(LPAR,token_list);
    if(currentToken->type==RPAR)
    {
        match(RPAR,token_list);
        return node;
    }
    else if (k!=NULL)
    {
        node->child[1]=args(token_list);
        match(RPAR,token_list);
    }
    return node;
}

TreeNode * args(List * token_list){
    TreeNode * node=newNode(ArgsK);
    TreeNode * snode=NULL;
    TreeNode * pnode=NULL;
    if(currentToken->type!=RPAR){
        snode=expression(token_list);
        pnode=snode;
        while(currentToken->type==COMMA)
        {
            TreeNode *qnode;
            match(COMMA,token_list);
            qnode=expression(token_list);
            if(qnode!=NULL){
                if(snode==NULL){
                    snode=pnode=qnode;
                }
                else{
                    pnode->sibling=qnode;
                }
            }
        }
    }
    if(snode!=NULL){
        node->child[0]=snode;
    }
    return node;
}



