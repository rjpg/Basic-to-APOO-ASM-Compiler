#include <stdio.h>



typedef struct var_id
{
  char *id;
}var_id;

typedef struct const_id
{
  char *id;
}const_id;

typedef struct var_o_const_id
{
  char *id;
}var_o_const_id;

typedef struct rel_op
{
  char *op;
}rel_op;

typedef struct const_expr
{
  enum{C_E_MINUS_const_expr,
	C_E_const_expr_MUL_const_expr,
	C_E_const_expr_DIV_const_expr,
	C_E_const_expr_MOD_const_expr,
	C_E_const_expr_MINUS_const_expr,
	C_E_const_expr_PLUS_const_expr,
	C_E_OPAR_const_expr_CPAR,
	C_E_NUMBER_LITERAL,
	C_E_const_identifier}kind;
  union 
  {
    struct const_expr *const_expr;
    struct 
    {
      struct const_expr *const_expr_1;
      struct const_expr *const_expr_2;
    }const_expr_arit_op_const_expr;
    int NUMBER_L;
    struct const_id *const_id;
  }u;
}const_expr;

typedef struct tCOMMA_e_expr_mais
{
  enum{T_E_E_M_COMMA_expr,
	T_E_E_M_COMMA_expr_tCOMMA_e_expr_mais} kind;
  union
  {
    struct expr *expr;
    struct 
    {
      struct expr *expr;
      struct tCOMMA_e_expr_mais *tCOMMA_e_expr_mais;
    }COMMA_expr_tCOMMA_e_expr_mais;
  }u;
}tCOMMA_e_expr_mais;

typedef struct arit_expr
{
  enum{A_E_MINUS_arit_expr,
	A_E_arit_expr_MUL_arit_expr,
	A_E_arit_expr_DIV_arit_expr,
	A_E_arit_expr_MINUS_arit_expr,
	A_E_arit_expr_PLUS_arit_expr,
	A_E_arit_expr_MOD_arit_expr,
	A_E_OPAR_arit_expr_CPAR,
	A_E_NUMBER_LITERAL,
	A_E_var_o_const_id,
	A_E_use_array_var} kind;
  union 
  {
    struct arit_expr *arit_expr;
    struct 
    {
      struct arit_expr *arit_expr_1;
      struct arit_expr *arit_expr_2;
    }arit_expr_arit_op_arit_expr;
    int NUMBER_L;
    struct var_o_const_id *var_o_const_id;
    struct use_array_var *use_array_var;
  }u;
}arit_expr;

typedef struct rel_expr
{
  struct arit_expr *arit_expr1;
  struct rel_op *rel_op;
  struct arit_expr *arit_expr2;
}rel_expr;


typedef struct bool_expr
{
  enum {B_E_NOT_bool_expr,
	B_E_bool_expr_AND_bool_expr,
	B_E_bool_expr_OR_bool_expr,
	B_E_rel_expr,
	B_E_OPAR_bool_expr_CPAR} kind;
  union 
  {
    struct bool_expr *bool_expr;
    struct 
    {
      struct bool_expr *bool_expr_1;
      struct bool_expr *bool_expr_2;
    }bool_expr_bool_op_bool_expr;
    struct rel_expr *rel_expr;
  } u;
}bool_expr;

typedef struct expr
{
  struct arit_expr *arit_expr;
}expr;

typedef struct tCOMMA_e_expr_ast
{
  struct expr *expr;
  struct tCOMMA_e_expr_ast *tCOMMA_e_expr_ast;
}tCOMMA_e_expr_ast;

typedef struct expr_list
{
  struct expr *expr;
  struct tCOMMA_e_expr_ast *tCOMMA_e_expr_ast;
}expr_list;

typedef struct expr_list_01
{
  struct expr_list *expr_list;
}expr_list_01;

typedef struct cond
{
  struct bool_expr *bool_expr;
}cond;

typedef struct print_expr
{
  enum { P_E_expr, 
	 P_E_STRING_LITERAL } kind;
  union
  {
    struct expr *expr;
    char *STRING_L;
  }u;
}print_expr;

