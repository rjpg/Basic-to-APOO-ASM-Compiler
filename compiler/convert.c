#include <stdio.h>
//#include "estr.h"
#include "convert.h"
//#include "tree.h"
#include "hash.h"

//------------------------REG && LABELS--------------------------------
int LABEL=0;        // controlo de Labels

int REG[32];         // controlo de registos
int ST_R[32];

void reset_reg()
{
  int i =0;
  for (i=0;i<32;i++)
    {
      REG[i]=0;           // 0 livre
      ST_R[i]=-1;
    }
}



int ocupa_reg()
{
  int i=0;
  int x=0;
  for(i=0;i<32;i++)
    if (REG[i]==0) 
      {
	REG[i]=1;
	while(ST_R[x]!=-1)x++;
	ST_R[x]=i;
	return i;
      }
  
  
  printf("erro: NO MORE REGISTERS!!!\n");
  exit(1);
}

void limpa_reg(int i) 
{
  REG[i]=0;
  
}

void limpa_ST_R()
{
  int x=0;
  while(ST_R[x]!=-1)x++;
  ST_R[x-1]=-1;
}

int give_ST_R()
{
  int x=0;
  while(ST_R[x]!=-1)x++;
  return ST_R[x-1];
}




//--------------------------------inter tree------------------------------------

static void indent(FILE *out, int d) {
 int i;
 for (i = 0; i <= d; i++) fprintf(out, " ");
}

void pr_tree_exp(FILE *out, T_exp exp, int d)
{
  switch (exp->kind) {
  case T_BINOP:
    indent(out,d); fprintf(out, "BINOP(%s,\n", exp->u.BINOP.op);
    pr_tree_exp(out, exp->u.BINOP.left,d+1); fprintf(out, ",\n");
    pr_tree_exp(out, exp->u.BINOP.right,d+1); fprintf(out, ")");
    break;
  case T_Exp:
    indent(out,d); 
    fprintf(out, "MEM");
    fprintf(out, "(\n"); pr_tree_exp(out, exp->u.exp,d+1); fprintf(out, ")");
    break;
    /* case T_Temp:
    indent(out,d); fprintf(out, "TEMP t%s",
			   Temp_look(Temp_name(), exp->u.temp));
			   break;*/
  case T_ESEQ:
    indent(out,d); fprintf(out, "ESEQ(\n"); pr_stm(out, exp->u.ESEQ.stm,d+1);
    fprintf(out, ",\n");
    pr_tree_exp(out, exp->u.ESEQ.exp,d+1); fprintf(out, ")");
    break;
  case T_NAME:
    indent(out,d); fprintf(out, "NAME %s", exp->u.name);
    break;
  case T_CONST:
    indent(out,d); fprintf(out, "CONST %d", exp->u.constant);
    break;
    /*  case T_CALL:
    {T_expList args = exp->u.CALL.args;
     indent(out,d); fprintf(out, "CALL(\n"); pr_tree_exp(out, exp->u.CALL.fun,d+1);
     for (;args; args=args->tail) {
       fprintf(out, ",\n"); pr_tree_exp(out, args->head,d+2);
     }
     fprintf(out, ")");
     break;*/
  } /* end of switch */
}






void pr_stm(FILE *out, T_stm stm, int d)
{
  switch (stm->kind) {
  case T_SEQ:
    indent(out,d);
    fprintf(out, "SEQ(\n"); pr_stm(out, stm->u.SEQ.left,d+1);  fprintf(out, ",\n");
    pr_stm(out, stm->u.SEQ.right,d+1); fprintf(out, ")");
    break;
  case T_LABEL:
    indent(out,d); fprintf(out, "LABEL %s", stm->u.LABEL);
    break;
  case T_JUMP:
    indent(out,d); fprintf(out, "JUMP(\n"); 
    //pr_tree_exp(out, stm->u.JUMP.label,d+1);
    fprintf(out, ")");
    break;
  case T_CJUMP:
    indent(out,d); fprintf(out, "CJUMP(%s,\n", stm->u.CJUMP.op);
    pr_tree_exp(out, stm->u.CJUMP.left,d+1); fprintf(out, ",\n");
    pr_tree_exp(out, stm->u.CJUMP.right,d+1); fprintf(out, ",\n");
    indent(out,d+1); fprintf(out, "%s,", stm->u.CJUMP.true);
    fprintf(out, "%s", stm->u.CJUMP.false); fprintf(out, ")");
    break;
  case T_MOVE:
    indent(out,d); fprintf(out, "MOVE(\n"); pr_tree_exp(out, stm->u.MOVE.destino,d+1);
    fprintf(out, ",\n");
    pr_tree_exp(out, stm->u.MOVE.origem,d+1); fprintf(out, ")");
    break;
  case T_Exp_MEM:
    indent(out,d); fprintf(out, "EXP(\n"); pr_tree_exp(out, stm->u.exp,d+1);
    fprintf(out, ")");
    break;
  }
}





