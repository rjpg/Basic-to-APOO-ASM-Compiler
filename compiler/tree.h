
typedef struct T_stm_ *T_stm;
typedef struct T_exp_ *T_exp;
typedef struct T_exp_list_ *T_exp_list;
typedef struct T_stmList_ *T_stm_list;

//typedef enum {T_plus, T_minus, T_mul, T_div,T_and, T_or, T_lshift, T_rshift, T_arshift, T_xor} T_binOp ;
//typedef enum  {T_eq, T_ne, T_lt, T_gt, T_le, T_ge,T_ult, T_ule, T_ugt, T_uge} T_relOp;


extern T_exp T_const(int);
extern T_exp_list T_ExpList(T_exp,T_exp_list);
extern T_exp T_simple_var(char *);
extern T_exp T_mem(T_exp);
extern T_exp T_Binop(char *,T_exp,T_exp);
extern T_exp T_Name(int *);
extern T_exp_list T_ExpList(T_exp,T_exp_list);
extern T_stm_list T_StmList(T_stm, T_stm_list);
extern T_stm T_Seq(T_stm, T_stm);
extern T_stm T_Label(int);
extern T_stm T_Jump(/*T_exp,*/int);
extern T_stm T_Cjump(char *, T_exp,T_exp,int, int);
extern T_stm T_Move(T_exp, T_exp);
extern T_stm T_expr(T_exp);
extern int newLabel(void);


struct T_stmList_ {
  T_stm head; 
  T_stm_list tail;
};




typedef struct call_{
  T_exp exp;
  T_exp_list args;
}*call;

//exp_list

struct T_exp_list_{
  T_exp first;
  T_exp_list exp;
};

  
struct T_stm_ {
  enum {T_SEQ,T_LABEL,T_JUMP, T_CJUMP, T_MOVE,T_Exp_MEM} kind;
  union {
    struct {T_stm left, right;} SEQ;
    int LABEL;
    struct{
      //      T_exp exp;
      int label;
    }JUMP; 
    struct{
      char *op;
      T_exp left,right;
      int true; //patchList
      int false; //patchList
    }CJUMP;
    struct {
      T_exp origem,destino;
    }MOVE;
    T_exp exp;
  } u;
};

struct T_exp_ {
  enum {T_BINOP, T_Exp, T_Temp,T_ESEQ, T_NAME,T_CONST, T_CALL} kind;
  union {
    struct{
      char *op;
      T_exp left,right;
    } BINOP; 
    T_exp exp;
    int *temp; 
    char *name;
    struct {T_stm stm; T_exp exp;} ESEQ;
    int constant;
    call c; 
    
  } u;
};
