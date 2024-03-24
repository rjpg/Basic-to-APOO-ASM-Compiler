#include "estr.h"
#include "tree.h"

FILE *apoo;

T_stm T_STM;

T_exp convert_expr(arit_expr *);
T_stm convert_assig(assignment_cmd *);


void pr_stm(FILE *out, T_stm stm, int d); // imprime apenas um stm


void print_var_decl(var_decl *v,int spaces);
void printt_cmd(cmd *c,int spaces);
void print_const_decl(const_decl *c,int spaces);
void print_prg(prg *p,int spaces);
void print_start(start *s,int spaces);
void print_const_id(const_id *c,int spaces);
void print_const_decl(const_decl *c,int spaces);


void print_var_id(var_id *c,int spaces);
void print_const_id(const_id *c,int spaces);
void print_var_o_const_id(var_o_const_id *c,int spaces);
void print_rel_op(rel_op *c,int spaces);
void print_const_expr(const_expr *p,int spaces);
void print_tCOMMA_e_expr_mais(tCOMMA_e_expr_mais *p,int spaces);
void print_arit_expr(arit_expr *p,int spaces);
void print_rel_expr(rel_expr *p,int spaces);
void print_bool_expr(bool_expr *p,int spaces);
void printt_expr(expr *p,int spaces);
void print_tCOMMA_e_expr_ast(tCOMMA_e_expr_ast *p,int spaces);
void printt_expr_list(expr_list *p,int spaces);
void print_expr_list_01(expr_list_01 *p,int spaces);
void print_cond(cond *p,int spaces);
void print_print_expr(print_expr *p,int spaces);
void print_print_cmd(print_cmd *p,int spaces);
void print_print_expr_list(print_expr_list *p,int spaces);
void print_tCOMMA_print_expr_ast(tCOMMA_print_expr_ast *p,int spaces);
void print_use_simple_var(use_simple_var *p,int spaces);
void print_use_array_var(use_array_var *p,int spaces);
void print_use_var(use_var *p,int spaces);
void print_input_cmd(input_cmd *p,int spaces);
void print_exit_loop_cmd(exit_loop_cmd *P,int spaces);
void print_end_cmd(end_cmd *p,int spaces);
void print_assignment_cmd(assignment_cmd *p,int spaces);
void print_var_decl_o_const_decl_o_cmd_ast(var_decl_o_const_decl_o_cmd_ast *p,int spaces);
void print_loop_until_cmd(loop_until_cmd *p,int spaces);
void print_do_while_cmd(do_while_cmd *p,int spaces);
void print_tSTEP_e_expr_01(tSTEP_e_expr_01 *p,int spaces);
void print_for_cmd(for_cmd *p,int spaces);
void print_else_nl_01(else_nl_01 *p,int spaces);
void print_if_cmd(if_cmd *p,int spaces);
void printt_cmd(cmd *c,int spaces);
void print_const_decl(const_decl *p,int spaces);
void print_tOSQR_e_expr_list_e_tCSQR_01(tOSQR_e_expr_list_e_tCSQR_01 *p,int spaces);
void print_decl_var(decl_var *p,int spaces);
void print_tCOMMA_e_decl_var_ast(tCOMMA_e_decl_var_ast *p,int spaces);
void print_decl_var_list(decl_var_list *p,int spaces);
void print_var_decl(var_decl *v,int spaces);
void print_prg(prg *p,int spaces);
void print_start(start *s,int spaces);