//-------------------------------------End inter tree--------------------------------

#define Base 0


T_stm convert_assig(assignment_cmd *com)
{
  T_stm c;
  T_exp c1,c2;
  Hash *s;

  //printf("-%s",com->use_var->u.use_simple_var->var_id->id);
  s = pesquisa(com->use_var->u.use_simple_var->var_id->id);

  c1 = T_Binop("PLUS",T_const(Base),T_const(s->offset));
  c2 = convert_expr(com->expr->arit_expr);
  c =  T_Move(c1,c2);
  
  return c;
}


T_exp convert_expr(arit_expr *exp)
{
  T_exp c1,c2;
  T_exp c;
  int k = 0;
  Hash *s;
  
  switch(exp->kind)
    {
    case A_E_arit_expr_MUL_arit_expr:
      c1 = convert_expr(exp->u.arit_expr_arit_op_arit_expr.arit_expr_1);
      c2 = convert_expr(exp->u.arit_expr_arit_op_arit_expr.arit_expr_2);
      c = T_Binop("MUL",c1,c2);
      break;
    case A_E_arit_expr_PLUS_arit_expr:
      c1 = convert_expr(exp->u.arit_expr_arit_op_arit_expr.arit_expr_1);
      c2 = convert_expr(exp->u.arit_expr_arit_op_arit_expr.arit_expr_2);
      c = T_Binop("PLUS",c1,c2);
      break;
    case A_E_arit_expr_DIV_arit_expr:
      c1 = convert_expr(exp->u.arit_expr_arit_op_arit_expr.arit_expr_1);
      c2 = convert_expr(exp->u.arit_expr_arit_op_arit_expr.arit_expr_2);
      c = T_Binop("DIV",c1,c2);
      break;
    case A_E_arit_expr_MINUS_arit_expr:
      c1 = convert_expr(exp->u.arit_expr_arit_op_arit_expr.arit_expr_1);
      c2 = convert_expr(exp->u.arit_expr_arit_op_arit_expr.arit_expr_2);
      c = T_Binop("MINUS",c1,c2);
      break;
    case A_E_arit_expr_MOD_arit_expr:
      c1 = convert_expr(exp->u.arit_expr_arit_op_arit_expr.arit_expr_1);
      c2 = convert_expr(exp->u.arit_expr_arit_op_arit_expr.arit_expr_2);
      c = T_Binop("MOD",c1,c2);
      break; 
    case A_E_NUMBER_LITERAL: 
      c = T_const(exp->u.NUMBER_L);
      break;
    case A_E_var_o_const_id:
      s = pesquisa(exp->u.var_o_const_id->id);
      c = T_mem(T_Binop("PLUS",T_const(k),T_const(s->offset)));
      break;

    }
  return c;
}  



// -----------------------------------------------------------------------
#define ident_c 2   // dois espaços em cada descida na arv

void ident(int d)
{
  int i;
  for (i = 0; i <= d; i++) printf(" ");
}

void print_var_id(var_id *c,int spaces)
{
  ident(spaces);
  printf("estou em var_id");
  if (c==NULL) return;
  fprintf(apoo,"%s",c->id);
  printf("(%s)\n",c->id);
}

void print_const_id(const_id *c,int spaces)
{
  ident(spaces);
  printf("estou em const_id");
  if (c==NULL) return;
  fprintf(apoo,"%s",c->id);
  printf("(%s)\n",c->id);
}

void print_var_o_const_id(var_o_const_id *c,int spaces)
{
  ident(spaces);
  printf("estou em var_o_const_id");
  if (c==NULL) return;
  printf("(%s)\n",c->id);
}

