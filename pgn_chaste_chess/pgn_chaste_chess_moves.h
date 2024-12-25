/*
redraw the screen after the move
*/

void move_render()
{
 SDL_SetRenderDrawColor(renderer,0,0,0,255);
 SDL_RenderFillRect(renderer,NULL);
 chaste_checker();
 chess_draw_pieces();
 SDL_RenderPresent(renderer);
}


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

 chess_grid_print();
 move_render();
}






void move_xy(int x,int y,int x1,int y1)
{
 int x_src,y_src,x_dst,y_dst;
 struct chess_piece main_piece;

  main_piece=main_grid.array[x+y*8];
  main_grid.array[x+y*8].id='0';


x_src=check_left+x*main_check.rectsize;
y_src=y*main_check.rectsize;
x_dst=check_left+x1*main_check.rectsize;
y_dst=y1*main_check.rectsize; 

printf("From pixel location %d,%d\n",x_src,y_src);
printf("To pixel location %d,%d\n",x_dst,y_dst);

x_step=x1-x;
y_step=y1-y;
printf("x_step = %d y_step = %d\n",x_step,y_step);

 rect_src.x=0;
 rect_src.y=0;
 rect_src.w=t_rect_size;
 rect_src.h=t_rect_size;

 rect_dst.x=x_src;
 rect_dst.y=y_src;
 rect_dst.w=t_rect_size;
 rect_dst.h=t_rect_size;

 delay=100;

 while(rect_dst.x!=x_dst || rect_dst.y!=y_dst)
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;

  rect_dst.x+=x_step;
  rect_dst.y+=y_step;

  /*printf("rectangle at = %d,%d\n",rect_dst.x,rect_dst.y);*/


    /*beginning of piece source selection*/
    if(main_piece.color=='B')
    {
     if(main_piece.id=='P')
     {
      texture=pawn_black;
     }
     if(main_piece.id=='R')
     {
      texture=rook_black;
     }
     if(main_piece.id=='N')
     {
      texture=knight_black;
     }
     if(main_piece.id=='B')
     {
      texture=bishop_black;
     }
     if(main_piece.id=='Q')
     {
      texture=queen_black;
     }
     if(main_piece.id=='K')
     {
      texture=king_black;
     }
    }

    if(main_piece.color=='W')
    {
     if(main_piece.id=='P')
     {
      texture=pawn_white;
     }
     if(main_piece.id=='R')
     {
      texture=rook_white;
     }
     if(main_piece.id=='N')
     {
      texture=knight_white;
     }
     if(main_piece.id=='B')
     {
      texture=bishop_white;
     }
     if(main_piece.id=='Q')
     {
      texture=queen_white;
     }
     if(main_piece.id=='K')
     {
      texture=king_white;
     }
    }
    /*end of piece source selection*/

  /*move_render();*/
  SDL_RenderCopy(renderer, texture, &rect_src, &rect_dst);
  SDL_RenderPresent(renderer);

  /*time loop used to slow the game down so users can see it*/
  while(sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
  }

 }


  main_grid.array[x1+y1*8]=main_piece;
  move_render();


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





 chess_grid_print();



}
