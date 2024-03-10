/*
this file is where all of the code for checking input and calling other functions based on it occurs. This was done to reduce the size of main.c because it was large enough and unmanagable

however, these functions are by no means independent and uses tons of global variables defined in main.c
*/




void chess_square_select()
{
    p=main_grid.array[x+y*8];

    p.x=x;
    p.y=y;

    /*print information on the square selected, including what piece.*/

    printf("%c %d: ",'A'+x,8-y);

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

         init_highlight();
         check_moves_of_clicked_piece();
	}

/*special case for en passant*/
if(ps.id=='P' && en_passant.id=='P')
{
 if(x==en_passant.x && y==en_passant.y)
 {
  ps.moves++; /*must add to move counter for piece or pawns will not be correct*/
  main_grid.array[x+y*8]=ps; /*move piece to new square*/
  main_grid.array[ps.x+ps.y*8].id='0'; /*clear previous square*/

  main_grid.array[x+(y-dir)*8].id='0';

  en_passant.id='0';
  init_highlight(); /*clear highlights now that move is complete*/

  if(turn=='W')
  {
   turn='B';
   printf("White has moved. It is now Black's turn.\n");
  }
  else
  {
   turn='W';
   printf("Black has moved. It is now White's turn.\n");
  }

 }
}
	
	if(p.color!=turn || p.id=='0')
	{
		/*ps.id='0';*/ /*deselect piece*/
		printf("It is not this player's turn. This piece cannot be selected for move\n");

 /*
	 if piece has been selected previously
	 move it there if it has been highlighted as valid move!
	*/
	if(ps.id!='0')
	{
	 if(highlight[x+y*8]>0)
	 {
    ps.moves++; /*must add to move counter for piece or pawns will not be correct*/
	  main_grid.array[x+y*8]=ps; /*move piece to new square*/
      main_grid.array[ps.x+ps.y*8].id='0'; /*clear previous square*/

      if(x==ps.x && y==(ps.y+dir*2))
      {
       en_passant.id='P';
       en_passant.x=x;
       en_passant.y=ps.y+dir;
       printf("en_passant marked at %d,%d\n",en_passant.x,en_passant.y);
      }
      else
      {
       en_passant.id='0';
      }

      if(turn=='W')
      {
       turn='B';
       printf("White has moved. It is now Black's turn.\n");
      }
      else
      {
       turn='W';
       printf("Black has moved. It is now White's turn.\n");
      }

    	 printf("Piece moved to %d,%d\n", x,y );
	  ps.id='0'; /*deselect piece after move*/
    init_highlight(); /*clear highlights now that move is complete*/
	 }
	 else
	 {
		 ps.id='0';
		 printf("piece can't move there\n");
	 }
	 
	}
    
	}

      
	

	
   

  draw_game_scene();
  chess_grid_draw_highlight();
  /*draw_en_passant();*/
  chess_grid_draw();

  SDL_RenderPresent(renderer);

}








void chaste_chess_check_input()
{
 int key;

while(SDL_PollEvent(&e))
  {

   if(e.type == SDL_QUIT){loop=0;}
   if(e.type == SDL_KEYUP)
   {
    if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}
    if(e.key.keysym.sym==SDLK_r)
    {
     init_main_grid();
     turn='W';
     draw_game_scene();
     chess_grid_draw();
     SDL_RenderPresent(renderer);
    }

    keyboard_state=0;
    key=e.key.keysym.sym;

   switch(key)
   {

    /*the main 4 directions*/
    case SDLK_UP:
    case SDLK_w:
     ky--;
     keyboard_shown=1;
    break;
    case SDLK_DOWN:
    case SDLK_s:
     ky++;
     keyboard_shown=1;
    break;
    case SDLK_LEFT:
    case SDLK_a:
     kx--;
     keyboard_shown=1;
    break;
    case SDLK_RIGHT:
    case SDLK_d:
     kx++;
     keyboard_shown=1;
    break;


    case SDLK_z:
     
    break;

    case SDLK_x:
     x=kx;
     y=ky;
     chess_square_select();
    break;

   }


 if(kx<0){kx=7;}
 if(ky<0){kx=7;}
 if(kx>=8){kx=0;}
 if(ky>=8){ky=0;}


  }


   mouse_state=0;

   if(e.type == SDL_MOUSEBUTTONDOWN)
   {
    x=e.button.x;
    y=e.button.y;
    mouse_state=1;

    /*printf("Mouse clicked at position X=%d Y=%d ",x,y);*/

    /*if(e.button.button==SDL_BUTTON_LEFT){printf("SDL_BUTTON_LEFT");}
    if(e.button.button==SDL_BUTTON_RIGHT){printf("SDL_BUTTON_RIGHT");}
    if(e.button.button==SDL_BUTTON_MIDDLE){printf("SDL_BUTTON_MIDDLE");}
    printf("\n");*/

    x=x/main_check.rectsize;
    y=y/main_check.rectsize;

    printf("Cartesian Square clicked: X=%d Y=%d\n",x,y);
    /*printf("Chess Square clicked: %c %d\n",'A'+x,8-y);*/
   }

   if(mouse_state)
   {
    chess_square_select();
   }

   if(keyboard_shown)
   {
    draw_game_scene();
    chess_grid_draw_highlight();
    /*draw_en_passant();*/
    chess_grid_draw();

    /*draw outline of cursor controlled by keyboard*/
    key_rect.x=kx*main_check.rectsize;
    key_rect.y=ky*main_check.rectsize;
    key_rect.w=main_check.rectsize;
    key_rect.h=main_check.rectsize;
    SDL_SetRenderDrawColor(renderer,0xFF,0x00,0xFF,255);
    SDL_RenderDrawRect(renderer,&key_rect);

    /*draw X with two lines for additional visibility*/
    SDL_RenderDrawLine(renderer,key_rect.x, key_rect.y, key_rect.x+main_check.rectsize, key_rect.y+main_check.rectsize);
    SDL_RenderDrawLine(renderer,key_rect.x, key_rect.y+main_check.rectsize, key_rect.x+main_check.rectsize, key_rect.y);

    SDL_RenderPresent(renderer);
   }

  }

}