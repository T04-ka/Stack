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

#define STK_HEAD_MXBUFSZ (SIZE_MAX / 8)

#ifndef STK_MXBUFSZ
#define STK_MXBUFSZ STK_HEAD_MXBUFSZ
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

str dmpsep = "\n-----------------------------------------------------------------------------------------\n";


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
    STK_WRONG_FUNC_CALLED_STKVRF = 1,
    STK_STRUCT_NULLPTR           = 2,
    STK_BUF_NULLPTR              = 3,
    STK_WRONG_CPTY               = 4,
    STK_WRONG_SZ                 = 5,
    STK_BUF_OVRFLW               = 6,
    STK_BUF_UNDRFLW              = 7,
    STK_DEF_CPTY_EXC             = 8,
    STK_WRONG_MX_BUF_SZ_DEF      = 9
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
    LOG("Dump was called by error handler from function " FAT "%s" FAT ".\n", _frmfnc);
    LOG(FAT "\"%s\"" DEF " created in file " FAT "%s" DEF" in " FAT "%s" DEF " on line " FAT "%d" DEF ".\n",
              Stk->_nm,                              Stk->_brnfl,          Stk->_brnfnc,               Stk->_brnln);


    LOG("Stack address: [%p]. Stack type: \"%s\".\n", Stk, Stk->_tp);

    if (Stk == NULL) {

        return;
    }

    LOG("Capacity = %zu. ", Stk->cpty);
    LOG("Size = %zu. ", Stk->sz);
    LOG("Buffer adress = [%p]. \n", Stk->bffr);

    if (Stk->bffr == NULL) {

        return;
    }

    NLN NLN
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

#define IS_FUNCTION_STKCDTOR !strcmp("int stkctor(stack_t*, str, str, str, int, size_t)", prvfnc) || !strcmp("int stkdtor(stack_t*, str, str, int)", prvfnc)

int stkvrf(stack_t* Stk, str prvfnc, size_t defcpty_ONLYFORSTKCTOR) {

    PRVFNC_OK

    if (!prvfnc_ok) {

        return 1; //DONE
    }

    if (Stk == NULL) {

        return 2; //DONE
    }


    if (IS_FUNCTION_STKCDTOR) {

        return 0;
    }


    if (Stk->cpty < 1) {

        return 4; //WRONG CAPACITY
    }

    if (Stk->sz > Stk->cpty) {

        return 5; //WRONG SIZE
    }

    if (Stk->bffr == NULL) {

        return 3; //BUFFER NULL POINTER
    }

    //TODO КАНАРЕЙКИ И ХЭШИ

    return 0;
}

#undef PRVFNC_OK
/*
enum _errt
{
    OK            = 0,
    STK_WRONG_FUNC_CALLED_STKVRF = 1,
    STK_STRUCT_NULLPTR = 2,
    STK_BUF_NULLPTR = 3,
    WRONGCPTY     = 4,
    WRONGSZ       = 5,
    STK_BUF_UNDRFLW  = 6,
    STK_BUF_UNDRFLW = 7,
    STK_DEF_CPTY_EXC    = 8
};
*/

//-------------------------------------------------------------------------------------
#define END fprintf(stderr, RED FAT "\n================================================================================ YASHA PIDORAS ================================================================================\n" DEF);
#define ERRLOG(format, ...) fprintf(stderr, format, __VA_ARGS__);

#define FRMT1 "=========================================================="
#define FRMT2 "======================================================="
#define FRMT3 "========================================================="
#define FRMT4 "==========================================================="
#define FRMT5 "=========================================================="
#define FRMT6 "==========================================================="
#define FRMT7 "========================================================="
#define FRMT8 "==========================================================="
#define FRMT9 "====================================================="

#define PRNTERRMSG(N, ERR) ERRLOG(RED FAT FRMT##N " CRITICAL FATAL PANIC UNRECOVERABLE ERROR " #N ": " #ERR " %s" FRMT##N "\n\n" DEF, "");

#define PRINT_WHERE_FROM_CALLED ERRLOG(" Last stack call was in " FAT"%s" DEF":" FAT"%d" DEF" in function " FAT"%s" DEF".\n", _fl, _nln, _fnc);

