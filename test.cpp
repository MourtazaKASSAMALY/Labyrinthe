#include "doctest.h"
#include <unistd.h>
#include "Cell.h"

TEST_CASE("Ajout de cellules et de voisins")
{
    //Initialisation d'une cellule
    Cell* c= new Cell(0, 0);
    CHECK(c->m_x == 0);
    CHECK(c->m_y == 0);

    //Ajout d'un voisin
    Cell *neighb = new Cell(1, 0);
    c->add_neighb(neighb);
    CHECK(c->m_neighb[0] == neighb);
    CHECK(neighb->m_neighb[0] == c); 

    delete c;
    delete neighb;
}