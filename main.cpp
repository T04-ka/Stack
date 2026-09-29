
#include <cstdlib>
#include <stdio.h>
#include <assert.h>


struct stack_t {
    int* bffr;
    size_t cpty;
    size_t sz;
};


#define PZN 69


//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
void stkdmp(stack_t* Stk);


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
//-------------------------------------------------------------------------------------
int stkctor(stack_t* Stk, const size_t defcpty = 4);



//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
int stkdtor(stack_t* Stk);



//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
int stkpzn(stack_t* Stk);



void stkdmp(stack_t* Stk) {

    printf("Stack address = %p\n", Stk);

    if (Stk == NULL) {

        return;
    }

    printf("Capacity = %zu\n", Stk->cpty);
    printf("Size = %zu\n", Stk->sz);
    printf("Buffer adress = %p\n", Stk->bffr);
    printf("Buffer: \n");
    size_t i = 0;
    for (i = 0; i < Stk->sz; i++){

        printf("*[%zu] = %d\n", i, Stk->bffr [i]);
    }

    for (; i < Stk->cpty; i++) {

        printf("[%zu] = %d (PZN)\n", i, Stk->bffr [i]);
    }
}


//-------------------------------------------------------------------------------------
int stkpush(stack_t* Stk, int var){

    assert(Stk != 0);

    if (Stk->cpty == Stk->sz) {

        stkgrow(Stk);
    }


    *(Stk->bffr + Stk->sz) = var;
    Stk->sz ++;

   return 0;
}


//-------------------------------------------------------------------------------------
int stkpop(stack_t* Stk, int* var){

    assert(Stk != 0);

    if (Stk->sz == 0) {

        return 1; //DO STCKUNDERFLOW
    }

    Stk->sz --;
    *var = *(Stk->bffr + Stk->sz);

    return 0;
}


//-------------------------------------------------------------------------------------
int stkgrow(stack_t* Stk) {

    assert(Stk != 0);

    Stk->bffr = (int*) realloc(Stk->bffr, 2 * (Stk->cpty) * sizeof((Stk->bffr)[0]));

    Stk->cpty *= 2;

    stkpzn(Stk);

    return 0;
}


//-------------------------------------------------------------------------------------
int stkctor(stack_t* Stk, const size_t defcpty){

    assert(Stk != 0);

    Stk->bffr = (int*) calloc(defcpty, sizeof(int));
    Stk->cpty = defcpty;
    Stk->sz = 0;

    stkpzn(Stk);

    return 0;
}


//-------------------------------------------------------------------------------------
int stkdtor(stack_t* Stk){

    assert(Stk != 0);

    free(Stk->bffr);
    Stk->cpty = -1;
    Stk->sz = -1;

    return 0;
}


//-------------------------------------------------------------------------------------
int stkpzn(stack_t* Stk){

    for (size_t i = Stk->sz; i < Stk->cpty; i++){

        Stk->bffr [i] = PZN;
    }

    return 0;
}


//-------------------------------------------------------------------------------------
int main(){

    stack_t Stk = {};

    stkctor(&Stk);

    int inp = 1;
    while (inp != 0) {



        scanf("%d", &inp);
        getchar();
        stkpush(&Stk, inp);

        stkdmp(&Stk);
    }

    int out = 0;
    stkpop(&Stk, &out);
    printf("Last stack elem = %d\n", out);

    stkpop(&Stk, &out);
    printf("Last last stack elem = %d\n", out);

    stkdtor(&Stk);
}
