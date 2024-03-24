#include "estr.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mem.h"
//#include "symbol.c"

var_id *MK_var_id(char *id)
{
  var_id *p=(var_id *)safemalloc(sizeof(var_id));
  p->id=(char *)safemalloc(strlen(id));
  strcpy(p->id,id);
  //printf("MK_var_id (%s)\n",p->id);
  return p;
}  

const_id *MK_const_id(char *id)
{
  const_id *p=(const_id *)safemalloc(sizeof(const_id));
  p->id=(char *)safemalloc(strlen(id));
  strcpy(p->id,id);
  //printf("MK_const_id (%s)\n",p->id);
  return p;
}

var_o_const_id *MK_var_o_const_id(char *id)
{
  var_o_const_id *p=(var_o_const_id *)safemalloc(sizeof(var_o_const_id));
  p->id=(char *)safemalloc(strlen(id));
  strcpy(p->id,id);
  //printf("MK_var_o_const_id (%s)\n",p->id);
  return p;
}

rel_op *MK_rel_op(char *op)
{
  rel_op *p=(rel_op *)safemalloc(sizeof(rel_op));
  p->op=(char *)safemalloc(strlen(op));
  strcpy(p->op,op);
  //printf("MK_rel_id (%s)\n",p->op);
  return p;
}

const_expr *MK_const_expr1(const_expr *const_expr_a)
{
  const_expr *p;
  p=(const_expr *) safemalloc (sizeof(const_expr));
  p->kind=C_E_MINUS_const_expr;
  p->u.const_expr=const_expr_a;
  //printf("MK_const_expr1 \n");
  return p;
}

const_expr *MK_const_expr2(const_expr *const_expr_1_a,const_expr *const_expr_2_a,int n)
{
  const_expr *p;
  p=(const_expr *) safemalloc (sizeof(const_expr));
  switch(n)
    {
    case 1:
      p->kind=C_E_const_expr_MUL_const_expr;
      break;
    case 2:
      p->kind=C_E_const_expr_DIV_const_expr;
      break;
    case 3:
      p->kind=C_E_const_expr_MOD_const_expr;
      break;  
    case 4:
      p->kind=C_E_const_expr_MINUS_const_expr;
      break;
    case 5:
      p->kind=C_E_const_expr_PLUS_const_expr;
      break;
    }
  p->u.const_expr_arit_op_const_expr.const_expr_1=const_expr_1_a;
  p->u.const_expr_arit_op_const_expr.const_expr_2=const_expr_2_a;
  //printf("MK_const_expr2 \n");
  return p;
}

const_expr *MK_const_expr3(const_expr *const_expr_a)
{
  const_expr *p;
  p=(const_expr *) safemalloc (sizeof(const_expr));
  p->kind=C_E_OPAR_const_expr_CPAR;
  p->u.const_expr=const_expr_a;
  //printf("MK_const_expr3 \n");
  return p;
}

const_expr *MK_const_expr4(int NUMBER)
{
  const_expr *p;
  p=(const_expr *) safemalloc (sizeof(const_expr));
  p->kind=C_E_NUMBER_LITERAL;
  sscanf((char*)NUMBER,"%d",&p->u.NUMBER_L); // passar para inteiro 
  // p->u.NUMBER_L=NUMBER;
  //printf("MK_const_expr4 \n");
  return p;
}

const_expr *MK_const_expr5(const_id *const_id_a)
{
  const_expr *p;
  p=(const_expr *) safemalloc (sizeof(const_expr));
  p->kind=C_E_NUMBER_LITERAL;
  p->u.const_id=const_id_a;
  //printf("MK_const_expr5 \n");
  return p;
}

tCOMMA_e_expr_mais *MK_tCOMMA_e_expr_mais1(expr *expr_a)
{
  tCOMMA_e_expr_mais *p=(tCOMMA_e_expr_mais*)safemalloc (sizeof(tCOMMA_e_expr_mais));
  p->kind=T_E_E_M_COMMA_expr;
  p->u.expr=expr_a;
  //printf("MK_tCOMMA_e_expr_mais1 \n");
  return p;
}

