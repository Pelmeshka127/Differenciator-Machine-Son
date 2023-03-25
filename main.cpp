#include "Tree/tree.h"
#include "Tree/dump.h"
#include "Differenciator/differenciator.h"

int main(void)
{
    Open_Log_File();

    tree_s my_tree = {};

    Tree_Ctor(&my_tree);

    Tree_Download(&my_tree);

    Tree_Dump(&my_tree);

    Tree_Dtor(&my_tree);

    Close_Log_File();

    char *s = "( o )4444";
    char i[10] = "";

    sscanf(s, "(%s)", i);
    printf("%s\n", i);

    return 0;
}