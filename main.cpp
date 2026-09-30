#include "stack.cpp"


//TODO сделать __VA_ARGS__
//-------------------------------------------------------------------------------------
int main(){

    stack_t Stk = {};

    stkctor(&Stk, __FILE__, __FUNCTION__, __LINE__);

    char cmd = 0;
    int n = 0;

    while (cmd != 'e') {

        scanf("%c%d", &cmd, &n);

        switch (cmd) {

            case 'r':
            {
                stkpop(&Stk, &n, __FILE__, __FUNCTION__, __LINE__);
                printf("Poped: %d\n", n);
                //stkdmp(&Stk, 0);
                break;
            }

            case 'w':
            {
                stkpush(&Stk, n, __FILE__, __FUNCTION__, __LINE__);
                //stkdmp(&Stk, 0);
                break;
            }
        }
    }


    stkdtor(&Stk, __FILE__, __FUNCTION__, __LINE__);
}