tCOMMA_e_expr_mais *MK_tCOMMA_e_expr_mais2(expr *expr_a, tCOMMA_e_expr_mais *tCOMMA_e_expr_mais_a)
{
  tCOMMA_e_expr_mais *p=(tCOMMA_e_expr_mais*)safemalloc(sizeof(tCOMMA_e_expr_mais));
  p->kind=T_E_E_M_COMMA_expr_tCOMMA_e_expr_mais;
  p->u.COMMA_expr_tCOMMA_e_expr_mais.expr=expr_a;
  p->u.COMMA_expr_tCOMMA_e_expr_mais.tCOMMA_e_expr_mais=tCOMMA_e_expr_mais_a;
  //printf("MK_tCOMMA_e_expr_mais2 \n");
  return p;
}

arit_expr *MK_arit_expr1(arit_expr *arit_expr_a,int n)
{
  if (n==1)
    {
      arit_expr *p=(arit_expr *)safemalloc(sizeof(arit_expr));
      p->kind=A_E_MINUS_arit_expr;
      p->u.arit_expr=arit_expr_a;
      //printf("MK_arit_expr1 \n");
      return p;
    }
  else
    {
      arit_expr *p=(arit_expr *)safemalloc(sizeof(arit_expr));
      p->kind=A_E_OPAR_arit_expr_CPAR;
      p->u.arit_expr=arit_expr_a;
      //printf("MK_arit_expr1 \n");
      return p; 
    }
}

arit_expr *MK_arit_expr2(arit_expr *arit_expr_1_a,arit_expr *arit_expr_2_a,int n)
{
  arit_expr *p;
  p=(arit_expr *) safemalloc(sizeof(arit_expr));
  switch(n)
    {
    case 1:
      p->kind=A_E_arit_expr_MUL_arit_expr;
      break;
    case 2:
      p->kind=A_E_arit_expr_DIV_arit_expr;
      break;
    case 3:
      p->kind=A_E_arit_expr_MOD_arit_expr;
      break;  
    case 4:
      p->kind=A_E_arit_expr_MINUS_arit_expr;
      break;
    case 5:
      p->kind=A_E_arit_expr_PLUS_arit_expr;
      break;
    }
  p->u.arit_expr_arit_op_arit_expr.arit_expr_1=arit_expr_1_a;
  p->u.arit_expr_arit_op_arit_expr.arit_expr_2=arit_expr_2_a;
  //printf("MK_arit_expr2 \n");
  return p;
}

arit_expr *MK_arit_expr3(int NUMBER)
{
  arit_expr *p=(arit_expr *) safemalloc (sizeof(arit_expr));
  p->kind=A_E_NUMBER_LITERAL;
  sscanf((char*)NUMBER,"%d",&p->u.NUMBER_L);//por em modo int
  //p->u.NUMBER_L=NUMBER;
  //printf("MK_arit_expr3 (%s)\n",NUMBER); // tenho de comverter para int
  return p;
}

arit_expr *MK_arit_expr4(var_o_const_id *var_o_const_id_a)
{
  arit_expr *p=(arit_expr *) safemalloc (sizeof(arit_expr));
  p->kind=A_E_var_o_const_id;
  p->u.var_o_const_id=var_o_const_id_a;
  //printf("MK_arit_expr4 \n");
  return p;
}


arit_expr *MK_arit_expr5(use_array_var *use_array_var_a)
{
  arit_expr *p=(arit_expr *) safemalloc (sizeof(arit_expr));
  p->kind=A_E_use_array_var;
  p->u.use_array_var=use_array_var_a;
  //printf("MK_arit_expr5 \n");
  return p;
}

rel_expr *MK_rel_expr(arit_expr *arit_expr1_a,rel_op *rel_op_a,arit_expr *arit_expr2_a)
{
  rel_expr *p=(rel_expr *) safemalloc (sizeof(rel_expr));
  p->arit_expr1=arit_expr1_a;
  p->rel_op=rel_op_a;
  p->arit_expr2=arit_expr2_a;
  //printf("MK_rel_expr \n");
  return p;
}

bool_expr *MK_bool_expr1(bool_expr *bool_expr_a,int n)
{
  bool_expr *p=(bool_expr *)safemalloc (sizeof(bool_expr));
  switch(n)
    {
    case 1:
      p->kind=B_E_NOT_bool_expr;
      p->u.bool_expr=bool_expr_a;
      break;
    case 2:
      p->kind=B_E_OPAR_bool_expr_CPAR;
      p->u.bool_expr=bool_expr_a;
      break;
    }
  //printf("MK_bool_expr1 \n");
  return p;
}

