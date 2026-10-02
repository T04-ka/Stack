#ifndef STACK_H
#define STACK_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define RED "\e[31m"
#define BLUE "\e[34m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define FAT "\e[1m"
#define DEF "\e[0m"

#define STK_HEAD_MXBFFRSZ (SIZE_MAX / 8)
#define MXSTKNM 100

#ifndef STK_MXBFFRSZ
#define STK_MXBFFRSZ STK_HEAD_MXBFFRSZ
#endif

#ifdef str
fprintf(stderr, RED FAT "YASHA PIDOR EBANIY\n" DEF);
abort();
#endif

typedef const char* str;

#ifndef stkelm_t
typedef int stkelm_t;
#endif


str const FNCNMS[] = {
        "int stkdmp(stack_t*, str, str, str, int)",
        "int stkvrf(stack_t*, str, str, str, int)",
        "void stkerrhnd(stack_t*, _errt, str, str, str, int)",
        "int stkpush(stack_t*, int, str, str, int)",
        "int stkpop(stack_t*, int*, str, str, int)",
        "int stkgrow(stack_t*, str, str, str, int)",
        "int stkshrnk(stack_t*, str, str, str, int)",
        "int stkctor(stack_t*, str, str, str, int, size_t)",
        "int stkdtor(stack_t*, str, str, int)",
        "int stkpzn(stack_t*, str, str, str, int)"
};

const int NFNCS = 10;


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
    STK_OK                       = 0,
    STK_WRONG_PREVFUNC_ACCESS    = 1,
    STK_STRUCT_NULLPTR           = 2,
    STK_BUFFER_NULLPTR           = 3,
    STK_WRONG_CPTY               = 4,
    STK_WRONG_SZ                 = 5,
    STK_MALLOC_FAILED            = 6,
    STK_BUFFER_UNDERFLOW         = 7,
    STK_DEFINED_CPTY_EXCESS      = 8,
    STK_WRONG_MXBFFRSZ_DEFINED   = 9,
    STK_POP_RECIEVER_NULLPTR     = 10
};

#ifdef STK_SANITIZE_LOUD
FILE* logfl = stderr;
#else
FILE* logfl = fopen("log.log", "w");
#endif


#include "stack.h"

#define STACK_DUMP(STKPTR)           stkdmp(STKPTR, __PRETTY_FUNCTION__, __FILE__, __PRETTY_FUNCTION__, __LINE__)
#define STACK_CTOR(STKNM, ...)       stkctor(&STKNM, #STKNM, __FILE__, __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#define STACK_PUSH(STKPTR, VAR)      stkpush(STKPTR, VAR, __FILE__, __PRETTY_FUNCTION__, __LINE__)
#define STACK_POP(STKPTR, VARPTR)    stkpop(STKPTR, VARPTR, __FILE__, __PRETTY_FUNCTION__, __LINE__)
#define STACK_DTOR(STKNM)            stkdtor(&STKNM, #STKNM, __FILE__, __PRETTY_FUNCTION__, __LINE__)


#define PZN 69

#ifdef STK_SANITIZE
#define HANDLER_TOGGLE  stkerrhnd(Stk, (_errt) err, __PRETTY_FUNCTION__, _fl, _fnc, _nln);
#else
#define HANDLER_TOGGLE void(0)
#endif

//-------------------------------------------------------------------------------------

#define STACK_OK                                                                                \
    int err = stkvrf(Stk, __PRETTY_FUNCTION__, _fl, _fnc, _nln);                                \
    HANDLER_TOGGLE;                                                                             \
    if (err) return err;


//-------------------------------------------------------------------------------------
#define ERROR_HANDLER_CALL  HANDLER_TOGGLE; \
                            return err;


