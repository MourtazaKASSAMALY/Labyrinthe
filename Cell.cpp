#include "Cell.h" 

Cell::Cell(int x, int y) : m_x(x), m_y(y)
{
	// -
}

void Cell::add_neighb(Cell *c)
{
	this->set_neighb(c);
	c->set_neighb(this);
}

void Cell::add_neighb(Cell *c1, Cell *c2)
{
	this->add_neighb(c1);
	this->add_neighb(c2);
}

void Cell::set_neighb(Cell *c)
{
	delete[] m_backup;
	m_backup = new Cell*[m_nb_neighb];
	if (m_nb_neighb > 0)
	{
		//Backup des voisins actuels de la cellule	
		for (int i=0; i<m_nb_neighb; i++)
		{
			m_backup[i] = m_neighb[i];
		}
		
		//Allocation du tableau de pointeur vers les voisins avec le nouveau nombre de voisins
		m_nb_neighb++;
		delete[] m_neighb;
		m_neighb = new Cell*[m_nb_neighb];
		for (int i=0; i<m_nb_neighb-1; i++)
		{
			m_neighb[i] = m_backup[i];
		}
		m_neighb[m_nb_neighb-1] = c;
	}

	else
	{
		m_nb_neighb++;
		m_neighb = new Cell*[m_nb_neighb];
		m_neighb[m_nb_neighb-1] = c;
	}
}

Cell::~Cell()
{
	delete[] m_backup;
	delete[] m_neighb;
}

std::ostream &operator<<(std::ostream &out, const Cell &c)
{
	out << "(" << c.m_x << "," << c.m_y << ")";
	return out;
}

std::istream &operator>>(std::istream &in, Cell &c)
{
	std::string chain;
	in >> chain;
	if (chain == "")
	{
		c.m_corrupted = true;
		return in;
	}
	chain = chain.substr(1,chain.size()-2);
	c.m_x = std::stoi(chain.substr(0, chain.find(',')));
	c.m_y = std::stoi(chain.substr(chain.find(',')+1, chain.size()));
	return in;
}

bool operator==(const Cell &c1, const Cell &c2)
{
	if (c1.m_x == c2.m_x and c1.m_y == c2.m_y)
		return true;
	else
		return false;
}