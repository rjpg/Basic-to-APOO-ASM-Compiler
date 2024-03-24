%{
  
#include <stdio.h>
#include "estr.h"
#include "hash.h"
  
#define YYERROR_VERBOSE
  
  // struct start *root; // raiz da arvore
  
  void yyerror(char *);
  int yylex();  

  int LINE_PRG=1;  
%}

%start start

%union{
  char *str;
  int num;
  struct prg *prg;
  struct var_decl *var_decl;
  struct decl_var_list *decl_var_list_;
  struct tCOMMA_e_decl_var_ast *tCOMMA_e_decl_var_ast;
  struct decl_var *decl_var;
  struct tOSQR_e_expr_list_e_tCSQR_01 *tOSQR_e_expr_list_e_tCSQR_01;
  struct const_decl *const_decl;
  struct cmd *cmd;
  struct if_cmd *if_cmd;
  struct else_nl_01 *else_nl_01;
  struct for_cmd *for_cmd;
  struct tSTEP_e_expr_01 *tSTEP_e_expr_01;
  struct do_while_cmd *do_while_cmd;
  struct loop_until_cmd *loop_until_cmd;
  struct var_decl_o_const_decl_o_cmd_ast *var_decl_o_const_decl_o_cmd_ast;
  struct assignment_cmd *assignment_cmd;
  struct end_cmd *end_cmd;
  struct exit_loop_cmd *exit_loop_cmd;
  struct input_cmd *input_cmd;
  struct use_var *use_var;
  struct use_array_var *use_array_var;
  struct use_simple_var *use_simple_var;
  struct tCOMMA_print_expr_ast *tCOMMA_print_expr_ast;
  struct print_expr_list *print_expr_list;
  struct print_cmd *print_cmd;
  struct print_expr *print_expr;
  struct cond *cond;
  struct expr_list_01 *expr_list_01;
  struct expr_list *expr_list;
  struct tCOMMA_e_expr_ast *tCOMMA_e_expr_ast;
  struct expr *expr;
  struct bool_expr *bool_expr;
  struct rel_expr *rel_expr;
  struct arit_expr *arit_expr;
  struct tCOMMA_e_expr_mais *tCOMMA_e_expr_mais;
  struct const_expr *const_expr;
  struct rel_op *rel_op;
  struct var_o_const_id *var_o_const_id;
  struct const_id *const_id;
  struct var_id *var_id;
  struct start *start;
};



%token NL
%token COMMENT
%token OPAR
%token CPAR
%token OSQR
%token CSQR
 
%token COMMA

%token EQ
%token NE
%token LT
%token GT
%token LE
%token GE
 
%token NOT
%token AND
%token OR

%token PLUS
%token MINUS
%token MUL
%token DIV
%token MOD
 
%token STRING_LITERAL
%token NUMBER_LITERAL

%token STRING
%token INTEGER
 
%token TYPE
%token AS
%token LET
%token DIM
%token STATIC
%token SHARED
%token CONST

%token BYVAL
%token BYREF

%token IF
%token ENDIF
%token ELSEIF
%token ELSE
%token THEN

%token SELECT
%token ENDSELECT
%token CASE
%token CASEELSE
%token IS

%token FOR
%token TO
%token STEP
%token NEXT

%token DO
%token WHILE
%token LOOP
%token UNTIL
%token EXITLOOP

%token DECLARE

%token END
%token CALL
%token FUNCTION
%token ENDFUNCTION
%token EXITFUNCTION

%token SUB
%token ENDSUB
%token EXITSUB
%token PRINT
%token INPUT
%token IDENTIFIER

%token UBOUND

