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






void draw_game_scene()
{

/*draw the checkerboard*/
    SDL_SetRenderDrawColor(renderer,0xAA,0xAA,0xAA,255);
    SDL_RenderFillRect(renderer,NULL);
    SDL_SetRenderDrawColor(renderer,0x55,0x55,0x55,255);
    chaste_checker();

    /*highlight the square which was clicked*/
    rect.x=x*main_check.rectsize;
    rect.y=y*main_check.rectsize;
    rect.w=main_check.rectsize;
    rect.h=main_check.rectsize;
    SDL_SetRenderDrawColor(renderer,0x80,0x80,0x80,255);
    SDL_RenderFillRect(renderer,&rect);

}







char highlight[64];

void init_highlight()
{
 int x,y;

 y=0;
 while(y<8)
 {
  x=0;
  while(x<8)
  {
   highlight[x+y*8]=0;
   x+=1;
  }
  y+=1;
 }

}

int highloop=0; /*highlight loop control*/

void chess_grid_highlight(int x,int y)
{

 if(x<0){ /*printf("Error: Negative X\n");*/ return;}
 if(y<0){ /*printf("Error: Negative Y\n");*/ return;}
 if(x>=8){/*printf("Error: X too high.\n");*/ return;}
 if(y>=8){/*printf("Error: Y too high.\n");*/ return;}

 if(main_grid.array[x+y*8].id=='0')
 {
  /*this space will be marked green meaning "go" because you can move here and it is blank*/
  SDL_SetRenderDrawColor(renderer,0x00,0xFF,0x00,255);
  highlight[x+y*8]=1;
 }
 else 
{
 /*this condition happens if there is a piece and the space is not blank*/

 if(main_grid.array[x+y*8].color==p.color)
 {
  /*this space will be marked red meaning "stop" because you can't move here and the piece is the same color as the piece you are moving*/
  SDL_SetRenderDrawColor(renderer,0xFF,0x00,0x00,255);
  /*
   same color as moving piece
   can't capture this piece or move beyond it
  */
  highlight[x+y*8]=0;
  highloop=0;
 }

 if(main_grid.array[x+y*8].color!=p.color)
 {
  /*this space will be marked blue to indicate a piece can be captured*/
  SDL_SetRenderDrawColor(renderer,0x00,0x00,0xFF,255);
  /*
   same color as moving piece
   can't capture this piece or move beyond it
  */
  highlight[x+y*8]=1;
  highloop=0;
 }

}

 /*highlight the square which was clicked*/
 rect.x=x*main_check.rectsize;
 rect.y=y*main_check.rectsize;
 rect.w=main_check.rectsize;
 rect.h=main_check.rectsize;
 
 SDL_RenderFillRect(renderer,&rect);

}



void check_moves_rook()
{
     highloop=1;
     x1=x+1;
     y1=y;
     while(x1<8 && highloop)
     {
      chess_grid_highlight(x1,y1);
      x1++;
     }
    
	 highloop=1;
     x1=x-1;
     y1=y;
     while(x1>=0 && highloop)
     {
      chess_grid_highlight(x1,y1);
      x1--;
     }

     highloop=1;
     x1=x;
     y1=y+1;
     while(y1<8 && highloop)
     {
      chess_grid_highlight(x1,y1);
      y1++;
     }
    
	 highloop=1;
     x1=x;
     y1=y-1;
     while(y1>=0 && highloop)
     {
      chess_grid_highlight(x1,y1);
      y1--;
     }
}


void check_moves_bishop()
{
	 highloop=1;
	 x1=x+1;
     y1=y+1;
     while(x1<8&&y1<8 && highloop)
     {
      chess_grid_highlight(x1,y1);
      x1++;
      y1++;
     }
    
	highloop=1;
     x1=x-1;
     y1=y-1;
     while(x1>=0&&y1>=0 && highloop)
     {
      chess_grid_highlight(x1,y1);
      x1--;
      y1--;
     }

highloop=1;
     x1=x+1;
     y1=y-1;
     while(x1<8&&y1>=0 && highloop)
     {
      chess_grid_highlight(x1,y1);
      x1++;
      y1--;
     }
    
	highloop=1;
     x1=x-1;
     y1=y+1;
     while(x1>=0&&y1<=8 && highloop)
     {
      chess_grid_highlight(x1,y1);
      x1--;
      y1++;
     }
}

void check_moves_of_clicked_piece()
{
    /*check all legal pawn moves*/
    if(p.id=='P')
    {

     if(p.color=='B'){dir=1;} 
     if(p.color=='W'){dir=-1;}

     chess_grid_highlight(x,y+dir);
     if(p.moves==0)
     {
      chess_grid_highlight(x,y+dir*2);
     }

    }

    if(p.id=='N')
    {
     chess_grid_highlight(x+1,y-2);
     chess_grid_highlight(x+2,y-1);

     chess_grid_highlight(x+1,y+2);
     chess_grid_highlight(x+2,y+1);

     chess_grid_highlight(x-1,y-2);
     chess_grid_highlight(x-2,y-1);

     chess_grid_highlight(x-1,y+2);
     chess_grid_highlight(x-2,y+1);
    }

    if(p.id=='R')
    {
     check_moves_rook();
    }


    if(p.id=='B')
    {
     check_moves_bishop();
    }


    if(p.id=='K')
    {
     chess_grid_highlight(x-1,y-1);
     chess_grid_highlight(x  ,y-1);
     chess_grid_highlight(x+1,y-1);

     chess_grid_highlight(x-1,y);
     chess_grid_highlight(x+1,y);

     chess_grid_highlight(x-1,y+1);
     chess_grid_highlight(x  ,y+1);
     chess_grid_highlight(x+1,y+1);
    }

    /*
     the queen inherits the moves of both the rook and the bishop
     so they have been copy pasted from their sections
    */
    if(p.id=='Q')
    {
     check_moves_rook();
   	 check_moves_bishop();
    }
	
}
