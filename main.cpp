#include "Tree/tree.h"
#include "Tree/dump.h"
#include "Differenciator/differenciator.h"

int main(void)
{
    Open_Log_File();

    tree_s my_tree = {};

    Tree_Ctor(&my_tree);

    Tree_Download(&my_tree);

    Tree_Get_Size(&my_tree, my_tree.root);

    tree_s diff_tree = {};

    diff_tree.root = Diff(my_tree.root);

    Tree_Printer(diff_tree.root, Pre_Order);

    Tree_Dump(&my_tree);

    Tree_Dump(&diff_tree);

    Diff_Print_Equation(my_tree.root, diff_tree.root);

    Tree_Dtor(&my_tree);

    Close_Log_File();

    return 0;
}