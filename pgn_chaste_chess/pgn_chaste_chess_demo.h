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
 move("Nf6");
}

/*
using the easy API that ignores standard notation

This example shows the Queen's Gambit Old Variation Trap where black defends the c4 pawn with b5. This puts black in a position of losing material one way or another. This example is good so I am keeping it.

*/
void pgn_chaste_chess_demo_2()
{
move_xy(3,6,3,4);
move_xy(3,1,3,3);
move_xy(2,6,2,4);
move_xy(3,3,2,4);
move_xy(4,6,4,5);
move_xy(1,1,1,3);
move_xy(0,6,0,4);
move_xy(2,1,2,2);
move_xy(0,4,1,3);
move_xy(2,2,1,3);
move_xy(3,7,5,5);
move_xy(1,0,2,2);
move_xy(5,5,2,2);

}

/* this example starts with queen's gambit but includes an en-passant.*/
void pgn_chaste_chess_demo_3()
{

move_xy(3,6,3,4);
move_xy(3,1,3,3);
move_xy(2,6,2,4);
move_xy(4,1,4,2);
move_xy(2,4,2,3);
move_xy(1,1,1,3);
move_xy(2,3,1,2);

}


/*
a replay of an actual game that happened

https://lichess.org/I1gkSCRJuPxD
*/

/* this example starts with queen's gambit but includes an en-passant.*/
void pgn_chaste_chess_demo_4()
{

move_xy(3,6,3,4);
move_xy(6,0,5,2);
move_xy(2,7,6,3);
move_xy(7,1,7,2);
move_xy(6,3,7,4);
move_xy(6,1,6,3);
move_xy(7,4,6,5);
move_xy(5,2,4,4);
move_xy(6,5,4,3);
move_xy(5,1,5,2);
move_xy(4,6,4,5);
move_xy(5,2,4,3);
move_xy(3,7,7,3);


}