//-------------------------------------------------------------------------------------
// //printf("strcmp(%s, %s) = %d\n", __PRETTY_FUNCTION__, FNCNMS[i], strcmp(__PRETTY_FUNCTION__, FNCNMS[i]));
#define PREVFUNC_ACCESS_OK                                                                  \
    int prvfnc_ok = 0;                                                                      \
    for (int i = 0; i < NFNCS; i++) {                                                       \
        if (!strcmp(_prvfnc, FNCNMS[i])) {                                                  \
                                                                                            \
            prvfnc_ok = 1;                                                                  \
            break;                                                                          \
        }                                                                                   \
    }                                                                                       \
    if (!prvfnc_ok) {                                                                       \
                                                                                            \
        stkerrhnd(Stk, STK_WRONG_PREVFUNC_ACCESS,  __PRETTY_FUNCTION__, _fl, _fnc, _nln);   \
    }


//-------------------------------------------------------------------------------------
#define LOG(format, ...) fprintf(outfl, format, __VA_ARGS__);
#define SEP fprintf(outfl, "\n-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
#define NLN putc('\n', outfl);
#define IF_CALLEDFUNCTION_STKERRHND if (!strcmp(FNCNMS[2], _frmfnc))

int stkdmp(stack_t* Stk, str _frmfnc, str _fl, str _fnc, int _nln) {

    FILE* outfl = stderr;

    IF_CALLEDFUNCTION_STKERRHND {

        outfl = logfl;
        SEP;
        LOG("Dump was called by error handler. %s", "");
    }
    else {

        STACK_OK;

        outfl = stdout;
        SEP;
        LOG("Dump was called from function " FAT "%s" DEF ", exactly from " FAT"%s:%d" DEF". ", _frmfnc, _fl, _nln);
    }


    LOG(FAT "\"%s\"" DEF " created in file " FAT "%s" DEF" in " FAT "%s" DEF " on line " FAT "%d" DEF ".\n\n",
              Stk->_nm,                              Stk->_brnfl,          Stk->_brnfnc,               Stk->_brnln);


    LOG("\tStack address: [%p]. Stack type: \"%s\".\n", Stk, Stk->_tp);

    LOG("\tCapacity = %zu. ", Stk->cpty);
    LOG("Size = %zu. ", Stk->sz);
    LOG("Buffer adress = [%p]. \n", Stk->bffr);

    if (Stk->bffr == NULL) {

        return STK_BUFFER_NULLPTR;
    }

    NLN;
    NLN;
    size_t i = 0;
    for (i = 0; i < Stk->sz; i++){

        LOG("\t*[%zu] = %d\n", i, Stk->bffr [i]); //TODO СДЕЛАТЬ МАКРОСС ДЛЯ ПРИЗВОЛЬНОГО ТИПА
    }

    for (; i < Stk->cpty; i++) {

        LOG("\t[%zu] = %d (PZN)\n", i, PZN);
    }
    NLN;
    SEP;

    return 0;
}

#undef LOG
#undef SEP
#undef NLN


//-------------------------------------------------------------------------------------
#define IS_FUNCTION_STKCDTOR !strcmp(FNCNMS[7], _prvfnc) || !strcmp(FNCNMS[8], _prvfnc)

int stkvrf(stack_t* Stk, str _prvfnc, str _fl, str _fnc, int _nln) {

    PREVFUNC_ACCESS_OK


    if (Stk == NULL) {

        return 2;
    }


    if (IS_FUNCTION_STKCDTOR) {

        return 0;
    }


    if (Stk->cpty > STK_MXBFFRSZ) {

        return 4; //WRONG CAPACITY //TODO сделать проверку на длину динамической памяти
    }

    if (Stk->sz > Stk->cpty) {

        return 5;
    }

    if (Stk->bffr == NULL) {

        return 3;
    }

    //TODO КАНАРЕЙКИ И ХЭШИ

    return 0;
}


#ifdef STK_SANITIZE
//-------------------------------------------------------------------------------------
#define PRINT_END_MESSAGE fprintf(logfl, RED FAT "\n================================================================================ YASHA PIDORAS ================================================================================\n" DEF);

