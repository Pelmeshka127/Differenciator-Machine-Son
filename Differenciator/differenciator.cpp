#include "differenciator.h"

//-------------------------------------------------------------------------------//

#define DEF_CMD(name, number, code)     \
    case number:                        \
    code                                

//-------------------------------------------------------------------------------//

data_t Eval(tree_node * const cur_node)
{
    if (cur_node->type == Num_Type)
        return cur_node->data;

    switch ((int) (cur_node->data))
    {
        #include "../Architecture/cmd.h"

        default:
            fprintf(stderr, "Incorrect node type %d\n", cur_node->type);
    }

    return Incorrect_Node;
}

//-------------------------------------------------------------------------------//

tree_node * Diff(tree_node * const cur_node)
{
    switch(cur_node->type)
    {
        case Num_Type:
        return New_Num(0);

        case Op_Type:
        switch((int) cur_node->data)
        {
            case Op_Add:
            return New_Op(Op_Add, dL, dR);

            case Op_Sub:
            return New_Op(Op_Sub, dL, dR);

            case Op_Mul:
            return New_Op(Op_Add, New_Op(Op_Mul, dL, cR), New_Op(Op_Mul, cL, dR));

            case Op_Div:
            return New_Op(Op_Div, New_Op(Op_Sub, New_Op(Op_Mul, dL, cR), New_Op(Op_Mul, cL, dR)), New_Op(Op_Mul, cL, cR));

            default:
                fprintf(stderr, "Incorrect type of operation %d, in %s", (int) cur_node->data, __PRETTY_FUNCTION__);
                return nullptr;
        }

        case Var_Type:
        return New_Num(1);

        default:
            fprintf(stderr, "Incorrect type %d, in %s", (int) cur_node->data, __PRETTY_FUNCTION__);
            return nullptr;
    }
}

//-------------------------------------------------------------------------------//

tree_node * Copy_Node(tree_node * const cur_node)
{
    tree_node * copy_node = (tree_node *)calloc (1, sizeof(tree_node));
    if (copy_node == nullptr)
    {
        fprintf(stderr, "Failed allocation new node in function %s\n", __PRETTY_FUNCTION__);
        return nullptr;
    }

    memmove(copy_node, cur_node, sizeof(tree_node));

    if (cur_node->left)
        copy_node->left  = Copy_Node(cur_node->left);

    if (cur_node->right)
        copy_node->right = Copy_Node(cur_node->right);

    return copy_node;
}

//-------------------------------------------------------------------------------//

int Diff_Print_Equation(tree_node * src_root, tree_node * diff_root)
{
    FILE * diff_file = fopen("trees/diff_file", "w");
    if (diff_file == nullptr)
    {
        fprintf(stderr, "Failed openning file with of tree printing in function %s\n", __PRETTY_FUNCTION__);
        return File_Error;
    }

    Tree_Print_In_Order(src_root, diff_file);

    fprintf(diff_file, "' = ");

    Tree_Print_In_Order(diff_root, diff_file);

    fclose(diff_file);

    return No_Error;
}