/*
 * bingo.cc
 * Copyright (C) 2014 Guido Aulisi <guido.aulisi@gmail.com>
 *
 * tombola is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * tombola is distributed in the hope that it will be useful, but
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
#include <random>
#include <ctime>
#include <cstdlib>
#include "bingo.h"

bingo::bingo() : siblings(0), neighbours(0)
{
	unsigned short i;

	the_numbers = new std::vector<unsigned short>;
	for (i = 0; i < 90; ++i) the_numbers->push_back(i);

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(the_numbers->begin(), the_numbers->end(), g);

	current = the_numbers->begin();

#ifdef HAVE_DEBUG
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
	return current != the_numbers->end();
}

unsigned short bingo::get_next()
{
	unsigned short number, old;
	unsigned short card, line;

	siblings = 0;
	neighbours = 0;

	if (has_next()) {
		number = *current;
		card = get_card(number);
		line = get_card_row(number);

		for (std::vector<unsigned short>::const_iterator i = the_numbers->begin(); i != current; ++i) {
			old = *i;
			if (card == get_card(old)) {
				++neighbours;
				if (line == get_card_row(old)) ++siblings;
			}
		}
		++current;
		return (number);
	}
	else return 0;
}

bool bingo::is_bingo() const
{
	return neighbours == 14;
}

const std::string bingo::name[6] = {"Nessuna", "Ambo", "Terno", "Quaterna", "Cinquina", "Tombola"};
