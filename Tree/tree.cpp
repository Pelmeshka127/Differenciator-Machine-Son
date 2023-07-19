#include "tree.h"
#include "dump.h"
#include "../Recursive_Decsent/decsent.h"

//-------------------------------------------------------------------------------//

FILE * log_file = nullptr;

//-------------------------------------------------------------------------------//

int Tree_Ctor(tree_s * const my_tree)
{
    my_tree->size = 0;

    my_tree->root = nullptr;

    return No_Error;
}
 
//-------------------------------------------------------------------------------//

tree_node * Tree_New_Node(type_t type, data_t data, tree_node * left, tree_node * right)
{
    tree_node * inserting_node = (tree_node *)calloc (1, sizeof(tree_node));
    if (inserting_node == nullptr)
    {
        fprintf(stderr, "Failed allocation new node in function %s\n", __PRETTY_FUNCTION__);
        return nullptr;
    }

    inserting_node->type  = type;
    inserting_node->data  = data;
    inserting_node->left  = left;
    inserting_node->right = right;

    return inserting_node;
}


//-------------------------------------------------------------------------------//

int Tree_Get_Size(tree_s * const my_tree, tree_node * const node)
{
    if (my_tree->root == nullptr)
        return 0;

    if (node == my_tree->root)
        my_tree->size = 0;

    my_tree->size++;

    if (node->left)
        Tree_Get_Size(my_tree, node->left);

    if (node->right)
        Tree_Get_Size(my_tree, node->right);

    return my_tree->size;
}

//-------------------------------------------------------------------------------//

int Tree_Download(tree_s * const my_tree, char * file_name)
{
    Text_Info onegin = {};

    FILE * input_file  = fopen(file_name, "r");
    if (input_file == nullptr)
    {
        fprintf(stderr, "Failed reading file with source tree in function %s\n", __PRETTY_FUNCTION__);
        return File_Error;
    }

    if (Onegin_Read(&onegin, input_file) != No_Error)
    {
        fprintf(stderr, "Failed parsering in function %s\n", __PRETTY_FUNCTION__);
        return File_Error;
    }

    if (fclose(input_file) == EOF)
    {
        fprintf(stderr, "Failed clothing the source file in function %s\n", __PRETTY_FUNCTION__);
        return File_Error;
    }

    my_tree->root = Get_General(onegin.pointers); //Adding recursive decsent

    Onegin_Dtor(&onegin);

    return No_Error;
}

//-------------------------------------------------------------------------------//

int Tree_Get_Operator_By_Number(int operation, char * oper_symbol, unsigned long len)
{
    if (operation == Op_Add)
        strncpy(oper_symbol, "+", len);
    else if (operation == Op_Sub)
        strncpy(oper_symbol, "-", len);
    else if (operation == Op_Mul)
        strncpy(oper_symbol, "*", len);
    else if (operation == Op_Div)
        strncpy(oper_symbol, "/", len);
    else if (operation == Op_Pow)
        strncpy(oper_symbol, "^", len);
    else if (operation == Op_Sin)
        strncpy(oper_symbol, "sin", len);
    else if (operation == Op_Cos)
        strncpy(oper_symbol, "cos", len);
    else if (operation == Op_Ln)
        strncpy(oper_symbol, "ln", len);
    else if (operation == Op_Exp)
        strncpy(oper_symbol, "exp", len);

    else
    {
        //fprintf(stderr, "Incorrect type of oper %s in %s\n", operation, __PRETTY_FUNCTION__);
        return Incorrect_Node;
    }
    
    return No_Error;
}

//-------------------------------------------------------------------------------//

char Tree_Get_Variable_By_Number(int variable)
{
    if (variable == Var_X)
        return 'x';

    else
    {
        //fprintf(stderr, "Incorrect type of variable %d in %s\n", variable, __PRETTY_FUNCTION__);
        return Incorrect_Var;
    }
}

//-------------------------------------------------------------------------------//

int Tree_Find_Variable_Node(tree_node * const cur_node)
{
    if (cur_node != nullptr && cur_node->type == Var_Type)
        return Var_Type;

    return No_Error;
}

//-------------------------------------------------------------------------------//

int Tree_Is_There_Variables(tree_node * const cur_node)
{
    if (Tree_Find_Variable_Node(cur_node))
        return Var_Type;

    if (cur_node->right == nullptr && cur_node->left == nullptr)
        return No_Error;
    
    if (cur_node->left && Tree_Is_There_Variables(cur_node->left))
        return Var_Type;

    if (cur_node->right && Tree_Is_There_Variables(cur_node->right))
        return Var_Type;

    return No_Error;
}

//-------------------------------------------------------------------------------//

int Tree_Clean(tree_node ** root)
{
    assert(root);

    if ((*root)->left != nullptr)
        Tree_Clean(&(*root)->left);

    if ((*root)->right != nullptr)
        Tree_Clean(&(*root)->right);

    free(*root);

    *root = nullptr;

    return No_Error;
}

//-------------------------------------------------------------------------------//

int Tree_Dtor(tree_s * const my_tree)
{
    assert(my_tree);

    Tree_Clean(&my_tree->root);

    my_tree->root = nullptr;

    my_tree->size = 0;

    return No_Error;
}

// //-------------------------------------------------------------------------------//

// int Tree_Reader(Text_Info * const onegin, tree_s * const my_tree, tree_node ** cur_node)
// {
//     assert(onegin);
//     assert(my_tree);

//     char node_symbol[5] = "";
//     int node_value = 0;

//     if (**onegin->pointers == '(')
//     {
//         if (sscanf(*onegin->pointers, "( %d )", &node_value))
//         {
//             *cur_node = Tree_New_Node(Num_Type, node_value);
//             while (**onegin->pointers != ')')
//                 (*onegin->pointers)++;

//             return No_Error;
//         }
        
//         else
//         {
//             sscanf(*onegin->pointers, "( %s )", node_symbol);
//             (*onegin->pointers)++;

//             if ((node_value = Tree_Get_Number_By_Operator(node_symbol)) != Incorrect_Type)
//             {
//                 *cur_node = Tree_New_Node(Op_Type, node_value);

//                 while (**onegin->pointers != '(')
//                     (*onegin->pointers)++;

//                 Tree_Reader(onegin, my_tree, &(*cur_node)->left);
                
//                 if (node_value < Op_Sin)
//                 {
//                     while (**onegin->pointers != '(')
//                         (*onegin->pointers)++;

//                     Tree_Reader(onegin, my_tree, &(*cur_node)->right);
//                 }

//                 else if (node_value >= Op_Sin)
//                     (*cur_node)->right = nullptr;

//                return No_Error;
//             }

//             else if ((node_value = Tree_Get_Number_By_Variable(node_symbol)) != Incorrect_Var)
//             {
//                 *cur_node = Tree_New_Node(Var_Type, node_value);
//                 while (**onegin->pointers != ')')
//                     (*onegin->pointers)++;

//                 return No_Error;
//             }

//             else
//             {
//                 fprintf(stderr, "No any varaibles and operations in %s\n", __PRETTY_FUNCTION__);
//                 return File_Error;
//             }
//         }
//     }

//     else
//     {
//         fprintf(stderr, "Incorrect start of the tree: %s. Failed reading in function %s", __PRETTY_FUNCTION__, *onegin->pointers);
//         return File_Error;
//     }
// }

// //-------------------------------------------------------------------------------//