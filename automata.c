#include "automata.h"

char keyword_table[][10]={"char","int","num","str","bool","false","true",
"tm","any","while","if","else","return","decl","rule","var"};

int num=0;
int line=1;//line num 

typedef enum
{
    START = 1,INNUM,INID,INDBSYM,INSTRC,DONE,TRAP
}DFA_state;

int is_symbol(char ch)
{
    switch (ch)
    {
    case '+':
        return True;
    case '-':
        return True;
    case '*':
        return True;
    case ';':
        return True;
    case ',':
        return True;
    case '(':
        return True;
    case ')': 
        return True;
    case '[':
        return True; 
    case ']':
        return True;
    case '{':
        return True;
    case '}':
        return True;
    case EOF:
        return True;
    default:
        return False;
    }
}

int is_keyword(char buffer [])
{
    for (size_t i = 0; i < KEYWORD_TABLE_NUM ; i++)
    {
        if (strcmp(buffer,keyword_table[i])==0)
        {
            return True;
        }
    }
    return False;
}

int get_prev_state(char c)  //返回字符的类型
{   
    if(c == ' '|| c == '\n' || c == '\t' || c == '\r')
       return START;
    else if(isdigit(c))
       return INNUM;
    else if(islower(c)||isupper(c))//islower(c) isupper(c)
       return INID;
    else if(c == '<'||c == '>'||c == '='||c == '!')
       return INDBSYM;
    else if(is_symbol(c))
       return DONE;
    else if(c == '\"')
       return INSTRC;
    else
       return TRAP;
}


