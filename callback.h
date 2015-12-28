/*
 * callback.h
 * Copyright (C) 2015 Guido Aulisi <guido.aulisi@gmail.com>
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

#ifndef CALLBACK_H
#define CALLBACK_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef HAVE_REMOTE

class callback
{
public:
	virtual void call() = 0;
};

#endif // HAVE_REMOTE
#endif