#define ERRLOG(format, ...) fprintf(logfl, format, __VA_ARGS__);

//-------------------------------------------------------------------------------------
#define FRMT1 "=================================================="
#define FRMT2 "======================================================="
#define FRMT3 "======================================================="
#define FRMT4 "========================================================="
#define FRMT5 "==========================================================="
#define FRMT6 "========================================================"
#define FRMT7 "======================================================="
#define FRMT8 "==========================================================="
#define FRMT9 "====================================================="
#define FRMT10 "===================================================="
//-------------------------------------------------------------------------------------
#define ERRMSG1  ERRLOG("Function " FAT "%s" DEF" was called from function " FAT "%s" DEF ", that has no acces to сall.", _prvfnc, _fnc);
#define ERRMSG2  ERRLOG("For some reason, NULL was passed as a pointer to the structure.%s", "");
#define ERRMSG3  ERRLOG("For some reason, the pointer to the buffer turned out to be NULL.%s", "");
#define ERRMSG4  ERRLOG("For some reason, stack buffer capacity has wrong value: " FAT "%zu" DEF ". In particular, it's larger than maximum size of stack buffer: " FAT"%zu" DEF".", Stk->cpty, STK_MXBFFRSZ);
#define ERRMSG5  ERRLOG("For some reason, size of filled stack buffer has wrong value: " FAT "%zu" DEF ". In particular, it's larger than current stack buffer capacity: " FAT"%zu" DEF".", \
                                                                                        Stk->sz,                                                                             Stk->cpty);
#define ERRMSG6  ERRLOG("For some reason, memory allocation in function " FAT"%s" DEF" failed.", _prvfnc);
#define ERRMSG7  ERRLOG("Stack buffer underflow.%s", "");
#define ERRMSG8  ERRLOG("An attempt to create an array that is too large. Max stack buffer len: " FAT "%zu" DEF ". Given capacity: " FAT "%zu" DEF".", \
                                                                                    STK_MXBFFRSZ,                       Stk->cpty);
#define ERRMSG9  ERRLOG("Bad attempt to define STK_MXBFFRSZ. STK_MXBFFRSZ defined as " FAT "%zu" DEF ", which is too large.", \
                                                                            STK_MXBFFRSZ);
#define ERRMSG10 ERRLOG("For some reason, NULL was passed as a pointer to the poped value reciever.%s", "");
//-------------------------------------------------------------------------------------

#define PRINT_WHERE_FROM_CALLED ERRLOG(" Error handler was called from function " FAT"%s" DEF". Last stack call was in " FAT"%s" DEF":" FAT"%d" DEF" in function " FAT"%s" DEF".\n", _prvfnc, _fl, _nln, _fnc);