Token* automata(char * code_stream)
{
    int prev_state = START;
    char *token_string;
    token_string=(char *)calloc(30,sizeof(char));
    char ch ;
    int count=0;
    Token* newtoken;
    newtoken=(Token *)malloc(sizeof(Token));
    newtoken->content=(char *)calloc(30,sizeof(char));
    while(prev_state < 6)
    {
        newtoken->lineno=line;
        ch = code_stream[num];
        //printf("%c\n",ch); 
        
        // if(ch == '\n')
        // {
        //     ch = code_stream[num++];
        //     return NULL;
        // }
        num++;
        if(prev_state == START)
        {  //puts("1");
            if(num!=0)
            {
                
                //token_string[count]=ch;
                if (ch=='\n')
                {
                    newtoken->type=-1;//-1 means illegal
                    line++;
                }
                token_string[count]=ch;
                prev_state = get_prev_state(ch);
                //num--;
            }
            if (prev_state ==DONE)
            {
                if(strrchr(token_string,';')!=NULL)
                    newtoken->type=40;//40 ->SEMI
                else if(strrchr(token_string,',')!=NULL)
                    newtoken->type=41;
                else if(strrchr(token_string,'(')!=NULL)
                    newtoken->type=42;
                else if(strrchr(token_string,')')!=NULL)
                    newtoken->type=43;
                else if(strrchr(token_string,'[')!=NULL)
                    newtoken->type=44;
                else if(strrchr(token_string,']')!=NULL)
                    newtoken->type=45;
                else if(strrchr(token_string,'{')!=NULL)
                    newtoken->type=46;
                else if(strrchr(token_string,'}')!=NULL)
                    newtoken->type=47;
                else if(strrchr(token_string,'+')!=NULL)
                    newtoken->type=28;
                else if(strrchr(token_string,'-')!=NULL)
                    newtoken->type=29;  
                else if(strrchr(token_string,'*')!=NULL)
                    newtoken->type=30;
                else if(strrchr(token_string,'/')!=NULL)
                    newtoken->type=31;    
            }
            
            if(prev_state != START)
                token_string[count]=ch;
               //strncat(token_string,ch,1);
        }
        else if(prev_state == INNUM)
        {
            prev_state = get_prev_state(ch);
            newtoken->type=14;//14->INTC tokentype
            if(prev_state != INNUM)
            {
                prev_state = DONE;
                num--;
            }
                 // jump the while loop
            else
               token_string[count]=ch;
               //strncat(token_string,ch,1);
        }
        else if(prev_state == INID)
        {
            prev_state = get_prev_state(ch);
            newtoken->type=7;//7 -> ID tokentype
            if(prev_state != INID)
            {
                if (strstr(token_string,"str")!=NULL)
                    newtoken->type=9;//9->STR
                else if (strstr(token_string,"int")!=NULL)
                    newtoken->type=10;//10->INT
                else if (strstr(token_string,"char")!=NULL)
                    newtoken->type=11;//10->CHAR
                else if (strstr(token_string,"bool")!=NULL)
                    newtoken->type=16;//16->BOOL
                else if (strstr(token_string,"num")!=NULL)
                    newtoken->type=8;//8->NUM
                else if (strstr(token_string,"void")!=NULL)
                    newtoken->type=5;//5->VOID
                prev_state = DONE;
                num--;
            }
               
            else
                token_string[count]=ch;
               //strncat(token_string,ch,1);
        }
        else if (prev_state == INSTRC)
        {
            //prev_state = get_prev_state(ch);
            newtoken->type=13;//13 ->STRC
            if(ch == '\"')
            {
                prev_state = DONE;
                token_string[count] = ch;
            }
            else
            {
                prev_state = INSTRC;
                token_string[count] = ch;
            }
        }
        else if(prev_state ==INDBSYM)
        {//need update somthing wrong
            if(ch == '=')
            {
                switch (token_string[count-1])
                {
                case '=':
                    newtoken->type=37;//37 -> EQ
                    break;
                case '!':
                    newtoken->type=38;//38 -> NEQ
                    break;
                case '>':
                    newtoken->type=36;//36 -> GTE
                    break;
                case '<':
                    newtoken->type=34;//34 -> LTE
                    break;        
                default:
                    break;
                }
                token_string[count]=ch;
                //strncat(token_string,ch,1);
                prev_state = DONE;
            }
            else
            {   
                switch (token_string[count-1])
                {
                case '=':
                    newtoken->type=39;//39 -> ASSGIN
                    break;
                case '!':
                    newtoken->type=48;//38 -> NOT
                    break;
                case '>':
                    newtoken->type=35;//36 -> GT
                    break;
                case '<':
                    newtoken->type=33;//34 -> LT
                    break;        
                default:
                    break;
                }
                num--;
                prev_state = DONE;
            }
        }
        //printf("%d\n",num);
        count++;
    }
    //num--;
    //printf("%s\n",token_string); 
    token_string[count+1]='\0';
    token_string=trim(token_string);
    //token_string=skipSpaceAtTheHead(token_string);
    strcpy(newtoken->content,token_string);
    //printf("%s\n",newtoken->content);
    //newtoken.string = token_string;
    /*
    if(token_string == "else")//token_string == 'else'
       newtoken.type = ELSE;
    else if(token_string == "if")
       newtoken.type = IF;
    else if(strcmp(token_string,"int"))//token_string == "int"
       newtoken.type = INT;
    else if(token_string == "return")
       newtoken.type = RETURN;
    else if(token_string == "void")
       newtoken.type = VOID;
    else if(token_string == "while")
       newtoken.type = WHILE;
    else if(token_string == "+")
       newtoken.type = PLUS;
    else if(token_string == "-")
       newtoken.type = MINUS;
    else 
       newtoken.type = ERROR;
       */
    free(token_string);
    return newtoken;
}


List * scan(const char *filename){
    char *test;
    test=read_file(filename);
    Token * test_token=NULL;
    List *new_list=(List *)malloc(sizeof(List));
    Node *head=NULL;
    Node *tail=NULL;
        while (test[num]!=EOF)
        {
            test_token = automata(Code_stream);
            head=append_node(head,test_token);
            tail=find_tail(head);
            //printf("%s----------%d---------------line-no:%d\n",tail->content,tail->type,tail->linenum);
        }
    Token *EOP_token=(Token *)malloc(sizeof(Token));
    EOP_token->content=NULL;
    EOP_token->type=EOP;
    EOP_token->lineno=-1;
    head=append_node(head,EOP_token);
    new_list=create_list(head);
    //puts("----------------------------------scan end----------------------------------------------");
    return new_list;
}