bool_expr *MK_bool_expr2(bool_expr *bool_expr_1_a,bool_expr *bool_expr_2_a,int n)
{
  bool_expr *p=(bool_expr *)safemalloc (sizeof(bool_expr));
  switch(n)
    {
    case 1:
      p->kind=B_E_bool_expr_AND_bool_expr;
      p->u.bool_expr_bool_op_bool_expr.bool_expr_1=bool_expr_1_a;
      p->u.bool_expr_bool_op_bool_expr.bool_expr_2=bool_expr_2_a;
      break;
    case 2:
      p->kind=B_E_bool_expr_OR_bool_expr;
      p->u.bool_expr_bool_op_bool_expr.bool_expr_1=bool_expr_1_a;
      p->u.bool_expr_bool_op_bool_expr.bool_expr_2=bool_expr_2_a;
      break;
    }
  //printf("MK_bool_expr2 \n");
  return p;
}

bool_expr *MK_bool_expr3(rel_expr *rel_expr_a)
{
  bool_expr *p=(bool_expr *)safemalloc (sizeof(bool_expr));
  p->kind=B_E_OPAR_bool_expr_CPAR;
  p->u.rel_expr=rel_expr_a;
  //printf("MK_bool_expr3 \n");
  return p;
}

expr *MK_expr(arit_expr *arit_expr_a)
{
  expr *p=(expr*)safemalloc(sizeof(expr));
  p->arit_expr=arit_expr_a;
  //printf("MK_expr \n");
  return p;
}

tCOMMA_e_expr_ast *MK_tCOMMA_e_expr_ast(expr *expr_a,tCOMMA_e_expr_ast *tCOMMA_e_expr_ast_a)
{
  tCOMMA_e_expr_ast *p=(tCOMMA_e_expr_ast *)safemalloc(sizeof(tCOMMA_e_expr_ast));
  p->expr=expr_a;
  p->tCOMMA_e_expr_ast=tCOMMA_e_expr_ast_a;
  //printf("MK_tCOMMA_e_expr_ast \n");
  return p;
}

expr_list *MK_expr_list(expr *expr_a,tCOMMA_e_expr_ast *tCOMMA_e_expr_ast_a)
{
  expr_list *p=(expr_list *)safemalloc(sizeof(expr_list));
  p->expr=expr_a;
  p->tCOMMA_e_expr_ast=tCOMMA_e_expr_ast_a;
  //printf("MK_expr_list \n");
  return p;
}

expr_list_01 *MK_expr_list_01(expr_list *expr_list_a)
{
  expr_list_01 *p=(expr_list_01 *)safemalloc(sizeof(expr_list_01));
  p->expr_list=expr_list_a;
  //printf("MK_expr_list_01 \n");
  return p;
}

cond *MK_cond( bool_expr *bool_expr_a)
{
  cond *p=(cond*)safemalloc(sizeof(cond));
  p->bool_expr=bool_expr_a;
  //printf("MK_cond \n");
  return p;
}

print_expr *MK_print_expr1( expr *expr_a)
{
  print_expr *p=(print_expr *)safemalloc(sizeof(print_expr));
  p->kind=P_E_expr;
  p->u.expr=expr_a;
  //printf("MK_print_expr1 \n");
  return p;
}

print_expr *MK_print_expr2(char *STRING_L_a)
{
  print_expr *p=(print_expr *)safemalloc(sizeof(print_expr));
  p->kind=P_E_STRING_LITERAL;
  p->u.STRING_L=STRING_L_a;
  return p;
}

print_cmd *MK_print_cmd(print_expr_list *print_expr_list_a)
{
  print_cmd *p=(print_cmd *)safemalloc(sizeof(print_cmd));
  p->print_expr_list=print_expr_list_a;
  return p;
}

print_expr_list *MK_print_expr_list(print_expr *print_expr_a,tCOMMA_print_expr_ast *tCOMMA_print_expr_ast_a)
{
  print_expr_list *p=(print_expr_list *)safemalloc(sizeof(print_expr_list));
  p->print_expr=print_expr_a;
  p->tCOMMA_print_expr_ast=tCOMMA_print_expr_ast_a;
  return p;
}

tCOMMA_print_expr_ast *MK_tCOMMA_print_expr_ast( print_expr *print_expr_a, tCOMMA_print_expr_ast *tCOMMA_print_expr_ast_a)
{
  tCOMMA_print_expr_ast *p=( tCOMMA_print_expr_ast *)safemalloc(sizeof(tCOMMA_print_expr_ast));
  p->print_expr=print_expr_a;
  p->tCOMMA_print_expr_ast=tCOMMA_print_expr_ast_a;
  return p;
}

