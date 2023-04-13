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

    // //log(exp(1));

    // printf("%f\n", exp(1));

    Start_Programm(&my_tree);

    Tree_Dtor(&my_tree);

    Close_Log_File();

    return 0;
}