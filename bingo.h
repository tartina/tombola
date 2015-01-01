/*
 * bingo.h
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

#ifndef TOMBOLA_BINGO_H
#define TOMBOLA_BINGO_H

#include <vector>
#include <string>

class bingo
{
public:
	bingo();
	virtual ~bingo();

	bool has_next() const;
	unsigned short get_next();
	unsigned short get_siblings() const {return siblings;};
	bool is_bingo() const;

	static inline unsigned short get_card(unsigned short n) {return (n / 30) * 2 + (n % 10) / 5;};
	static inline unsigned short get_card_column(unsigned short n) {return n % 5;};
	static inline unsigned short get_card_row(unsigned short n) {return (n / 10) % 3;};

	static const std::string name[6];

private:
	std::vector<unsigned short> *the_numbers;
	std::vector<unsigned short>::const_iterator current;
	unsigned short siblings;
	unsigned short neighbours;
};
#endif
