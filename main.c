#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "Cell.h"
#include "Fish.h"
#include "Shark.h"
/**
*Make2dArray
* -Create 2-d Array in memory
*@param  int rows 
*	-Rows of in array.
*@param  int cols 
*	-CoLs of in array.
*@return Cell ** array
* 	-return 2-D pointer cell Array
*/
Cell ** Make2dArray(int row,int col)
{
	Cell ** array;
	array = (Cell**) malloc(row*sizeof(Cell*));  
	int i = 0;
	for (i = 0; i < row; i++)  
		array[i] = (Cell*) malloc(col*sizeof(Cell));  

   return array;  
}
/**
*randomEmptyCell
* -Picks Random Empty Cell
*@param  Cell ** world
*	-2-D world array.
*@param  int rows 
*	-Rows of in array.
*@param  int cols 
*	-Cols of in array.
*@return Cell * &world[randomRow][randomCol]
* 	-return pointer to empty cell from Array
*/
Cell * randomEmptyCell(Cell ** world,int row,int col)
{
	int randomCol = rand() % row;
	int randomRow = rand() % col;
	while(world[randomRow][randomCol].fish != 0 && world[randomRow][randomCol].shark != 0)
	{
		randomCol = rand() % row;
		randomRow = rand() % col;
	}
	return &world[randomRow][randomCol] ;
}
/**
*PopulateWorld
* -Populates the World array
*@param  int nFish 
*	-Number of fish to create.
*@param  int rows 
*	-Rows of in array.
*@param  int cols 
*	-CoLs of in array.
*@param  Cell ** world
*	-2-D world array.
*/
void PopulateWorld(int nFish,int nSharks,int rows, int cols,Cell ** world)
{
	int i;

	Cell * p;
	for (i = 0; i < nFish; ++i)
	{
		p = randomEmptyCell(world,rows,cols);
		p->fish =  malloc(sizeof(Fish));
		p->fish->moved = -1;
		p->fish->SpawnTime=3;
	}
	int j;
	for (j = 0; j < nSharks; ++j)
	{
		p = randomEmptyCell(world,rows,cols);
		p->shark =  malloc(sizeof(Shark));
		p->shark->moved = -1;
		p->shark->SpawnTime = 4;
		p->shark->StarveTime = 3;
	}

}
int main(void)
{
	//printf("Cunt");
	srand(time(NULL));
	int Gridsize = 30;
	int FishPop = 200;
	int SharkPop = 6;
	Cell ** world = Make2dArray(Gridsize,Gridsize);
	PopulateWorld(FishPop,SharkPop,Gridsize,Gridsize,world);
	
	int i;
	int j;
	int Year = 0;
	int endYear = 50;
	while(Year < endYear)
	{
		for(i=0; i < Gridsize;i++)
		{

			for(j=0; j < Gridsize;j++)
			{       
				if(world[i][j].fish != 0 && world[i][j].fish->moved != Year){  
					world[i][j].fish->moved = Year;
					FishUpdate(&world[i][j], world, i, j, (Gridsize - 1));
				}
				else if(world[i][j].shark != 0 && world[i][j].shark->moved != Year)
				{
					world[i][j].shark->moved = Year;
					SharkUpdate(&world[i][j], world, i, j, (Gridsize - 1));
				}
			}
      		
      	}
      	for(i=0; i <= (Gridsize * 2);i++)
		{
			printf("_");
		}
		printf("\n");
      	SharkPop = 0;
      	FishPop = 0;
		for(i=0; i < Gridsize;i++)
		{

			for(j=0; j < Gridsize;j++)
			{  
			printf("|"); 
				if(world[i][j].shark != 0)
				{
					printf("S");
					SharkPop++;
				}
				else if(world[i][j].fish != 0)
				{
					printf("F");
					FishPop++;
				}
				else
				{
					printf(" ");
				}
				
			}
			printf("|\n");

		}
	    for(i=0; i <= (Gridsize * 2);i++)
		{
			printf("_");
		}
		printf("\n");
		printf("%i ", SharkPop);
		printf("%i\n", FishPop);
		sleep(1);
		Year++;
		if(SharkPop == 0 || FishPop == 0)
		{
			Year = endYear;
		}
	} 

	for (i = 0; i < Gridsize; i++){  
	free( world [i]);  
	}	  
	free(world); 

}
