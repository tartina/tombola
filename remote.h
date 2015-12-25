/*
 * remote.h
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

#ifndef TOMBOLA_REMOTE_H
#define TOMBOLA_REMOTE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <sigc++/sigc++.h>
#include <boost/asio.hpp>
#include <glibmm.h>

#include "callback.h"

using boost::asio::ip::udp;
using Glib::Threads::Thread;

class remote
{
public:
	remote(callback *);
	virtual ~remote();
	void run();
	sigc::signal<void> signal_extract;
private:
	udp::endpoint remote_endpoint;
	char data;
	boost::asio::io_service ios;
	udp::socket socket;
	callback *caller;
	Thread *thread = 0;
	void start_receive();
	void handle_receive(const boost::system::error_code& error, std::size_t);
};

#endif
