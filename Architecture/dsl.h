#define NODE node

#define LEFT cur_node->left

#define RIGHT cur_node->right

#define EVAL(node)  \
    Eval(node)

#define dL  \
    Diff(LEFT)

#define dR  \
    Diff(RIGHT)

#define cL  \
    Copy_Node(LEFT)

#define cR  \
    Copy_Node(RIGHT)

#define New_Num(data) \
    Tree_New_Node(Num_Type, data)

#define New_Op(data, left, right)   \
    Tree_New_Node(Op_Type, data, left, right)

#define New_Var(data, left, right)  \
    Tree_New_Node(Var_Type, data, left, right)