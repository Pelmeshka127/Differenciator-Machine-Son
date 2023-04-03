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
    data_t a = EVAL(LEFT);
    data_t b = EVAL(RIGHT);
    if ((int) b == 0)
    {
        fprintf(stderr, "Division by zero in function %s\n", __PRETTY_FUNCTION__);
        return Incorrect_Node;
    }
    return a / b;
})

DEF_CMD(POW, Op_Pow,
{
    data_t a = EVAL(LEFT);
    data_t b = EVAL(RIGHT);
    if ((int) a == 0)
        return 0;
    else if ((int) a == 0)
        return 1;
    else
    {
        for (int i = 1; i < (int) b; i++)
            a *= a;
        return a;
    }
})