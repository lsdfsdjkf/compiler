#include "syntax.tab.h"



int main(int argc, char *argv[])
{
    //yydebug=1;
    yyparse();
    return 0;
}
