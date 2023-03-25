#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "treeconfig.h"
#include "../Parsering/parser.h"
#include "../architecture.h"

struct tree_node {
    type_t type;
    data_t data;
    tree_node * left;
    tree_node * right;
};

struct tree_s {
    tree_node * root;
    int size;               //number of the uneempty nodes
};

//-------------------------------------------------------------------------------//

/// @brief Function allocates memory for the root of the tree
/// @param my_tree is ptr on the tree struct
/// @param root is ptr on the tree's root
/// @param word is value of the root
/// @return nullptr is there's bad alloc, root if it's ok
int Tree_Ctor(tree_s * const my_tree);

//-------------------------------------------------------------------------------//

/// @brief Function allocates memory for the new node and inserts value to this node
/// @param my_tree is ptr on the tree struct
/// @param inserting_node is ptr on the inserting node
/// @param word is value of the node
/// @return nullptr if there's error, inserting_node if it's ok
tree_node * Tree_Insert_Node(type_t type, data_t data, tree_node * left, tree_node * right);

//-------------------------------------------------------------------------------//

/// @brief 
/// @param my_tree 
/// @return 
int Tree_Get_Size(tree_s * const my_tree, tree_node * const node);

//-------------------------------------------------------------------------------//

/// @brief Function makes tree from source file
/// @param my_tree is ptr on the tree struct
/// @return File_Error if creating tree failed, No_Error if it's ok
int Tree_Download(tree_s * const my_tree);

//-------------------------------------------------------------------------------//

/// @brief Function 
/// @param Onegin 
/// @param my_tree 
/// @param cur_node 
/// @return 
int Tree_Reader(Text_Info * const onegin, tree_s * const my_tree, tree_node ** cur_node);

//-------------------------------------------------------------------------------//

int New_Tree_Reader(Text_Info * const onegin, tree_s * const my_tree, tree_node ** cur_node);

//-------------------------------------------------------------------------------//

int Tree_Get_Number_By_Operator(char * operation);    

//-------------------------------------------------------------------------------//

/// @brief 
/// @param node_item 
/// @param line_start 
/// @return 
int Tree_Make_Node_Item(char * node_item, const char * line_start);

//-------------------------------------------------------------------------------//

/// @brief Function walks tree in the infix order
/// @param my_tree is ptr on the tree struct
/// @return 
int Tree_Walk_In_Order(tree_node * const root);

//-------------------------------------------------------------------------------//

/// @brief 
/// @param root 
/// @return 
int Tree_Walk_Pre_Order(tree_node * const root);

//-------------------------------------------------------------------------------//

/// @brief 
/// @param root 
/// @return 
int Tree_Walk_Post_Order(tree_node * const root);

//-------------------------------------------------------------------------------//

/// @brief Fuction cleans all of the nodes
/// @param root is ptr on the root of the tree
/// @return No_Error
int Tree_Clean(tree_node * const root);

//-------------------------------------------------------------------------------//

/// @brief Function destroys tree
/// @param my_tree is ptr on the tree struct
/// @return No_Error
int Tree_Dtor(tree_s * const my_tree);

//-------------------------------------------------------------------------------//

#endif