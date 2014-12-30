/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * window.cc
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

#include <iostream>

#ifdef HAVE_BOOST_LEXICAL_CAST_HPP
#include <boost/lexical_cast.hpp>
#else
#error We need boost lexical_cast
#endif

#ifdef HAVE_DEBUG
#include <iostream>
#endif

#include "window.h"
#include "about.h"

tombola_window::tombola_window()
	: m_Application_Box(Gtk::ORIENTATION_VERTICAL),
	main_box(Gtk::ORIENTATION_HORIZONTAL, 2),
	command_box(Gtk::ORIENTATION_VERTICAL, 2),
	extract("Estrai")
{
	unsigned short i;
	Gtk::IconInfo icon_info;

	try {
		icon_theme = Gtk::IconTheme::get_default();
#ifdef HAVE_DEBUG
		std::vector<Glib::ustring> paths = icon_theme->get_search_path();
		for (std::vector<Glib::ustring>::const_iterator it = paths.begin();
		     it < paths.end(); ++it)
				std::cout << "Icon search path: " << *it << std::endl;
#endif
		icon_info = icon_theme->lookup_icon(PACKAGE_NAME, 48, Gtk::ICON_LOOKUP_NO_SVG);
#ifdef HAVE_DEBUG
		if (icon_info) std::cout << "Icon path: " << icon_info.get_filename() << std::endl;
#endif
		if (icon_info) set_default_icon_from_file(icon_info.get_filename());
	}
	catch (const Gdk::PixbufError& pixbuf_error) {
		std::cerr << pixbuf_error.what() << std::endl;
	}
	catch (const Glib::FileError& file_error) {
		std::cerr << file_error.what() << std::endl;
	}

	the_numbers = new bingo();

	set_title(window_title);
	set_border_width(6);

	add(m_Application_Box);

	m_refActionGroup = Gtk::ActionGroup::create();
	m_refActionGroup->add( Gtk::Action::create("MenuFile", "_Programma") );
	m_refActionGroup->add( Gtk::Action::create("Inizia", "_Inizia"),
		sigc::mem_fun(*this, &tombola_window::on_action_file_start) );
	m_refActionGroup->add( Gtk::Action::create("Estrai", "_Estrai"),
		sigc::mem_fun(*this, &tombola_window::on_extract_button_clicked) );
	m_refActionGroup->add( Gtk::Action::create("Esci", "E_sci"),
		sigc::mem_fun(*this, &tombola_window::on_action_file_quit) );
	m_refActionGroup->add( Gtk::Action::create("MenuHelp", "_Aiuto") );
	m_refActionGroup->add( Gtk::Action::create("Informazioni", "_Informazioni"),
		sigc::mem_fun(*this, &tombola_window::on_action_help_about) );

	m_refUIManager = Gtk::UIManager::create();
	m_refUIManager->insert_action_group(m_refActionGroup);
	add_accel_group(m_refUIManager->get_accel_group());

	Glib::ustring ui_info =
		"<ui>"
		"  <menubar name='MenuBar'>"
		"    <menu action='MenuFile'>"
		"      <menuitem action='Inizia'/>"
		"      <menuitem action='Estrai'/>"
		"      <separator/>"
		"      <menuitem action='Esci'/>"
		"    </menu>"
		"    <menu action='MenuHelp'>"
		"      <menuitem action='Informazioni'/>"
		"    </menu>"
		"  </menubar>"
		"</ui>";

	m_refUIManager->add_ui_from_string(ui_info);

	Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");
	m_Application_Box.pack_start(*pMenubar, Gtk::PACK_SHRINK);

	for (i = 0; i < 90; i++) {
		number[i].set_text(boost::lexical_cast<std::string>(i + 1));
		number[i].set_editable(false);
		number[i].set_sensitive(false);
		number[i].override_font(Pango::FontDescription("Monospace 24"));
		number[i].set_width_chars(2);
		number[i].set_alignment(Gtk::ALIGN_CENTER);
		card_grid[get_card(i)].attach(number[i], get_card_column(i), get_card_row(i), 1, 1);
	}
	for (i = 0; i < 6; i++) {
		card_grid[i].set_border_width(4);
		card_grid[i].set_row_spacing(8);
		card_grid[i].set_column_spacing(8);
		card_grid[i].set_column_homogeneous(true);

		card_frame[i].add(card_grid[i]);
		card_frame[i].set_border_width(2);
		card_frame[i].set_label("Cartella " + boost::lexical_cast<std::string>(i + 1));
		card_frame[i].set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
		outer_grid.attach(card_frame[i], i % 2, i / 2, 1, 1);
	}
	outer_grid.set_row_spacing(5);
	outer_grid.set_column_spacing(5);

	extract.signal_clicked().connect(sigc::mem_fun(*this,
		&tombola_window::on_extract_button_clicked));
	current_number.set_editable(false);
	current_number.set_sensitive(false);
	current_number.override_font(Pango::FontDescription("Monospace 24"));
	current_number.override_color(Gdk::RGBA("Black"));
	current_number.set_width_chars(2);
	current_number.set_alignment(Gtk::ALIGN_CENTER);
	command_box.pack_start(extract, Gtk::PACK_SHRINK);
	command_box.pack_start(current_number, Gtk::PACK_SHRINK);

	main_box.pack_start(outer_grid, Gtk::PACK_SHRINK);
	main_box.pack_start(command_box, Gtk::PACK_SHRINK);
	m_Application_Box.pack_start(main_box, Gtk::PACK_SHRINK);

	show_all_children();
}

tombola_window::~tombola_window()
{
	delete the_numbers;
	the_numbers = 0;
}

void tombola_window::on_action_file_start()
{
	Gtk::MessageDialog* dialog;
	int result;

	dialog = new Gtk::MessageDialog("Ricomincio la tombola?", false,
	                               Gtk::MESSAGE_QUESTION,
	                               Gtk::BUTTONS_OK_CANCEL,
	                               true);
	dialog->set_transient_for(*this);
	result = dialog->run();
	if (result == Gtk::RESPONSE_OK) {
		delete the_numbers;
		the_numbers = 0;
		the_numbers = new bingo();
		for (unsigned short i = 0; i < 90; i++) {
			number[i].unset_color();
			number[i].unset_background_color();
		}
		extract.set_sensitive(true);
		current_number.set_text("");
	}
	delete dialog;
}

void tombola_window::on_action_help_about()
{
	about* dialog = new about();
	dialog->set_transient_for(*this);
	dialog->run();
	delete dialog;
}

void tombola_window::on_extract_button_clicked()
{
	unsigned short i;

	if (timer.elapsed() < 1) return;
	if (the_numbers->has_next()) {
		i = the_numbers->get_next();
#ifdef HAVE_DEBUG
		std::cout << number[i].get_state_flags() << ":";
#endif
		number[i].override_color(Gdk::RGBA("Black"));
		number[i].override_background_color(number_color[get_card(i)]);
		current_number.set_text(boost::lexical_cast<std::string>(i + 1));
#ifdef HAVE_DEBUG
		std::cout << number[i].get_state_flags() << std::endl;
#endif
		timer.reset();
	}
	else extract.set_sensitive(false);
}

const std::string tombola_window::window_title = "Tombola";

const Gdk::RGBA tombola_window::number_color[6] = {Gdk::RGBA("Red"), Gdk::RGBA("Blue"), Gdk::RGBA("Green"),
	Gdk::RGBA("Orange"), Gdk::RGBA("Yellow"), Gdk::RGBA("Purple")};