void print_rel_op(rel_op *c,int spaces)
{
  ident(spaces);
  printf("estou em rel_op");
  if (c==NULL) return;
  printf("(%s)\n",c->op);
}

void print_const_expr(const_expr *p,int spaces)
{
  ident(spaces);
  printf("estou em const_expr\n");
  if (p==NULL) return;
  switch(p->kind)
    {
    case C_E_MINUS_const_expr:
      print_const_expr(p->u.const_expr,spaces+ident_c);
      break;
    case C_E_const_expr_MUL_const_expr:
      print_const_expr(p->u.const_expr_arit_op_const_expr.const_expr_1,spaces+ident_c);
      print_const_expr(p->u.const_expr_arit_op_const_expr.const_expr_2,spaces+ident_c);
      break;
    case C_E_const_expr_DIV_const_expr:
      print_const_expr(p->u.const_expr_arit_op_const_expr.const_expr_1,spaces+ident_c);
      print_const_expr(p->u.const_expr_arit_op_const_expr.const_expr_2,spaces+ident_c);
      break;
    case C_E_const_expr_MOD_const_expr:
      print_const_expr(p->u.const_expr_arit_op_const_expr.const_expr_1,spaces+ident_c);
      print_const_expr(p->u.const_expr_arit_op_const_expr.const_expr_2,spaces+ident_c);
      break;
    case C_E_const_expr_MINUS_const_expr:
      print_const_expr(p->u.const_expr_arit_op_const_expr.const_expr_1,spaces+ident_c);
      print_const_expr(p->u.const_expr_arit_op_const_expr.const_expr_2,spaces+ident_c);
      break;
    case C_E_const_expr_PLUS_const_expr:
      print_const_expr(p->u.const_expr_arit_op_const_expr.const_expr_1,spaces+ident_c);
      print_const_expr(p->u.const_expr_arit_op_const_expr.const_expr_2,spaces+ident_c);
      break;
    case C_E_OPAR_const_expr_CPAR:
      print_const_expr(p->u.const_expr,spaces+ident_c);
      break;
    case C_E_NUMBER_LITERAL:
      ident(spaces);
      printf("Number Literal:%d\n",p->u.NUMBER_L);
      fprintf(apoo,"%d\n",p->u.NUMBER_L);
      break;
    case C_E_const_identifier:
      print_const_id(p->u.const_id,spaces+ident_c);
      break; 
    }

}

void print_tCOMMA_e_expr_mais(tCOMMA_e_expr_mais *p,int spaces)
{
  ident(spaces);
  printf("estou em arit_expr\n");
  if (p==NULL) return;
  switch(p->kind)
    {
    case T_E_E_M_COMMA_expr:
      printt_expr(p->u.expr,spaces+ident_c);
      break;
    case T_E_E_M_COMMA_expr_tCOMMA_e_expr_mais:
      printt_expr(p->u.COMMA_expr_tCOMMA_e_expr_mais.expr,spaces+ident_c);
      print_tCOMMA_e_expr_mais(p->u.COMMA_expr_tCOMMA_e_expr_mais.tCOMMA_e_expr_mais,spaces+ident_c);
      break;
    }
}

