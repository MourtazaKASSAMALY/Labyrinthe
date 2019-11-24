#include "Path.h"

Path::Path(const Cell *c) : m_c(c)
{
	// -
}

void Path::add_to_path(const Cell* c)
{
	delete m_next;
	m_next = new Path(c);
}

//Méthode récursive qui affiche le chemin, elle dessine un rectangle entre la cellule actuelle et sa cellule voisine si elle existe
void Path::display_path()
{	
	if (m_next != NULL)
	{
		vibes::drawBox(
			std::min(m_c->m_x, m_next->m_c->m_x) + 0.4, std::max(m_c->m_x, m_next->m_c->m_x) + 0.6,
			std::min(m_c->m_y, m_next->m_c->m_y) + 0.4, std::max(m_c->m_y, m_next->m_c->m_y) + 0.6,
			"Blue[Blue]");

		m_next->display_path();
	}
}

Path::~Path()
{
	delete m_c;
	delete m_next;
}