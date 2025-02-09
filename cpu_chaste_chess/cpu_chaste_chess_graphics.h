

void chess_grid_draw_highlight()
{
 int x,y;

 y=0;
 while(y<8)
 {
  x=0;
  while(x<8)
  {
   /*highlight[x+y*8]=0;*/

   rect.x=check_left+x*main_check.rectsize;
   rect.y=y*main_check.rectsize;
   rect.w=main_check.rectsize;
   rect.h=main_check.rectsize;

   if(highlight[x+y*8]!=0)
   {

    if(highlight[x+y*8]==1)
    {
     /*this space will be marked green meaning "go" because you can move here and it is blank*/
     SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,0x00,0xFF,0x00));
    }
    if(highlight[x+y*8]==-1)
    {
     /*this space will be marked red meaning "stop" because you can't move here and the piece is the same color as the piece you are moving*/
     SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,0xFF,0x00,0x00));
    }
    if(highlight[x+y*8]==2)
    {
     /*this space will be marked blue to indicate a piece can be captured*/
     SDL_FillRect(surface,&rect,SDL_MapRGB(surface->format,0x00,0x00,0xFF));
    }

   }

   x+=1;
  }
  y+=1;
 }

}