typedef struct print_cmd
{
  struct print_expr_list *print_expr_list;
}print_cmd;

typedef struct print_expr_list
{
  struct print_expr *print_expr;
  struct tCOMMA_print_expr_ast *tCOMMA_print_expr_ast;
}print_expr_list;

typedef struct tCOMMA_print_expr_ast
{
  struct print_expr *print_expr;
  struct tCOMMA_print_expr_ast *tCOMMA_print_expr_ast;
}tCOMMA_print_expr_ast;

typedef struct use_simple_var
{
  struct var_id *var_id;
}use_simple_var;

typedef struct use_array_var
{
  struct var_id *var_id;
  struct expr_list *expr_list;
}use_array_var;

typedef struct use_var
{
  enum { U_V_use_simple_var,
	 U_V_use_array_var} kind;
  union
  {
    struct use_simple_var *use_simple_var;
    struct use_array_var *use_array_var;
  }u;
}use_var;

typedef struct input_cmd
{
  struct use_var *use_var;
}input_cmd;

typedef struct exit_loop_cmd
{
  char *EXITLOOP_NL;
}exit_loop_cmd;

typedef struct end_cmd
{
  char *END_NL;
}end_cmd;

typedef struct assignment_cmd
{ 
  enum {A_C_use_var_EQ_expr_NL, 
	A_C_LET_use_var_EQ_expr_NL} kind;
  struct use_var *use_var;
  struct expr *expr;
}assignment_cmd;



//-------------------------------------- lembrar depois ---------------
typedef struct var_decl_o_const_decl_o_cmd_ast
{
  enum {V_D_O_var_decl_var_decl_o_const_decl_o_cmd_ast,
	V_D_O_const_decl_var_decl_o_const_decl_o_cmd_ast,
	V_D_O_cmd_var_decl_o_const_decl_o_cmd_ast} kind;
  union
  {
    struct 
    {
      struct var_decl *var_decl;
      struct var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast;
    }var_decl_var_decl_o_const_decl_o_cmd_ast;
    struct 
    {
      struct const_decl *const_decl;
      struct var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast;
    }const_decl_var_decl_o_const_decl_o_cmd_ast;
    struct 
    {
      struct cmd *cmd;
      struct var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast; 
    }cmd_var_decl_o_const_decl_o_cmd_ast;
  }u;
}var_decl_o_const_decl_o_cmd_ast; 


typedef struct loop_until_cmd
{
  struct var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast;
  struct cond *cond;
}loop_until_cmd;

typedef struct do_while_cmd
{
  struct cond *cond;
  struct var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast;
}do_while_cmd;

typedef struct tSTEP_e_expr_01
{
  struct expr *expr;
}tSTEP_e_expr_01 ;

typedef struct for_cmd
{
  struct use_simple_var *use_simple_var;
  struct expr *expr1;
  struct expr *expr2;
  struct tSTEP_e_expr_01 *tSTEP_e_expr_01;
  struct var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast;
}for_cmd;

typedef struct else_nl_01
{
  struct var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast;
}else_nl_01;

typedef struct if_cmd
{
      struct cond *cond;
      struct var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast;
      struct else_nl_01 *else_nl_01;
}if_cmd;

typedef struct cmd
{
  enum { C_if_cmd, 
	 C_for_cmd, 
	 C_do_while_cmd, 
	 C_loop_until_cmd, 
	 C_assignment_cmd,
	 C_end_cmd,
	 C_exit_loop_cmd,
	 C_input_cmd,
	 C_print_cmd
  } kind;
  union
  {
    struct if_cmd *if_cmd;
    struct for_cmd *for_cmd;
    struct do_while_cmd *do_while_cmd;
    struct loop_until_cmd *loop_until_cmd;
    struct assignment_cmd *assignment_cmd;
    struct end_cmd *end_cmd;
    struct exit_loop_cmd *exit_loop_cmd;
    struct input_cmd *input_cmd;
    struct print_cmd *print_cmd;
  }u;
}cmd;