//-------------------------------------------------------------------------------------
#define PRINT_ERROR_MESSAGE(N, ERR)                                                                                 \
    ERRLOG(RED FAT FRMT##N " CRITICAL FATAL PANIC UNRECOVERABLE ERROR " #N ": " #ERR " %s" FRMT##N "\n\n" DEF, ""); \
    ERRMSG##N                                                                                                       \
    PRINT_WHERE_FROM_CALLED                                                                                         \
    PRINT_END_MESSAGE                                                                                               \


//-------------------------------------------------------------------------------------
#ifdef STK_HANDLER_ABORT

#ifdef STK_SANITIZE_LOUD
#define TOGGLE_ABORT abort();
#else
#define TOGGLE_ABORT fclose(logfl); abort();
#endif

#else
#define TOGGLE_ABORT (void) 0
#endif


void stkerrhnd(stack_t* Stk, _errt err, str _prvfnc, str _fl, str _fnc, int _nln) {

    PREVFUNC_ACCESS_OK

    switch (err)
    {
        case STK_OK: {

            break;
        }

        case STK_WRONG_PREVFUNC_ACCESS://WRONG FUNCTION CALLED VERIFICATOR
        {
            PRINT_ERROR_MESSAGE(1, STK_WRONG_PREVFUNC_ACCESS);
            TOGGLE_ABORT;
            break;
        }

        case STK_STRUCT_NULLPTR: //STRUCTURE HAS NULL POINTER
        {
            PRINT_ERROR_MESSAGE(2, STK_STRUCT_NULLPTR);
            TOGGLE_ABORT;
            break;
        }

        case STK_BUFFER_NULLPTR: //STACK BUFFER HAS NULL POINTER
        {
            PRINT_ERROR_MESSAGE(3, STK_BUFFER_NULLPTR);
            stkdmp(Stk, __PRETTY_FUNCTION__, _fl, _fnc, _nln);
            TOGGLE_ABORT;
            break;
        }

        case STK_WRONG_CPTY: //CAPACITY HAS WRONG VALUE
        {
            PRINT_ERROR_MESSAGE(4, STK_WRONG_CPTY);
            TOGGLE_ABORT;
            break;
        }

        case STK_WRONG_SZ: //SIZE HAS WRONG VALUE
        {
            PRINT_ERROR_MESSAGE(5, STK_WRONG_SZ);
            TOGGLE_ABORT;
            break;
        }

        case STK_MALLOC_FAILED: //6: FAILED MALLOCATION
        {
            PRINT_ERROR_MESSAGE(6, STK_MALLOC_FAILED);
            stkdmp(Stk, __PRETTY_FUNCTION__, _fl, _fnc, _nln);
            TOGGLE_ABORT;
            break;
        }

        case STK_BUFFER_UNDERFLOW: //STACKBUFFERUNDERFLOW
        {
            PRINT_ERROR_MESSAGE(7, STK_BUFFER_UNDERFLOW);
            stkdmp(Stk, __PRETTY_FUNCTION__, _fl, _fnc, _nln);
            TOGGLE_ABORT;
            break;
        }

        case STK_DEFINED_CPTY_EXCESS:
        {
            PRINT_ERROR_MESSAGE(8, STK_DEFINED_CPTY_EXCESS);
            TOGGLE_ABORT;
            break;
        }

        case STK_WRONG_MXBFFRSZ_DEFINED:
        {
            PRINT_ERROR_MESSAGE(9, STK_WRONG_MXBFFRSZ_DEFINED);
            TOGGLE_ABORT;
            break;
        }

        case STK_POP_RECIEVER_NULLPTR:
        {
            PRINT_ERROR_MESSAGE(10, STK_POP_RECIEVER_NULLPTR);
            stkdmp(Stk, __PRETTY_FUNCTION__, _fl, _fnc, _nln);
            TOGGLE_ABORT;
            break;
        }


        default: {}
    }

}

#undef PRINT_END_MESSAGE
#undef ERRLOG
#undef FRMT1
#undef FRMT2
#undef FRMT3
#undef FRMT4
#undef FRMT5
#undef FRMT6
#undef FRMT7
#undef FRMT8
#undef FRMT9
#undef FRMT10
#undef ERRMSG1
#undef ERRMSG2
#undef ERRMSG3
#undef ERRMSG4
#undef ERRMSG5
#undef ERRMSG6
#undef ERRMSG7
#undef ERRMSG8
#undef ERRMSG9
#undef ERRMSG10

#endif


//-------------------------------------------------------------------------------------
int stkpush(stack_t* Stk, int var, str _fl, str _fnc, int _nln){

    STACK_OK

    if (Stk->cpty == Stk->sz) {

        stkgrow(Stk, __PRETTY_FUNCTION__, _fl, _fnc, _nln);
    }

    *(Stk->bffr + Stk->sz) = var;
    Stk->sz ++;

   return 0;
}


//-------------------------------------------------------------------------------------
int stkpop(stack_t* Stk, int* var, str _fl, str _fnc, int _nln){

    STACK_OK

    if (var == NULL) {

        err = 10;
        ERROR_HANDLER_CALL
    }

    if (Stk->sz == 0) {

        err = 7;
        ERROR_HANDLER_CALL
    }

    Stk->sz --;
    *var = *(Stk->bffr + Stk->sz);

    if (2 * Stk->sz < Stk->cpty && Stk->cpty > 5){

        stkshrnk(Stk, __PRETTY_FUNCTION__, _fl, _fnc, _nln);
    }

    return 0;
}


//-------------------------------------------------------------------------------------
int stkgrow(stack_t* Stk, str _prvfnc, str _fl, str _fnc, int _nln) {

    PREVFUNC_ACCESS_OK

    STACK_OK

    stkelm_t* tmpbf = (stkelm_t*) realloc(Stk->bffr, 2 * (Stk->cpty) * sizeof((Stk->bffr)[0]));
    //tmpbf = NULL;
    if (tmpbf == NULL) {

        err = 6;
        ERROR_HANDLER_CALL
    }

    Stk->bffr = tmpbf;

    Stk->cpty *= 2;

    stkpzn(Stk, __PRETTY_FUNCTION__, _fl, _fnc, _nln);

    return 0;
}


//-------------------------------------------------------------------------------------
int stkshrnk(stack_t *Stk, str _prvfnc, str _fl, str _fnc, int _nln){

    PREVFUNC_ACCESS_OK

    STACK_OK

    stkelm_t* tmpbf = (stkelm_t*) realloc(Stk->bffr, (Stk->cpty / 2) * sizeof((Stk->bffr)[0]));

    //FOR ERR CHECK
    //tmpbf = NULL;
    if (tmpbf == NULL) {

        err = 6;
        ERROR_HANDLER_CALL
    }

    Stk->bffr = tmpbf;
    Stk->cpty /= 2;

    return 0;
}


//-------------------------------------------------------------------------------------

int stkctor(stack_t* Stk, str _nm, str _fl, str _fnc, int _nln, const size_t defcpty){


    STACK_OK

    #ifdef STK_SANITIZE
    Stk->_tp = "int";
    Stk->_nm = _nm;
    Stk->_brnfl = _fl;
    Stk->_brnfnc = _fnc;
    Stk->_brnln = _nln;


    #endif

    //printf("read: %zu, head: %zu", STK_MXBFFRSZ, STK_HEAD_MXBFFRSZ);
    if (STK_MXBFFRSZ > STK_HEAD_MXBFFRSZ) {

        err = 9;
        ERROR_HANDLER_CALL
    }

    Stk->cpty = defcpty;

    if (defcpty > STK_MXBFFRSZ) {

        err = 8;
        ERROR_HANDLER_CALL

    }

    Stk->bffr = (stkelm_t*) calloc(defcpty, sizeof(int));

    Stk->sz = 0;

    stkpzn(Stk, __PRETTY_FUNCTION__, _fl, _fnc, _nln);


    return 0;
}


//-------------------------------------------------------------------------------------
int stkdtor(stack_t* Stk, str _nm, str _fl, str _fnc, int _nln){

    STACK_OK

    free(Stk->bffr); //TODO IS_MALLOCED
    Stk->cpty =  -1u;
    Stk->sz = -1u;

    #ifdef STK_SANITIZE
    Stk->_brnfl = "DED_LOH";
    Stk->_brnfnc = "DED_LOH";
    Stk->_brnln = -1;

    #ifndef STK_SANITIZE_LOUD
    fclose(logfl);
    #endif

    #endif

    return 0;
}


//-------------------------------------------------------------------------------------
int stkpzn(stack_t* Stk, str _prvfnc, str _fl, str _fnc, int _nln){

    PREVFUNC_ACCESS_OK

    STACK_OK

    for (size_t i = Stk->sz; i < Stk->cpty; i++){

        Stk->bffr [i] = PZN;
    }

    return 0;
}


#endif
