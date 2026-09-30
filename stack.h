//-------------------------------------------------------------------------------------
void stkdmp(stack_t* Stk, int err, str _fnc, str _fl, str _frmfnc, int _nln, str stknm);

//-------------------------------------------------------------------------------------
int stkvrf(stack_t* Stk, str prvfnc);

//-------------------------------------------------------------------------------------
void stkerrhnd(_errt err, str prvfnc);

//-------------------------------------------------------------------------------------
int stkpush(stack_t* Stk, int var, str _fl, str _fromfnc, int _nln);

//-------------------------------------------------------------------------------------
int stkpop(stack_t* Stk, int* var, str _fl, str _fromfnc, int _nln);

//-------------------------------------------------------------------------------------
int stkgrow(stack_t* Stk, str _fl, str _fromfnc, int _nln) ;

//-------------------------------------------------------------------------------------
int stkshrnk(stack_t *Stk, str _fl, str _fromfnc, int _nln);

//-------------------------------------------------------------------------------------
int stkctor(stack_t* Stk, str _nm, str _fl, str _fromfnc, int _nln, const size_t defcpty = 4);

//-------------------------------------------------------------------------------------
int stkdtor(stack_t* Stk, str _fl, str _fromfnc, int _nln);

//-------------------------------------------------------------------------------------
int stkpzn(stack_t* Stk, str _fl, str _fromfnc, int _nln);