typedef struct const_decl
{
  struct const_id *const_id;
  struct const_expr *const_expr;
}const_decl;

typedef struct tOSQR_e_expr_list_e_tCSQR_01
{
  struct expr_list *expr_list;
}tOSQR_e_expr_list_e_tCSQR_01;

typedef struct decl_var
{
  struct var_id *var_id;
  struct tOSQR_e_expr_list_e_tCSQR_01 *tOSQR_e_expr_list_e_tCSQR_01;
}decl_var;

typedef struct tCOMMA_e_decl_var_ast
{
  struct  decl_var *decl_var;
  struct tCOMMA_e_decl_var_ast *tCOMMA_e_decl_var_ast;
}tCOMMA_e_decl_var_ast; 

typedef struct decl_var_list
{
  struct decl_var *decl_var;
  struct tCOMMA_e_decl_var_ast *tCOMMA_e_decl_var_ast;
}decl_var_list;

typedef struct var_decl
{
  struct decl_var_list *decl_var_list;
}var_decl;

typedef struct prg
{
  enum {P_var_decl_prg, 
	P_cmd_prg, 
	P_const_decl_prg, 
	P_NL_prg} kind;
  union
  {
    struct {
      struct var_decl *var_decl;
      struct prg *prg;
    }var_decl_prg;
    struct {
      struct cmd *cmd;
      struct prg *prg;
    }cmd_prg;
    struct {
      struct const_decl *const_decl;
      struct prg *prg;
    }const_decl_prg;
    struct prg *prg;
  }u;
}prg;

typedef struct start
{
  struct prg *prg;
}start;

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/

/*
main ()
{
  return 0;
  }
*/



