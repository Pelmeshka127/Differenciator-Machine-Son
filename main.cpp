#include "Tree/tree.h"
#include "Tree/dump.h"
#include "Differenciator/differenciator.h"
#include "Tex_Pdf/tex.h"

int main(void)
{
    Open_Log_File();

    tree_s my_tree = {};

    Tree_Ctor(&my_tree);

    Tree_Download(&my_tree);

    Start_Programm(&my_tree);

    // tree_s diff_tree = {};

    // Tree_Ctor(&diff_tree);

    // Diff(&diff_tree, my_tree.root);

    // Start_Programm(&diff_tree);

    // printf("%d\n", Find_Function_At_Point(&diff_tree, diff_tree.root, 4));

    Tree_Dtor(&my_tree);

    // Tree_Dtor(&diff_tree);

    Close_Log_File();

    return 0;
}