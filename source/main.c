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

#include "sdl_chaste_checkerboard.h"


int main(int argc, char **argv)
{
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

 SDL_RenderPresent(renderer);



 while(loop)
 {



  while(SDL_PollEvent(&e))
  {

   if(e.type == SDL_QUIT){loop=0;}
   if(e.type == SDL_KEYUP)
   {
    if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}
   }

   if(e.type == SDL_MOUSEBUTTONDOWN)
   {
    SDL_SetRenderDrawColor(renderer,0xAA,0xAA,0xAA,255);
    SDL_RenderFillRect(renderer,NULL);
    SDL_SetRenderDrawColor(renderer,0x55,0x55,0x55,255);
    chaste_checker();

    x=e.button.x;
    y=e.button.y;

    /*printf("Mouse clicked at position X=%d Y=%d ",x,y);*/

    /*if(e.button.button==SDL_BUTTON_LEFT){printf("SDL_BUTTON_LEFT");}
    if(e.button.button==SDL_BUTTON_RIGHT){printf("SDL_BUTTON_RIGHT");}
    if(e.button.button==SDL_BUTTON_MIDDLE){printf("SDL_BUTTON_MIDDLE");}
    printf("\n");*/

    x1=x/main_check.rectsize;
    y1=y/main_check.rectsize;

    /*printf("Cartesian Square clicked: X=%d Y=%d\n",x1,y1);*/
    printf("Chess Square clicked: %c %d\n",'A'+x1,8-y1);

    rect.x=x1*main_check.rectsize;
    rect.y=y1*main_check.rectsize;
    rect.w=main_check.rectsize;
    rect.h=main_check.rectsize;

    SDL_SetRenderDrawColor(renderer,0x80,0x80,0x80,255);
    SDL_RenderFillRect(renderer,&rect);
    SDL_RenderPresent(renderer);

   }

  }


 }
 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 SDL_Quit();
 return 0;
}
