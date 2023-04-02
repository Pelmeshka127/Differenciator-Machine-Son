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
/// @param node 
/// @return 
tree_node * Diff(tree_node * const cur_node);

//-------------------------------------------------------------------------------//

/// @brief 
/// @param cur_node 
/// @return 
tree_node * Copy_Node(tree_node * const cur_node);

//-------------------------------------------------------------------------------//

/// @brief 
/// @param src_root 
/// @param diff_root 
/// @return 
int Diff_Print_Equation(tree_node * src_root, tree_node * diff_root);

//-------------------------------------------------------------------------------//

#endif