void print_arit_expr(arit_expr *p,int spaces)
{
  int R1,R2;
  ident(spaces);
  printf("estou em arit_expr\n");
  if (p==NULL) return;
  switch(p->kind)
    {
    case A_E_MINUS_arit_expr:
      print_arit_expr(p->u.arit_expr,spaces+ident_c);
      break;
    case A_E_arit_expr_MUL_arit_expr:
      print_arit_expr(p->u.arit_expr_arit_op_arit_expr.arit_expr_1,spaces+ident_c);
      print_arit_expr(p->u.arit_expr_arit_op_arit_expr.arit_expr_2,spaces+ident_c);
      break;
    case A_E_arit_expr_DIV_arit_expr:
      print_arit_expr(p->u.arit_expr_arit_op_arit_expr.arit_expr_1,spaces+ident_c);
      print_arit_expr(p->u.arit_expr_arit_op_arit_expr.arit_expr_2,spaces+ident_c);
      break;
    case A_E_arit_expr_MINUS_arit_expr:
      print_arit_expr(p->u.arit_expr_arit_op_arit_expr.arit_expr_1,spaces+ident_c);
      print_arit_expr(p->u.arit_expr_arit_op_arit_expr.arit_expr_2,spaces+ident_c);
      break;
    case A_E_arit_expr_PLUS_arit_expr:
      print_arit_expr(p->u.arit_expr_arit_op_arit_expr.arit_expr_1,spaces+ident_c);
      print_arit_expr(p->u.arit_expr_arit_op_arit_expr.arit_expr_2,spaces+ident_c);
      break;
    case A_E_arit_expr_MOD_arit_expr:
      print_arit_expr(p->u.arit_expr_arit_op_arit_expr.arit_expr_1,spaces+ident_c);
      print_arit_expr(p->u.arit_expr_arit_op_arit_expr.arit_expr_2,spaces+ident_c);
      break;
    case A_E_OPAR_arit_expr_CPAR:
      print_arit_expr(p->u.arit_expr,spaces+ident_c);
      break;
    case A_E_NUMBER_LITERAL:
      ident(spaces);
      printf("Number Literal:%d\n",p->u.NUMBER_L);
      R1=ocupa_reg();
      fprintf(apoo,"loadn\t%d\tR%d\n",p->u.NUMBER_L,R1);
      break;
    case A_E_var_o_const_id:
      //R1=ocupa_reg();
      fprintf(apoo,"loadn\t");
      print_var_o_const_id(p->u.var_o_const_id,spaces+ident_c);
      //fprintf(apoo,"\tR%d\n",R1);
      break;
    case A_E_use_array_var:
      print_use_array_var(p->u.use_array_var,spaces+ident_c);
      break;
    }
}

void print_rel_expr(rel_expr *p,int spaces)
{
  ident(spaces);
  printf("estou em rel_expr\n");
  if (p==NULL) return;
  print_arit_expr(p->arit_expr1,spaces+ident_c);
  print_rel_op(p->rel_op,spaces+ident_c);
  print_arit_expr(p->arit_expr2,spaces+ident_c);
}

void print_bool_expr(bool_expr *p,int spaces)
{
  ident(spaces);
  printf("estou em bool_expr\n");
  if (p==NULL) return;
  switch(p->kind)
    {
    case B_E_NOT_bool_expr:
      print_bool_expr(p->u.bool_expr,spaces+ident_c);
      break;
    case B_E_bool_expr_AND_bool_expr:
      print_bool_expr(p->u.bool_expr_bool_op_bool_expr.bool_expr_1,spaces+ident_c);
      print_bool_expr(p->u.bool_expr_bool_op_bool_expr.bool_expr_2,spaces+ident_c);
      break;
    case B_E_bool_expr_OR_bool_expr:
      print_bool_expr(p->u.bool_expr_bool_op_bool_expr.bool_expr_1,spaces+ident_c);
      print_bool_expr(p->u.bool_expr_bool_op_bool_expr.bool_expr_2,spaces+ident_c);
      break;
    case B_E_rel_expr:
      print_rel_expr(p->u.rel_expr,spaces+ident_c);
      break;
    case B_E_OPAR_bool_expr_CPAR:
      print_bool_expr(p->u.bool_expr,spaces+ident_c);
      break;
    }
}

void printt_expr(expr *p,int spaces)
{
  ident(spaces);
  printf("estou em expr\n");
  if (p==NULL) return;
  print_arit_expr(p->arit_expr,spaces+ident_c);
}

void print_tCOMMA_e_expr_ast(tCOMMA_e_expr_ast *p,int spaces)
{
  ident(spaces);
  printf("estou em tCOMMA_e_expr_ast\n");
  if (p==NULL) return;
  printt_expr(p->expr,spaces+ident_c); 
  print_tCOMMA_e_expr_ast(p->tCOMMA_e_expr_ast,spaces+ident_c);
}

void printt_expr_list(expr_list *p,int spaces)
{
  ident(spaces);
  printf("estou em expr_list\n");
  if (p==NULL) return;
  printt_expr(p->expr,spaces+ident_c); 
  print_tCOMMA_e_expr_ast(p->tCOMMA_e_expr_ast,spaces+ident_c); 

}