void stkerrhnd(stack_t* Stk, _errt err, str _prvfnc, str _fl, str _fnc, int _nln) {

    switch (err)
    {
        case STK_WRONG_FUNC_CALLED_STKVRF: //WRONG FUNCTION CALLED VERIFICATOR
        {
            PRNTERRMSG(1, STK_WRONG_FUNC_CALLED_STKVRF);
            ERRLOG("Verifier was called from function \"%s\", that has no acces to сall.", _prvfnc);
            PRINT_WHERE_FROM_CALLED

            //stkdtor(Stk, "", "", 0); //СДЕЛАТЬ ПО МАКРОССУ STDERR (CМ DTOR)
            END
            abort();
            break;
        }

        case STK_STRUCT_NULLPTR: //STRUCTURE HAS NULL POINTER
        {
            PRNTERRMSG(2, STK_STRUCT_NULLPTR);
            ERRLOG("NULL was passed as a pointer to the structure.%s", "");
            PRINT_WHERE_FROM_CALLED

            //stkdmp(Stk, _prvfnc, _fl, _fnc, _nln);
            //putc('\n', stderr);

            //stkdtor(Stk, "", "", 0);
            END

            abort();
            break;
        }

        case 3: //STACK BUFFER HAS NULL POINTER
        {
            PRNTERRMSG(3, STK_BUF_NULLPTR);
            ERRLOG("The pointer to the buffer turned out to be NULL.%s", "");
            PRINT_WHERE_FROM_CALLED
            stkdmp(Stk, _prvfnc, _fl, _fnc, _nln);

            //stkdtor(Stk, "", "", 0);

            END

            abort();
            break;
        }

        case 4: //CAPACITY HAS WRONG VALUE
        {

        }

        case 5: //SIZE HAS WRONG VALUE
        {

        }

        case 6: //STACKBUFFEROVERFLOW
        {

        }

        case STK_BUF_UNDRFLW: //STACKBUFFERUNDERFLOW
        {
            PRNTERRMSG(7, STK_BUF_UNDRFLW);
            ERRLOG("Stack buffer underflow.%s", "");
            PRINT_WHERE_FROM_CALLED
            //putc('\n', stderr);
            stkdmp(Stk, _prvfnc, _fl, _fnc, _nln);

            END

            stkdtor(Stk, "", "", 0);

            abort();
            break;
        }

        case STK_DEF_CPTY_EXC:
        {
            PRNTERRMSG(8, STK_DEF_CPTY_EXC);
            ERRLOG("An attempt to create an array that is too large. Max stack buffer len: " FAT "%zu" DEF ". Given capacity: " FAT "%zu" DEF".",
                                                                                        (size_t) STK_MXBUFSZ,                       Stk->cpty);
            PRINT_WHERE_FROM_CALLED

            END

            abort();
            break;
        }

        case STK_WRONG_MX_BUF_SZ_DEF:
        {
            PRNTERRMSG(9, STK_WRONG_MX_BUF_SZ_DEF);
            ERRLOG("Bad attempt to define STK_MXBUFSZ. STK_MXBUFSZ defined as " FAT "%zu" DEF ", which is too large.",
                                                                                 (size_t) STK_MXBUFSZ);

            END

            abort();
            break;
        }

        default: {}
    }

}

#undef END
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

        stkerrhnd(Stk, STK_BUF_UNDRFLW, __PRETTY_FUNCTION__, _fl, _fnc, _nln);
        return 7;
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

    stkelm_t* tmpbf = (stkelm_t*) realloc(Stk->bffr, 2 * (Stk->cpty) * sizeof((Stk->bffr)[0]));

    Stk->bffr = tmpbf;

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
#define ERROR_HANDLER_CALL stkerrhnd(Stk, (_errt) err, __PRETTY_FUNCTION__, _fl, _fnc, _nln); \
                   return err;

int stkctor(stack_t* Stk, str _nm, str _fl, str _fnc, int _nln, const size_t defcpty){


    STACK_OK
    //printf("read: %zu, head: %zu", STK_MXBUFSZ, STK_HEAD_MXBUFSZ);
    if (STK_MXBUFSZ > STK_HEAD_MXBUFSZ) {

        err = 9;
        ERROR_HANDLER_CALL
    }

    Stk->cpty = defcpty;

    if (defcpty > STK_MXBUFSZ) {

        err = 8;
        ERROR_HANDLER_CALL

    }

    Stk->bffr = (stkelm_t*) calloc(defcpty, sizeof(int));

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

#undef ERRHNDLRCL

//-------------------------------------------------------------------------------------
int stkdtor(stack_t* Stk, str _fl, str _fnc, int _nln){

    STACK_OK

    free(Stk->bffr); //TODO IS_MALLOCED
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
