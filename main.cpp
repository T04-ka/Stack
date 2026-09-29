
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




//-------------------------------------------------------------------------------------
int stkpush(stack_t* Stk, int var){

    if (Stk -> cpty == Stk -> ind) {

        stkgrow(Stk);
    }

    Stk -> ind ++;
    *(Stk -> bffr + Stk -> ind) = var;

   return 0;
}


//-------------------------------------------------------------------------------------
int stkpop(stack_t* Stk, int* var){

    if (Stk -> ind == 0) {

        return 1; //DO STCKUNDERFLOW
    }

    *var = *(Stk -> bffr + Stk -> ind);
    Stk -> ind --;

    return 0;
}


//-------------------------------------------------------------------------------------
int main(){


}
