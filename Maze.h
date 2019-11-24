#include <iostream>
#include "Cell.h"

/**
* \struct 	Maze
* \author	Mourtaza KASSAMALY
* \brief	Structure implémentant un labyrinthe
* \details	La connaissance des cellules de départ, d'arrivée, et des voisins de chaque cellule permet
*			de reconstituer tout le labyrinthe	
* \date 	24 nov 2019
*/
struct Maze
{
	Cell *startCell = NULL;
	Cell *stopCell = NULL;
};