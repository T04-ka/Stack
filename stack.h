//-------------------------------------------------------------------------------------
void stkdmp(stack_t* Stk, str _frmfnc, str _fl, str _fnc, int _nln);

//-------------------------------------------------------------------------------------
int stkvrf(stack_t* Stk, str _prvfnc, str _fl, str _fnc, int _nln);

//-------------------------------------------------------------------------------------
void stkerrhnd(stack_t* Stk, _errt err, str _prvfnc, str _fl, str _fnc, int _nln);

//-------------------------------------------------------------------------------------
int stkpush(stack_t* Stk, int var, str _fl, str _frmfnc, int _nln);

//-------------------------------------------------------------------------------------
int stkpop(stack_t* Stk, int* var, str _fl, str _frmfnc, int _nln);

//-------------------------------------------------------------------------------------
int stkgrow(stack_t* Stk, str _prvfnc, str _fl, str _frmfnc, int _nln) ;

//-------------------------------------------------------------------------------------
int stkshrnk(stack_t *Stk, str _prvfnc, str _fl, str _frmfnc, int _nln);

//-------------------------------------------------------------------------------------
int stkctor(stack_t* Stk, str _nm, str _fl, str _frmfnc, int _nln, const size_t defcpty = 4);

//-------------------------------------------------------------------------------------
int stkdtor(stack_t* Stk, str _fl, str _frmfnc, int _nln);

//-------------------------------------------------------------------------------------
int stkpzn(stack_t* Stk, str _prvfnc, str _fl, str _frmfnc, int _nln);
