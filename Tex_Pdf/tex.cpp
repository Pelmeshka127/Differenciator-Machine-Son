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

int Tex_Programm_Mode(tree_s * const my_tree, tree_s * const diff_tree, int mode)
{
    assert(my_tree);

    int point = 0;

    switch(mode)
    {
        case Show_Tree:
            fprintf(tex_file, "\\section{Showing the source tree}\n");
            Tex_Show_Function_Tree(my_tree);
            break;

        case Find_Func_Value_At_Point:
            fprintf(tex_file, "\\section{Finding function at the point}\n");
            printf("Enter point where you want to find value of the function: ");
            while (scanf("%d", &point) != 1)
            {
                Skip_Line();
                printf("Incorrect value. Try one more time\n");
            }
            Tex_Calc_Tree(my_tree, point);
            fprintf(tex_file, "\\newpage\n");
            break;

        case Get_Diff:
            fprintf(tex_file, "\\section{Getting derivative}\n");
            Tex_Differenciation(my_tree, diff_tree);
            break;

        case Find_Diff_Value_At_Point:
            fprintf(tex_file, "\\section{Getting derivative at the point}\n");
            printf("Enter point where you want to find value of the derivative: ");
            while (scanf("%d", &point) != 1)
            {
                Skip_Line();
                printf("Incorrect value. Try one more time\n");
            }
            Tex_Calc_Tree(diff_tree, point);
            fprintf(tex_file, "\\newpage\n");
            break;

        case Show_Diff_Tree:
            fprintf(tex_file, "\\section{Showing the Diff tree}\n");
            Tex_Show_Function_Tree(diff_tree);
            break;

        case Maclaurin:
            fprintf(tex_file, "\\section{Makclurin formula}\n");
            Tex_Maclaurin(my_tree, diff_tree);
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

    tree_s copy = {};
    Tree_Ctor(&copy);

    tree_node *copy_tree = Diff_Copy_Node(my_tree->root);

    copy.root = copy_tree;

    fprintf(tex_file, "\\begin{center}\n");

    fprintf(tex_file, "Your function is $F = ");

    Tex_Print_Tree_Node(copy_tree);

    fprintf(tex_file, "$.\n");

    fprintf(tex_file, "The value of your function at %d: $ F(%d) = ", value, value);   

    copy_tree->data = Find_Function_At_Point(copy_tree, value);

    fprintf(tex_file, "%d $\n", copy_tree->data);

    fprintf(tex_file, "\\end{center}\n");

    Tree_Dtor(&copy);

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

                case Op_Exp:
                    fprintf(tex_file, "e^{");
                    Tex_Print_Tree_Node(cur_node->left);
                    fprintf(tex_file, "}");
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

int Tex_Differenciation(tree_s * const my_tree, tree_s * const diff_tree)
{
    assert(my_tree);
    assert(diff_tree);

    static int frase_num = 0;

    fprintf(tex_file, "\\begin{center}\n");

    char * frases [5] = {   "Oh shit, it so deep...\\\\",
                            "Oh shit, it's depper than before\\\\",
                            "Fuck, i'm cumming from this calculations\\\\",
                            "Ya me te kudasay...\\\\",
                            "Gimme gimme more, gimme gimme more\\\\"};
                        
    fprintf(tex_file, "$(");

    Tex_Print_Tree_Node(my_tree->root);

    fprintf(tex_file, ")' = ");
    
    Tex_Print_Tree_Node(diff_tree->root);
    
    fprintf(tex_file, "$\\\\\n");

    int is_simplified = 0;

    do {
        is_simplified = 0;

        Diff_Simplifier(diff_tree->root, &is_simplified);

        fprintf(tex_file, "%s\n", frases[(frase_num++) % 5]);

        fprintf(tex_file, "$(");
        Tex_Print_Tree_Node(my_tree->root);
        fprintf(tex_file, ")' = ");

        Tex_Print_Tree_Node(diff_tree->root);

        fprintf(tex_file, "$\\\\\n");

        if (!is_simplified)
            break;

    } while (is_simplified);

    fprintf(tex_file, "It was the best sex.., xm, differenciation ever\n");

    fprintf(tex_file, "\\end{center}\n");

    fprintf(tex_file, "\\newpage\n");

    printf("Differenciations end\n");

    return No_Error;
}

//-------------------------------------------------------------------------------//

int Tex_Maclaurin(tree_s * const my_tree, tree_s * const diff_tree)
{
    int order = 0;

    tree_node *maclaurin  = Diff_Copy_Node(my_tree->root);
    tree_node *diff = Diff_Copy_Node(diff_tree->root);

    int f_0 = Find_Function_At_Point(maclaurin, 0);
    int f_1 = Find_Function_At_Point(diff, 0);

    printf("Enter order which you want to get decomposition: ");
    while (scanf("%d", &order) != 1 || order < 1)
    {
        Skip_Line();
        printf("Incorrect order. Try one more time\n");
    }

    fprintf(tex_file, "I like big expressions XD\\\\\n");

    fprintf(tex_file, "\\begin{center}\n");

    fprintf(tex_file, "$");

    Tex_Print_Tree_Node(my_tree->root);

    fprintf(tex_file, " = ");

    if (f_0 != 0)
        fprintf(tex_file," %d + ", f_0);
    
    if (f_1 == 1)
        fprintf(tex_file, " x + ");

    else if (f_1 == -1)
        fprintf(tex_file, " -x + ");

    else if (f_1 != -1 && f_1 != 1 && f_1 != 0)
        fprintf(tex_file, " %dx + ", f_1);

    for (int index = 2; index <= order; index++)
    {
        Diff(diff_tree, diff_tree->root);
        tree_node * copy_node = Diff_Copy_Node(diff_tree->root);
        copy_node->data = Find_Function_At_Point(copy_node, 0);

        if (copy_node->data != 0 && copy_node->data != 1 && copy_node->data != -1)
            fprintf(tex_file, "\\frac{%dx^{%d}}{%d!} + ", copy_node->data, index, index);

        else if (copy_node->data == 1)
            fprintf(tex_file, "\\frac{x^{%d}}{%d!} + ", index, index);

        else if (copy_node->data == -1)
            fprintf(tex_file, "\\frac{-x^{%d}}{%d!} + ", index, index);

        Tree_Clean(&copy_node);
    }

    fprintf(tex_file, "o(x^{%d}) $\n", order);

    fprintf(tex_file, "\\end{center}\n");

    Tree_Clean(&maclaurin);
    Tree_Clean(&diff);

    return No_Error;
}