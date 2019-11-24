#include <iostream>
#include "Cell.h"

//Par définition des voisins de chaque cellules, connaître le départ et l'arrivée suffit à reconstituer le labyrinthe

struct Maze
{
	Cell *startCell = NULL;
	Cell *stopCell = NULL;
};