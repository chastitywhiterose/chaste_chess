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
