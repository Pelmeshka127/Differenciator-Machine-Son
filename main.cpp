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

    tree_s diff_tree = {};

    diff_tree.root = Diff(&diff_tree, my_tree.root);

    Diff_Print_Equation(my_tree.root, diff_tree.root);

    Tree_Dtor(&my_tree);

    Tree_Dtor(&diff_tree);

    Close_Log_File();

    return 0;
}