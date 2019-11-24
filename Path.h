#ifndef __PATH_H__
#define __PATH_H__

#include "Cell.h"
#include "vibes.h"

/**
* \class 	Path
* \author 	Mourtaza KASSAMALY
* \brief 	Classe permettant d'enregistrer un chemin de cellules en cellules
* \date 	24 nov 2019
*/
class Path
{
	public:
		/**
 		* \brief	Initialise un chemin élémentaire entre la cellule courante et une cellule voisine
 		* \param	*c	Pointeur vers la cellule courante
 		*/
		Path(const Cell *c);

		/**
 		* \brief	Permet d'ajouter une cellule voisine pour le chemin élémentaire
 		* \param	*c	Pointeur vers la cellule voisine
 		* \return	Ne retourne rien
 		*/
		void add_to_path(const Cell *c);

		/**
 		* \brief	Permet d'afficher le chemin élémentaire entre la cellule courante et sa cellule voisine
 		* \details	Affichage d'un rectangle fin entre les deux cellules
 		* \return	Ne retourne rien
 		*/
		void display_path();

		~Path();


	public:
		const Cell *m_c;
		Path *m_next = NULL;
};

#endif