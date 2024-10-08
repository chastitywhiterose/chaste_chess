/*
this uses direct pixel access of the source font surface to draw only when the source pixel is not black. But this one is "special" because it can optionally change the color for each scaled pixel!
*/
void chaste_font_draw_string_scaled_special(const char *s,int cx,int cy,int scale)
{
 int x,y,i,c,cx_start=cx;
 Uint32 *ssp; /*ssp is short for Source Surface Pointer*/
 int sx,sy,sx2,sy2,dx,dy; /*x,y coordinates for both source and destination*/
 Uint32 pixel,r,g,b; /*pixel that will be read from*/
 int source_surface_width;
 SDL_Rect rect_source,rect_dest;

 source_surface_width=main_font.surface->w;

 /*SDL_LockSurface(main_font.surface);*/
 ssp=(Uint32*)main_font.surface->pixels;
  
 i=0;
 while(s[i]!=0)
 {
  c=s[i];
  if(c=='\n'){ cx=cx_start; cy+=main_font.char_height*scale;}
  else
  {
   x=(c-' ')*main_font.char_width;
   y=0*main_font.char_height;

   /*set up source rectangle where this character will be copied from*/
   rect_source.x=x;
   rect_source.y=y;
   rect_source.w=main_font.char_width;
   rect_source.h=main_font.char_height;

 
   /*Now for the ultra complicated stuff that only Chastity can read and understand!*/
   sx2=rect_source.x+rect_source.w;
   sy2=rect_source.y+rect_source.h;
   
   dx=cx;
   dy=cy;
   
   sy=rect_source.y;
   while(sy<sy2)
   {
    dx=cx;
    sx=rect_source.x;
    while(sx<sx2)
    {
     pixel=ssp[sx+sy*source_surface_width];

      pixel&=0xFFFFFF;
     
     /*printf("pixel 0x%06X %d,%d\n",pixel,sx,sy);*/
     if(pixel!=0) /*only if source pixel is nonzero(not black) draw square to destination*/
     {
      /*set up the rectangle to draw to*/
      rect_dest.x=dx;
      rect_dest.y=dy;
      rect_dest.w=scale;
      rect_dest.h=scale;
      
      pixel=chaste_palette[chaste_palette_index];
      
      r=(pixel&0xFF0000)>>16;
      g=(pixel&0x00FF00)>>8;
      b=(pixel&0x0000FF);
      
      SDL_SetRenderDrawColor(renderer,r,g,b,255);
      SDL_RenderFillRect(renderer,&rect_dest);
      
      chaste_next_color();
     }
     
     sx++;
     dx+=scale;
    }
    sy++;
    dy+=scale;
   }
   /*End of really complicated section*/
   cx+=main_font.char_width*scale;
  }
  i++;
 }
 /*SDL_UnlockSurface(main_font.surface);*/
}
