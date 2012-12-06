/**	@Name:		Fish.h
	@Authors:	James Kelly, Sean Senchyna.
	@Brief:		This is the Fish Class. This class holds all the
				Functionality of every Fish in the simulation. Controls 
				the checks, movements, updates and death and creation of
				other Sharks.
	@Arguments:	N/A
	@Returns:	N/A
*/
#ifndef FISH_H
#define FISH_H
#include "Cell.h"

/**
*@Name:CheckIfEmty
*@Brief: Check If cell is Empty
*@Arguments: Cell * c -Pointer to cell you won't to check.
*@return int 0 or 1 -o indicate the cell is not available
*/
int CheckIfEmty(Cell * M)
{
	if(M->shark == 0 && M->fish == 0)
	{
		return 1;
	}
	return 0;
}
/**
*@Name:ChooseCell
*@Brief: Choose a cell to move
*@Arguments:
*	Struct Move-Cell Available To be Move too.
*@return int Dirrection
*	-Position in array of avaiable cell -1 if no position available..
*/
int ChooseCell(Move Available)
{
	int x = 0;
	int Dirrection = 0;
	if (Available.left == 0 &&
		Available.right == 0 &&
		Available.up ==0 &&
		Available.down ==0)
	{
		x = 1;
		Dirrection = -1;
	}
	
	while(x == 0)
	{
		int r = rand() % 4;
		Dirrection = r;
		switch(r){
			case(0):
		    if(Available.up == 1)
				x = 1;
			break;
			case(1):
			if(Available.down == 1)
				x = 1;
			break;
			case(2):
			if(Available.left == 1)
				x = 1;
			break;
			case(3):
			if(Available.right == 1)
				x = 1;
			break;
		}
	}
	return Dirrection;
}
/**
*@Name:FishMove
*@Brief Moves Fish pointer from one cell to the next, Spawns Next fish when spawntime raech's o
*@Arguments: 	Cell * Movto -Cell To Move too.
*				Cell * currentCell- current Cell contioning Fish Object .
*/
void FishMove(Cell * Moveto, Cell * currentCell){

	if(currentCell->fish->SpawnTime == 0)
	{

		currentCell->fish->SpawnTime = 3;
		Moveto->fish = malloc(sizeof(Fish));
		Moveto->fish->SpawnTime = 3;
		Moveto->fish->moved = currentCell->fish->moved;

	}
	else
	{
		Moveto->fish = currentCell->fish;
		Moveto->fish->SpawnTime--;
		currentCell->fish = 0;
	}
	
}

/**
*@Name:FishUpadate
*@Brief Updates Fish
*@Arguments: Cell * Fish -Pointer to cell Containing Fish.
*	Cell ** tempworld - 2d-Array Containg world Cells.
*	int x -Row Cell is On.
*	int y -Col cell On.
*	int range -Range represnts the number of cols and rows in the world used for wrap around.
*/
void FishUpdate(Cell * fish, Cell ** tempworld, int x, int y, int range)
{   
	Move Available;
	
	/**
	*Picks Psition of cells around fish cell in world array
	*/
	int top = y - 1;
	int bot = y + 1;
	int left = x - 1;
	int right = x + 1;
	/**
	*Add Wrap around if Move Poition out of range 
	*/
	if (top < 0)
		top = range;
	if (left < 0)
		left = range;
	if (right > range)
		right = 0;
	if (bot > range)
		bot = 0;
	/**
	*@param Array of Cell * to cells around fish
	*/
	Cell * array[4] = {&(tempworld)[x][top],&(tempworld)[x][bot],&(tempworld)[left][y],&(tempworld)[right][y]};
	Available.up = CheckIfEmty(array[0]);
	Available.down = CheckIfEmty(array[1]);
	Available.left = CheckIfEmty(array[2]);
	Available.right = CheckIfEmty(array[3]);
	int ChoosenCell = ChooseCell(Available);
	if (ChoosenCell != -1)
	{
		FishMove(array[ChoosenCell], fish);
	}
}
#endif