#define STK_SANITIZE
#define STK_SANITIZE_LOUD
#define STK_HANDLER_ABORT
//#define STK_NOCHECK_STRUCT_HASH
//#define STK_CHECK_BUFFER_HASH
#include "stack.cpp"


//-------------------------------------------------------------------------------------
int main(){

    stack_t Stk1 = {};
    stack_t* Stk = &Stk1;



    $d(isgoodreadptr((void*) ((char*) NULL + 1), 4))


    STACK_CTOR(Stk1, 4);

    //Stk1.bffr = (stkelm_t*) ((char*) NULL + 1);

    //STACK_PUSH(Stk, 10);
    // STACK_PUSH(Stk, 20);
    // STACK_PUSH(Stk, 30);
    // STACK_PUSH(Stk, 40);
    // STACK_PUSH(Stk, 50);

    //Stk1.cpty = 4;
    //Stk1.sz = Stk1.cpty + 3;

    STACK_PUSH(Stk, 100);

    //Stk1.sz --;

    //stkctor(NULL, "Stk", __FILE__, __FUNCTION__, __LINE__, 5); //TODO СДЕЛАТЬ ПЕРЕДАЧУ ИМЕНИ МАКРОСОМ
    STACK_DUMP(&Stk1);


    //stkpzn(Stk, __PRETTY_FUNCTION__, __FILE__, __PRETTY_FUNCTION__, __LINE__);
    //stkshrnk(Stk, __PRETTY_FUNCTION__, __FILE__, __PRETTY_FUNCTION__, __LINE__);


    char cmd = 0;
    int n = 0; //TODO СДЕЛАТЬ NULL POINTER n
    //printf(__PRETTY_FUNCTION__);
    //stkerrhnd((_errt) stkvrf(&Stk, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);

    //Stk1.bffr = NULL;

    //Stk1.sz = STK_MXBUFSZ + 10;


    for (int i = 0; i < 50; i++){

        STACK_PUSH(Stk, 1);
        fprintf(stderr, "%2d: ", i);
        $zu(Stk1.cpty);
    }

    int var = 0;

    for (int i = 0; i < 50; i++){

        STACK_POP(Stk, &var);
        fprintf(stderr, "%2d: ", i);
        $zu(Stk1.cpty);
    }


    while (cmd != 'e') {

        scanf("%c%d", &cmd, &n);

        switch (cmd) {

            case 'r':
            {              //ПОМЕНЯТЬ НА NULL
                STACK_POP(Stk, &n);
                printf("Poped: %d\n", n);
                //stkdmp(&Stk, 0);
                break;
            }

            case 'w':
            {
                STACK_PUSH(Stk, n);
                //stkdmp(&Stk, 0);
                break;
            }

            case 'p':
            {
                STACK_DUMP(Stk);
                break;
            }

            default: {}
        }
    }


    STACK_DTOR(Stk1);
}
