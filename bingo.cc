/*
 * bingo.cc
 * Copyright (C) 2014 Guido Aulisi <guido.aulisi@gmail.com>
 *
 * tombola is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * pg800 is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_DEBUG
#include <iostream>
#endif

#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "bingo.h"

bingo::bingo()
{
	unsigned short i;

	std::srand(unsigned(std::time(0)));

	current = 0;
	the_numbers = new std::vector<unsigned short>;

	for (i = 0; i < 90; i++) the_numbers->push_back(i);

  std::random_shuffle(the_numbers->begin(), the_numbers->end());

#ifdef HAVE_DEBUG
  // print out content:
  std::cout << "Numeri tombola: ";
  for (std::vector<unsigned short>::iterator it=the_numbers->begin(); it!=the_numbers->end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
#endif
}

bingo::~bingo()
{
	delete the_numbers;
	the_numbers = 0;
}

bool bingo::has_next() const
{
	return current < 90;
}

unsigned short bingo::get_next()
{
	if (current < 90)	return the_numbers->at(current++);
	else return 0;
}
