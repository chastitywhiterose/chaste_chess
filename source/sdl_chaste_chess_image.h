/*
the purpose of this source file is to manage loading an image which contains the pieces for a chessboard
it only works according to the one that I have specifically edited for this purpose. I edited it so that it is the correct size and has alpha background behind the pieces
*/

/*
load the chess pieces from a 720x720 image I prepared
*/

int load_pieces(char *filename)
{
 int w,h;
 /* Open the image file */

 texture = IMG_LoadTexture(renderer, filename);
 if (!texture)
 {
  SDL_Log("Couldn't load %s: %s\n", filename, SDL_GetError());
  return 0;
 }
 else
 {
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  printf("Image '%s' loaded\n",filename);
  printf("Texture dimensions w=%d,h=%d\n",w,h);
 }
 return 1;
}







void chess_grid_draw_pieces()
{
 int x,y,x1,y1;
 struct chess_piece p;
 SDL_Rect rect_dst;

 rect.w=main_check.rectsize;
 rect.h=main_check.rectsize;
 rect_dst.w=main_check.rectsize;
 rect_dst.h=main_check.rectsize;

 /*printf("main_check.rectsize=%d\n",main_check.rectsize);*/

 y=0;
 while(y<8)
 {
  x=0;
  while(x<8)
  {
   p=main_grid.array[x+y*8];

   if(p.id!='0')
   {

   /*printf(" %c%c",p.color,p.id);*/
   /*printf(" %c",p.id);*/
   
    sprintf(text,"%c",p.id);

    x1=x*main_check.rectsize;
    y1=y*main_check.rectsize;

    if(p.color=='B')
    {
     if(p.id=='P')
     {
      rect.x=0*main_check.rectsize;
      rect.y=1*main_check.rectsize;
     }
     if(p.id=='R')
     {
      rect.x=0*main_check.rectsize;
      rect.y=0*main_check.rectsize;
     }
     if(p.id=='N')
     {
      rect.x=1*main_check.rectsize;
      rect.y=0*main_check.rectsize;
     }
     if(p.id=='B')
     {
      rect.x=2*main_check.rectsize;
      rect.y=0*main_check.rectsize;
     }
     if(p.id=='Q')
     {
      rect.x=3*main_check.rectsize;
      rect.y=0*main_check.rectsize;
     }
     if(p.id=='K')
     {
      rect.x=4*main_check.rectsize;
      rect.y=0*main_check.rectsize;
     }

     
    }
    if(p.color=='W')
    {
     if(p.id=='P')
     {
      rect.x=0*main_check.rectsize;
      rect.y=6*main_check.rectsize;
     }
     if(p.id=='R')
     {
      rect.x=0*main_check.rectsize;
      rect.y=7*main_check.rectsize;
     }
     if(p.id=='N')
     {
      rect.x=1*main_check.rectsize;
      rect.y=7*main_check.rectsize;
     }
     if(p.id=='B')
     {
      rect.x=2*main_check.rectsize;
      rect.y=7*main_check.rectsize;
     }
     if(p.id=='Q')
     {
      rect.x=3*main_check.rectsize;
      rect.y=7*main_check.rectsize;
     }
     if(p.id=='K')
     {
      rect.x=4*main_check.rectsize;
      rect.y=7*main_check.rectsize;
     }



    }

    rect_dst.x=x1;
    rect_dst.y=y1;

    SDL_RenderCopy(renderer, texture, &rect, &rect_dst);

   }

   x+=1;
  }
  /*printf("\n"); */
  y+=1;
 }

}






/*
fills the screen with an image passed as a filename string
this is merely for debugging to see if the file can load and display correctly
*/

void image_fill(char *filename)
{
 int w,h;

 /* Open the image file */

 texture = IMG_LoadTexture(renderer, filename);
 if (!texture)
 {
  SDL_Log("Couldn't load %s: %s\n", filename, SDL_GetError());
 }
 else
 {
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  printf("Image '%s' loaded\n",filename);
  printf("Texture dimensions w=%d,h=%d\n",w,h);
 }

 /* Display the image */
 SDL_RenderCopy(renderer, texture, NULL, NULL);

 /*free the memory and delete the texture*/
 SDL_DestroyTexture(texture);

 SDL_RenderPresent(renderer);

 loop=1;
 while(loop)
 {
  while(SDL_PollEvent(&e))
  {
   if(e.type == SDL_QUIT){loop=0;}
   if(e.type == SDL_KEYUP && e.key.repeat==0)
   {
    if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}
   }
  }
 }

}