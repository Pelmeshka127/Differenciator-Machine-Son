#ifndef ARCHITECTURE_H_
#define ARCHITECTURE_H_

enum Errors_Code {
    No_Error        = 0,
    Bad_Alloc       = 1,
    File_Error      = 2,
    Undef_Capacity  = 3,
    Incorrect_Node  = 4,
    Underflow       = 5,
    Overflow        = 6,
};

enum Operation_Types {
    Num_Subject = 0,
    Op_Add      = 1,
    Op_Sub      = 2,
    Op_Mul      = 3,
    Op_Div      = 4,
};

const int Operation = 0;

const int Max_Length = 40;

#endif