void print_expr_list_01(expr_list_01 *p,int spaces)
{
  ident(spaces);
  printf("estou em expr_list_01\n");
  if (p==NULL) return;
  printt_expr_list(p->expr_list,spaces+ident_c); 
}

void print_cond(cond *p,int spaces)
{
  ident(spaces);
  printf("estou em cond\n");
  if (p==NULL) return;
  print_bool_expr(p->bool_expr,spaces+ident_c);
}

void print_print_expr(print_expr *p,int spaces)
{
  ident(spaces);
  printf("estou em print_expr\n");
  if (p==NULL) return;
  switch(p->kind)
    {
    case P_E_expr:
      printt_expr(p->u.expr,spaces+ident_c);
      break;
    case P_E_STRING_LITERAL:
      //--------------------imprime string...
      return;
      break;
    }  
}

void print_print_cmd(print_cmd *p,int spaces)
{
  ident(spaces);
  printf("estou em print_cmd\n");
  if (p==NULL) return;
  print_print_expr_list(p->print_expr_list,spaces+ident_c);
}

void print_print_expr_list(print_expr_list *p,int spaces)
{
  ident(spaces);
  printf("estou em print_expr_list\n");
  if (p==NULL) return;
  print_print_expr(p->print_expr,spaces+ident_c);
  print_tCOMMA_print_expr_ast(p->tCOMMA_print_expr_ast,spaces+ident_c);
}

void print_tCOMMA_print_expr_ast(tCOMMA_print_expr_ast *p,int spaces)
{
  ident(spaces);
  printf("estou em tCOMMA_print_expr_ast\n");
  if (p==NULL) return;
  print_print_expr(p->print_expr,spaces+ident_c);
  print_tCOMMA_print_expr_ast(p->tCOMMA_print_expr_ast,spaces+ident_c);
}

void print_use_simple_var(use_simple_var *p,int spaces)
{
  ident(spaces);
  printf("estou em use_simple_var\n");
  if (p==NULL) return;
  //fprintf(apoo,"%s",p->var_id->id);
  print_var_id(p->var_id,spaces+ident_c);
}

void print_use_array_var(use_array_var *p,int spaces)
{
  ident(spaces);
  printf("estou em use_array_var\n");
  if (p==NULL) return;
  print_var_id(p->var_id,spaces+ident_c);
  printt_expr_list(p->expr_list,spaces+ident_c);

}

void print_use_var(use_var *p,int spaces)
{
  ident(spaces);
  printf("estou em use_var\n");
  if (p==NULL) return;
  switch(p->kind)
    {
    case U_V_use_simple_var:
      print_use_simple_var(p->u.use_simple_var,spaces+ident_c);
      break;
    case U_V_use_array_var:
      print_use_array_var(p->u.use_array_var,spaces+ident_c);
      break;
    }
}

void print_input_cmd(input_cmd *p,int spaces)
{
  ident(spaces);
  printf("estou em input_cmd\n");
  if (p==NULL) return;
  print_use_var(p->use_var,spaces+ident_c);
}

void print_exit_loop_cmd(exit_loop_cmd *p,int spaces)
{
  ident(spaces);
  printf("estou em exit_loop_cmd:");
  if (p==NULL) return;
  printf("*%s*\n",p->EXITLOOP_NL);
}

void print_end_cmd(end_cmd *p,int spaces)
{
  ident(spaces);
  printf("estou em end_cmd:");
  if (p==NULL) return;
  printf("*%s*\n",p->END_NL);
}

void print_assignment_cmd(assignment_cmd *p,int spaces)
{
  int R;
  ident(spaces);
  printf("estou em print_assignment_cmd\n");
  if (p==NULL) return;
  //store\tR%d\t%s

  printt_expr(p->expr,spaces+ident_c);
  R=give_ST_R();
  fprintf(apoo,"store\tR%d\t",R);
  limpa_reg(R);
  limpa_ST_R();
  print_use_var(p->use_var,spaces+ident_c);
  fprintf(apoo,"\n");

}

