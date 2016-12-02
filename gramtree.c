#include <stdio.h>
#include <stdlib.h>
#include "gramtree.h"

struct ast *new_ast(char *name, int num,...)
{
    va_list valist;
    struct ast *root = (struct ast *)malloc(sizeof(struct ast));
    struct ast *p;
    if (root == 0)
    {
        printf("malloc fail!!!");
        system("pause");
        return root;
    }
    root->name = name;
    va_start(valist, num);
    if (num >= 1)
    {
        p = va_arg(valist, struct ast *);
        root->line = p->line;
        root->l = p;
        while(num>1)
        {
            p->r = va_arg(valist, struct ast *);
            p = p->r;
            num -= 1;
        }
    }
    else if (num != -1)
    {
        root->line = yylineno;
        if (!strcmp(name, "ID")||!strcmp(name, "TYPE"))
        {
            root->id = (char *)malloc(sizeof(char) * 50);
            strcpy(root->id, yytext);
            root->l = root->r = 0;
        }
        else if (!strcmp(name, "INT"))
        {
            root->a = strtol(yytext,NULL,0);
            root->l = root->r = 0;
        }
        else if (!strcmp(name, "FLOAT"))
        {
            root->b = atof(yytext);
            root->l = root->r = 0;
        }
    }
    else
        root->line = -1;
    return root;
}
void print_tree(struct ast *root, int level)
{
    int i;
    if (root != NULL)
    {
        if(root->line!=-1)
            for(i=0; i<level; ++i)
                printf("  ");
        if(root->line!=-1){ 
            printf("%s",root->name);
            if((!strcmp(root->name,"ID"))||(!strcmp(root->name,"TYPE")))printf(": %s",root->id);
            else if(!strcmp(root->name,"INT"))printf(": %d",root->a);
            else if(!strcmp(root->name,"FLOAT"))printf(": %f",root->b);
            else if (root->l != 0)
                printf("(%d)",root->line);
        }
        if(root->line!=-1) printf("\n");
        print_tree(root->l,level+1);
        print_tree(root->r,level);
    }
}