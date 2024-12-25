/*pgn_chaste_chess_demo.h*/

void pgn_chaste_chess_demo()
{
 int x=0;
 char c=1;
 char demo_string[]="1. e4 e6 2. d4 d5 3. Nc3 Bb4";
 char *s=demo_string;
 char move[100];

 printf("%s\n\n",demo_string);

 c=*s;
 x=0;
 while(c!=0)
 {

  c=*s;

  /*if character is not space, add to move string*/
  if(!isspace(c))
  {
   move[x]=c;
   x++;
   /*printf("%c",c);*/
  }
  if(isspace(c)||c==0)
  {
   /*printf("\n");*/
   move[x]=0;
   x=0;

   /*printf("strlen(move)=%u\n",(int)strlen(move));*/

   if(move[1]!='.')
   {
    printf("move = %s\n",move);
   }
  }
  
  s++;

 }

 /*printf("last char = %d",c);*/

}





void pgn_chaste_chess_demo_1()
{
 move("d4");
 move("d5");
 move("c4");
}
