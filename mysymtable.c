#include "mysymtable.h"

#define SHIFT 4

int hash(char * key)
{
    int temp = 0;
    int i = 0;
    while(key[i] != '\0')
    {
        temp = ((temp << SHIFT) + key[i]) % SIZE;
        ++i;
    }
    return temp;
}

Scope * newScope(char * scopeName)
{
    Scope * newscope = (Scope*)malloc(sizeof(Scope));
    newscope->name = scopeName;
    return newscope;   
}

/*Stack to deal with scope*/
void popScope(void)
{
    scopeStack[topScope--] = NULL; //let scopeStack[topScope] = NULL, then topScope = topScope - 1;
}

void pushScope(Scope * scope)
{
    for(int i=0;i<sizeOfList;i++)
    {
        if(strcmp(scopeList[i]->name,scope->name) == 0)
        {
            scope->nestedLevel++;
        }
    }
    scopeStack[topScope++] = scope;
    insertScopeToList(scope);
}

void insertScopeToList(Scope * scope)
{
    scopeList[sizeOfList++] = scope;
}

Scope * currScope()
{
    return scopeStack[topScope-1];
}

void st_insert(char * scopeName, char * name, ExpType type, TreeNode * treeNode, int loc)
{
    int v = hash(name);
    Scope * scope = currScope();
    
    BucketList * l = scope->hashTable[v];
    BucketList * lh = scopeList[sizeOfList-1]->hashTable[v];
    while((l != NULL) && (strcmp(name,l->name) != 0))
       l = l->next;
    
    if(l == NULL)
    {
        l = (BucketList*)malloc(sizeof(BucketList));
        l->name = name;
        l->treeNode = treeNode;
        l->lines = (LineList*)malloc(sizeof(LineList));
        l->lines->lineno = treeNode->line_no;
        l->lines->next = NULL;
        l->type = type;
        l->memloc = loc;
        l->next = scope->hashTable[v];
        scope->hashTable[v] = l;
        
        lh = (BucketList*)malloc(sizeof(BucketList));
        lh->name = name;
        lh->treeNode = treeNode;
        lh->lines->lineno = treeNode->line_no;
        lh->type = type;
        lh->memloc = loc;
        lh->next = scopeList[sizeOfList-1]->hashTable[v];
    }
    else  /*already in the bucketlist, insert in the linelist*/
    {
        LineList * t = l->lines;
        while(t->next != NULL)
           t = t->next;
        t->next = (LineList *)malloc(sizeof(LineList));
        t->next->lineno = treeNode->line_no;  /*fixed, pay attention!!!!!!!!!!*/
        t = t->next;
        t->next = NULL;
    }
}

BucketList * st_lookup(char * name) 
{
    Scope * scope = currScope();
    int v = hash(name);
    BucketList * bucket = scope->hashTable[v];

    while ((bucket != NULL) && (strcmp(name, bucket->name) != 0)) 
        bucket = bucket->next;
    return bucket;
}

/* st_lookup_all_scope(char *name)*/
BucketList * st_lookup_all_scope(char * name) 
{
    Scope * scope = currScope();
    int v = hash(name);
    BucketList * bucket;

    while (scope != NULL) 
    {
        BucketList * bucket = scope->hashTable[v];
        while ((bucket != NULL) && (strcmp(name, bucket->name) != 0)) 
           bucket = bucket->next;
        if (bucket != NULL) 
           return bucket;
        scope = scope->parent;
    }
    return NULL;
}
/* Function st_lookup returns Bucket
 * location of a variable or NULL if not found
 * To check redefinition of function
 */
Scope * st_lookup_scope(char * scopeName) 
{
    Scope * scope = NULL;
    for (int i=0; i<sizeOfList; i++) 
    {
        if (strcmp(scopeList[i]->name, scopeName) == 0) 
        {
            scope = scopeList[i];
            break;
        }
    }
    return scope;
}

/* insert reference line */ 
void insertLines(char* name, int lineno) 
{
    Scope * scope = currScope();
    int v = hash(name);
    BucketList * l = scope->hashTable[v];

    while (scope != NULL) 
    {

        if (l != NULL) 
        {
            LineList * lines = l->lines;
            while (lines->next != NULL) 
            {
                lines = lines->next;
            }

            lines->next =  (LineList*) malloc(sizeof(LineList));
            lines->next->lineno = lineno;
            lines->next->next = NULL;
            return;
        }
        scope = scope->parent;
    }
}

void printSymTabRows(Scope * scope) 
{
    // BucketList * hashTable = scope->hashTable;
    
    for (int i=0; i<SIZE; ++i) 
    {
        if (scope->hashTable[i] != NULL) 
        {
            BucketList * l = scope->hashTable[i];
            TreeNode * node = l->treeNode;
            while (l != NULL) 
            {
                LineList * lines = l->lines;
                printf("%-10s", l->name);

                switch (node->nodekind) 
                {
                    
                    case FunK:
                        printf("Function         ");
                        break;
                    
                    case Var_DeclK:
                        printf("Variable         ");
                        break;
                    
                    case Arry_DeclK:
                        printf("Array Variable   ");
                        break;
                    
                    case ParamK:
                        printf("Parameter        ");
                        break;
                    
                    case Arry_ElemK:
                        printf("Array Parameter  ");
                        break;
                    
                    default:
                        break;
                      
                }

                switch (l->type) 
                {
                    case Void:
                    printf("Void          ");
                    break;
                    case Integer:
                    printf("Integer       ");
                    break;
                    // case IntegerArray:
                    // printf("Integer Array ");
                    // break;
                    default:
                    break;
                }

                // print memory location
                printf("%d          ", l->memloc);

                // print line numbers
                while (lines->next != NULL) 
                {
                    printf("%d, ", lines->lineno);
                    lines = lines->next;
                }
                printf("%d\n", lines->lineno);
                l = l->next;
            }
        }
    }
}
/* Procedure printSymTab prints a formatted
 * listing of the symbol table contents
 * to the listing file
 */
void printSymTab(FILE * listing) {

  printf("\n------------------\n");
  printf("|  Symbol table  |");
  printf("\n------------------\n\n");

  for (int i = 0; i<sizeOfList; ++i) 
  {
        Scope * scope = scopeList[i];
        printf("Scope Name : %s, Nested Level: %d\n", scope->name, scope->nestedLevel);
        printf("---------------------------------------------------------------------------\n");
        printf("Name       Type             Data Type     Location   Line Numbers \n");
        printf("---------  ---------------  ------------  ---------  ----------------------\n");
        printSymTabRows(scope);
        printf( "---------------------------------------------------------------------------\n");
        fputc('\n', listing);
  }
} /* printSymTab */
