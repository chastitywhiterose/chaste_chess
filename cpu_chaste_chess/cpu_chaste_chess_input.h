/* cpu_chaste_chess_input.h */


void get_rank_and_file()
{
 if(view_flipped!=0)
 {
  square_rank=y+'1';
  square_file='H'-x;
 }
 else
 {
  square_rank='8'-y;
  square_file='A'+x;
 }
}

/*
 dummy function just to test if we can get the mouse and keyboard input correct
 prints to the terminal but has no effect on the actual game
*/
void chaste_chess_check_input_dummy()
{

while(SDL_PollEvent(&e))
  {

   if(e.type == SDL_QUIT){loop=0;}
   if(e.type == SDL_KEYUP)
   {
    if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}
   }

   mouse_state=0;

   if(e.type == SDL_MOUSEBUTTONDOWN)
   {
    x=e.button.x;
    y=e.button.y;
    mouse_state=1;
    keyboard_shown=0;

    if(x<check_left){printf("Mouse clicked too far left outside of board\n");return;}
    if(x>check_left+check_size){printf("Mouse clicked too far right outside of board\n");return;}

    /*printf("Mouse clicked at position X=%d Y=%d ",x,y);*/

    /*if(e.button.button==SDL_BUTTON_LEFT){printf("SDL_BUTTON_LEFT");}
    if(e.button.button==SDL_BUTTON_RIGHT){printf("SDL_BUTTON_RIGHT");}
    if(e.button.button==SDL_BUTTON_MIDDLE){printf("SDL_BUTTON_MIDDLE");}
    printf("\n");*/


    x=(x-check_left)/main_check.rectsize;
    y=y/main_check.rectsize;

    get_rank_and_file();


    printf("Cartesian Square clicked: X=%d Y=%d\n",x,y);
    printf("Chess Square clicked: %c%c\n",square_file,square_rank);
   }

  }

}


/*moves the piece by calling the new function which is defined in cpu_chaste_chess_moves.h*/
void move_piece()
{
 move_xy(ps.x,ps.y,x,y);
 init_highlight();
}