%type <str> STRING_LITERAL
%type <str> IDENTIFIER
%type <num> NUMBER_LITERAL
%type <prg> program
%type <var_decl> variable_decl
%type <decl_var_list_> declared_variable_list
%type <tCOMMA_e_decl_var_ast> tCOMMA_e_declared_variable_ast 
%type <decl_var> declared_variable
%type <tOSQR_e_expr_list_e_tCSQR_01> tOSQR_e_expression_list_e_tCSQR_01
%type <const_decl> constant_decl
%type <cmd> command
%type <if_cmd> if_command
%type <else_nl_01> else_nl_01
%type <for_cmd> for_command
%type <tSTEP_e_expr_01> tSTEP_e_expression_01
%type <do_while_cmd> do_while_command
%type <loop_until_cmd> loop_until_command
%type <var_decl_o_const_decl_o_cmd_ast>variable_decl_ou_constant_decl_ou_command_ast
%type <assignment_cmd> assignment_command
%type <end_cmd> end_command
%type <exit_loop_cmd> exit_loop_command
%type <input_cmd> input_command
%type <use_var> using_variable
%type <use_array_var> using_array_variable
%type <use_simple_var> using_simple_variable
%type <tCOMMA_print_expr_ast> tCOMMA_print_expression_ast
%type <print_expr_list> print_expression_list
%type <print_cmd> print_command
%type <print_expr> print_expression
%type <cond> condition
%type <expr_list_01> expression_list_01
%type <expr_list> expression_list
%type <tCOMMA_e_expr_ast> tCOMMA_e_expression_ast
%type <expr> expression
%type <bool_expr> boolean_expression
%type <rel_expr> relational_expression
%type <arit_expr> arithmetic_expression
                  
%type <tCOMMA_e_expr_mais> tCOMMA_e_expression_mais
%type <const_expr> constant_expression
%type <rel_op> relational_op
%type <var_o_const_id> var_or_const_identifier
%type <const_id> const_identifier
%type <var_id> var_identifier
%type <start> start

%left AND OR
%left LT GT EQ NE LE GE
%left MINUS PLUS
%left MUL DIV MOD

%nonassoc NEG



%%
nl:NL {LINE_PRG++;};

start : program {root = MK_start($1);}
;

program : /*vazio */ { $$ = NULL;}
| variable_decl program { $$ = MK_prg1($1,$2);}
| command program {$$ =MK_prg2($1,$2);}
| constant_decl program {$$ =MK_prg3($1,$2);}
| nl program {$$ = MK_prg4($2);}
;

variable_decl: DIM declared_variable_list nl { $$ = MK_var_decl($2);}
;

declared_variable_list: declared_variable tCOMMA_e_declared_variable_ast {$$=MK_decl_var_list($1,$2);}
;

//{COMMA declared_variable}* 
tCOMMA_e_declared_variable_ast: {$$=NULL;}//vazio
| COMMA declared_variable tCOMMA_e_declared_variable_ast {$$=MK_tCOMMA_e_decl_var_ast($2,$3);}
;


declared_variable: var_identifier tOSQR_e_expression_list_e_tCSQR_01 {

 Hash *s;
  if((s = pesquisa($1->id)) == NULL)
    insert($1->id);
  else
    printf("warning(%d): variável \"%s\" já declarada!\n",LINE_PRG,$1->id);
  //printf("bison (237): %s\n",$1->id);

$$=MK_decl_var($1,$2);   
}
  
;

//{OSQR expression_list CSQR}?
tOSQR_e_expression_list_e_tCSQR_01: {$$=NULL;}
| OSQR expression_list CSQR { $$=MK_tOSQR_e_expr_list_e_tCSQR_01($2);}
;

constant_decl: CONST const_identifier EQ constant_expression nl 
{
  Hash *s;
  if((s = pesquisa($2->id)) == NULL)
    insert($2->id);
  else
    printf("warning(%d): constant \"%s\" já declarada!\n",LINE_PRG-1,$2->id);
  
  $$=MK_const_decl($2,$4);}
;

