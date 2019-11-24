#ifndef __CELL_H__
#define __CELL_H__

#include <iostream>

class Cell
{
	public:
		Cell(int x, int y);
		void add_neighb(Cell *c);
		void add_neighb(Cell *c1, Cell *c2);
		void set_neighb(Cell *c);
		~Cell();

	public:
		int m_x;
		int m_y;
		int m_nb_neighb = 0;
		Cell **m_neighb = NULL; //tableau de pointeurs vers les voisins
		Cell **m_backup = NULL; //tableau de pointeurs vers les voisins
		bool m_displayed = false;
		bool m_treated = false; //utile pour le parcours du labyrinthe
		bool m_saved = false;
		bool m_corrupted = false;
};

std::ostream &operator<<(std::ostream &out, const Cell &c); //surcharge le flux d'écriture
std::istream &operator>>(std::istream &in, Cell &c); //surcharge le flux de lecture
bool operator==(const Cell &c1, const Cell &c2);

#endif
