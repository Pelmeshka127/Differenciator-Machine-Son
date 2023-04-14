#ifndef TEX_H_
#define TEX_H_

#include "../Tree/tree.h"
#include "../Tree/dump.h"
#include "../Differenciator/differenciator.h"

//-------------------------------------------------------------------------------//

/// @brief Function opens Tex_File and writes down the startinformation
/// @return File_Error if there's open error, No_Error if it's ok
int Tex_Start_File();

//-------------------------------------------------------------------------------//

/// @brief Function closes Tex_File
/// @return File_Error if there's open error, No_Error if it's ok
int Tex_End_File();

//-------------------------------------------------------------------------------//

/// @brief Function works with the mode of the programm
/// @param my_tree is ptr on the source tree
/// @param diff_tree is ptr on the diff tree
/// @param mode is mode of the programm
/// @return continues work with the tree an returns No_Error
int Tex_Programm_Mode(tree_s * const my_tree, tree_s * const diff_tree, int mode);

//-------------------------------------------------------------------------------//

/// @brief Function writes down the picture of the tree to Tex_File
/// @param my_tree is ptr on the current tree
/// @return No_Error
int Tex_Show_Function_Tree(tree_s * const my_tree);

//-------------------------------------------------------------------------------//

/// @brief Function get the value of the tree at the point and writes it to the Tex_File
/// @param my_tree is ptr on the source tree
/// @param point is point)))
/// @return No_Error
int Tex_Calc_Tree(tree_s * const my_tree, int point);

//-------------------------------------------------------------------------------//

/// @brief Function prints the node of the tree to the Tex_File
/// @param cur_node is ptr on the current node
/// @return No_Error if it's ok, Incorrect_Node if there's an error
int Tex_Print_Tree_Node(tree_node * const cur_node);

//-------------------------------------------------------------------------------//

/// @brief Function gets the derivative of the tree and writes it to the Tex_File
/// @param my_tree is ptr on the source tree
/// @param diff_tree is ptr on the diff tree
/// @return No_Error
int Tex_Differenciation(tree_s * const my_tree, tree_s * const diff_tree);

//-------------------------------------------------------------------------------//

/// @brief Function gets the Maclaurin formula of the function
/// @param my_tree is ptr on the source tree
/// @param diff_tree is ptr on the diff tree
/// @return No_Error
int Tex_Maclaurin(tree_s * const my_tree, tree_s * const diff_tree);

//-------------------------------------------------------------------------------//

#endif