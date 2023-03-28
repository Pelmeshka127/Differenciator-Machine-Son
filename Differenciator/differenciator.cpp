#include "differenciator.h"

//-------------------------------------------------------------------------------//

#define DEF_CMD(name, number, code)     \
    case number:                        \
    code                                

//-------------------------------------------------------------------------------//

double Eval(tree_node * const node)
{
    if (node->type == Num_Subject)
        return node->data;

    switch (node->type)
    {
        #include "../Architecture/cmd.h"

        default:
            fprintf(stderr, "Incorrect node type %d\n", node->type);
    }

    return Incorrect_Node;
}

//-------------------------------------------------------------------------------//