#ifndef STACK_H
#define STACK_H

#include <cstdlib>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


typedef int stkelm_t;

const char* const FNCNMS[] = {
    "int stkpush(stack_t* Stk, int var)",
    "int stkpop(stack_t* Stk, int* var)",
    "int stkgrow(stack_t* Stk)",
    "int stkshrnk(stack_t* Stk)",
    "int stkctor(stack_t* Stk, const size_t defcpty = 4)",
    "int stkdtor(stack_t* Stk)",
    "int stkpzn(stack_t* Stk)"
};

const int NFNCS = 7;

struct stack_t {
    stkelm_t* bffr;
    size_t cpty;
    size_t sz;

    //ifdef
    const char* brnfl;
    const char* brnfnc;
    int brnln;
    FILE* logfl;
};


#include "stack.h"


#define PZN 69

#define STACK_OK                                \
    err = stkvrf(Stk, __PRETTY_FUNCTION__);     \
    if (err) {                                  \
                                                \
        stkdmp(Stk, err);                       \
        abort();                                \
    }


#define LOG(format, ...) fprintf(Stk->logfl, format, __VA_ARGS__);
void stkdmp(stack_t* Stk, int err) {

    LOG("Stack address = %p\n", Stk);

    if (Stk == NULL) {

        return;
    }

    LOG("Capacity = %zu\n", Stk->cpty);
    LOG("Size = %zu\n", Stk->sz);
    LOG("Buffer adress = %p\n", Stk->bffr);

    size_t i = 0;
    for (i = 0; i < Stk->sz; i++){

        LOG("*[%zu] = %d\n", i, Stk->bffr [i]); //СДЕЛАТЬ МАКРОСС ДЛЯ ПРИЗВОЛЬНОГО ТИПА
    }

    for (; i < Stk->cpty; i++) {

        LOG("[%zu] = %d (PZN)\n", i, PZN);
    }
}

#define PRVFNC_OK                           \
    int prvfnc_ok = 0;                      \
    for (int i = 0; i < NFNCS; i++) {       \
                                            \
        if (strcmp(prvfnc, FNCNMS[i])) {    \
                                            \
            prvfnc_ok = 1;                  \
            break;                          \
        }                                   \
    }

//-------------------------------------------------------------------------------------
int stkvrf(stack_t* Stk, const char* prvfnc) {

    PRVFNC_OK
    if (!prvfnc_ok) {

        return 1; //WRONG PREV FUNCTION CALL
    }

    if (Stk == NULL) {

        return 2; //NULL POINTER
    }

    if (Stk->bffr == NULL) {

        return 3; //BUFFER NULL POINTER
    }

    if (Stk->cpty < 1) {

        return 4; //WRONG CAPACITY
    }

    if (Stk->sz > Stk->cpty) {

        return 5; //WRONG SIZE
    }

    //TODO КАНАРЕЙКИ И ХЭШИ

    return 0;
}

#undef PRVFNC_OK


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
//сделать ошибки
// сделть дамп

//-------------------------------------------------------------------------------------
int stkpop(stack_t* Stk, int* var){

    assert(Stk != 0);

    if (Stk->sz == 0) {

        return 1; //DO STCKUNDERFLOW
    }

    Stk->sz --;
    *var = *(Stk->bffr + Stk->sz);

    if (2 * Stk->sz < Stk->cpty && Stk->cpty > 5){

        stkshrnk(Stk);
    }

    return 0;
}


//-------------------------------------------------------------------------------------
int stkgrow(stack_t* Stk) {

    assert(Stk != 0);

    Stk->bffr = (stkelm_t*) realloc(Stk->bffr, 2 * (Stk->cpty) * sizeof((Stk->bffr)[0]));

    Stk->cpty *= 2;

    stkpzn(Stk);

    return 0;
}


//-------------------------------------------------------------------------------------
int stkshrnk(stack_t *Stk){

    assert(Stk != 0);

    Stk->bffr = (stkelm_t*) realloc(Stk->bffr, (Stk->cpty / 2) * sizeof((Stk->bffr)[0]));

    Stk->cpty /= 2;

    return 0;
}


//-------------------------------------------------------------------------------------
int stkctor(stack_t* Stk, const char* brnfl, const char* brnfnc, int brnln, const size_t defcpty){


    printf("line: %d\n", __LINE__);
    printf("file: %s\n", __FILE__);
    printf("func: %s\n", __FUNCTION__);
    printf("prevFunc: %s\n", __PRETTY_FUNCTION__);

    assert(Stk != 0);

    Stk->bffr = (stkelm_t*) calloc(defcpty, sizeof(int));
    Stk->cpty = defcpty;
    Stk->sz = 0;

    //ifdef
    Stk->brnfl = brnfl;
    Stk->brnfnc = brnfnc;
    Stk->brnln = brnln;
    Stk->logfl = fopen("log.txt","w");

    stkpzn(Stk);

    return 0;
}


//-------------------------------------------------------------------------------------
int stkdtor(stack_t* Stk){

    assert(Stk != 0);

    free(Stk->bffr);
    Stk->cpty = -1;
    Stk->sz = -1;

    //ifdef
    Stk->brnfl = "DED_LOH";
    Stk->brnfnc = "DED_LOH";
    Stk->brnln = -1;
    fclose(Stk->logfl);

    return 0;
}


//-------------------------------------------------------------------------------------
int stkpzn(stack_t* Stk){

    for (size_t i = Stk->sz; i < Stk->cpty; i++){

        Stk->bffr [i] = PZN;
    }

    return 0;
}

#endif
