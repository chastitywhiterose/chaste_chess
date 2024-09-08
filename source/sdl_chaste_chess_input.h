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

    printf("%c%d: ",square_file,square_rank);

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
  main_grid.array[x+y*8]=ps; /*move piece to new square*/
  main_grid.array[ps.x+ps.y*8].id='0'; /*clear previous square*/

  main_grid.array[x+(y-dir)*8].id='0';

  en_passant.id='0';
  swap_turn();
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
    ps.moves++; /*must add to move counter for piece or pawns will not be correct*/
	  main_grid.array[x+y*8]=ps; /*move piece to new square*/
      main_grid.array[ps.x+ps.y*8].id='0'; /*clear previous square*/

x1=ps.x*main_check.rectsize;
y1=ps.y*main_check.rectsize;
x2=x*main_check.rectsize;
y2=y*main_check.rectsize;


printf("Moving Piece %c\n",ps.id);
printf("From pixel location %d,%d\n",x1,y1);
printf("To pixel location %d,%d\n",x2,y2);

x_step=x-ps.x;
y_step=y-ps.y;
printf("x_step = %d y_step = %d\n",x_step,y_step);

/*beginning of slide animation*/

 rect.x=x1;
 rect.y=y1;
 rect.w=main_check.rectsize;
 rect.h=main_check.rectsize;

 while(rect.x!=x2 || rect.y!=y2)
 {
  rect.x+=x_step;
  rect.y+=y_step;
  printf("rectangle at = %d,%d\n",rect.x,rect.y);
 }

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

      swap_turn();

    	 printf("Piece moved to %d,%d\n", x,y );
	  ps.id='0'; /*deselect piece after move*/
    init_highlight(); /*clear highlights now that move is complete*/
	 }
	 else
	 {
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
     view_flipped=0;
     draw_game_scene();
     chess_grid_draw();
     SDL_RenderPresent(renderer);
    }





    /*next section deals with controlling the game with the keyboard*/
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

    case SDLK_v:
     flip_main_grid();
     draw_game_scene();
     chess_grid_draw();
     SDL_RenderPresent(renderer);
    break;

   /*keys after this are for managing save states*/

     
    case SDLK_i:
     save_gamesave();
    break;
    case SDLK_p:
     load_gamesave();
    break;
    
   case SDLK_0:
    save_index=0;
    printf("State %d selected.\n",save_index);
   break;
   case SDLK_1:
    save_index=1;
    printf("State %d selected.\n",save_index);
   break;
   case SDLK_2:
    save_index=2;
    printf("State %d selected.\n",save_index);
   break;
   case SDLK_3:
    save_index=3;
    printf("State %d selected.\n",save_index);
   break;
  case SDLK_4:
   save_index=4;
   printf("State %d selected.\n",save_index);
   break;
  case SDLK_5:
   save_index=5;
   printf("State %d selected.\n",save_index);
  break;
  case SDLK_6:
   save_index=6;
   printf("State %d selected.\n",save_index);
  break;
  case SDLK_7:
   save_index=7;
   printf("State %d selected.\n",save_index);
  break;
  case SDLK_8:
   save_index=8;
   printf("State %d selected.\n",save_index);
  break;
  case SDLK_9:
   save_index=9;
   printf("State %d selected.\n",save_index);
  break;
    
    /*end of save state managing keys*/
   }

 /*if a save state was loaded, redraw the entire screen just like we do if it is reset with the 'R' key */
 if(load_flag==1)
 {
  draw_game_scene();
  chess_grid_draw();
  SDL_RenderPresent(renderer);
  load_flag=0; /*set the load flag to default of 0*/
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

    

    if(view_flipped!=0)
    {
     square_rank=y+1;
     square_file='H'-x;
    }
    else
    {
     square_rank=8-y;
     square_file='A'+x;
    }

    printf("Cartesian Square clicked: X=%d Y=%d\n",x,y);
    printf("Chess Square clicked: %c%d\n",square_file,square_rank);
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
    key_rect.x=kx*main_check.rectsize+check_left;
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