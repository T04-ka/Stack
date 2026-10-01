#ifndef STACK_H
#define STACK_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#define RED "\e[31m"
#define BLUE "\e[34m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define FAT "\e[1m"
#define DEF "\e[0m"


typedef const char* str;

typedef int stkelm_t;

str const FNCNMS[] = {
    "void stkdmp(stack_t*, str, str, str, int)",
    "int stkvrf(stack_t*, str)",
    "void stkerrhnd(stack_t*, _errt, str, str, str, int)",
    "int stkpush(stack_t*, int, str, str, int)",
    "int stkpop(stack_t*, int*, str, str, int)",
    "int stkgrow(stack_t*, str, str, int)",
    "int stkshrnk(stack_t*, str, str, int)",
    "int stkctor(stack_t*, str, str, str, int, size_t)",
    "int stkdtor(stack_t*, str, str, int)",
    "int stkpzn(stack_t*, str, str, int)",
};

const int NFNCS = 10;

str dmpsep = "//-------------------------------------------------------------------------------------";


struct stack_t {
    stkelm_t* bffr;
    size_t cpty;
    size_t sz;

    //ifdef
    str _tp;
    str _nm;
    str _brnfl;
    str _brnfnc;
    int _brnln;
    FILE* _logfl;
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

#define STACK_OK                                                            \
    int err = stkvrf(Stk, __PRETTY_FUNCTION__);                             \
    stkerrhnd(Stk, (_errt) err, __PRETTY_FUNCTION__, _fl, _fnc, _nln);


//-------------------------------------------------------------------------------------
#define LOG(format, ...) fprintf(Stk->_logfl, format, __VA_ARGS__);
#define SEP fprintf(Stk->_logfl, "%s\n", dmpsep);
#define NLN putc('\n', Stk->_logfl);

void stkdmp(stack_t* Stk, str _frmfnc, str _fl, str _fnc, int _nln) {

    SEP
    LOG("Dump was called by error handler from function " GREEN "%s.\n" DEF, _frmfnc);
    LOG(GREEN "\"%s\"" DEF " created in file " GREEN "%s" DEF " in " GREEN "%s" DEF " on line " GREEN "%d.\n" DEF,
              Stk->_nm,                              Stk->_brnfl,          Stk->_brnfnc,               Stk->_brnln);


    LOG("Stack address: [%p]. Stack type: \"%s\".\n", Stk, Stk->_tp);

    if (Stk == NULL) {

        return;
    }

    LOG("Capacity = %zu. ", Stk->cpty);
    LOG("Size = %zu. ", Stk->sz);
    LOG("Buffer adress = [%p]. \n", Stk->bffr);
    NLN
    size_t i = 0;
    for (i = 0; i < Stk->sz; i++){

        LOG("*[%zu] = %d\n", i, Stk->bffr [i]); //TODO СДЕЛАТЬ МАКРОСС ДЛЯ ПРИЗВОЛЬНОГО ТИПА
    }

    for (; i < Stk->cpty; i++) {

        LOG("[%zu] = %d (PZN)\n", i, PZN);
    }
    NLN
    SEP
}

#undef LOG


//-------------------------------------------------------------------------------------
//printf("strcmp(%s, %s) = %d\n)", prvfnc, FNCNMS[i], strcmp(prvfnc, FNCNMS[i]));

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

    if (!prvfnc_ok) {

        return 1; //WRONG PREV FUNCTION CALL
    }

    if (Stk == NULL) {

        return 2; //NULL POINTER
    }

