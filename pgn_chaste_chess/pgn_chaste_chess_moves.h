void move(char *move)
{
 int x=-1,y=-1,x1,y1;
 char *p=move;
 struct chess_piece main_piece;


 printf("%s\n",move);

 /*move processing begin*/
 
 if(islower(*p))
 {
  printf("letter '%c' implies pawn move\n",*p);

  x=*p-'a';

  y=0;
  while(y<8)
  {
   main_piece=main_grid.array[x+y*8];
   if(main_piece.color==turn&&main_piece.id=='P'){break;}
   y++;
  }

  printf("coordinate of source pawn is: %d,%d\n",x,y);

  p++;

  if(isdigit(*p))
  {
   printf("number %c impies target location\n",*p);
  }

  x1=x;
  y1=8-(*p-'0');

  printf("destination for pawn is coord %d,%d\n", x1,y1);

  /*now perform the movement!*/

  main_grid.array[x+y*8].id='0';
  main_grid.array[x1+y1*8]=main_piece;

 }

 /*move processing end*/

 /*swap whose turn it is*/
  if(turn=='W')
  {
   turn='B';
  }
  else
  {
   turn='W';
  }
}
