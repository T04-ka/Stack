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

#define HEAD_MXBUFLEN (2<<64 / 8)

#ifndef MXBUFLEN
#define MXBUFLEN HEAD_MXBUFLEN
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
    OK            = 0,
    WRONGFUNCCALL = 1,
    STRUCTNULLPTR = 2,
    STKBUFNULLPTR = 3,
    WRONGCPTY     = 4,
    WRONGSZ       = 5,
    STKBUFOVRFLW  = 6,
    STKBUFUNDRFLW = 7,
    DEFCPTYEXC    = 8,
    WRNGMXBFSZDEF = 9
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
    LOG("Dump was called by error handler from function " RED "%s" DEF ".\n", _frmfnc);
    LOG(RED "\"%s\"" DEF " created in file " RED "%s" DEF " in " RED "%s" DEF " on line " RED "%d" DEF ".\n",
              Stk->_nm,                              Stk->_brnfl,          Stk->_brnfnc,               Stk->_brnln);


    LOG("Stack address: [%p]. Stack type: \"%s\".\n", Stk, Stk->_tp);

    if (Stk == NULL) {

        return;
    }

    LOG("Capacity = %zu. ", Stk->cpty);
    LOG("Size = %zu. ", Stk->sz);
    LOG("Buffer adress = [%p]. \n", Stk->bffr);
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

#define ISF_STKVRF !strcmp("int stkctor(stack_t*, str, str, str, int, size_t)", prvfnc)

//-------------------------------------------------------------------------------------
int stkvrf(stack_t* Stk, str prvfnc, size_t defcpty_ONLYFORSTKCTOR) {

    PRVFNC_OK

    if (!prvfnc_ok) {

        return 1; //DONE
    }

    if (Stk == NULL) {

        return 2; //DONE
    }


    if (ISF_STKVRF) {

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
    WRONGFUNCCALL = 1,
    STRUCTNULLPTR = 2,
    STKBUFNULLPTR = 3,
    WRONGCPTY     = 4,
    WRONGSZ       = 5,
    STKBUFOVRFLW  = 6,
    STKBUFUNDRFLW = 7,
    DEFCPTYEXC    = 8
};
*/


#define END fprintf(stderr, RED FAT "================================================================================ YASHA PIDORAS ================================================================================\n" DEF);
#define ERRLOG(format, ...) fprintf(stderr, format, __VA_ARGS__);

#define FRMT1 "=========================================================="
#define FRMT2 "=========================================================="
#define FRMT3 "==========================================================="
#define FRMT4 "==========================================================="
#define FRMT5 "=========================================================="
#define FRMT6 "==========================================================="
#define FRMT7 "==========================================================="
#define FRMT8 "==========================================================="
#define FRMT9 "==========================================================="

#define ERRMSG(N) PRNTERRMSG(N, (_errt) N)
#define PRNTERRMSG(N, ERR) ERRLOG(RED FAT FRMT##N " CRITICAL FATAL PANIC UNRECOVERABLE ERROR " #N ":" #ERR " %s" FRMT##N "\n" DEF, "");

void stkerrhnd(stack_t* Stk, _errt err, str _prvfnc, str _fl, str _fnc, int _nln) {

    switch (err)
    {
        case WRONGFUNCCALL: //WRONG FUNCTION CALLED VERIFICATOR
        {
            ERRMSG(1);
            ERRLOG("Verifier was called from function \"%s\", that has no acces to сall. Last stack call was in %s:%d in function %s.\n",
                                                        _prvfnc,                                                _fl, _nln,          _fnc);
            //stkdtor(Stk, "", "", 0); //СДЕЛАТЬ ПО МАКРОССУ STDERR (CМ DTOR)
            END
            abort();
            break;
        }

        case STRUCTNULLPTR: //STRUCTURE HAS NULL POINTER
        {
            ERRMSG(2);
            ERRLOG("NULL was passed as a pointer to the structure. Last stack call was in %s:%d in function %s.\n",
                                                                                        _fl, _nln,          _fnc);
            //stkdmp(Stk, _prvfnc, _fl, _fnc, _nln);
            //putc('\n', stderr);

            //stkdtor(Stk, "", "", 0);
            END

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

        case 6: //STACKBUFFEROVERFLOW
        {

        }

        case STKBUFUNDRFLW: //STACKBUFFERUNDERFLOW
        {
            ERRMSG(7);
            ERRLOG("Stack buffer underflow. Last stack call was in %s:%d in function %s.\n" DEF,
                                                                   _fl, _nln,        _fnc);
            //putc('\n', stderr);
            stkdmp(Stk, _prvfnc, _fl, _fnc, _nln);

            END

            stkdtor(Stk, "", "", 0);

            abort();
            break;
        }

        case DEFCPTYEXC:
        {
            ERRLOG(RED FAT FRMT8 " CRITICAL FATAL PANIC UNRECOVERABLE ERROR 8: DEFCPTYEXC %s" FRMT8 "\n" DEF, "");
            ERRLOG("An attempt to create an array that is too large. Max stack buffer len: " FAT RED "%zu" DEF ". Given capacity: " FAT RED "%zu" DEF". Last stack call was in %s:%d in function %s.\n" DEF,
                                                                                        (size_t) MXBUFLEN,             Stk->cpty,                 _fl, _nln,        _fnc);

            END

            abort();
            break;
        }

        case WRNGMXBFSZDEF:
        {
            ERRMSG(9);
            ERRLOG("An attempt to create an array that is too large. Max stack buffer len: " FAT RED "%zu" DEF ". Given capacity: " FAT RED "%zu" DEF". Last stack call was in %s:%d in function %s.\n" DEF,
                                                                                        (size_t) MXBUFLEN,             Stk->cpty,                 _fl, _nln,        _fnc);

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

        stkerrhnd(Stk, STKBUFUNDRFLW, __PRETTY_FUNCTION__, _fl, _fnc, _nln);
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
#define ERRHNDLRCL stkerrhnd(Stk, (_errt) err, __PRETTY_FUNCTION__, _fl, _fnc, _nln); \
                   return err;

int stkctor(stack_t* Stk, str _nm, str _fl, str _fnc, int _nln, const size_t defcpty){


    STACK_OK

    if (MXBUFLEN > HEAD_MXBUFLEN) {

        err = 9;
        ERRHNDLRCL
    }

    Stk->cpty = defcpty;

    if (defcpty > MXBUFLEN) {

        err = 8;
        ERRHNDLRCL

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
