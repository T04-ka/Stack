#define STK_SANITIZE
//#define STK_SANITIZE_LOUD
//#define STK_HANDLER_ABORT
#include "stack.cpp"


//size_t BIGNUM = (size_t) (1u << 64) - 1u;
//-------------------------------------------------------------------------------------
int main(){

    stack_t Stk1 = {};
    stack_t* Stk = NULL;

    STACK_CTOR(Stk1, 5);

    //stkctor(NULL, "Stk", __FILE__, __FUNCTION__, __LINE__, 5); //TODO СДЕЛАТЬ ПЕРЕДАЧУ ИМЕНИ МАКРОСОМ

    STACK_DUMP(Stk); //ВЫЗОВИ ДАМП ДО CTORA И ЧЕКНИ ЧТО БУДЕТ

    //stkpzn(Stk, __PRETTY_FUNCTION__, __FILE__, __PRETTY_FUNCTION__, __LINE__);
    //stkshrnk(Stk, __PRETTY_FUNCTION__, __FILE__, __PRETTY_FUNCTION__, __LINE__);


    char cmd = 0;
    int n = 0; //TODO СДЕЛАТЬ NULL POINTER n
    //printf(__PRETTY_FUNCTION__);
    //stkerrhnd((_errt) stkvrf(&Stk, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);

    //Stk1.bffr = NULL;

    //Stk1.sz = STK_MXBUFSZ + 10;

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
