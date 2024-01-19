/*

 sdl_chaste_chess_graphics.h

*/

void chess_grid_draw()
{
 int x,y,x1,y1,x2;
 struct chess_piece p;


 /*printf("main_check.rectsize=%d\n",main_check.rectsize);*/

 text_scale=8;

 x2=(main_check.rectsize-(text_scale*main_font.char_width))/2;
 /*printf("x2=%d\n",x2);*/

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

 if(p.color=='B'){text_color=0x000000;}
 if(p.color=='W'){text_color=0xFFFFFF;}

   chaste_font_draw_string_scaled_alpha(text,x1+x2,y1+x2,text_scale);
}

   x+=1;
  }
  /*printf("\n"); */
  y+=1;
 }

}




void chess_grid_highlight(int x,int y)
{

 if(x<0){printf("Error: Negative X\n"); return;}
 if(y<0){ printf("Error: Negative Y\n"); return;}
 if(x>=8){printf("Error: X too high.\n"); return;}
 if(y>=8){printf("Error: Y too high.\n"); return;}

 if(main_grid.array[x+y*8].id=='0')
 {
  SDL_SetRenderDrawColor(renderer,0x00,0xFF,0x00,255);
 }
 else
 {
  SDL_SetRenderDrawColor(renderer,0xFF,0x00,0x00,255);
 }


 /*highlight the square which was clicked*/
 rect.x=x*main_check.rectsize;
 rect.y=y*main_check.rectsize;
 rect.w=main_check.rectsize;
 rect.h=main_check.rectsize;
 
 SDL_RenderFillRect(renderer,&rect);

}