var_id *MK_var_id(char *id);
const_id *MK_const_id(char *id);
var_o_const_id *MK_var_o_const_id(char *id);
rel_op *MK_rel_op(char *op);
const_expr *MK_const_expr1(const_expr *const_expr_a);
const_expr *MK_const_expr2(const_expr *const_expr_1_a,const_expr *const_expr_2_a,int n);
const_expr *MK_const_expr3(const_expr *const_expr_a);
const_expr *MK_const_expr4(int NUMBER);
const_expr *MK_const_expr5(const_id *const_id_a);
tCOMMA_e_expr_mais *MK_tCOMMA_e_expr_mais1(expr *expr_a);
tCOMMA_e_expr_mais *MK_tCOMMA_e_expr_mais2(expr *expr_a, tCOMMA_e_expr_mais *tCOMMA_e_expr_mais_a);
arit_expr *MK_arit_expr1(arit_expr *arit_expr_a,int n);
arit_expr *MK_arit_expr2(arit_expr *arit_expr_1_a,arit_expr *arit_expr_2_a,int n);
arit_expr *MK_arit_expr3(int NUMBER);
arit_expr *MK_arit_expr4(var_o_const_id *var_o_const_id_a);
arit_expr *MK_arit_expr5(use_array_var *use_array_var_a);
rel_expr *MK_rel_expr(arit_expr *arit_expr1_a,rel_op *rel_op_a,arit_expr *arit_expr2_a);
bool_expr *MK_bool_expr1(bool_expr *bool_expr_a,int n);
bool_expr *MK_bool_expr2(bool_expr *bool_expr_1_a,bool_expr *bool_expr_2_a,int n);
bool_expr *MK_bool_expr3(rel_expr *rel_expr_a);
expr *MK_expr(arit_expr *arit_expr_a);
tCOMMA_e_expr_ast *MK_tCOMMA_e_expr_ast(expr *expr_a,tCOMMA_e_expr_ast *tCOMMA_e_expr_ast_a);
expr_list *MK_expr_list(expr *expr_a,tCOMMA_e_expr_ast *tCOMMA_e_expr_ast_a);
expr_list_01 *MK_expr_list_01(expr_list *expr_list_a);
cond *MK_cond( bool_expr *bool_expr_a);
print_expr *MK_print_expr1( expr *expr_a);
print_expr *MK_print_expr2(char *STRING_L_a);
print_cmd *MK_print_cmd(print_expr_list *print_expr_list_a);
print_expr_list *MK_print_expr_list(print_expr *print_expr_a,tCOMMA_print_expr_ast *tCOMMA_print_expr_ast_a);
tCOMMA_print_expr_ast *MK_tCOMMA_print_expr_ast( print_expr *print_expr_a, tCOMMA_print_expr_ast *tCOMMA_print_expr_ast_a);
use_simple_var *MK_use_simple_var(var_id *var_id_a);
use_array_var *MK_use_array_var(var_id *var_id_a,expr_list *expr_list_a);
use_var *MK_use_var1(use_simple_var *use_simple_var_a);
use_var *MK_use_var2(use_array_var *use_array_var_a);
input_cmd *MK_input_cmd(use_var *use_var_a);
exit_loop_cmd *MK_exit_loop_cmd();
end_cmd *MK_end_cmd();
assignment_cmd *MK_assignment_cmd(use_var *use_var_a,expr *expr_a,int n);
var_decl_o_const_decl_o_cmd_ast *MK_var_decl_o_const_decl_o_cmd_ast1(var_decl *var_decl_a,var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast_a);
var_decl_o_const_decl_o_cmd_ast *MK_var_decl_o_const_decl_o_cmd_ast2(const_decl *const_decl_a,var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast_a);
var_decl_o_const_decl_o_cmd_ast *MK_var_decl_o_const_decl_o_cmd_ast3(cmd *cmd_a,var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast_a);
loop_until_cmd *MK_loop_until_cmd(var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast_a,cond *cond_a);
do_while_cmd *MK_do_while_cmd(cond *cond_a,var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast_a);
tSTEP_e_expr_01 *MK_tSTEP_e_expr_01(expr *expr_a);
for_cmd *MK_for_cmd(use_simple_var *use_simple_var_a,expr *expr1_a,expr *expr2_a,tSTEP_e_expr_01 *tSTEP_e_expr_01_a,var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast_a);
else_nl_01 *MK_else_nl_01(var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast_a);
if_cmd *MK_if_cmd(cond *cond_a,var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast_a,else_nl_01 *else_nl_01_a);
cmd *MK_cmd1(if_cmd *if_cmd_a);
cmd *MK_cmd2(for_cmd *for_cmd_a);
cmd *MK_cmd3(do_while_cmd *do_while_cmd_a);
cmd *MK_cmd4(loop_until_cmd *loop_until_cmd_a);
cmd *MK_cmd5(assignment_cmd *assignment_cmd_a);
cmd *MK_cmd6(end_cmd *end_cmd_a);
cmd *MK_cmd7(exit_loop_cmd *exit_loop_cmd_a);
cmd *MK_cmd8(input_cmd *input_cmd_a);
cmd *MK_cmd9(print_cmd *print_cmd_a);
const_decl *MK_const_decl(const_id *const_id_a,const_expr *const_expr_a);
tOSQR_e_expr_list_e_tCSQR_01 *MK_tOSQR_e_expr_list_e_tCSQR_01(expr_list *expr_list_a);
decl_var *MK_decl_var(var_id *var_id_a,tOSQR_e_expr_list_e_tCSQR_01 *tOSQR_e_expr_list_e_tCSQR_01_a);
tCOMMA_e_decl_var_ast *MK_tCOMMA_e_decl_var_ast(decl_var *decl_var_a,tCOMMA_e_decl_var_ast *tCOMMA_e_decl_var_ast_a);
decl_var_list *MK_decl_var_list(decl_var *decl_var_a,tCOMMA_e_decl_var_ast *tCOMMA_e_decl_var_ast_a);
var_decl *MK_var_decl(decl_var_list *decl_var_list_a);
prg *MK_prg1(var_decl *var_decl_a,prg *prg_a);
prg *MK_prg2(cmd *cmd_a,prg *prg_a);
prg *MK_prg3(const_decl *const_decl_a,prg *prg_a);
prg *MK_prg4(prg *prg_a);
start *MK_start(prg *prg_a);




struct start *root; // raiz da arvore
