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
 * tombola is distributed in the hope that it will be useful, but
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

protected:
	bool on_delete_event(GdkEventAny* event);

private:
	bingo *the_numbers;
	unsigned short win_status;

	Glib::RefPtr<Gtk::IconTheme> icon_theme;

	Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
	Glib::RefPtr<Gtk::UIManager> m_refUIManager;

	Gtk::Box m_Application_Box;
	Gtk::Box main_box;
	Gtk::Box command_box;
	Gtk::Grid outer_grid;
	Gtk::Frame card_frame[6];
	Gtk::Grid card_grid[6];
	Gtk::Label number[90];
	Gtk::Label current_number[5];
	Glib::Timer timer;
	Gtk::Frame command_frame;
	Gtk::Button extract;
	Gtk::Separator separator;
	Gtk::RadioButton win[6];
	Gtk::Label win_label;
	Glib::RefPtr<Gtk::Action> extract_action;

	static const Gdk::RGBA number_color[6];

	// Signal handlers
	void on_action_file_start();
	bool confirm_quit();
	void on_action_file_quit();
	void on_action_help_about();
	void on_action_file_extract();
	void on_win_button_clicked(unsigned short index);
};
#endif