void chess_square_select()
{

  p=main_grid.array[x+y*8];

    p.x=x;
    p.y=y;

    /*print information on the square selected, including what piece.*/

    printf("%c%c: ",square_file,square_rank);

    if(p.id=='0')
    {
     printf("Blank Space\n");
    }
    else
    {

     if(p.color=='B'){printf("Black ");} 
     if(p.color=='W'){printf("White ");}

     if(p.id=='P'){printf("Pawn");}
     if(p.id=='R'){printf("Rook");}
     if(p.id=='N'){printf("kNight");}
     if(p.id=='B'){printf("Bishop");}
     if(p.id=='Q'){printf("Queen");}
     if(p.id=='K'){printf("King");}

     printf("\n");
    }
    /*printf(" %c%c",p.color,p.id);*/

 
   

    /*
	 no piece is selected. we will try to select this piece and check the moves it might make
     now that we know which square was clicked and what piece is there
     the major step is to highlight which squares it is possible to move it to
    */

		
 
	

        /*if the color of clicked piece is the same as who's turn it is, then we will selecte it and highlight the moves it can make*/
	if(p.color==turn && p.id!='0')
	{
		ps=p;
		printf("This piece has been selected for possible move\n");

		square_file_source=square_file;
		square_rank_source=square_rank;
		square_file_dest='?';
		square_rank_dest='?';


        init_highlight();
        check_moves_of_clicked_piece();
	}

/*special case for en passant*/
if(ps.id=='P' && en_passant.id=='P')
{
 int xdiff=0,ydiff=0;

 xdiff=abs(en_passant.x-ps.x);
 ydiff=en_passant.y-ps.y;

 /*printf("Difference between selected piece and en_passant mark is %d %d\n",xdiff,ydiff);*/


 /*this conditional makes sure that only the correct pawns capture on the en_passant square*/
 if(xdiff==1&&ydiff==dir)
 {

 if(x==en_passant.x && y==en_passant.y)
 {
  ps.moves++; /*must add to move counter for piece or pawns will not be correct*/

  move_piece();
  printf("Moving piece to valid space\n");



  /*
   the following two statements are commented out because move_piece takes care of them. I keep them for special legacy reasons though.
  */

  /*main_grid.array[x+y*8]=ps;*/ /*move piece to new square*/
  /*main_grid.array[ps.x+ps.y*8].id='0';*/ /*clear previous square*/
  /*swap_turn();*/

  main_grid.array[x+(y-dir)*8].id='0';

  en_passant.id='0';
  
  init_highlight();

  }

 }

}
/*end of en passant*/


/*special case for castling*/
if(p.id=='0'&&ps.id=='K')
{
 int xdiff=0,ydiff=0;
 int rx;

 xdiff=x-ps.x;
 ydiff=y-ps.y;

 printf("Difference between selected space and selected king is %d %d\n",xdiff,ydiff);

 if(xdiff==2&&ydiff==0)
 {
  rx=7;
  pt=main_grid.array[rx+y*8];
  if(pt.moves==0&&ps.moves==0)
  {
   main_grid.array[rx+y*8].id='0';
   rx=5;
   main_grid.array[rx+y*8]=pt;
   main_grid.array[ps.x+ps.y*8].id='0';
   ps.moves++;
   main_grid.array[x+y*8]=ps;
   swap_turn();
   init_highlight();
  }
 }

 if(xdiff==-2&&ydiff==0)
 {
  rx=0;
  pt=main_grid.array[rx+y*8];
  if(pt.moves==0&&ps.moves==0)
  {
   main_grid.array[rx+y*8].id='0';
   rx=3;
   main_grid.array[rx+y*8]=pt;
   main_grid.array[ps.x+ps.y*8].id='0';
   ps.moves++;
   main_grid.array[x+y*8]=ps;
   swap_turn();
   init_highlight();
  }
 }



}
/*end of castling*/

	
   if(p.color!=turn || p.id=='0')
   {
     /*
	 if piece has been selected previously
	 move it there if it has been highlighted as valid move!
	 */
	if(ps.id!='0')
	{
	 if(highlight[x+y*8]>0)
	 {
      move_piece();

      printf("Moving piece to valid space\n");



	 }
	 else
	 {
		 printf("piece can't move there\n");
	 }
	}
   }

      
	
 SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,255,0,255));
 chaste_checker();
 chess_grid_draw_highlight();
 chess_draw_pieces();

  /*draw_en_passant();*/

 SDL_UpdateWindowSurface(window);

}



















/*
 the real input function which has more code for specific cases and can affect the game
*/
void chaste_chess_check_input()
{

while(SDL_PollEvent(&e))
  {

   if(e.type == SDL_QUIT){loop=0;}
   if(e.type == SDL_KEYUP)
   {
    if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}
   }

   mouse_state=0;

   if(e.type == SDL_MOUSEBUTTONDOWN)
   {
    x=e.button.x;
    y=e.button.y;
    mouse_state=1;
    keyboard_shown=0;

    if(x<check_left){printf("Mouse clicked too far left outside of board\n");return;}
    if(x>check_left+check_size){printf("Mouse clicked too far right outside of board\n");return;}

    /*printf("Mouse clicked at position X=%d Y=%d ",x,y);*/

    /*if(e.button.button==SDL_BUTTON_LEFT){printf("SDL_BUTTON_LEFT");}
    if(e.button.button==SDL_BUTTON_RIGHT){printf("SDL_BUTTON_RIGHT");}
    if(e.button.button==SDL_BUTTON_MIDDLE){printf("SDL_BUTTON_MIDDLE");}
    printf("\n");*/


    x=(x-check_left)/main_check.rectsize;
    y=y/main_check.rectsize;

    get_rank_and_file();


    printf("Cartesian Square clicked: X=%d Y=%d\n",x,y);
    printf("Chess Square clicked: %c%c\n",square_file,square_rank);
   }

   if(mouse_state)
   {
    chess_square_select();
   }

  }

}