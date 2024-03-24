%{
  #include "gram.tab.h"
  //NL ((" ")*("\n"|":"))+
  //int LINE_PRG=0;
%}

LETRA [a-zA-Z]
DIGITO [0-9]



IDENTIFIER {LETRA}({LETRA}|{DIGITO}|"_")*
NUMBER_LITERAL 0|[1-9]{DIGITO}*
STRING_LITERAL "\""[^"\""]*"\""

NL [\n]+

SPACE [ \t]*
OTHER .


%%




END" "FUNCTION {/*printf("END_FUNCTION\n");*/return ENDFUNCTION;}
exit" "loop return EXITLOOP;
exit" "function return EXITFUNCTION;
exit" "sub return EXITSUB;
END" "SELECT return ENDSELECT;
CASE" "ELSE return CASEELSE;
end" "sub return ENDSUB;
END" "IF {/*printf("END_IF\n");*/return ENDIF;};
function {/*printf("FUNCTION\n")*/;return FUNCTION;}
integer return INTEGER;
declare return DECLARE;
string return STRING;
ubound return UBOUND;
select return SELECT;
STATIC return STATIC;
shared return SHARED;
ELSEIF return ELSEIF;
input {/*printf("INPUT\n");*/return INPUT;}
byval return BYVAL;
byref return BYREF;
print {/*printf("PRINT\n");*/return PRINT;}
WHILE return WHILE;
until return UNTIL;
call return CALL;
CASE return CASE;
CONST return CONST;
then return THEN;
LOOP {/*printf("encontrei LOOP:%s\n",yytext);*/return LOOP;}
step return STEP;
next return NEXT;
ELSE return ELSE;
FOR return FOR;
not return NOT;
sub return SUB;
dim {/*printf("DIM\n");*/return DIM;}
and return AND;
mod return MOD;
end return END;
let return LET;
DO {/*printf("DO\n");*/return DO;}
as return AS;
or return OR;
is return IS;
to return TO;
IF {/*printf("IF\n");*/return IF;}

"(" {/*printf("(\n");*/return OPAR;}
")" {/*printf(")\n");*/return CPAR;}
"[" {/*printf("[\n");*/return OSQR;}
"]" {/*printf("]\n");*/return CSQR;}
"," return COMMA;
"=" return EQ;
"<>" return NE;
"<=" return LE;
">=" return GE;
"<" return GT;
">" return LT;
"+" return PLUS;
"-" return MINUS;
"*" return MUL;
"/" return DIV;
":" {/*printf(":(NL)\n");*/return NL;}
{NL} {/*printf("NLwwn\n");*/return NL;}


{IDENTIFIER} {yylval.str =( char*) strdup(yytext);/*printf("IDENTIFIER %s\n",yytext);*/return IDENTIFIER;}
{STRING_LITERAL} {yylval.str =(char *) strdup(yytext);/*printf("STRING_LITERAL %s\n",yytext);*/return STRING_LITERAL;}
{NUMBER_LITERAL} {yylval.num = strdup(yytext);/*printf ("NUMBER_LITERAL %s\n",yytext);*/return NUMBER_LITERAL;}







%%
