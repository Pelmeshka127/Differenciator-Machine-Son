#ifndef DIFFERENCIATOR_H_
#define DIFFERENCIATOR_H_

#include "../Tree/tree.h"
#include "../Architecture/dsl.h"
#include "../Tree/dump.h"
#include "../Tex_Pdf/tex.h"

/// @brief Function checks the value of the command line arguments
/// @param args is the number of arguments
/// @return Cmdline_Error if there's an error, No_Error if it's ok
int Check_Cmdline_Arg(int args);

//-------------------------------------------------------------------------------//

/// @brief Function starts working with the source funtion written in the tree
/// @param my_tree is ptr on the tree of the function
/// @return smth)))
int Start_Programm(tree_s * const my_tree);

//-------------------------------------------------------------------------------//

/// @brief Function calculates constant expressions
/// @param cur_node is ptr on the curren node
/// @return the value of the tree_node
data_t Eval(tree_node * const cur_node);

//-------------------------------------------------------------------------------//

/// @brief Function starts to derivative function and simplify it
/// @param diff_tree is ptr on the diff_tree
/// @param src_root is ptr on the source tree
/// @return tree root of derivative tree
tree_node * Diff(tree_s * const diff_tree, tree_node * const src_root);

//-------------------------------------------------------------------------------//

/// @brief Functions gets the derivative of the function
/// @param my_tree is ptr on the source tree
/// @param cur_node is ptr on the current node of the tree
/// @return new derivative node
tree_node * Diff_Calc(tree_s * const my_tree, tree_node * const cur_node);

//-------------------------------------------------------------------------------//

/// @brief Function makes a copy of the node
/// @param cur_node is ptr on the current node
/// @return copy node
tree_node * Diff_Copy_Node(tree_node * const cur_node);

//-------------------------------------------------------------------------------//

/// @brief Function makes three easier
/// @param cur_node is ptr on the current node of tree
/// @param simplified_flag is flag of simplify
/// @return No_Error; makes simplified_flag = 1, if there's simplifiers, 0, if it's simplified
int Diff_Simplifier(tree_node * const cur_node, int *simplified_flag);

//-------------------------------------------------------------------------------//

/// @brief Function get the value of function at the point
/// @param cur_node is ptr on the current node of the tre
/// @param value is value of the point
/// @return function value
int Find_Function_At_Point(tree_node * cur_node, int value);

//-------------------------------------------------------------------------------//

/// @brief Function just allows you to enter new value after a mistake
void Skip_Line();

//-------------------------------------------------------------------------------//

/// @brief Function clears terminal
void Clear_Terminal();

//-------------------------------------------------------------------------------//

#endif