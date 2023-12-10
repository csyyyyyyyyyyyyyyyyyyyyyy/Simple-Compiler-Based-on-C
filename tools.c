/*update at 2022/11/27 written by @HYC*/
#include "tools.h"
//List * token_list = NULL;

int set_times=1;
//get code stream from any file you chose 
//and realloc mem space for Code_stream if
//there are not enough space 
char * read_file(const char *Filename){
    FILE* fp;
    Code_stream=(char *)calloc(MAX_NUM,sizeof(char));
    fp =fopen(Filename,"r");
    //index for addressing Code_stream
    int count=0;
    while ((Code_stream[count]=fgetc(fp))!=EOF)
    {
        //putchar(Code_stream[count]);
        count++;
        if (count==(MAX_NUM * set_times))
        {
            set_times++;
            /*
            buffer=calloc(MAX_NUM,sizeof(char));
            strcpy(buffer,Code_stream);
            free(Code_stream);
            Code_stream=calloc(MAX_NUM*set_times,sizeof(char));
            strcpy(Code_stream,buffer);
            free(buffer);
            */
            Code_stream=realloc(Code_stream,(MAX_NUM * set_times));
            if (Code_stream==NULL)
            {
                puts("no mem allocated");
            }
            
        }
    }
    //printf("%s",Code_stream);
    //puts(Code_stream);
    filter(Code_stream,strlen(Code_stream));
    //printf("%d----------->strlen: \n%d-------------->MAX_NUM*set_times\n",strlen(Code_stream),(MAX_NUM*set_times));
    return Code_stream;
}
void free_code_stream(){
    free(Code_stream);
}

char *rtrim(char *str)
{
    if (str == NULL || *str == '\0')
    {
        return str;
    }

    int len = strlen(str);
    char *p = str + len - 1;
    while (p >= str  && isspace(*p))
    {
        *p = '\0';
        --p;
    }

    return str;
}


//去除首部空格
char *ltrim(char *str)
{
    if (str == NULL || *str == '\0')
    {
        return str;
    }

    int len = 0;
    char *p = str;
    while (*p != '\0' && isspace(*p))
    {
        ++p;
        ++len;
    }

    memmove(str, p, strlen(str) - len + 1);

    return str;
}

//去除首尾空格
char *trim(char *str)
{
    str = rtrim(str);
    str = ltrim(str);

    return str;
}

int get_file_lines(char *Code_stream){
    int count=0;
    int num=0;
    while (Code_stream[num]!=EOF)
    {
        if (Code_stream[num]=='\n')
        {
            count++;
        }
        num++;
    }
    count++;
    return count;
}

void print_lines_code(char *Code_stream,int lines,int *table){
        if (lines==1)
        {
            for (size_t i = 0; i < table[lines]; i++)
        {
            printf("%c",Code_stream[i]);
        }
        }
        else
        {
        for (size_t j = table[lines-1]+1; j < table[lines]; j++)
        {
            printf("%c",Code_stream[j]);
        }
        }
       
}

int *get_table(int lines,char *Code_stream){
    int *table=(int *)calloc(lines+1,sizeof(int));
    table[0]=0;
    int count=1;
    int num=0;
    while (Code_stream[num]!=EOF)
    {
        if (Code_stream[num]=='\n')
        {
            table[count]=num;
            count++;
        }
        num++;
    }
    table[count]=num;
    return table;
}

void filter(char *r,int pProject)
{
    char *tempstr;
    tempstr=calloc(MAX_NUM*set_times,sizeof(char));
    int count = 0;
    for(int i = 0;i<=pProject;i++)
    {
        //单行注释，直到遇到回车换行
        if(r[i]=='/'&&r[i+1]=='/')
        {
            while(r[i]!='\n')
            {
                i++;
            }
        }
        //多行注释
        if(r[i]=='/'&&r[i+1]=='*')
        {
            i+=2;
            while(r[i]!='*'||r[i+1]!='/')
            {
                i++;
                if(r[i]=='$')
                {
                    printf("error");
                    exit(0);
                }
            }
            i += 2;
        }
            tempstr[count++] = r[i];
    }
    tempstr[count] = '\0';
    strcpy(r, tempstr);
}
