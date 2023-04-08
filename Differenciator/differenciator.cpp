#include "differenciator.h"

//-------------------------------------------------------------------------------//

/// @brief 
/// @param cur_node 
/// @return 
static tree_node * Not_Zero_Node(tree_node * const cur_node);

//-------------------------------------------------------------------------------//

/// @brief 
/// @param cur_node 
/// @return 
static tree_node * Is_Zero_Node(tree_node * const cur_node);

//-------------------------------------------------------------------------------//

int Start_Programm(tree_s * const my_tree)
{
    assert(my_tree);

    Tex_Start_File();    

    Speaker("Hi, guys!\nEnter 1 to check the tree.\n"
            "Enter 2 to find value of the function at the point.\n"
            "Enter 10 to live the programm\n");
    int interactive = true;
    while (interactive)
    {
        int mode = 0;
        if (scanf ("%d", &mode))
        {
            switch (mode)
            {
                case Show_Tree:
                    Tex_Programm_Mode(my_tree, Show_Tree);
                    Speaker("pam pam pi dam, done, now you can watch the tree of your grpahic\n");
                    break;

                case Find_Func_Value_At_Point:
                    Tex_Programm_Mode(my_tree, Find_Func_Value_At_Point);
                    Speaker("Oh my God, i'm cumming... Yes you get your value\n");
                    break;

                case Finish_Prog:
                    interactive = false;
                    break;

                default:
                    Skip_Line();
                    Speaker("Incorrect command. Try one more time\n");
            }
        }
        else
        {
            Skip_Line();
            Speaker("Incorrect command. Try one more time\n"); 
        }
    }

    Tex_End_File();

    return No_Error;
}

//-------------------------------------------------------------------------------//

data_t Eval(tree_node * const cur_node)
{
    if (cur_node->type == Num_Type)
        return cur_node->data;

    switch (cur_node->data)
    {

#       define DEF_CMD(name, number, code)     \
            case number:                        \
            code                                

#       include "../Architecture/cmd.h"

#       undef DEF_CMD

        default:
            fprintf(stderr, "Incorrect node type %d\n", cur_node->type);
    }

    return Incorrect_Node;
}

//-------------------------------------------------------------------------------//

tree_node * Diff(tree_s * const diff_tree, tree_node * src_root)
{
    assert(diff_tree);

    diff_tree->root = Diff_Calc(diff_tree, src_root);

    int is_simplified = 0;

    Tree_Dump(diff_tree);

    do {
        is_simplified = 0;

        int old_size = Tree_Get_Size(diff_tree, diff_tree->root);

        Diff_Simplifier(diff_tree->root);

        int new_size = Tree_Get_Size(diff_tree, diff_tree->root);

        if (new_size != old_size)
            is_simplified += 1;

    } while (is_simplified);

    Tree_Dump(diff_tree);

    return diff_tree->root;
}

//-------------------------------------------------------------------------------//

tree_node * Diff_Calc(tree_s * const my_tree, tree_node * const NODE)
{
    switch(NODE->type)
    {
        case Num_Type:
        return New_Num(0);

        case Op_Type:
        switch(NODE->data)
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
            if (RIGHT->type == Num_Type && LEFT->type == Var_Type)
                return MUL(cR, POW(cL, SUB(cR, New_Num(1))));
            else if (RIGHT->type == Num_Type && LEFT->type == Num_Type)
                return New_Num(0);
            
            case Op_Sin:
            return MUL(dL, COS(cL));

            case Op_Cos:
            return MUL(dL, MUL(SIN(cL), New_Num(-1)));

            case Op_Ln:
                return DIV(dL, cL);

            default:
                fprintf(stderr, "Incorrect type of operation %d, in %s",  NODE->data, __PRETTY_FUNCTION__);
                return nullptr;
        }

        case Var_Type:
        return New_Num(1);

        default:
            fprintf(stderr, "Incorrect type %d, in %s",  NODE->data, __PRETTY_FUNCTION__);
            return nullptr;
    }
}

//-------------------------------------------------------------------------------//

