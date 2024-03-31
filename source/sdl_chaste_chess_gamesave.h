/*
This file is for the handling of multiple game states for Chaste Chess
Unlike most chess games, it allows saving and loading from 10 different states. This means that you can't just go back or forward one move but instead strategically save a state before a move that you think might be a mistake and want to rewind to.

This system exists because it was used in Chaste Tris and I copied over the code. It also makes my chess game unique which is a big plus in my opinion.
*/

int save_index=0;
int load_flag=0; /*used for telling if a game has been loaded recently and we need to refresh the screen to see what happened*/

/*a big structure to hold all relevant data that should be saved or loaded*/
struct gamesave
{
 int exist;
 struct chess_grid grid;
 int turn;
 int x,y;
};

struct gamesave state[10];



/*
 a special function which saves all the important data in the game. This allows reloading to a previous position when I make a mistake.
*/
void save_gamesave()
{
 state[save_index].grid=main_grid;
 printf("State %d saved\n",save_index);
 state[save_index].exist=1;
 state[save_index].turn=turn;
 state[save_index].x=x;
 state[save_index].y=y;
}





/*
 a special function which loads the data previously saved. This allows reloading to a previous position when I make a mistake.
*/
void load_gamesave()
{
 if(!state[save_index].exist)
 {
  printf("State %d has not be saved yet! Nothing to load!\n",save_index);
  return;
 }

 main_grid=state[save_index].grid;
 turn=state[save_index].turn;
 x=state[save_index].x;
 y=state[save_index].y;
 
 printf("State %d loaded\n",save_index);
 load_flag=1; /*signal to main application that a state was loaded*/
}

