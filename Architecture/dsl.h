#define NODE cur_node

#define LEFT cur_node->left

#define RIGHT cur_node->right

#define EVAL(node)  \
    Eval(node)

#define dL  \
    Diff(my_tree, LEFT)

#define dR  \
    Diff(my_tree, RIGHT)

#define cL  \
    Copy_Node(LEFT)

#define cR  \
    Copy_Node(RIGHT)

#define ADD(left, right) \
    Tree_New_Node(Op_Type, Op_Add, left, right)

#define SUB(left, right) \
    Tree_New_Node(Op_Type, Op_Sub, left, right)

#define MUL(left, right) \
    Tree_New_Node(Op_Type, Op_Mul, left, right)

#define DIV(left, right) \
    Tree_New_Node(Op_Type, Op_Div, left, right)

#define POW(left, right) \
    Tree_New_Node(Op_Type, Op_Pow, left, right)

#define New_Num(data) \
    Tree_New_Node(Num_Type, data)

#define New_Op(data, left, right)   \
    Tree_New_Node(Op_Type, data, left, right)

#define New_Var(data)  \
    Tree_New_Node(Var_Type, data)