/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * window.h
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

#ifndef TOMBOLA_WINDOW_H
#define TOMBOLA_WINDOW_H

#include <gtkmm.h>
#include "bingo.h"

class tombola_window : public Gtk::ApplicationWindow
{
	public:
		tombola_window();
		virtual ~tombola_window();
		static const std::string window_title;

	private:
		bingo *the_numbers;

		Glib::RefPtr<Gtk::IconTheme> icon_theme;

		Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
		Glib::RefPtr<Gtk::UIManager> m_refUIManager;

		Gtk::Box m_Application_Box;
		Gtk::Box main_box;
		Gtk::Box command_box;
		Gtk::Statusbar status_bar;
		Gtk::Grid outer_grid;
		Gtk::Frame card_frame[6];
		Gtk::Grid card_grid[6];
		Gtk::Button number[90];
		Gtk::Button extract;

		inline unsigned short get_card(unsigned short n) {return (n / 30) * 2 + (n % 10) / 5;};
		inline unsigned short get_card_column(unsigned short n) {return n % 5;};
		inline unsigned short get_card_row(unsigned short n) {return (n / 10) % 3;};

		// Signal handlers
		void on_action_file_start();
		void inline on_action_file_quit() {hide();};
		void on_action_help_about();
		void on_extract_button_clicked();
};
#endif