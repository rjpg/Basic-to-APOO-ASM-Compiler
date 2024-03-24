#include <stdio.h>
#include "convert.h"


main(int argc, char **argv)
{
  if (argc == 1) 
    {printf("erro: falta de argumento (ficheiro output)\n");return;}
  printf (" ------- Start compilation ------- \n");
  printf("warning: opening file(%s)\n",argv[1]);
  apoo = fopen( argv[1], "w" );
  printf (" ------- Constroi abs-tree  ------- \n");
  yyparse();
  printf (" ------- Construida abs-tree  ------- \n");
  printf (" ------- Print abs-tree ------- \n");
  print_start(root,0);
  printf (" ------- Printed abs-tree  ------- \n");
  //printf (" ------- Print Inter-tree  ------- \n");
  //pr_stm(stdout, T_STM , 0);printf("\n");
  fclose(apoo);
  printf (" ------- End compilation ------- \n");


  return 0;
}
