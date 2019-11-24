#ifndef __PATH_H__
#define __PATH_H__

#include "Cell.h"
#include "vibes.h"

class Path
{
	public:
		Path(const Cell *c);
		~Path();
		void add_to_path(const Cell *c);
		void display_path();

	public:
		const Cell *m_c;
		Path *m_next = NULL;
};

#endif