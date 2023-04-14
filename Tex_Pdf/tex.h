#ifndef TEX_H_
#define TEX_H_

#include "../Tree/tree.h"
#include "../Tree/dump.h"
#include "../Differenciator/differenciator.h"

//-------------------------------------------------------------------------------//

/// @brief 
/// @return 
int Tex_Start_File();

//-------------------------------------------------------------------------------//

/// @brief 
/// @return 
int Tex_End_File();

//-------------------------------------------------------------------------------//

/// @brief 
/// @param my_tree 
/// @param mode 
/// @return 
int Tex_Programm_Mode(tree_s * const my_tree, tree_s * const diff_tree, int mode);

//-------------------------------------------------------------------------------//

/// @brief 
/// @param my_tree 
/// @param file 
/// @return 
int Tex_Show_Function_Tree(tree_s * const my_tree);

//-------------------------------------------------------------------------------//

/// @brief 
/// @param my_tree 
/// @param value 
/// @return 
int Tex_Calc_Tree(tree_s * const my_tree, int value);

//-------------------------------------------------------------------------------//

/// @brief 
/// @param cur_node 
/// @return 
int Tex_Print_Tree_Node(tree_node * const cur_node);

//-------------------------------------------------------------------------------//

/// @brief 
/// @param my_tree 
/// @param diff_tree 
/// @return 
int Tex_Differenciation(tree_s * const my_tree, tree_s * const diff_tree);

//-------------------------------------------------------------------------------//

/// @brief 
/// @param my_tree 
/// @param diff_tree 
/// @return 
int Tex_Maclaurin(tree_s * const my_tree, tree_s * const diff_tree);

//-------------------------------------------------------------------------------//

#endif