use_simple_var *MK_use_simple_var(var_id *var_id_a)
{
  use_simple_var *p=( use_simple_var *)safemalloc(sizeof(use_simple_var));
  p->var_id=var_id_a;
  return p;
}

use_array_var *MK_use_array_var(var_id *var_id_a,expr_list *expr_list_a)
{
  use_array_var *p=( use_array_var *)safemalloc(sizeof(use_array_var));
  p->var_id=var_id_a;
  p->expr_list=expr_list_a;
  return p;
}


use_var *MK_use_var1(use_simple_var *use_simple_var_a)
{
  use_var *p=(use_var*)safemalloc(sizeof(use_var));
  p->kind= U_V_use_simple_var;
  p->u.use_simple_var=use_simple_var_a;
  return p;
}

use_var *MK_use_var2(use_array_var *use_array_var_a)
{
  use_var *p=(use_var*)safemalloc(sizeof(use_var));
  p->kind=U_V_use_array_var;
  p->u.use_array_var=use_array_var_a;
  return p;
}

input_cmd *MK_input_cmd(use_var *use_var_a)
{
  input_cmd *p=(input_cmd *)safemalloc(sizeof(input_cmd));
  p->use_var=use_var_a;
  return p;
}
//---------------------------------------------ver isto
exit_loop_cmd *MK_exit_loop_cmd()
{
  char *a="exit loop\n";
  exit_loop_cmd *p=(exit_loop_cmd*)safemalloc(sizeof(exit_loop_cmd));
  p->EXITLOOP_NL=(char *)safemalloc(strlen(a));
  strcpy(p->EXITLOOP_NL,a);
  return p;
}

end_cmd *MK_end_cmd()
{
  char *a="end\n";
  end_cmd *p=(end_cmd*)safemalloc(sizeof(end_cmd));
  p->END_NL=(char *)safemalloc(strlen(a));
  strcpy(p->END_NL,a);
  return p;
}
//----------------------------------------------------------------

assignment_cmd *MK_assignment_cmd(use_var *use_var_a,expr *expr_a,int n)
{
  assignment_cmd *p=(assignment_cmd *)safemalloc(sizeof(assignment_cmd));
  switch(n)
    {
    case 1:
      p->kind=A_C_use_var_EQ_expr_NL;
      break;
    case 2:
      p->kind=A_C_LET_use_var_EQ_expr_NL;
      break;
    }  
  p->use_var=use_var_a;
  p->expr=expr_a;
  return p;
}

var_decl_o_const_decl_o_cmd_ast *MK_var_decl_o_const_decl_o_cmd_ast1(var_decl *var_decl_a,var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast_a)
{
  var_decl_o_const_decl_o_cmd_ast *p=(var_decl_o_const_decl_o_cmd_ast *)safemalloc(sizeof(var_decl_o_const_decl_o_cmd_ast));
  p->kind=V_D_O_var_decl_var_decl_o_const_decl_o_cmd_ast;
  p->u.var_decl_var_decl_o_const_decl_o_cmd_ast.var_decl=var_decl_a;
  p->u.var_decl_var_decl_o_const_decl_o_cmd_ast.var_decl_o_const_decl_o_cmd_ast=var_decl_o_const_decl_o_cmd_ast_a;
  return p;
}

var_decl_o_const_decl_o_cmd_ast *MK_var_decl_o_const_decl_o_cmd_ast2(const_decl *const_decl_a,var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast_a)
{
  var_decl_o_const_decl_o_cmd_ast *p=(var_decl_o_const_decl_o_cmd_ast *)safemalloc(sizeof(var_decl_o_const_decl_o_cmd_ast));
  p->kind=V_D_O_const_decl_var_decl_o_const_decl_o_cmd_ast;
  p->u.const_decl_var_decl_o_const_decl_o_cmd_ast.const_decl=const_decl_a;
  p->u.const_decl_var_decl_o_const_decl_o_cmd_ast.var_decl_o_const_decl_o_cmd_ast=var_decl_o_const_decl_o_cmd_ast_a;
  return p;
}

var_decl_o_const_decl_o_cmd_ast *MK_var_decl_o_const_decl_o_cmd_ast3(cmd *cmd_a,var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast_a)
{
  var_decl_o_const_decl_o_cmd_ast *p=(var_decl_o_const_decl_o_cmd_ast *)safemalloc(sizeof(var_decl_o_const_decl_o_cmd_ast));
  p->kind=V_D_O_cmd_var_decl_o_const_decl_o_cmd_ast;
  p->u.cmd_var_decl_o_const_decl_o_cmd_ast.cmd=cmd_a;
  p->u.cmd_var_decl_o_const_decl_o_cmd_ast.var_decl_o_const_decl_o_cmd_ast=var_decl_o_const_decl_o_cmd_ast_a;
  return p;
}

