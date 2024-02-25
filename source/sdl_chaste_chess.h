/*
 sdl_chaste_chess.h

a file for representing what the chess pieces are and controlling their movements 

*/


char chess_board_pieces[]=
{
 "RNBQKBNR"
 "PPPPPPPP"
 "00000000"
 "00000000"
 "00000000"
 "00000000"
 "PPPPPPPP"
 "RNBQKBNR"
};

char chess_board_pieces_color[]=
{
 "BBBBBBBB"
 "BBBBBBBB"
 "00000000"
 "00000000"
 "00000000"
 "00000000"
 "WWWWWWWW"
 "WWWWWWWW"
};


void chess_board_print()
{
 
 /*printf("%s\n",chess_board_pieces);*/

 printf("\n"); 

 y=0;
 while(y<8)
 {
  x=0;
  while(x<8)
  {
   printf(" %c",chess_board_pieces[x+y*8]);
   x+=1;
  }
  printf("\n"); 
  y+=1;
 }
 
 printf("\n"); 

}




struct chess_piece
{
 char color;
 char id;
 int moves;
 int x,y;
};

/*global chess piece that will be used for analyzing all data about the recently clicked piece*/
struct chess_piece p;

/*global chess piece that will be used for analyzing all data about the currently selected piece if it was clicked last time*/
struct chess_piece ps;


struct chess_grid
{
 struct chess_piece array[64];
};


struct chess_grid main_grid;

void init_main_grid()
{

 y=0;
 while(y<8)
 {
  x=0;
  while(x<8)
  {
   main_grid.array[x+y*8].id=chess_board_pieces[x+y*8];
   main_grid.array[x+y*8].color=chess_board_pieces_color[x+y*8];
   main_grid.array[x+y*8].moves=0;
   x+=1;
  }
  y+=1;
 }

}



void chess_grid_print()
{
 
 /*struct chess_piece p;*/

 y=0;
 while(y<8)
 {
  x=0;
  while(x<8)
  {
   p=main_grid.array[x+y*8];
   /*printf(" %c%c",p.color,p.id);*/
   printf(" %c",p.id);
   x+=1;
  }
  printf("\n"); 
  y+=1;
 }
 
}



/*more global variables*/

int dir=-1; /*the direction for pawn movements can be 1 or -1*/
char turn='W'; /*whose turn it is. W for white and B for black*/

/*
in the context of Chaste Chess, highlight refers to marking the spots on the board based on whether pieces can move to those spots or not.

0 Can't move
1 Can move to this blank space
2 Can move and capture a piece
-1 Could move and capture the piece here if it was the opposite color but it's the same.

The following functions keep track of the data but do not actually draw the highlights. It is only to internally represent the places the last selected piece can move to. There is a function which draws squares color coded according to their meaning in the graphics header for the game
*/

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
  /*SDL_SetRenderDrawColor(renderer,0x00,0xFF,0x00,255);*/
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
  highlight[x+y*8]=-1;
  highloop=0;
 }

 if(main_grid.array[x+y*8].color!=p.color)
 {
  /*this space will be marked blue to indicate a piece can be captured*/
  /*SDL_SetRenderDrawColor(renderer,0x00,0x00,0xFF,255);*/
  /*
   same color as moving piece
   can't capture this piece or move beyond it
  */
  highlight[x+y*8]=2;
  highloop=0;
 }

}

 /*highlight the square which was clicked*/
 /*rect.x=x*main_check.rectsize;
 rect.y=y*main_check.rectsize;
 rect.w=main_check.rectsize;
 rect.h=main_check.rectsize;*/
 
 /*SDL_RenderFillRect(renderer,&rect);*/

}