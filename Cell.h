#ifndef __CELL_H__
#define __CELL_H__

#include <iostream>

/**
* \class 	Cell
* \author 	Mourtaza KASSAMALY
* \brief 	Classe implémentant l'objet cellule
* \date 	24 nov 2019
*/
class Cell
{
	public:
		/**
 		* \brief	Initialise une cellule via ses coordonnées
 		* \param	x	Abscisse
 		* \param	y	Ordonnée
 		*/
		Cell(int x, int y);

		/**
 		* \brief	Permet d'ajouter un voisin à la cellule courante
 		* \details	Par double appel de la méthode set_neighb pour ajouter les voisins symétriquement
 		* \param	*c	Pointeur vers la cellule voisine
 		* \return	Ne retourne rien
 		*/
		void add_neighb(Cell *c);

		/**
 		* \brief	Permet d'ajouter deux voisins d'un seul coup
 		* \details	Par double appel de la méthode add_neighb(Cell *c)
 		* \param	*c1	Pointeur vers la première cellule voisine
 		* \param	*c2	Pointeur vers la seconde cellule voisine
 		* \return	Ne retourne rien
 		*/
		void add_neighb(Cell *c1, Cell *c2);

		/**
 		* \brief	Ajoute une cellule voisine au tableau de pointeurs des voisins
 		* \param	*c	Pointeur vers la cellule voisine
 		* \return	Ne retourne rien
 		*/
		void set_neighb(Cell *c);

		~Cell();

	public:
		int m_x;
		int m_y;
		int m_nb_neighb = 0;
		Cell **m_neighb = NULL; //tableau de pointeurs vers les voisins
		Cell **m_backup = NULL; //tableau de pointeurs vers les voisins
		bool m_displayed = false; //flag utile pour l'affichage du labyrinthe
		bool m_treated = false; //flag utile pour le parcours du labyrinthe
		bool m_saved = false; //flag utile pour l'écriture dans les fichiers
		bool m_corrupted = false; //flag utile pour la lecture depuis les fichiers
};

std::ostream &operator<<(std::ostream &out, const Cell &c); //surcharge le flux d'écriture
std::istream &operator>>(std::istream &in, Cell &c); //surcharge le flux de lecture
bool operator==(const Cell &c1, const Cell &c2); //surcharge l'opération d'égalité entre deux cellules, non utilisée dans le programme

#endif
