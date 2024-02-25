/*

 sdl_chaste_chess_graphics.h

*/

void chess_grid_draw_text()
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


/*
 a function pointer that points to the current function used for drawing the chess pieces
 by default it points to the function that represents them with text
*/
void (*chess_grid_draw)()=chess_grid_draw_text;


/*
function to draw the "game scene" which includes the checkerboard and the square which was clicked using the carefully chosen shades of gray I designed. This doesn't include drawing of the pieces because different functions for that specifically may be changed.
*/

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

   if(highlight[x+y*8]!=0)
   {

    if(highlight[x+y*8]==1)
    {
     /*this space will be marked green meaning "go" because you can move here and it is blank*/
     SDL_SetRenderDrawColor(renderer,0x00,0xFF,0x00,255);
    }
    if(highlight[x+y*8]==-1)
    {
    /*this space will be marked red meaning "stop" because you can't move here and the piece is the same color as the piece you are moving*/
     SDL_SetRenderDrawColor(renderer,0xFF,0x00,0x00,255);
    }
    if(highlight[x+y*8]==2)
    {
     /*this space will be marked blue to indicate a piece can be captured*/
     SDL_SetRenderDrawColor(renderer,0x00,0x00,0xFF,255);
    }

    rect.x=x*main_check.rectsize;
    rect.y=y*main_check.rectsize;
    rect.w=main_check.rectsize;
    rect.h=main_check.rectsize;
    SDL_RenderFillRect(renderer,&rect);
   }

   x+=1;
  }
  y+=1;
 }

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

     /*set direction of pawn based on whose turn it is*/
     if(p.color=='B'){dir=1;} 
     if(p.color=='W'){dir=-1;}

     /*these next two sections of conditionals make sure that pawns move forward only onto blank spaces but can't capture pieces directly in front of them because this is not legal in chess.*/

     if(main_grid.array[x+(y+dir)*8].id=='0')
     {
      chess_grid_highlight(x,y+dir);
     }

     if(p.moves==0)
     {
      if(main_grid.array[x+(y+dir*2)*8].id=='0')
      {
       chess_grid_highlight(x,y+dir*2);
      }
     }

   /*end of pawn moving forward section*/

   /*begin pawn capturing section*/

    if(main_grid.array[x+1+(y+dir)*8].id!='0')
    {
     chess_grid_highlight(x+1,y+dir);
    }

    if(main_grid.array[x-1+(y+dir)*8].id!='0')
    {
     chess_grid_highlight(x-1,y+dir);
    }

   /*end pawn capturing section*/

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
