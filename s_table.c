#include "s_table.h"
#include "myparser.h"

void traverse(TreeNode * t)
{
    int i;
    while(t != NULL)
    {
        if (t->nodekind==IdK)
        printf("node-id:%s\n",t->Attribute.name);
        for(i=0;i<MAX_CHILDREN;i++)
        {   
            if(t->child[i] != NULL)
            {   
                //puts("56");
                traverse(t->child[i]);
            }
        }
        t = t -> sibling;
        
    }
}

static int st_id=0;//record symbol table num

SymbolTable * st_initialize(int restart)
{
    SymbolTable *nst=(SymbolTable *)malloc(sizeof(SymbolTable));
    if (restart == 0)
    {
        nst->id=0;
        st_id++;
    }
    else
    {
        nst->id=st_id;
        st_id++;
    }
    nst->nd=NULL;
    nst->upper=NULL;
    nst->lower=NULL;
    nst->prev=NULL;
    nst->next=NULL;
    for (size_t i = 0; i < ST_SIZE; i++)
    {
        nst->hashTable[i]->st=NULL;
        nst->hashTable[i]->nd=NULL;

        //line list intial
        //nst->hashTable[i]->lines->line_no=NULL;
        nst->hashTable[i]->lines->prev=NULL;
        nst->hashTable[i]->lines->next=NULL;
        //nst->hashTable[i]->lines->bk=NULL;

        nst->hashTable[i]->prev=NULL;
        nst->hashTable[i]->next=NULL;
        nst->hashTable[i]->something=NULL;
    }
    return nst;
}

void st_insert_dcl(TreeNode * dclNd, SymbolTable * st)
{
    //TreeNode * tempnode=dclNd;
    st->nd=dclNd;
    int temp;
    temp=hash(st->nd->Attribute.name[0]);
    st->hashTable[temp]->st=st;
    st->hashTable[temp]->nd=dclNd;
    //st->hashTable[temp]->lines->bk=st->hashTable[temp];
    if(st->hashTable[temp]->prev==NULL&&st->hashTable[temp]->next==NULL)
    {
        st->hashTable[temp]->lines=(LineList *)malloc(sizeof(LineList));
        st->hashTable[temp]->lines->line_no=st->hashTable[temp]->nd->line_no;
        st->hashTable[temp]->prev=st->hashTable[temp]->lines;
    }
    else
    {
        LineList temp_list=(LineList *)malloc(sizeof(LineList));
        LineList tail=st->hashTable[temp]->lines;
        while(tail->next!=NULL&&tail!=NULL)tail=tail->next;
        temp_list->line_no=st->hashTable[temp]->nd->line_no;
        tail->next=temp_list;
        tail->next->prev=tail;
        temp_list->next=NULL;
    }
    /*
    if (tempnode->nodekind==Var_DeclK||tempnode->nodekind==FunK)
    {
        for (size_t i = 0; i < MAX_CHILDREN; i++)
        {
            if (tempnode->child[i]->nodekind==IdK)
            {
                st->nd=tempnode->child[i];
            }
            if (tempnode->child[i]->nodekind==CompK)
            {
                TreeNode *lowerst_nd=tempnode->child[i];
                SymbolTable *nst=st_initialize(st_id);
                st->lower=nst;
                for (size_t j = 0; j < MAX_CHILDREN; j++)
                {
                    if (lowerst_nd->child[j]==IdK)
                    {
                        st->lower->nd=lowerst_nd->child[j];
                    }
                    
                }
                
            }
            
            
        }
        
    }
    */
    
}

/*
void post_traverse(TreeNode * t){
    if (t !=NULL)
    {
        for (size_t i = 0; i < MAX_CHILDREN; i++)
        {
            
        }
        
    }
    
}*/

#define SHIFT 4

static int hash( const char * key )
{
	int temp = 0;
	int i = 0;
	while (key[i] != '\0'){
		temp = ((temp << SHIFT) + key[i]) % ST_SIZE;
		++i;
	}
	return temp;
}