tree_node * Diff_Copy_Node(tree_node * const cur_node)
{
    tree_node * copy_node = (tree_node *)calloc (1, sizeof(tree_node));
    if (copy_node == nullptr)
    {
        fprintf(stderr, "Failed allocation new node in function %s\n", __PRETTY_FUNCTION__);
        return nullptr;
    }

    copy_node->data = cur_node->data;
    copy_node->type = cur_node->type;
    copy_node->left = cur_node->left;
    copy_node->right = cur_node->right;

    if (cur_node->left)
        copy_node->left  = Diff_Copy_Node(cur_node->left);

    if (cur_node->right)
        copy_node->right = Diff_Copy_Node(cur_node->right);

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

int Diff_Simplifier(tree_node * NODE)
{
    if (LEFT == nullptr || RIGHT == nullptr)
        return No_Error;

    if (NODE->type == Op_Type && LEFT->type == Num_Type && RIGHT->type == Num_Type)
    {
        data_t node_value = Eval(NODE);
        
        NODE->data = node_value;
        NODE->type = Num_Type;

        Tree_Clean(&LEFT);
        Tree_Clean(&RIGHT);

        return No_Error;
    }

    if (NODE->type == Op_Type && Is_Zero_Node(NODE))
    {
        tree_node * copy_node = Diff_Copy_Node(Not_Zero_Node(NODE));
        NODE->type = Num_Type;

        if (NODE->data == Op_Add ||  NODE->data == Op_Sub)
        {
            NODE->type = copy_node->type;
            NODE->data = copy_node->data;
            LEFT = copy_node->left;
            RIGHT = copy_node->right;
        }

        else if (NODE->data == Op_Mul)
        {
            NODE->data = 0;
            Tree_Clean(&LEFT);
            Tree_Clean(&RIGHT);
        }
        
        else if (NODE->data == Op_Div)
        {
            if (LEFT->data == 0)
            {
                NODE->data = 0;
                Tree_Clean(&LEFT);
                Tree_Clean(&RIGHT);
            }
            else if (RIGHT->data == 0)
                fprintf(stderr, "Огузок, нельзя делить на ноль!\n");
        }

        else if (NODE->data == Op_Pow)
        {
            NODE->data = 1;
            Tree_Clean(&LEFT);
            Tree_Clean(&RIGHT);
        }

        else
            printf("Will be soon new operations...\n");

        return No_Error;
    }

    else if (NODE->type == Op_Type && (NODE->data == Op_Mul || NODE->data == Op_Div || NODE->data == Op_Pow) && RIGHT->type == Num_Type && RIGHT->data == 1)
    {
        tree_node * copy_node = Diff_Copy_Node(LEFT);

        NODE->type = copy_node->type;
        NODE->data = copy_node->data;
        LEFT       = copy_node->left;
        RIGHT      = copy_node->right;

        return No_Error;
    }

    else if (NODE->type == Op_Type && NODE->data == Op_Mul && LEFT->type == Num_Type && LEFT->data == 1)
    {
        tree_node * copy_node = Diff_Copy_Node(RIGHT);

        NODE->type = copy_node->type;
        NODE->data = copy_node->data;
        LEFT       = copy_node->left;
        RIGHT      = copy_node->right;

        return No_Error;
    }

    else
    {
        Diff_Simplifier(LEFT);
        Diff_Simplifier(RIGHT);
    }

    return No_Error;
}

//-------------------------------------------------------------------------------//

int Find_Function_At_Point(tree_s * const my_tree, tree_node * cur_node, int value)
{
    assert(my_tree);

    if (Tree_Find_Variable_Node(cur_node))
    {
        cur_node->type = Num_Type;
        cur_node->data = value;
    }

    if (cur_node->left)
        Find_Function_At_Point(my_tree, cur_node->left, value);

    if (cur_node->right)
        Find_Function_At_Point(my_tree, cur_node->right, value);

    Diff_Simplifier(cur_node);

    return my_tree->root->data;
}

//-------------------------------------------------------------------------------//

static tree_node * Not_Zero_Node(tree_node * const cur_node)
{
    assert(cur_node);

    if (LEFT->data == 0)
        return RIGHT;

    else if (RIGHT->data == 0)
        return LEFT;

    else
        return nullptr;
}

//-------------------------------------------------------------------------------//

static tree_node * Is_Zero_Node(tree_node * const cur_node)
{
    assert(cur_node);

    if (LEFT->data == 0)
        return LEFT;

    if (RIGHT)
        if (RIGHT->data == 0)
            return RIGHT;
        else 
            return nullptr;

    else
        return nullptr;
}

//-------------------------------------------------------------------------------//

void Speaker(const char * string...)
{
    va_list args = {0};
    va_start (args, string);

    char message[500] = {};

    vsprintf(message, string, args);

    printf("%s", message);

    // char cmd[550] = {};

    // sprintf(cmd, "espeak -s 150 -v en \"%s\"", message);

    // system(cmd);
}

//-------------------------------------------------------------------------------//

void Skip_Line()
{
    while (getchar() != '\n');
}

//-------------------------------------------------------------------------------//

void Clear_Terminal()
{
    system("clear");
}

//-------------------------------------------------------------------------------//