#define MXBUFLEN 2

#include "stack.cpp"


//size_t BIGNUM = (size_t) (1u << 64) - 1u;
//-------------------------------------------------------------------------------------
int main(){

    stack_t Stk1 = {};
    stack_t* Stk = &Stk1;
    stkctor(Stk, "Stk", __FILE__, __FUNCTION__, __LINE__); //TODO СДЕЛАТЬ ПЕРЕДАЧУ ИМЕНИ МАКРОСОМ

    //ERR 1 TEST
    // str _fl = __FILE__, _fnc = __FUNCTION__;
    // int _nln = __LINE__;
    // STACK_OK

    char cmd = 0;
    int n = 0; //TODO СДЕЛАТЬ NULL POINTER n
    //printf(__PRETTY_FUNCTION__);
    //stkerrhnd((_errt) stkvrf(&Stk, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);


    while (cmd != 'e') {

        scanf("%c%d", &cmd, &n);

        switch (cmd) {

            case 'r':
            {
                stkpop(Stk, &n, __FILE__, __FUNCTION__, __LINE__);
                printf("Poped: %d\n", n);
                //stkdmp(&Stk, 0);
                break;
            }

            case 'w':
            {
                stkpush(Stk, n, __FILE__, __FUNCTION__, __LINE__);
                //stkdmp(&Stk, 0);
                break;
            }
        }
    }


    stkdtor(Stk, __FILE__, __FUNCTION__, __LINE__);
}