command: if_command { $$=MK_cmd1($1); }
| for_command { $$=MK_cmd2($1);}
       | do_while_command { $$=MK_cmd3($1);}
       | loop_until_command{ $$=MK_cmd4($1);}
       | assignment_command{ $$=MK_cmd5($1);}
       | end_command { $$=MK_cmd6($1);}
       | exit_loop_command { $$=MK_cmd7($1);}
       | input_command { $$=MK_cmd8($1);}
       | print_command { $$=MK_cmd9($1);}
;

if_command : IF condition THEN nl variable_decl_ou_constant_decl_ou_command_ast else_nl_01 ENDIF nl {$$=MK_if_cmd($2,$5,$6);}
;

else_nl_01 : ELSE nl variable_decl_ou_constant_decl_ou_command_ast {$$=MK_else_nl_01($3);}
| {$$=NULL;}
;

for_command: FOR using_simple_variable EQ expression TO expression tSTEP_e_expression_01 nl
             variable_decl_ou_constant_decl_ou_command_ast
NEXT nl {

  Hash *s;
  if((s = pesquisa($2->var_id->id)) == NULL)
    {
      insert($2->var_id->id);
      printf ("warning(%d): variavel \"%s\" nao declarada (for cmd)\n",LINE_PRG-1,$2->var_id->id);
    }  
$$=MK_for_cmd($2,$4,$6,$7,$9);}
;

//{STEP expression}
tSTEP_e_expression_01: {$$=NULL;}// vazio
| STEP expression {$$=MK_tSTEP_e_expr_01($2);}
;


do_while_command: DO WHILE condition nl 
                  variable_decl_ou_constant_decl_ou_command_ast
LOOP nl {$$=MK_do_while_cmd($3,$5);}
;

loop_until_command: DO nl variable_decl_ou_constant_decl_ou_command_ast LOOP UNTIL condition nl {$$=MK_loop_until_cmd($3,$6);}
;

variable_decl_ou_constant_decl_ou_command_ast: {$$=NULL;}//vazio
|variable_decl variable_decl_ou_constant_decl_ou_command_ast {$$=MK_var_decl_o_const_decl_o_cmd_ast1($1,$2);}
|constant_decl variable_decl_ou_constant_decl_ou_command_ast {$$=MK_var_decl_o_const_decl_o_cmd_ast2($1,$2);}
|command variable_decl_ou_constant_decl_ou_command_ast {$$=MK_var_decl_o_const_decl_o_cmd_ast3($1,$2);}
					     ;




assignment_command: using_variable EQ expression nl {$$=MK_assignment_cmd($1,$3,1);}
| LET using_variable EQ expression nl {$$=MK_assignment_cmd($2,$4,2);}
;

end_command: END nl {$$=MK_end_cmd();}
;

exit_loop_command: EXITLOOP nl {$$=MK_exit_loop_cmd();}
;

input_command: INPUT using_variable nl {$$=MK_input_cmd($2);}
;

using_variable: using_simple_variable {$$=MK_use_var1($1);}
| using_array_variable {$$=MK_use_var2($1);}
;

using_array_variable: var_identifier OSQR expression_list CSQR {$$=MK_use_array_var($1,$3);}
;

using_simple_variable: var_identifier {$$=MK_use_simple_var($1);}
;

print_command: PRINT print_expression_list nl {$$=MK_print_cmd($2);}
;

print_expression_list: print_expression tCOMMA_print_expression_ast {$$=MK_print_expr_list($1,$2);}
;

tCOMMA_print_expression_ast: {$$=NULL;}
| COMMA print_expression tCOMMA_print_expression_ast {$$=MK_tCOMMA_print_expr_ast($2,$3);}
			   ;

print_expression: expression {$$=MK_print_expr1($1);}
| STRING_LITERAL {$$=MK_print_expr2($1);}
;


condition: boolean_expression {$$=MK_cond($1);}
;

expression_list: expression tCOMMA_e_expression_ast {$$=MK_expr_list($1,$2);}
;

