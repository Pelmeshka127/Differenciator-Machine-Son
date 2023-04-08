#include "tex.h"

static FILE * tex_file = nullptr;

static const char * const file_name = "main.tex";

//-------------------------------------------------------------------------------//

int Tex_Start_File()
{
    tex_file = fopen(file_name, "w");
    if (tex_file == nullptr)
    {
        fprintf(stderr, "Failed openning tex file in function %s\n", __PRETTY_FUNCTION__);
        return File_Error;
    }

    fprintf(tex_file, "\\documentclass[12pt, letterpaper, twoside]{article}\n");
    fprintf(tex_file, "\\usepackage[T1]{fontenc}\n");
    fprintf(tex_file, "\\usepackage[utf8]{inputenc}\n");
    fprintf(tex_file, "\\usepackage[russian]{babel}\n");
    fprintf(tex_file, "\\usepackage[a1paper]{geometry}\n"
                      "\\geometry{papersize={29.7 cm, 25.0 cm}}\n");
    fprintf(tex_file, "\\usepackage{graphicx}\n");

    fprintf(tex_file, "\\title{DIFFERENCIATOR MACHINE}\n");
    fprintf(tex_file, "\\author{Makson from 225}\n");
    fprintf(tex_file, "\\date{}\n");

    fprintf(tex_file, "\\begin{document}\n");
    fprintf(tex_file, "\\maketitle\n");

    fprintf(tex_file, "\\newpage\n");

    return No_Error;
}

//-------------------------------------------------------------------------------//

int Tex_End_File()
{
    fprintf(tex_file, "\\end{document}");

    if (fclose(tex_file) == EOF)
    {
        fprintf(stderr, "Failed closing tex file in function %s\n", __PRETTY_FUNCTION__);
        return File_Error;
    }

    system("pdflatex main.tex");
    system("open main.pdf");
    system("rm main.aux");
    system("rm main.log");

    Clear_Terminal();

    return No_Error;
}

//-------------------------------------------------------------------------------//

int Tex_Programm_Mode(tree_s * const my_tree, int mode)
{
    assert(my_tree);

    int point = 0;

    switch(mode)
    {
        case Show_Tree:
            Tex_Show_Function_Tree(my_tree);
            break;

        case Find_Func_Value_At_Point:
            Speaker("Enter point where you want to find value of the function: ");
            while (scanf("%d", &point) != 1)
            {
                Skip_Line();
                Speaker("Incorrect value. Try one more time\n");
            }
            Tex_Calc_Tree(my_tree, point);
            break;

        default:
            fprintf(stderr, "Incorrect mode of the programm\n");
            break;
    }

    return No_Error;
}

//-------------------------------------------------------------------------------//

int Tex_Calc_Tree(tree_s * const my_tree, int value)
{
    assert(my_tree);

    fprintf(tex_file, "Your function is $F = ");

    Tex_Print_Tree_Node(my_tree->root);

    fprintf(tex_file, "$.\n");

    fprintf(tex_file, "The value of your function at %d: $ F(%d) = ", value, value);

    Find_Function_At_Point(my_tree, my_tree->root, value);

    fprintf(tex_file, "%d $\n", my_tree->root->data);

    return No_Error;
}

//-------------------------------------------------------------------------------//

int Tex_Show_Function_Tree(tree_s * const my_tree)
{
    assert(my_tree);

    fprintf(tex_file, "\\begin{center}\n");

    fprintf(tex_file, "Your function is $F = ");

    Tex_Print_Tree_Node(my_tree->root);

    fprintf(tex_file, "$\\newline \n");

    char png_name[Max_Length];

    Tree_Dump_To_Tex(my_tree, png_name);

    fprintf(tex_file, "\\begin{figure}\n");
    fprintf(tex_file, "\\begin{center}\n");
    fprintf(tex_file, "\\includegraphics [scale = 0.4]{%s}\n", png_name);
    fprintf(tex_file, "\\caption{Get your funtion}\n");
    fprintf(tex_file, "\\end{center}\n");
    fprintf(tex_file, "\\end{figure}\n");

    fprintf(tex_file, "\\end{center}\n");

    fprintf(tex_file, "\\newpage\n");

    return No_Error;
}

//-------------------------------------------------------------------------------//

int Tex_Print_Tree_Node(tree_node * const cur_node)
{
    switch(cur_node->type)
    {
        case Num_Type:
            if (cur_node->data < 0)
                fprintf(tex_file, "(%d)", cur_node->data);
            else 
                fprintf(tex_file, "%d", cur_node->data);
            break;

        case Var_Type:
            fprintf(tex_file, "%c", Tree_Get_Variable_By_Number(cur_node->data));
            break;

        case Op_Type:
            switch(cur_node->data)
            {
                case Op_Add:
                    fprintf(tex_file, "(");
                    Tex_Print_Tree_Node(cur_node->left);
                    fprintf(tex_file, " + ");
                    Tex_Print_Tree_Node(cur_node->right);
                    fprintf(tex_file, ")");
                    break;
                
                case Op_Sub:
                    fprintf(tex_file, "(");
                    Tex_Print_Tree_Node(cur_node->left);
                    fprintf(tex_file, " - ");
                    Tex_Print_Tree_Node(cur_node->right);
                    fprintf(tex_file, ")");
                    break;

                case Op_Mul:
                    Tex_Print_Tree_Node(cur_node->left); 
                    fprintf(tex_file, " \\cdot ");
                    Tex_Print_Tree_Node(cur_node->right);
                    break;

                case Op_Div:
                    fprintf(tex_file, "\\frac{");
                    Tex_Print_Tree_Node(cur_node->left);
                    fprintf(tex_file, "}{");
                    Tex_Print_Tree_Node(cur_node->right);
                    fprintf(tex_file, "} ");
                    break;

                case Op_Pow:
                    Tex_Print_Tree_Node(cur_node->left);
                    fprintf(tex_file, "^{");
                    Tex_Print_Tree_Node(cur_node->right);
                    fprintf(tex_file, "}");
                    break;

                case Op_Sin:
                    fprintf(tex_file, "sin(");
                    Tex_Print_Tree_Node(cur_node->left);
                    fprintf(tex_file, ")");
                    break;

                case Op_Cos:
                    fprintf(tex_file, "cos(");
                    Tex_Print_Tree_Node(cur_node->left);
                    fprintf(tex_file, ")");
                    break;

                case Op_Ln:
                    fprintf(tex_file, "ln(");
                    Tex_Print_Tree_Node(cur_node->left);
                    fprintf(tex_file, ")");
                    break;

                default:
                    fprintf(stderr, "Incorrect node writing in tex\n");
                    return Incorrect_Node;
            }
            break;

        default:
            fprintf(stderr, "incorrect type of node %d in tex\n", cur_node->type);
            return Incorrect_Mode;
    }

    return No_Error;
}

//-------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------//