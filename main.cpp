#include "Tree/tree.h"
#include "Tree/dump.h"
#include "Differenciator/differenciator.h"

int main(void)
{
    Open_Log_File();

    tree_s my_tree = {};

    Tree_Ctor(&my_tree);

    Tree_Download(&my_tree);

    tree_s diff_tree = {};

    diff_tree.root = Diff(&diff_tree, my_tree.root);

    Tree_Dump(&my_tree);

    Tree_Dump(&diff_tree);

    int is_simplified = 0;
    do {
        is_simplified = 0;

        int old_size = Tree_Get_Size(&diff_tree, diff_tree.root);

        Diff_Simplifier(diff_tree.root);

        int new_size = Tree_Get_Size(&diff_tree, diff_tree.root);

        if (new_size != old_size)
            is_simplified += 1;

    } while (is_simplified);

    Diff_Print_Equation(my_tree.root, diff_tree.root);

    Tree_Dump(&diff_tree);

    Tree_Dtor(&my_tree);

    Tree_Dtor(&diff_tree);

    Close_Log_File();

    return 0;
}