loop_until_cmd *MK_loop_until_cmd(var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast_a,cond *cond_a)
{
  loop_until_cmd *p=(loop_until_cmd *)safemalloc(sizeof(loop_until_cmd));
  p->var_decl_o_const_decl_o_cmd_ast=var_decl_o_const_decl_o_cmd_ast_a;
  p->cond=cond_a;
  return p;
}

do_while_cmd *MK_do_while_cmd(cond *cond_a,var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast_a)
{
  do_while_cmd *p=(do_while_cmd *)safemalloc(sizeof(do_while_cmd));
  p->var_decl_o_const_decl_o_cmd_ast=var_decl_o_const_decl_o_cmd_ast_a;
  p->cond=cond_a;
  return p;
}

tSTEP_e_expr_01 *MK_tSTEP_e_expr_01(expr *expr_a)
{
  tSTEP_e_expr_01 *p=(tSTEP_e_expr_01*)safemalloc(sizeof(tSTEP_e_expr_01));
  p->expr=expr_a;
  return p;
}

for_cmd *MK_for_cmd(use_simple_var *use_simple_var_a,expr *expr1_a,expr *expr2_a,tSTEP_e_expr_01 *tSTEP_e_expr_01_a,var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast_a)
{
  for_cmd *p=(for_cmd*)safemalloc(sizeof(for_cmd));
  p->use_simple_var=use_simple_var_a;
  p->expr1=expr1_a;
  p->expr2=expr2_a;
  p->tSTEP_e_expr_01=tSTEP_e_expr_01_a;
  p->var_decl_o_const_decl_o_cmd_ast=var_decl_o_const_decl_o_cmd_ast_a;
  return p;
}

else_nl_01 *MK_else_nl_01(var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast_a)
{
  else_nl_01 *p =(else_nl_01 *) safemalloc(sizeof(else_nl_01));
  p->var_decl_o_const_decl_o_cmd_ast=var_decl_o_const_decl_o_cmd_ast_a;
  return p;
}

if_cmd *MK_if_cmd(cond *cond_a,var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast_a,else_nl_01 *else_nl_01_a)
{
  if_cmd *p=(if_cmd *)safemalloc(sizeof(if_cmd));
  p->cond=cond_a;
  p->var_decl_o_const_decl_o_cmd_ast=var_decl_o_const_decl_o_cmd_ast_a;
  p->else_nl_01=else_nl_01_a;
  return p;
}

cmd *MK_cmd1(if_cmd *if_cmd_a)
{
  cmd *p=(cmd *)safemalloc(sizeof(cmd));
  p->kind=C_if_cmd;
  p->u.if_cmd=if_cmd_a;
  return p;
}

cmd *MK_cmd2(for_cmd *for_cmd_a)
{
  cmd *p=(cmd *)safemalloc(sizeof(cmd));
  p->kind=C_for_cmd;
  p->u.for_cmd=for_cmd_a;
  return p;
}

cmd *MK_cmd3(do_while_cmd *do_while_cmd_a)
{
  cmd *p=(cmd *)safemalloc(sizeof(cmd));
  p->kind=C_do_while_cmd;
  p->u.do_while_cmd=do_while_cmd_a;
  return p;
}

cmd *MK_cmd4(loop_until_cmd *loop_until_cmd_a)
{
  cmd *p=(cmd *)safemalloc(sizeof(cmd));
  p->kind=C_loop_until_cmd;
  p->u.loop_until_cmd=loop_until_cmd_a;
  return p;
}

cmd *MK_cmd5(assignment_cmd *assignment_cmd_a)
{
  cmd *p=(cmd *)safemalloc(sizeof(cmd));
  p->kind=C_assignment_cmd;
  p->u.assignment_cmd=assignment_cmd_a;
  return p;
}

cmd *MK_cmd6(end_cmd *end_cmd_a)
{
  cmd *p=(cmd *)safemalloc(sizeof(cmd));
  p->kind=C_end_cmd;
  p->u.end_cmd=end_cmd_a;
  return p;
}

