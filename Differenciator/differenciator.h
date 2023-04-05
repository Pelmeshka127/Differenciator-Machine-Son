#ifndef DIFFERENCIATOR_H_
#define DIFFERENCIATOR_H_

#include "../Tree/tree.h"
#include "../Architecture/dsl.h"

//-------------------------------------------------------------------------------//

/// @brief 
/// @param node 
/// @return 
data_t Eval(tree_node * const cur_node);

//-------------------------------------------------------------------------------//

/// @brief 
/// @param diff_tree 
/// @param src_root 
/// @return 
tree_node * Diff(tree_s * const diff_tree, tree_node * const src_root);

//-------------------------------------------------------------------------------//

/// @brief 
/// @param my_tree 
/// @param cur_node 
/// @return 
tree_node * Diff_Calc(tree_s * const my_tree, tree_node * const cur_node);

//-------------------------------------------------------------------------------//

/// @brief 
/// @param cur_node 
/// @return 
tree_node * Diff_Copy_Node(tree_node * cur_node);

//-------------------------------------------------------------------------------//

/// @brief 
/// @param src_root 
/// @param diff_root 
/// @return 
int Diff_Print_Equation(tree_node * src_root, tree_node * diff_root);

//-------------------------------------------------------------------------------//


int Diff_Simplifier(tree_node * const cur_node);

//-------------------------------------------------------------------------------//


#endif