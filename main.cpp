#include "Cell.h"
#include "Maze.h"
#include "vibes.h"
#include "Path.h"
#include <fstream>
using namespace std;
 
void draw_gate(const Cell *n1, const Cell *n2)
{
	vibes::drawBox(
		min(n1->m_x, n2->m_x) + 0.1, max(n1->m_x, n2->m_x) + 0.9,
		min(n1->m_y, n2->m_y) + 0.1, max(n1->m_y, n2->m_y) + 0.9,
		"lightGray[lightGray]");
}

void display_cell(Cell *cell)
{
	vibes::drawBox(cell->m_x, cell->m_x + 1, cell->m_y, cell->m_y + 1, "[lightGray]");
	
	cell->m_displayed = true;
	
	for(int i=0; i<cell->m_nb_neighb; i++)
	{
		if(!cell->m_neighb[i]->m_displayed)
			display_cell(cell->m_neighb[i]);
		draw_gate(cell, cell->m_neighb[i]);			
	}
}

void display(Maze maze)
{
	//Affichage de tout le labyrinthe par récursivité sur la cellule de départ
	Cell* startCell = maze.startCell;
	display_cell(startCell);

	//Mise en évidence des cellules de départ et d'arrivée
	Cell* stopCell = maze.stopCell;

	//Cellule de départ en vert
	vibes::drawBox(
		min(startCell->m_x, startCell->m_x) + 0.1, max(startCell->m_x, startCell->m_x) + 0.9,
		min(startCell->m_y, startCell->m_y) + 0.1, max(startCell->m_y, startCell->m_y) + 0.9,
		"Green[Green]");

	//Cellule d'arrivée en rouge
	vibes::drawBox(
		min(stopCell->m_x, stopCell->m_x) + 0.1, max(stopCell->m_x, stopCell->m_x) + 0.9,
		min(stopCell->m_y, stopCell->m_y) + 0.1, max(stopCell->m_y, stopCell->m_y) + 0.9,
		"Red[Red]");
}

Maze create_maze()
{
	//Création des cellules
	Cell *c1 = new Cell(0,0);
	Cell *c2 = new Cell(1,0);
	Cell *c3 = new Cell(2,0);
	Cell *c4 = new Cell(3,0);
	Cell *c5 = new Cell(0,1);
	Cell *c6 = new Cell(1,1);
	Cell *c7 = new Cell(2,1);
	Cell *c8 = new Cell(3,1);
	Cell *c9 = new Cell(0,2);
	Cell *c10 = new Cell(1,2);
	Cell *c11 = new Cell(2,2);
	Cell *c12 = new Cell(3,2);
	Cell *c13 = new Cell(0,3);
	Cell *c14 = new Cell(1,3);
	Cell *c15 = new Cell(2,3);
	Cell *c16 = new Cell(3,3);

	//Définition des voisins de chaque cellule
	c1->add_neighb(c2);
	c2->add_neighb(c3);
	c3->add_neighb(c4);
	c4->add_neighb(c8);
	c8->add_neighb(c12);
	c12->add_neighb(c16);
	c16->add_neighb(c15);
	c15->add_neighb(c11);
	c11->add_neighb(c10);
	c10->add_neighb(c6, c14);
	c6->add_neighb(c7);
	c14->add_neighb(c13);
	c13->add_neighb(c9);
	c9->add_neighb(c5);
	
	//Création du labyrinthe
	Maze maze;
	maze.startCell = c1;
	maze.stopCell = c5;
	return maze;
}

/*Détermine un chemin pour atteindre la cellule d'arrivée depuis la cellule *c passée en paramètre
Elle permet, par récursivité, de reconstituer un chemin de la cellule de départ à celle d'arrivée*/
bool find_path(Cell *c, Cell *cf, Path *path, bool &over)
{	
	c->m_treated = true; //flag

	if (c == cf)
	{
		over = true;
		return true;
	}

	for(int i=0; i<c->m_nb_neighb; i++) //pour tous les voisins de la cellule courante
	{
		if (!c->m_neighb[i]->m_treated) //flag
		{
			if (over == false)
			{
				path->add_to_path(c->m_neighb[i]);
				find_path(c->m_neighb[i], cf, path->m_next, over); //récursivité
			}
			else
			{
				return true;
			}
		}
	}
}

void save_cells(Cell *cell, ofstream *f)
{
	*f << *cell << " " << cell->m_nb_neighb;
	cell->m_saved = true; //flag

	for(int i=0; i<cell->m_nb_neighb; i++)
	{
		*f << " " << *(cell->m_neighb[i]);
	}
	
	for(int j=0; j<cell->m_nb_neighb; j++)
	{
		if(!cell->m_neighb[j]->m_saved) //flag
		{
			*f << endl;
			save_cells(cell->m_neighb[j], f); //récursivité
		}
	}
	
}