void print_var_decl_o_const_decl_o_cmd_ast(var_decl_o_const_decl_o_cmd_ast *p,int spaces)
{
  ident(spaces);
  printf("estou em var_decl_o_const_decl_o_cmd_ast\n");
  if (p==NULL) return;
  switch(p->kind)
    {
    case V_D_O_var_decl_var_decl_o_const_decl_o_cmd_ast:
      print_var_decl(p->u.var_decl_var_decl_o_const_decl_o_cmd_ast.var_decl,spaces+ident_c);
      print_var_decl_o_const_decl_o_cmd_ast(p->u.var_decl_var_decl_o_const_decl_o_cmd_ast.var_decl_o_const_decl_o_cmd_ast,spaces+ident_c);
      break;
    case V_D_O_const_decl_var_decl_o_const_decl_o_cmd_ast:
      print_const_decl(p->u.const_decl_var_decl_o_const_decl_o_cmd_ast.const_decl,spaces+ident_c);
      print_var_decl_o_const_decl_o_cmd_ast(p->u.const_decl_var_decl_o_const_decl_o_cmd_ast.var_decl_o_const_decl_o_cmd_ast,spaces+ident_c);
      break;
    case V_D_O_cmd_var_decl_o_const_decl_o_cmd_ast:
      printt_cmd(p->u.cmd_var_decl_o_const_decl_o_cmd_ast.cmd,spaces+ident_c);
      print_var_decl_o_const_decl_o_cmd_ast(p->u.cmd_var_decl_o_const_decl_o_cmd_ast.var_decl_o_const_decl_o_cmd_ast,spaces+ident_c);
      break;
    }
}

void print_loop_until_cmd(loop_until_cmd *p,int spaces)
{
  ident(spaces);
  printf("estou em loop_until_cmd\n");
  if (p==NULL) return;
  print_var_decl_o_const_decl_o_cmd_ast(p->var_decl_o_const_decl_o_cmd_ast,spaces+ident_c);
  print_cond(p->cond,spaces+ident_c);
}

void print_do_while_cmd(do_while_cmd *p,int spaces)
{
  ident(spaces);
  printf("estou em do_while_cmd\n");
  if (p==NULL) return;
  print_cond(p->cond,spaces+ident_c);
  print_var_decl_o_const_decl_o_cmd_ast(p->var_decl_o_const_decl_o_cmd_ast,spaces+ident_c);

}

void print_tSTEP_e_expr_01(tSTEP_e_expr_01 *p,int spaces)
{
  ident(spaces);
  printf("estou em tSTEP_e_expr_01\n");
  if (p==NULL) return;
  printt_expr(p->expr,spaces+ident_c);
}

void print_for_cmd(for_cmd *p,int spaces)
{
  ident(spaces);
  printf("estou em for_cmd\n");
  if (p==NULL) return;
  print_use_simple_var(p->use_simple_var,spaces+ident_c);
  printt_expr(p->expr1,spaces+ident_c);
  printt_expr(p->expr2,spaces+ident_c);
  print_tSTEP_e_expr_01(p->tSTEP_e_expr_01,spaces+ident_c);
  print_var_decl_o_const_decl_o_cmd_ast(p->var_decl_o_const_decl_o_cmd_ast,spaces+ident_c);
}


void print_else_nl_01(else_nl_01 *p,int spaces)
{
  ident(spaces);
  printf("estou em else_nl_01\n");
  if (p==NULL) return;
  print_var_decl_o_const_decl_o_cmd_ast(p->var_decl_o_const_decl_o_cmd_ast,spaces+ident_c);
}

void print_if_cmd(if_cmd *p,int spaces)
{
  ident(spaces);
  printf("estou em if_cmd\n");
  if (p==NULL) return;
  print_cond(p->cond,spaces+ident_c);
  print_var_decl_o_const_decl_o_cmd_ast(p->var_decl_o_const_decl_o_cmd_ast,spaces+ident_c);
  print_else_nl_01(p->else_nl_01,spaces+ident_c);
}

