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
    if(ps.id=='0')
    {
		
	   draw_game_scene();
 
    init_highlight();
 
    check_moves_of_clicked_piece();

    chess_grid_draw_highlight();

    chess_grid_draw();

    SDL_RenderPresent(renderer);
	
     if(p.id!='0')
     {

	if(p.color==turn)
	{
		ps=p;
		printf("This piece has been selected for possible move\n");
	}
	
	if(p.color!=turn)
	{
		ps.id='0'; /*deselect piece*/
		printf("It is not this player's turn. This piece cannot be selected for move\n");
	}

      }
	
     }
	
    /*
	 piece has been selected previously
	 move it there if it has been highlighted as valid move!
	*/
	else
	{
	 if(highlight[x+y*8]>0)
	 {
          ps.moves++; /*must add to move counter for piece or pawns will not be correct*/
	  main_grid.array[x+y*8]=ps; /*move piece to new square*/
      main_grid.array[ps.x+ps.y*8].id='0'; /*clear previous square*/

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
	 }
	 else
	 {
		 ps.id='0';
		 printf("piece can't move there\n");
	 }
	 
     draw_game_scene();
     chess_grid_draw();
     SDL_RenderPresent(renderer);

	}
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

    key_rect_shown=1;
    key=e.key.keysym.sym;

   switch(key)
   {

    /*the main 4 directions*/
    case SDLK_UP:
    case SDLK_w:
     ky--;
     key_rect_shown=1;
    break;
    case SDLK_DOWN:
    case SDLK_s:
     ky++;
     key_rect_shown=1;
    break;
    case SDLK_LEFT:
    case SDLK_a:
     kx--;
     key_rect_shown=1;
    break;
    case SDLK_RIGHT:
    case SDLK_d:
     kx++;
     key_rect_shown=1;
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

  }

}