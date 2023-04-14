#include "Tree/tree.h"
#include "Tree/dump.h"
#include "Differenciator/differenciator.h"
#include "Tex_Pdf/tex.h"

int main(int argc, char ** argv)
{
    if (Check_Cmdline_Arg(argc) == Cmdline_Error)
        return Cmdline_Error;

    Open_Log_File();

    tree_s my_tree = {};

    Tree_Ctor(&my_tree);

    Tree_Download(&my_tree, argv[1]);

    Tree_Dump(&my_tree);

    Start_Programm(&my_tree);

    Tree_Dtor(&my_tree);

    Close_Log_File();

    return 0;
}