#include "tree.h"
#include "mem.h"

//D%d = D-(D/d)*d
int l= 0;

int newLabel(void)
{
  l = l+1;
  return l;
}

T_exp_list T_ExpList(T_exp head, T_exp_list tail)
{
  T_exp_list p = (T_exp_list) safemalloc (sizeof *p);
  p->first=head; p->exp=tail;
  return p;
}

//constructor para statments
T_stm_list T_StmList(T_stm head, T_stm_list tail)
{
  T_stm_list p = (T_stm_list) safemalloc (sizeof *p);
  p->head=head; p->tail=tail;
  return p;
}

T_stm T_Seq(T_stm left, T_stm right)
{
  T_stm p = (T_stm) safemalloc(sizeof *p);
  p->kind=T_SEQ;
  p->u.SEQ.left=left;
  p->u.SEQ.right=right;
  return p;
}



T_stm T_Label(int label)
{T_stm p = (T_stm) safemalloc(sizeof *p);
 p->kind=T_LABEL;
 p->u.LABEL=label;
 return p;
}


T_stm T_Jump(/*T_exp exp,*/int labels)
{T_stm p = (T_stm) safemalloc(sizeof *p);
 p->kind=T_JUMP;
 // p->u.JUMP.exp=exp;
 p->u.JUMP.label=labels;
 return p;
}

T_stm T_Cjump(char *op, T_exp left, T_exp right,int true, int false)
{
  T_stm p = (T_stm) safemalloc(sizeof *p);
  p->kind=T_CJUMP;
  p->u.CJUMP.op=op;
  p->u.CJUMP.left=left;
  p->u.CJUMP.right=right;
  p->u.CJUMP.true=true;
  p->u.CJUMP.false=false;
  return p;
}

T_stm T_Move(T_exp dst, T_exp src)
{
  T_stm p = (T_stm) safemalloc(sizeof *p);
  p->kind=T_MOVE;
  p->u.MOVE.destino=dst;
  p->u.MOVE.origem=src;
  return p;
}

T_stm T_expr(T_exp exp)
{
  T_stm p = (T_stm) safemalloc(sizeof *p);
  p->kind=T_Exp_MEM;
  p->u.exp=exp;
  return p;
}

//constructor para expressoes
T_exp T_const(int constant) //F
{
  T_exp p = (T_exp) safemalloc(sizeof *p);
  p->kind=T_CONST;
  p->u.constant=constant;
  return p;
}

T_exp_list T_Exp_list(T_exp head, T_exp_list tail)
{
  T_exp_list p = (T_exp_list) safemalloc (sizeof *p);
  p->first=head; p->exp=tail;
  return p;
}

T_exp T_mem(T_exp exp){

  T_exp p = (T_exp) safemalloc(sizeof *p);
  p->kind=T_Exp;
  p->u.exp=exp;
  return p;
}

T_exp T_Binop(char *op, T_exp left, T_exp right)
{
  T_exp p = (T_exp) safemalloc(sizeof *p);
  p->kind=T_BINOP;
  p->u.BINOP.op=op;
  p->u.BINOP.left=left;
  p->u.BINOP.right=right;
  return p;
}

T_exp T_Name(int *label_n)
{
  T_exp p = (T_exp)safemalloc(sizeof *p);
  p->kind=T_NAME;
  p->u.temp=label_n;
  return p;
}
