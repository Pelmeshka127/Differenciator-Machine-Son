#include "tree.h"
#include "dump.h"

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

tree_node * Tree_Insert_Node(type_t type, data_t data, tree_node * left, tree_node * right)
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

    my_tree->size++;

    if (node->left)
        Tree_Get_Size(my_tree, node->left);

    if (node->right)
        Tree_Get_Size(my_tree, node->right);

    return my_tree->size;
}

//-------------------------------------------------------------------------------//

int Tree_Download(tree_s * const my_tree)
{
    Text_Info onegin = {};

    FILE * input_file  = fopen("trees/newt.txt", "r");
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

    if (Tree_Reader(&onegin, my_tree, &my_tree->root) != No_Error)
    {
        fprintf(stderr, "Reading of thr tree failed ion function %s\n", __PRETTY_FUNCTION__);
        return File_Error;
    }

    Onegin_Dtor(&onegin);

    return No_Error;
}

//-------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------//

int Tree_Reader(Text_Info * const onegin, tree_s * const my_tree, tree_node ** cur_node)
{
    assert(onegin);
    assert(my_tree);

    char node_operator[10] = "";
    int node_value = 0;

    if (**onegin->pointers == '(')
    {
        if (sscanf(*onegin->pointers, "( %d )", &node_value))
        {
            *cur_node = Tree_Insert_Node(Num_Subject, node_value, nullptr, nullptr);
            while (**onegin->pointers != ')')
                (*onegin->pointers)++;

            return No_Error;
        }
        
        else
        {
            sscanf(*onegin->pointers, "( %s )", node_operator);
            (*onegin->pointers)++;

            *cur_node = Tree_Insert_Node(Tree_Get_Number_By_Operator(node_operator), Operation, nullptr, nullptr);

            while (**onegin->pointers != '(')
                (*onegin->pointers)++;

            Tree_Reader(onegin, my_tree, &(*cur_node)->left);
            
            while (**onegin->pointers != '(')
                (*onegin->pointers)++;

            Tree_Reader(onegin, my_tree, &(*cur_node)->right);

            return No_Error;
        }
    }

    else
    {
        fprintf(stderr, "Incorrect start of the tree: %s. Failed reading in function %s", __PRETTY_FUNCTION__, *onegin->pointers);
        return File_Error;
    }
}

//-------------------------------------------------------------------------------//

int Tree_Make_Node_Item(char * node_item, const char * line_start)
{
    line_start = strchr(line_start, '\"');
    line_start++;
    const char * end_line = strchr(line_start, '\"');

    if (line_start == nullptr || end_line == nullptr)
    {
        fprintf(stderr, "Incorrect item of the node %s\n", line_start);
        return Incorrect_Node;
    }

    strncpy(node_item, line_start, (size_t) (end_line - line_start));

    return No_Error;
}

//-------------------------------------------------------------------------------//

int Tree_Get_Number_By_Operator(char * operation)
{
    if (*operation == '+')
        return Op_Add;
    else if (*operation == '-')
        return Op_Sub;
    else if (*operation == '*')
        return Op_Mul;
    else if (*operation == '/')
        return Op_Div;

    else
    {
        fprintf(stderr, "Incorrect symbol of operation %c\n", *operation);
        return Incorrect_Type;
    }
}

//-------------------------------------------------------------------------------//

char Tree_Get_Operator_By_Number(type_t type)
{
    if (type == Op_Add)
        return '+';
    else if (type == Op_Sub)
        return '-';
    else if (type == Op_Mul)
        return '*';
    else if (type == Op_Div)
        return '/';
    
    else
    {
        fprintf(stderr, "Incorrect number of operation %d\n", type);
        return Incorrect_Type;
    }

}

//-------------------------------------------------------------------------------//

int Tree_Printer(tree_node * cur_node, const int print_type)
{   
    const char * file_name = nullptr;
    switch(print_type)
    {
        case Pre_Order:
        file_name = "trees/pre_order_tree.txt";
        break;

        case In_Order:
        file_name = "trees/in_order_tree.txt";
        break;

        case Post_Order:
        file_name = "trees/post_order_tree.txt";
        break;

        default:
        fprintf(stderr, "Incorrect type of tree print in function %s: %d\n", __PRETTY_FUNCTION__, print_type);
        return File_Error;
    }

    FILE * dst_file = fopen(file_name, "w");
    if (dst_file == nullptr)
    {
        fprintf(stderr, "Failed openning file with of tree printing in function %s\n", __PRETTY_FUNCTION__);
        return File_Error;
    }   

    switch(print_type)
    {
        case Pre_Order:
        Tree_Print_Pre_Order(cur_node, dst_file);
        break;

        case In_Order:
        Tree_Print_In_Order(cur_node, dst_file);
        break;

        case Post_Order:
        Tree_Print_Post_Order(cur_node, dst_file);
        break;
    }

    return No_Error;
}


//-------------------------------------------------------------------------------//

int Tree_Print_Pre_Order(tree_node * const cur_node, FILE * dst_file)
{
    if (cur_node == nullptr)
        return No_Error;

    fprintf(dst_file, " ( ");

    if (cur_node->type == Num_Subject)
        fprintf(dst_file, "%lg", cur_node->data);

    else
        fprintf(dst_file, "%c", Tree_Get_Operator_By_Number(cur_node->type));

    Tree_Print_Pre_Order(cur_node->left, dst_file);
    Tree_Print_Pre_Order(cur_node->right, dst_file);

    fprintf(dst_file, " ) ");

    return No_Error;
}

//-------------------------------------------------------------------------------//

int Tree_Print_In_Order(tree_node * const cur_node, FILE * dst_file)
{
    if (cur_node == nullptr)
        return No_Error;

    fprintf(dst_file, " ( ");    

    Tree_Print_In_Order(cur_node->left, dst_file);    

    if (cur_node->type == Num_Subject)
        fprintf(dst_file, "%lg", cur_node->data);

    else
        fprintf(dst_file, "%c", Tree_Get_Operator_By_Number(cur_node->type));

    Tree_Print_In_Order(cur_node->right, dst_file);

    fprintf(dst_file, " ) ");
    
    return No_Error;
}

//-------------------------------------------------------------------------------//

int Tree_Print_Post_Order(tree_node * const cur_node, FILE * dst_file)
{
    if (cur_node == nullptr)
        return No_Error;

    fprintf(dst_file, " ( ");

    Tree_Print_Post_Order(cur_node->left, dst_file);
    Tree_Print_Post_Order(cur_node->right, dst_file);

    if (cur_node->type == Num_Subject)
        fprintf(dst_file, "%lg", cur_node->data);

    else
        fprintf(dst_file, "%c", Tree_Get_Operator_By_Number(cur_node->type));

    fprintf(dst_file, " ) ");

    return No_Error;
}

//-------------------------------------------------------------------------------//

int Tree_Clean(tree_node * const root)
{
    assert(root);

    if (root->left != nullptr)
        Tree_Clean(root->left);

    if (root->right != nullptr)
        Tree_Clean(root->right);

    return No_Error;
}

//-------------------------------------------------------------------------------//

int Tree_Dtor(tree_s * const my_tree)
{
    assert(my_tree);

    Tree_Clean(my_tree->root);

    my_tree->root = nullptr;

    my_tree->size = 0;

    return No_Error;
}

//-------------------------------------------------------------------------------//