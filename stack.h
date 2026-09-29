#ifndef STACK_H
#define STACK_H


#include <stdio.h>


struct stack_t {
    int* bffr;
    long long cpty;
    size_t ind;
};


//-------------------------------------------------------------------------------------
/// Increases the stack capacity
///
/// @return 0 on success, non-null number on failure.
///
//-------------------------------------------------------------------------------------
int stkgrow(stack_t* Stk);



//-------------------------------------------------------------------------------------
/// Reduses the stack capacity
///
/// @return 0 on success, non-null number on failure.
///
//-------------------------------------------------------------------------------------
int stkshrnk(stack_t* Stk);



//-------------------------------------------------------------------------------------
/// Adds the ellement to stack
///
/// @return 0 on success, non-null number on failure.
///
//-------------------------------------------------------------------------------------
int stkpush(stack_t* Stk, int var);



//-------------------------------------------------------------------------------------
/// Gets the element from stack
///
/// @param[in]  Stk  Pointer to Stack structure
/// @param[out] elmw Pointer to a variable for writing.
///
/// @return 0 on success, non-null number on failure.
///
//-------------------------------------------------------------------------------------
int stkpop(stack_t* Stk, int* var);




#endif
