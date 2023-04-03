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

tree_node * Diff(tree_s * const my_tree, tree_node * const NODE)
{
    switch(NODE->type)
    {
        case Num_Type:
        return New_Num(0);

        case Op_Type:
        switch((int) NODE->data)
        {
            case Op_Add:
            return ADD(dL, dR);

            case Op_Sub:
            return SUB(dL, dR);

            case Op_Mul:
            return ADD(MUL(dL, cR), MUL(cL, dR));

            case Op_Div:
            return DIV(SUB(MUL(dL, cR), MUL(cL, dR)), MUL(cL, cR));

            case Op_Pow:
            if (cur_node->right->type == Num_Type)
                return MUL(cR, POW(cL, SUB(cR, New_Num(1))));

            default:
                fprintf(stderr, "Incorrect type of operation %d, in %s", (int) NODE->data, __PRETTY_FUNCTION__);
                return nullptr;
        }

        case Var_Type:
        return New_Num(1);

        default:
            fprintf(stderr, "Incorrect type %d, in %s", (int) NODE->data, __PRETTY_FUNCTION__);
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

//-------------------------------------------------------------------------------//

int Diff_Simplifier(tree_node * const NODE)
{
    if (LEFT == nullptr && RIGHT == nullptr)
        return No_Error;

    if (NODE->type == Op_Type && LEFT->type == Num_Type && RIGHT->type == Num_Type)
    {
        data_t node_value = Eval(NODE);

        Tree_Clean(&LEFT);
        Tree_Clean(&RIGHT);
        
        NODE->data = node_value;
        NODE->type = Num_Type;

        return No_Error;
    }

    else if (NODE->type == Op_Type && (int) NODE->data == Op_Pow)
    {
        if (LEFT->type == Var_Type)
        {
            NODE->data = LEFT->data;
            NODE->type = LEFT->type;

            Tree_Clean(&LEFT);
            Tree_Clean(&RIGHT);

            return No_Error;
        }

        else if (RIGHT->type == Var_Type)
        {
            NODE->type = RIGHT->type;
            NODE->data = RIGHT->data;

            Tree_Clean(&LEFT);
            Tree_Clean(&RIGHT);

            return No_Error;
        }

        else
            return No_Error;
    }

    else if (NODE->type == Op_Type && (int) LEFT->data == 0)
    {
        switch((int) NODE->data)
        {
            case Op_Add:
            
                NODE->type = RIGHT->type;
                NODE->data = RIGHT->data;
                
                Tree_Clean(&LEFT);
                Tree_Clean(&RIGHT);
                
                break;

            case Op_Sub:

                NODE->type = RIGHT->type;
                NODE->data = RIGHT->data;

                Tree_Clean(&LEFT);
                Tree_Clean(&RIGHT);

                break;

            case Op_Mul:

                NODE->type = Num_Type;
                NODE->data = 0;

                Tree_Clean(&LEFT);
                Tree_Clean(&RIGHT);

                break;

            case Op_Div:

                NODE->type = Num_Type;
                NODE->data = 0;

                Tree_Clean(&LEFT);
                Tree_Clean(&RIGHT);

                break;

            case Op_Pow:

                NODE->type = Num_Type;
                NODE->data = 1;

                Tree_Clean(&LEFT);
                Tree_Clean(&RIGHT);

                break;

            default:
                printf("Will be soon...\n");
        }

        return No_Error;

    }

    else if (NODE->type == Op_Type && (int) RIGHT->data == 0)
    {
        switch((int) NODE->data)
        {
                case Op_Add:
            
                NODE->type = LEFT->type;
                NODE->data = LEFT->data;
                
                Tree_Clean(&LEFT);
                Tree_Clean(&RIGHT);
                
                break;

            case Op_Sub:

                NODE->type = LEFT->type;
                NODE->data = LEFT->data;

                Tree_Clean(&LEFT);
                Tree_Clean(&RIGHT);

                break;

            case Op_Mul:

                NODE->type = Num_Type;
                NODE->data = 0;

                Tree_Clean(&LEFT);
                Tree_Clean(&RIGHT);

                break;

            case Op_Div:
                fprintf(stderr, "Oguzok, division by 0\n");
                break;

            case Op_Pow:

                NODE->type = Num_Type;
                NODE->data = 1;

                Tree_Clean(&LEFT);
                Tree_Clean(&RIGHT);

                break;

            default:
                printf("Will be soon...\n");
        }

        return No_Error;

    }

    else
    {
        Diff_Simplifier(LEFT);
        Diff_Simplifier(RIGHT);
    }

    return No_Error;
}