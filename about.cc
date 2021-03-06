/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * about.cc
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

#include <vector>
#include "about.h"

about::about() : authors(1, "Guido Aulisi <guido.aulisi@gmail.com>")
{
	set_program_name(PACKAGE_NAME);
	set_authors(authors);
	set_license_type(Gtk::LICENSE_GPL_3_0);
	set_version("Version " PACKAGE_VERSION);
	set_copyright("Copyright (C) 2014 Guido Aulisi");
	set_comments(PACKAGE_NAME " è una tombola automatica.");
}
