#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

int width=720,height=720;
int loop=1;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event e;
SDL_Rect rect;

/*mouse variables*/
int x,y,x1,y1;
int mouse_state=0;

/*keyboard variables*/
int kx=3,ky=3;
int keyboard_state=0;
int keyboard_shown=0;
SDL_Rect key_rect;

/*variables for the shades of gray used for checkerboard*/
int g0=0x55,g1=0xAA;


char text[0x200],text_scale=1;
int text_color=0xFF00FF;

SDL_Texture *texture;

#include "sdl_chaste_checkerboard.h"
#include "sdl_chaste_chess.h"
#include "sdl_chaste_chess_font_texture.h"
#include "sdl_chaste_chess_image.h"
#include "sdl_chaste_chess_graphics.h"
#include "sdl_chaste_chess_input.h"

int main(int argc, char **argv)
{
 init_main_grid();
 debug_castle();
 /*chess_grid_print();*/
 /*return 0;*/

 if(SDL_Init(SDL_INIT_VIDEO))
 {
  printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError());return -1;
 }
 window=SDL_CreateWindow("SDL Chaste Chess",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN );
 if(window==NULL){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}
 renderer = SDL_CreateRenderer(window,-1,0);
 if(renderer==NULL){printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}

 printf("SDL Program Compiled Correctly\n");

g0=0;g1=0xFF;

/*g0=0x40;g1=0xC0;*/

 /*first step is initializing the checkerboard that is drawn every frame of the game*/
 init_checkerboard();
 main_check.rectsize=height/8;
 printf("Square size of game board is %d\n",main_check.rectsize);

 x=IMG_Init(IMG_INIT_PNG);
 printf("IMG_Init: %d\n",x);

 /*image_fill("./image/Chessboard_720_Alpha.png");*/

 /*x=load_pieces("./image/Chessboard_720_Alpha.png");
 if(x){chess_grid_draw=chess_grid_draw_pieces;}*/

x=load_pieces("./image/winboard_mono_696_alpha.png");
 if(x){chess_grid_draw=chess_grid_draw_pieces;}






 /*SDL_SetRenderDrawColor(renderer,0x40,0x40,0x40,255);*/
 /*SDL_SetRenderDrawColor(renderer,0x80,0x80,0x80,255);*/
 /*SDL_SetRenderDrawColor(renderer,0xC0,0xC0,0xC0,255);*/

 SDL_SetRenderDrawColor(renderer,g1,g1,g1,255);
 SDL_RenderFillRect(renderer,NULL);
 SDL_SetRenderDrawColor(renderer,g0,g0,g0,255);
 chaste_checker();

 main_font=chaste_font_load("./font/FreeBASIC Font 8.bmp");

 text_scale=8;
 text_color=0x00FF00;

 /*sprintf(text,"Chaste\nChess");
 chaste_font_draw_string_scaled_alpha(text,100,100,text_scale);*/

 chess_grid_draw();

 SDL_RenderPresent(renderer);

 ps.id='0'; /*the id of the selected piece is '0' at the start of the game to signal that no piece is currently selected*/

 loop=1;
 while(loop)
 {

  /*the gameloop always starts with polling the input including mouse clicks.*/
  
  chaste_chess_check_input();


 }
 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 SDL_Quit();
 return 0;
}