void printt_cmd(cmd *c,int spaces)
{
  ident(spaces);
  printf("estou em cmd\n");
  if (c==NULL) return;
  switch(c->kind)
    {
    case C_if_cmd:
      print_if_cmd(c->u.if_cmd,spaces+ident_c);
      break;
    case C_for_cmd:
      print_for_cmd(c->u.for_cmd,spaces+ident_c);
      break;
    case C_do_while_cmd:
      print_do_while_cmd(c->u.do_while_cmd,spaces+ident_c);
      break;
    case C_loop_until_cmd:
      print_loop_until_cmd(c->u.loop_until_cmd,spaces+ident_c);
      break;
    case C_assignment_cmd:
      print_assignment_cmd(c->u.assignment_cmd,spaces+ident_c);
      //printf("wedfwef\n");
      //T_STM=convert_assig(c->u.assignment_cmd);
      break;
    case C_end_cmd:
      print_end_cmd(c->u.end_cmd,spaces+ident_c);
      break;
    case C_exit_loop_cmd:
      print_exit_loop_cmd(c->u.exit_loop_cmd,spaces+ident_c);
      break;
    case C_input_cmd:
      print_input_cmd(c->u.input_cmd,spaces+ident_c);
      break;
    case C_print_cmd:
      print_print_cmd(c->u.print_cmd,spaces+ident_c);
      break;
    }
  //...
}


void print_const_decl(const_decl *p,int spaces)
{
  ident(spaces);
  printf("estou em const_decl\n");
  if (p==NULL) return;

  print_const_id(p->const_id,spaces+ident_c);
  fprintf(apoo,":\tconst\t");
  print_const_expr(p->const_expr,spaces+ident_c);
}

void print_tOSQR_e_expr_list_e_tCSQR_01(tOSQR_e_expr_list_e_tCSQR_01 *p,int spaces)
{
  ident(spaces);
  printf("estou em tOSQR_e_expr_list_e_tCSQR_01\n");
  if (p==NULL) return;
  printt_expr_list(p->expr_list,spaces+ident_c);
}

void print_decl_var(decl_var *p,int spaces)
{  
  ident(spaces);
  printf("estou em decl_var\n");
  //return;
  if (p==NULL) { printf("é nulo\n");return;}

  print_var_id(p->var_id,spaces+ident_c);
  fprintf(apoo,":\tmem\t1");
  fprintf(apoo,"\n");
  print_tOSQR_e_expr_list_e_tCSQR_01(p->tOSQR_e_expr_list_e_tCSQR_01,spaces+ident_c);

}

void print_tCOMMA_e_decl_var_ast(tCOMMA_e_decl_var_ast *p,int spaces)
{
  ident(spaces);
  printf("estou em tCOMMA_e_decl_var_ast\n");
  if (p==NULL) return;
  print_decl_var(p->decl_var,spaces+ident_c);
  print_tCOMMA_e_decl_var_ast(p->tCOMMA_e_decl_var_ast,spaces+ident_c);
}

void print_decl_var_list(decl_var_list *p,int spaces)
{
  ident(spaces);
  printf("estou em decl_var_list\n");
  if (p==NULL) return;
  print_decl_var(p->decl_var,spaces+ident_c);
  print_tCOMMA_e_decl_var_ast(p->tCOMMA_e_decl_var_ast,spaces+ident_c);
}

void print_var_decl(var_decl *v,int spaces)
{
  ident(spaces);
  printf("estou em var_decl\n");
  if (v==NULL) return;
  print_decl_var_list(v->decl_var_list,spaces+ident_c);
  
}

void print_prg(prg *p,int spaces)
{
  ident(spaces);
  printf("estou em prg\n");
  if (p==NULL) return;
  switch(p->kind)
    {
    case P_var_decl_prg:
      print_var_decl(p->u.var_decl_prg.var_decl,spaces+ident_c);
      print_prg(p->u.var_decl_prg.prg,spaces+ident_c);
      p->kind=C_E_const_expr_MUL_const_expr;
      break;
    case P_cmd_prg:
      printt_cmd(p->u.cmd_prg.cmd,spaces+ident_c);
      print_prg(p->u.cmd_prg.prg,spaces+ident_c);
      break;
    case P_const_decl_prg:
      print_const_decl(p->u.const_decl_prg.const_decl,spaces+ident_c);
      print_prg(p->u.const_decl_prg.prg,spaces+ident_c);
      break;
    case P_NL_prg:
      print_prg(p->u.prg,spaces+ident_c);
      break;
    }
}

void print_start(start *s,int spaces)
{
  ident(spaces);
  printf("estou em start\n");
  if (s==NULL) return;
  print_prg(s->prg,spaces+ident_c);
}
