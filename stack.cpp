

//-------------------------------------------------------------------------------------
int stkpush(stack_t* Stk, int var){

    if (Stk -> cpty == Stk -> ind) {

        stkgrow(Stk);
    }

    Stk -> ind ++;
    *(Stk -> bffr + Stk -> ind) = var;

   return 0;
}


//-------------------------------------------------------------------------------------
int stkpop(stack_t* Stk, int* var){

    if (Stk -> ind == 0) {

        return 1; //DO STCKUNDERFLOW
    }

    *var = *(Stk -> bffr + Stk -> ind);
    Stk -> ind --;

    return 0;
}