    if (!strcmp("int stkctor(stack_t*, str, str, str, int, size_t)", prvfnc))
        return 0;

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
void stkerrhnd(stack_t* Stk, _errt err, str _prvfnc, str _fl, str _fnc, int _nln) {

    switch (err)
    {
        case WRONGFUNCCALL: //WRONG FUNCTION CALLED VERIFICATOR
        {
            fprintf(stderr, RED "==================================CRITICAL FATAL PANIC UNRECOVERABLE ERROR: Verifier was called from function \"%s\", that has no acces to сall.==================================\n" DEF, _prvfnc);

            //stkdtor(Stk, "", "", 0); //СДЕЛАТЬ ПО МАКРОССУ STDERR (CМ DTOR)

            abort();
            break;
        }

        case STRUCTNULLPTR: //STRUCTURE HAS NULL POINTER
        {
            fprintf(stderr, RED FAT "CRITICAL FATAL PANIC UNRECOVERABLE ERROR: NULL was passed as a pointer to the structure.\n" DEF);
            fprintf(stderr, RED "Last stack call was in %s:%d in function %s.\n" DEF,
                                                       _fl, _nln,        _fnc);
            //stkdmp(Stk, _prvfnc, _fl, _fnc, _nln);
            //putc('\n', stderr);

            //stkdtor(Stk, "", "", 0);

            abort();
            break;
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

        case STKBUFUNDRFLW: //STACKBUFFERUNDERFLOW
        {
            fprintf(stderr, RED FAT "====================================================== CRITICAL FATAL PANIC UNRECOVERABLE ERROR: Stack buffer underflow. ======================================================\n" DEF);
            fprintf(stderr, RED "Last stack call was in %s:%d in function %s.\n" DEF,
                                                       _fl, _nln,        _fnc);
            stkdmp(Stk, _prvfnc, _fl, _fnc, _nln);
            putc('\n', stderr);

            stkdtor(Stk, "", "", 0);

            abort();
            break;
        }

        case 6: //STACKBUFFEROVERFLOW
        {

        }

        default: {}
    }

}


//-------------------------------------------------------------------------------------
int stkpush(stack_t* Stk, int var, str _fl, str _fnc, int _nln){

    STACK_OK

    if (Stk->cpty == Stk->sz) {

        stkgrow(Stk, _fl, _fnc, _nln);
    }

    *(Stk->bffr + Stk->sz) = var;
    Stk->sz ++;

   return 0;
}
//сделать ошибки
// сделть дамп

//-------------------------------------------------------------------------------------
int stkpop(stack_t* Stk, int* var, str _fl, str _fnc, int _nln){

    STACK_OK

    if (Stk->sz == 0) {

        stkerrhnd(Stk, STKBUFUNDRFLW, __PRETTY_FUNCTION__, _fl, _fnc, _nln);
        return 7; //TODO STCKUNDERFLOW
    }

    Stk->sz --;
    *var = *(Stk->bffr + Stk->sz);

    if (2 * Stk->sz < Stk->cpty && Stk->cpty > 5){

        stkshrnk(Stk, _fl, _fnc, _nln);
    }

    return 0;
}


//-------------------------------------------------------------------------------------
int stkgrow(stack_t* Stk, str _fl, str _fnc, int _nln) {

    STACK_OK

    Stk->bffr = (stkelm_t*) realloc(Stk->bffr, 2 * (Stk->cpty) * sizeof((Stk->bffr)[0]));

    Stk->cpty *= 2;

    stkpzn(Stk, _fl, _fnc, _nln);

    return 0;
}


//-------------------------------------------------------------------------------------
int stkshrnk(stack_t *Stk, str _fl, str _fnc, int _nln){

    STACK_OK

    Stk->bffr = (stkelm_t*) realloc(Stk->bffr, (Stk->cpty / 2) * sizeof((Stk->bffr)[0]));

    Stk->cpty /= 2;

    return 0;
}


//-------------------------------------------------------------------------------------
int stkctor(stack_t* Stk, str _nm, str _fl, str _fnc, int _nln, const size_t defcpty){

    STACK_OK

    Stk->bffr = (stkelm_t*) calloc(defcpty, sizeof(int));
    Stk->cpty = defcpty;
    Stk->sz = 0;

    //ifdef
    Stk->_tp = "int";
    Stk->_nm = _nm;
    Stk->_brnfl = _fl;
    Stk->_brnfnc = _fnc;
    Stk->_brnln = _nln;
    Stk->_logfl = stderr;
    //Stk->_logfl = fopen("log.txt","w"); ////TODO: SDELAT DEFINOM ПЕРЕКЛЮЧЕНИЕ НА STDERR

    stkpzn(Stk, _fl, _fnc, _nln);

    return 0;
}


//-------------------------------------------------------------------------------------
int stkdtor(stack_t* Stk, str _fl, str _fnc, int _nln){

    //STACK_OK

    free(Stk->bffr);
    Stk->cpty = -1;
    Stk->sz = -1;

    //ifdef
    Stk->_brnfl = "DED_LOH";
    Stk->_brnfnc = "DED_LOH";
    Stk->_brnln = -1;
    fclose(Stk->_logfl);

    return 0;
}


//-------------------------------------------------------------------------------------
int stkpzn(stack_t* Stk, str _fl, str _fnc, int _nln){

    STACK_OK

    for (size_t i = Stk->sz; i < Stk->cpty; i++){

        Stk->bffr [i] = PZN;
    }

    return 0;
}


#endif
