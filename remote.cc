/*
 * remote.cc
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <boost/bind.hpp>
#include "remote.h"

using boost::asio::ip::udp;
using Glib::Threads::Thread;

remote::remote() : socket(ios, udp::endpoint(udp::v4(), 50000))
{
	start_receive();
}

remote::~remote()
{
	ios.stop();
	thread->join();
}

void remote::run(callback *caller)
{
	this->caller = caller;
	try {
		thread = Thread::create(boost::bind<void>(&boost::asio::io_service::run, &ios));
	}
	catch (const Glib::Threads::ThreadError& thread_error) {
		std::cerr << thread_error.what() << std::endl;
	}
}

void remote::start_receive()
{
	socket.async_receive_from(boost::asio::buffer(&data, 1), remote_endpoint,
		boost::bind(&remote::handle_receive, this,
		boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void remote::handle_receive(const boost::system::error_code& error, std::size_t)
{
	if (!error || error == boost::asio::error::message_size) {
		if (data == 'N') caller->call();
	}
	start_receive();
}