//{COMMA expression}*
tCOMMA_e_expression_ast: {$$=NULL;}//vazio
| COMMA expression tCOMMA_e_expression_ast {$$=MK_tCOMMA_e_expr_ast($2,$3);}
;

expression: arithmetic_expression {$$=MK_expr($1);}
;

boolean_expression: NOT boolean_expression %prec NEG {$$=MK_bool_expr1($2,1);}
| boolean_expression AND boolean_expression {$$=MK_bool_expr2($1,$3,1);}
                  | boolean_expression OR boolean_expression{$$=MK_bool_expr2($1,$3,2);}
                  | relational_expression {$$=MK_bool_expr3($1);}
                  | OPAR boolean_expression CPAR {$$=MK_bool_expr1($2,2);}
		  ;

relational_expression: arithmetic_expression relational_op arithmetic_expression {$$=MK_rel_expr($1,$2,$3);}
;

arithmetic_expression: MINUS arithmetic_expression %prec NEG {$$=MK_arit_expr1($2,1);}
                     | arithmetic_expression MUL arithmetic_expression {$$=MK_arit_expr2($1,$3,1);}
                     | arithmetic_expression DIV arithmetic_expression {$$=MK_arit_expr2($1,$3,2);}
                     | arithmetic_expression MINUS arithmetic_expression {$$=MK_arit_expr2($1,$3,4);}
                     | arithmetic_expression PLUS arithmetic_expression {$$=MK_arit_expr2($1,$3,5);}
                     | arithmetic_expression MOD arithmetic_expression {$$=MK_arit_expr2($1,$3,3);}
                     | OPAR arithmetic_expression CPAR {$$=MK_arit_expr1($2,2);}
                     | NUMBER_LITERAL {$$=MK_arit_expr3($1);}
                     | var_or_const_identifier {$$=MK_arit_expr4($1);}
                     | using_array_variable {$$=MK_arit_expr5($1);}
;

//{COMMA expression}+
tCOMMA_e_expression_mais: COMMA expression {$$=MK_tCOMMA_e_expr_mais1($2);}
                        | COMMA expression tCOMMA_e_expression_mais {$$=MK_tCOMMA_e_expr_mais2($2,$3);}
;

//{expression_list}?
expression_list_01: {$$=NULL;}//vazio
| expression_list {$$=MK_expr_list_01($1);}
;

constant_expression: MINUS constant_expression {$$=MK_const_expr1($2);}
| constant_expression MUL constant_expression {$$=MK_const_expr2($1,$3,1); }
| constant_expression DIV constant_expression {$$=MK_const_expr2($1,$3,2);}
| constant_expression MOD constant_expression {$$=MK_const_expr2($1,$3,3);}
| constant_expression MINUS constant_expression {$$=MK_const_expr2($1,$3,4);}
| constant_expression PLUS constant_expression {$$=MK_const_expr2($1,$3,5);}
| OPAR constant_expression CPAR {$$=MK_const_expr3($2);}
| NUMBER_LITERAL {$$=MK_const_expr4($1);}
| const_identifier {$$=MK_const_expr5($1);}
;

relational_op: EQ {$$=MK_rel_op("EQ")}
| NE {$$=MK_rel_op("NE")}
| LT {$$=MK_rel_op("LT")}
| GT {$$=MK_rel_op("GT")}
| LE {$$=MK_rel_op("LE")}
| GE {$$=MK_rel_op("GE")}
;

const_identifier: IDENTIFIER {$$ = MK_const_id($1)}
;

var_identifier: IDENTIFIER {$$ = MK_var_id($1)}
;

var_or_const_identifier: IDENTIFIER {$$ = MK_var_o_const_id($1)}
;

%%
/*
int main()
{
   yyparse();
   printf("\n Programa reconhecido:FIM\n");
   return 0;
}
*/

void yyerror(char *s)
{
  printf("erro(%d): %s\n",LINE_PRG,s);
  exit (-1);
}

