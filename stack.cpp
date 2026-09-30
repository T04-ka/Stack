#ifndef STACK_H
#define STACK_H

#include <cstdlib>
#include <locale>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#define RED "\e[31m"
#define BLUE "\e[34m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define DEF "\e[0m"


typedef const char* str;

typedef int stkelm_t;

str const FNCNMS[] = {
    "void stkdmp(stack_t*, int, str, str, str, int, str)",
    "int stkvrf(stack_t*, str)",
    "void stkerrhnd(_errt, str)",
    "int stkpush(stack_t*, int, str, str, int)",
    "int stkpop(stack_t*, int*, str, str, int)",
    "int stkgrow(stack_t*, str, str, int)",
    "int stkshrnk(stack_t*, str, str, int)",
    "int stkctor(stack_t*, str, str, str, int, const size_t)",
    "int stkdtor(stack_t*, str, str, int)",
    "int stkpzn(stack_t*, str, str, int)"
};

const int NFNCS = 10;

str dmpsep = "//-------------------------------------------------------------------------------------";

//сделать ввывод в дамп, откуда вызов какой функции

struct stack_t {
    stkelm_t* bffr;
    size_t cpty;
    size_t sz;

    //ifdef
    str tp;
    str nm;
    str brnfl;
    str brnfnc;
    int brnln;
    FILE* logfl;
};


enum _errt
{
    OK            = 0,
    WRONGFUNCCALL = 1,
    STRUCTNULLPTR = 2,
    STKBUFNULLPTR = 3,
    WRONGCPTY     = 4,
    WRONGSZ       = 5,
    STKBUFOVRFLW  = 6,
    STKBUFUNDRFLW = 7
};


#include "stack.h"


#define PZN 69

//-------------------------------------------------------------------------------------

#define STACK_OK                                                \
    int err = stkvrf(Stk, __PRETTY_FUNCTION__);                 \
    if (err) {                                                 \
                                                                \
        stkerrhnd((_errt) err, __PRETTY_FUNCTION__);           \
        stkdmp(Stk, err, __FUNCTION__, _fl, _frmfnc, _nln);    \
        stkdtor(Stk, _fl, _frmfnc, _nln);                      \
        //abort();                                                \
    }

//-------------------------------------------------------------------------------------
#define LOG(format, ...) fprintf(Stk->logfl, format, __VA_ARGS__);
#define SEP fprintf(Stk->logfl, "%s\n", dmpsep);
void stkdmp(stack_t* Stk, int err, str _fnc, str _fl, str _frmfnc, int _nln) {

    SEP
    LOG("Dump was called from function " GREEN "%s.\n" DEF, _fnc);
    LOG(GREEN "\"%s\"" DEF " created in file " GREEN "%s" DEF " in " GREEN "%s" DEF " on line " GREEN "%d.\n" DEF,
        Stk->nm,                     _fl,             _frmfnc,       _nln);

    LOG("Stack address: [%p]. Stack type: \"%s\".\n", Stk, Stk->tp);

    if (Stk == NULL) {

        return;
    }

    LOG("Capacity = %zu. ", Stk->cpty);
    LOG("Size = %zu. ", Stk->sz);
    LOG("Buffer adress = [%p]. \n", Stk->bffr);
    putc('\n', Stk->logfl);
    size_t i = 0;
    for (i = 0; i < Stk->sz; i++){

        LOG("*[%zu] = %d\n", i, Stk->bffr [i]); //СДЕЛАТЬ МАКРОСС ДЛЯ ПРИЗВОЛЬНОГО ТИПА
    }

    for (; i < Stk->cpty; i++) {

        LOG("[%zu] = %d (PZN)\n", i, PZN);
    }
    putc('\n', Stk->logfl);
    SEP
}

#undef LOG


//-------------------------------------------------------------------------------------

#define PRVFNC_OK                           \
    int prvfnc_ok = 0;                      \
    for (int i = 0; i < NFNCS; i++) {       \
        if (!strcmp(prvfnc, FNCNMS[i])) {   \
                                            \
            prvfnc_ok = 1;                  \
            break;                          \
        }                                   \
    }

//-------------------------------------------------------------------------------------
int stkvrf(stack_t* Stk, str prvfnc) {

    PRVFNC_OK

    int err = 0;

    if (!prvfnc_ok) {

        err = 1; //WRONG PREV FUNCTION CALL
    }

    if (Stk == NULL) {

        err = 2; //NULL POINTER
    }

    if (Stk->bffr == NULL) {

        err = 3; //BUFFER NULL POINTER
    }

    if (Stk->cpty < 1) {

        err = 4; //WRONG CAPACITY
    }

    if (Stk->sz > Stk->cpty) {

        err = 5; //WRONG SIZE
    }

    //TODO КАНАРЕЙКИ И ХЭШИ

    stkerrhnd((_errt) err, prvfnc);

    return err;
}

