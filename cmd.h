#include "dsl.h"

DEF_CMD(ADD, Op_Add, 
{
    return EVAL(LEFT) + EVAL(RIGHT);
})

DEF_CMD(SUB, Op_Sub, 
{
    return EVAL(LEFT) - EVAL(RIGHT);
})

DEF_CMD(MUL, Op_Mul,
{
    return EVAL(LEFT) * EVAL(RIGHT);
})

DEF_CMD(DIV, Op_Div,
{
    double a = EVAL(LEFT);
    double b = EVAL(RIGHT);
    if (b == 0)
    {
        fprintf(stderr, "Division by zero in function %s\n", __PRETTY_FUNCTION__);
        return Incorrect_Node;
    }
    return a / b;
})