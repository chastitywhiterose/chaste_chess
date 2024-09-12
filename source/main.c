#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

int width=1280,height=720;
int loop=1;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event e;
SDL_Rect rect,rect_dst,rect_src;

/*location of checkerboard variables*/
/*these are initialized to random values to be fixed later*/
int check_left=0,check_top=0,check_size=720;

/*mouse and coordinate variables*/
int x,y,x1,y1,x2,y2;
int mouse_state=0;

/*variables for possible piece slide animation*/
int x_step,y_step;
int sdl_time,sdl_time1,delay,fps=60;

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

/*chess notation variables*/
int square_file; /*A to H*/
int square_rank; /*1 to 8*/

int square_file_source; /*A to H*/
int square_rank_source; /*1 to 8*/

int square_file_dest; /*A to H*/
int square_rank_dest; /*1 to 8*/


/*
 large array to store moves
 each move is stored as 6 bytes as follows

 [0] ID of the source piece
 [1] File of the Source Square
 [2] Rank of the Source Square
 [3] ID of the Destination piece
 [4] File of the Destination Square
 [5] Rank of the Destination Square

However, the code to manage this is far from complete!

*/



char move_log[0x1000000];
int move_index=0;

#include "sdl_chaste_checkerboard.h"
#include "sdl_chaste_chess.h"
#include "sdl_chaste_chess_gamesave.h"
#include "sdl_chaste_chess_font_texture.h"
#include "sdl_chaste_chess_image.h"
#include "sdl_chaste_chess_graphics.h"
#include "sdl_chaste_chess_input.h"

int main(int argc, char **argv)
{
 init_main_grid();
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

/*g0=0;g1=0xFF;*/

 g0=0x40;g1=0xC0;

 /*first step is initializing the checkerboard that is drawn every frame of the game*/
 init_checkerboard();

 main_check.rectsize=height/8;

 check_size=main_check.rectsize*8;

 check_left=(width-check_size)/2;
 check_top=0;


 main_check.x_begin=check_left;
 main_check.y_begin=check_top;
 main_check.x_end=main_check.x_begin+main_check.rectsize*8;
 main_check.y_end=height;


 printf("Square size of game board is %d\n",main_check.rectsize);

 x=IMG_Init(IMG_INIT_PNG);
 printf("IMG_Init: %d\n",x);

 /*image_fill("./image/Chessboard_720_Alpha.png");*/

 x=0;

 x=load_pieces("./image/Chastity Chess Set Merida 720_alpha.png");

 if(x) /*if load was successful, change the function pointer to draw pieces instead of letters*/
 {
  chess_grid_draw=chess_grid_draw_pieces;
  /*g0=0;g1=0xFF;*/
 }








 /*SDL_SetRenderDrawColor(renderer,0x40,0x40,0x40,255);*/
 /*SDL_SetRenderDrawColor(renderer,0x80,0x80,0x80,255);*/
 /*SDL_SetRenderDrawColor(renderer,0xC0,0xC0,0xC0,255);*/

 SDL_SetRenderDrawColor(renderer,0,0,0,255);
 SDL_RenderFillRect(renderer,NULL);

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