void save_maze(const Maze& maze, const string& file_name)
{
	ofstream f(file_name);
	if(!f.is_open())
	{
		cout << "Erreur d'ouverture du fichier : " << file_name << endl;
		return;
	}

	Cell *startCell = maze.startCell;
	f << "# Start :" << endl << *startCell << endl;
	f << "# End:" << endl << *(maze.stopCell) << endl << "# Cells:" << endl; 
	save_cells(startCell, &f); //sauvegarde des cellules par récursivité

	f.close();
}

//Permet de convertir une chaine de caractère de type (int, int) en un objet de type pair<int, int> (4, 2)
pair<int,int> convert_coords(string coords)
{
	coords = coords.substr(1, coords.size()-2);
	int x = stoi(coords.substr(0, coords.find(',')));
	int y = stoi(coords.substr(coords.find(',')+1, coords.size()));
	return pair<int,int> (x, y);
}

Maze read_maze(const string& file_name)
{
	ifstream f(file_name);
	if(!f.is_open())
	{
		cout << "Erreur d'ouverture du fichier : " << file_name << endl;
		Maze maze;
		return maze;
	}

	string line = ""; //buffer de lecture, il sert de poubelle pour passer les lignes qui ne nous intéressent pas
	string startCoords = "";
	string stopCoords = "";

	getline(f, line);
	getline(f, startCoords); //récupère les coordonnées de départ
	getline(f, line);
	getline(f, stopCoords); //récupère les coordonnées d'arrivée
	getline(f, line);

	pair<int,int> startCellCoords = convert_coords(startCoords); //coordonnées de départ
	pair<int,int> stopCellCoords = convert_coords(stopCoords); //coordonnées d'arrivée

	map<pair<int,int>, Cell*> cells; //dictionnaire des cellules, les clés étant les coordonnées

	while(!f.eof()) //tant qu'on arrive pas à la fin du fichier
	{
		Cell *cell = new Cell(0,0);
		int nb_neighb;
		f >> *cell >> nb_neighb; //lecture de la cellule courante et de son nombre de voisins
		if(cell->m_corrupted) //flag qui vérifie si la cellule doit être ignorée ou non, cf la surcharge >> de la classe Cell 
		{
			delete cell;
			break;
		}

		//Traitement de la cellule courante

		if(cells.find(pair<int,int> (cell->m_x, cell->m_y)) == cells.end()) //si la clé n'existe pas
		{
			cells[pair<int,int> (cell->m_x, cell->m_y)] = cell; //elle est crée
		}
		else //si elle existe déjà
		{
			int x = cell->m_x;
			int y = cell->m_y;
			delete cell;
			cell = cells.find(pair<int,int> (x, y))->second; //on utilise la cellule déjà créée pour la suite du traitements
		}

		//Traitement des voisins

		for (int i=0; i<nb_neighb; i++)
		{
			Cell *neighb = new Cell(0,0);
			f >> *neighb;
			if(cells.find(pair<int,int> (neighb->m_x, neighb->m_y)) == cells.end()) //si le voisin n'existe pas déjà dans le dictionnaire
			{
				cell->add_neighb(neighb);
				cells[pair<int,int> (neighb->m_x, neighb->m_y)] = neighb; //on l'ajoute au dictionnaire
			}
			else //s'il existe déjà
			{
				cell->add_neighb(cells.find(pair<int,int> (neighb->m_x, neighb->m_y))->second);
				delete neighb;
			}
		}
		getline(f, line); //permet de passer à la ligne suivante
	}

	Maze maze; //création du labyrinthe
	maze.startCell = cells.find(startCellCoords)->second; //définition de la cellule de départ, ses coordonnées étant connues
	maze.stopCell = cells.find(stopCellCoords)->second; //définition de la cellule d'arrivée, ses coordonnées étant connues

	return maze;
}

// ------------------------------------------------------------------------------------------- //

int main()
{
	vibes::beginDrawing(); // initialisation de VIBes
	vibes::newFigure("Maze"); // création d’une figure
	vibes::axisLimits(-1., 9., -1., 9.); // dimensions de la vue graphique
	vibes::setFigureProperties(
		"Maze", 
		vibesParams("x", 100, "y", 100, "width", 400, "height", 400)); // propriétés de la figure

	//Maze maze = create_maze();
	//save_maze(maze, filepath);

	string filepath = "maze3.txt";
	Maze maze = read_maze(filepath); //chargement du labyrinthe via le fichier texte
	
	display(maze); //affichage du labyrinthe

	//Recherche et affichage d'un chemin pour résoudre le labyrinthe
	Path* path = new Path(maze.startCell);
	bool over = false;
	find_path(maze.startCell, maze.stopCell, path, over);
	path->display_path();

	delete path;

	return EXIT_SUCCESS;
}