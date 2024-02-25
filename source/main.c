#include <stdio.h>
#include <SDL.h>

int width=720,height=720;
int loop=1;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event e;
SDL_Rect rect;

int x,y,x1,y1;
int mouse_state;

char text[0x200],text_scale=1;
int text_color=0xFF00FF;

#include "sdl_chaste_checkerboard.h"
#include "sdl_chaste_chess.h"
#include "sdl_chaste_chess_font_texture.h"
#include "sdl_chaste_chess_graphics.h"

int main(int argc, char **argv)
{

 init_main_grid();
 /*chess_grid_print();*/
 /*return 0;*/

 if(SDL_Init(SDL_INIT_VIDEO))
 {
  printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError());return -1;
 }
 window=SDL_CreateWindow("Chaste Chess",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN );
 if(window==NULL){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}
 renderer = SDL_CreateRenderer(window,-1,0);
 if(renderer==NULL){printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}

 printf("SDL Program Compiled Correctly\n");

 init_checkerboard();
 main_check.rectsize=height/8;

 /*SDL_SetRenderDrawColor(renderer,0x40,0x40,0x40,255);*/
 /*SDL_SetRenderDrawColor(renderer,0x80,0x80,0x80,255);*/
 /*SDL_SetRenderDrawColor(renderer,0xC0,0xC0,0xC0,255);*/

 SDL_SetRenderDrawColor(renderer,0xAA,0xAA,0xAA,255);
 SDL_RenderFillRect(renderer,NULL);
 SDL_SetRenderDrawColor(renderer,0x55,0x55,0x55,255);
 chaste_checker();

 main_font=chaste_font_load("./font/FreeBASIC Font 8.bmp");

 text_scale=8;
 text_color=0x00FF00;

 /*sprintf(text,"Chaste\nChess");
 chaste_font_draw_string_scaled_alpha(text,100,100,text_scale);*/

 chess_grid_draw_text();

 SDL_RenderPresent(renderer);

 ps.id='0'; /*the id of the selected piece is '0' at the start of the game to signal that no piece is currently selected*/

 loop=1;
 while(loop)
 {

  /*the gameloop always starts with polling the input including mouse clicks.*/
  
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
     chess_grid_draw_text();
     SDL_RenderPresent(renderer);
    }
   }




   if(e.type == SDL_MOUSEBUTTONDOWN)
   {
    x=e.button.x;
    y=e.button.y;

    /*printf("Mouse clicked at position X=%d Y=%d ",x,y);*/

    /*if(e.button.button==SDL_BUTTON_LEFT){printf("SDL_BUTTON_LEFT");}
    if(e.button.button==SDL_BUTTON_RIGHT){printf("SDL_BUTTON_RIGHT");}
    if(e.button.button==SDL_BUTTON_MIDDLE){printf("SDL_BUTTON_MIDDLE");}
    printf("\n");*/

    x=x/main_check.rectsize;
    y=y/main_check.rectsize;

    printf("Cartesian Square clicked: X=%d Y=%d\n",x,y);
    /*printf("Chess Square clicked: %c %d\n",'A'+x,8-y);*/

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

    chess_grid_draw_text();

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
     chess_grid_draw_text();
     SDL_RenderPresent(renderer);

	}

   }

  }


 }
 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 SDL_Quit();
 return 0;
}
