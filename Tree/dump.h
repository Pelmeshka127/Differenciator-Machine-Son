#ifndef DUMP_H_
#define DUMP_H_

#include "tree.h"

#define TREE_DUMP

//-------------------------------------------------------------------------------//

/// @brief Function opens log_file
/// @return File_Error if there's error, No_Error if it's ok
int Open_Log_File();

//-------------------------------------------------------------------------------//

/// @brief Function closes log_file
/// @return File_Error if there's error, No_Error if it's ok
int Close_Log_File();

//-------------------------------------------------------------------------------//

/// @brief Function make picture of tree
/// @param my_tree is ptr on the tree struct
int Tree_Dump(tree_s * const my_tree);

//-------------------------------------------------------------------------------//

/// @brief Function draws nodes of the tree (function is called by Tree_Dump() )
/// @param root is ptr on the tree node
void Tree_Draw(tree_node * const node);

//-------------------------------------------------------------------------------//

/// @brief Functions draws tree to the latex file
/// @param my_tree is ptr on the tree struct
/// @param png_name is the dst picture name
void Tree_Dump_To_Tex(tree_s * const my_tree, char * png_name);

//-------------------------------------------------------------------------------//

/// @brief Function draws separate node of the tree
/// @param node is ptr on the src node
/// @return No_Error or File_Error if there's file error
int Tree_Dump_Node(tree_node * const node);

//-------------------------------------------------------------------------------//

#endif