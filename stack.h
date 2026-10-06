//-------------------------------------------------------------------------------------
int stkdmp(stack_t* Stk, str_t _frmfnc, str_t _fl, str_t _fnc, int _nln);

//-------------------------------------------------------------------------------------
int stkvrf(stack_t* Stk, str_t _prvfnc, str_t _fl, str_t _fnc, int _nln);

//-------------------------------------------------------------------------------------
void stkerrhnd(stack_t* Stk, _errt err, str_t _prvfnc, str_t _fl, str_t _fnc, int _nln);

//-------------------------------------------------------------------------------------
int stkpush(stack_t* Stk, int var, str_t _fl, str_t _frmfnc, int _nln);

//-------------------------------------------------------------------------------------
int stkpop(stack_t* Stk, int* var, str_t _fl, str_t _frmfnc, int _nln);

//-------------------------------------------------------------------------------------
int stkgrow(stack_t* Stk, str_t _prvfnc, str_t _fl, str_t _frmfnc, int _nln) ;

//-------------------------------------------------------------------------------------
int stkshrnk(stack_t *Stk, str_t _prvfnc, str_t _fl, str_t _frmfnc, int _nln);

//-------------------------------------------------------------------------------------
int stkctor(stack_t* Stk, str_t _nm, str_t _fl, str_t _frmfnc, int _nln, const size_t defcpty = 4);

//-------------------------------------------------------------------------------------
int stkdtor(stack_t* Stk, str_t _nm, str_t _fl, str_t _frmfnc, int _nln);

//-------------------------------------------------------------------------------------
int stkpzn(stack_t* Stk, str_t _prvfnc, str_t _fl, str_t _frmfnc, int _nln);

//-------------------------------------------------------------------------------------
int stkhsh(void* ptr, size_t sz);

//-------------------------------------------------------------------------------------
bool isgoodreadptr(const void* memptr, size_t sz);