#undef PRVFNC_OK
/*
enum _errt
{
    OK            = 0,
    WRONGFUNCCALL = 1,
    STRUCTNULLPTR = 2,
    STKBUFNULLPTR = 3,
    WRONGCPTY     = 4,
    WRONGSZ       = 5,
    STKBUFOVRFLW  = 6,
    STKBUFUNDRFLW = 7
};
*/
void stkerrhnd(_errt err, str prvfnc) {

    switch (err)
    {
        case WRONGFUNCCALL: //WRONG FUNCTION CALLED VERIFICATOR
        {
            fprintf(stderr, RED "Verifier was called from function \"%s\", that has no acces to сall.\n" DEF, prvfnc);

            abort();
            break;
        }

        case : //STRUCTURE HAS NULL POINTER
        {

        }

        case 3: //STACK BUFFER HAS NULL POINTER
        {

        }

        case 4: //CAPACITY HAS WRONG VALUE
        {

        }

        case 5: //SIZE HAS WRONG VALUE
        {

        }

        case 6: //STACKBUFFERUNDERFLOW
        {

        }

        case 7: //STACKBUFFEROVERFLOW
        {

        }

        default: {}
    }

}


//-------------------------------------------------------------------------------------
int stkpush(stack_t* Stk, int var, str _fl, str _frmfnc, int _nln){

    stkvrf(Stk, __PRETTY_FUNCTION__);

    if (Stk->cpty == Stk->sz) {

        stkgrow(Stk, _fl, _frmfnc, _nln);
    }

    *(Stk->bffr + Stk->sz) = var;
    Stk->sz ++;

   return 0;
}
//сделать ошибки
// сделть дамп

//-------------------------------------------------------------------------------------
int stkpop(stack_t* Stk, int* var, str _fl, str _frmfnc, int _nln){

    stkvrf(Stk, __PRETTY_FUNCTION__);

    if (Stk->sz == 0) {


        return 1; //DO STCKUNDERFLOW
    }

    Stk->sz --;
    *var = *(Stk->bffr + Stk->sz);

    if (2 * Stk->sz < Stk->cpty && Stk->cpty > 5){

        stkshrnk(Stk, _fl, _frmfnc, _nln);
    }

    return 0;
}


//-------------------------------------------------------------------------------------
int stkgrow(stack_t* Stk, str _fl, str _frmfnc, int _nln) {

    stkvrf(Stk, __PRETTY_FUNCTION__);

    Stk->bffr = (stkelm_t*) realloc(Stk->bffr, 2 * (Stk->cpty) * sizeof((Stk->bffr)[0]));

    Stk->cpty *= 2;

    stkpzn(Stk, _fl, _frmfnc, _nln);

    return 0;
}


//-------------------------------------------------------------------------------------
int stkshrnk(stack_t *Stk, str _fl, str _frmfnc, int _nln){

    stkvrf(Stk, __PRETTY_FUNCTION__);

    Stk->bffr = (stkelm_t*) realloc(Stk->bffr, (Stk->cpty / 2) * sizeof((Stk->bffr)[0]));

    Stk->cpty /= 2;

    return 0;
}


//-------------------------------------------------------------------------------------
int stkctor(stack_t* Stk, str _nm, str _fl, str _frmfnc, int _nln, const size_t defcpty){

    if (Stk == NULL) {

        stkdmp(Stk, 1, __FUNCTION__, _fl, _frmfnc, _nln); //DODELAT
    }

    Stk->bffr = (stkelm_t*) calloc(defcpty, sizeof(int));
    Stk->cpty = defcpty;
    Stk->sz = 0;

    //ifdef
    Stk->tp = "int";
    Stk->nm = _nm;
    Stk->brnfl = _fl;
    Stk->brnfnc = _frmfnc;
    Stk->brnln = _nln;
    Stk->logfl = fopen("log.txt","w");

    stkpzn(Stk, _fl, _frmfnc, _nln);

    return 0;
}


//-------------------------------------------------------------------------------------
int stkdtor(stack_t* Stk, str _fl, str _frmfnc, int _nln){

    //stkvrf(Stk, __PRETTY_FUNCTION__);

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
int stkpzn(stack_t* Stk, str _fl, str _frmfnc, int _nln){

    stkvrf(Stk, __PRETTY_FUNCTION__);

    for (size_t i = Stk->sz; i < Stk->cpty; i++){

        Stk->bffr [i] = PZN;
    }

    return 0;
}

#endif