cmd *MK_cmd7(exit_loop_cmd *exit_loop_cmd_a)
{
  cmd *p=(cmd *)safemalloc(sizeof(cmd));
  p->kind=C_exit_loop_cmd;
  p->u.exit_loop_cmd=exit_loop_cmd_a;
  return p;
}

cmd *MK_cmd8(input_cmd *input_cmd_a)
{
  cmd *p=(cmd *)safemalloc(sizeof(cmd));
  p->kind=C_input_cmd;
  p->u.input_cmd=input_cmd_a;
  return p;
}

cmd *MK_cmd9(print_cmd *print_cmd_a)
{
  cmd *p=(cmd *)safemalloc(sizeof(cmd));
  p->kind=C_print_cmd;
  p->u.print_cmd=print_cmd_a;
  return p;
}

const_decl *MK_const_decl(const_id *const_id_a,const_expr *const_expr_a)
{
  const_decl *p=(const_decl *)safemalloc(sizeof(const_decl));
  p->const_id=const_id_a;
  p->const_expr=const_expr_a;
  return p;
}

tOSQR_e_expr_list_e_tCSQR_01 *MK_tOSQR_e_expr_list_e_tCSQR_01(expr_list *expr_list_a)
{
  tOSQR_e_expr_list_e_tCSQR_01 *p=(tOSQR_e_expr_list_e_tCSQR_01 *)safemalloc(sizeof(tOSQR_e_expr_list_e_tCSQR_01));
  p->expr_list=expr_list_a;
  return p;
}

decl_var *MK_decl_var(var_id *var_id_a,tOSQR_e_expr_list_e_tCSQR_01 *tOSQR_e_expr_list_e_tCSQR_01_a)
{
  decl_var *p=(decl_var *)safemalloc(sizeof(decl_var));
  p->var_id=var_id_a;
  p->tOSQR_e_expr_list_e_tCSQR_01=tOSQR_e_expr_list_e_tCSQR_01_a;
  return p;
}

tCOMMA_e_decl_var_ast *MK_tCOMMA_e_decl_var_ast(decl_var *decl_var_a,tCOMMA_e_decl_var_ast *tCOMMA_e_decl_var_ast_a)
{
  tCOMMA_e_decl_var_ast *p=(tCOMMA_e_decl_var_ast *)safemalloc(sizeof(tCOMMA_e_decl_var_ast));
  p->decl_var=decl_var_a;
  p->tCOMMA_e_decl_var_ast=tCOMMA_e_decl_var_ast_a;
  return p;
}

decl_var_list *MK_decl_var_list(decl_var *decl_var_a,tCOMMA_e_decl_var_ast *tCOMMA_e_decl_var_ast_a)
{
  decl_var_list *p=(decl_var_list *)safemalloc(sizeof(decl_var_list));
  p->decl_var=decl_var_a;
  p->tCOMMA_e_decl_var_ast=tCOMMA_e_decl_var_ast_a;
  return p;
}

var_decl *MK_var_decl(decl_var_list *decl_var_list_a)
{
  var_decl *p=(var_decl *)safemalloc(sizeof(var_decl));
  p->decl_var_list=decl_var_list_a;
  return p;
}

prg *MK_prg1(var_decl *var_decl_a,prg *prg_a)
{
  prg *p=(prg *)safemalloc(sizeof(prg));
  p->kind=P_var_decl_prg;
  p->u.var_decl_prg.var_decl =var_decl_a;
  p->u.var_decl_prg.prg =prg_a;
  return p;
}

prg *MK_prg2(cmd *cmd_a,prg *prg_a)
{
  prg *p=(prg *)safemalloc(sizeof(*p));
  p->kind=P_cmd_prg;
  p->u.cmd_prg.cmd =cmd_a;
  p->u.cmd_prg.prg =prg_a;

  return p;
}

prg *MK_prg3(const_decl *const_decl_a,prg *prg_a)
{
  prg *p=(prg *)safemalloc(sizeof(prg));
  p->kind=P_const_decl_prg  ;
  p->u.const_decl_prg.const_decl=const_decl_a;
  p->u.const_decl_prg.prg =prg_a;

  return p;
}

prg *MK_prg4(prg *prg_a)
{
  prg *p=(prg *)safemalloc(sizeof(*p));
  p->kind=P_NL_prg;
  p->u.prg =prg_a;
  return p;
}

start *MK_start(prg *prg_a)
{
  start *p=(start *) safemalloc(sizeof(start));
  p->prg=prg_a;
  return p;
}

/*
main()
{
  yyparse();
  return 0;
}
*/
