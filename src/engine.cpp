
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include <string>
#include <glibmm/unicode.h>
#include <gtkmm/textview.h>

#include "engine.hpp"
#include "engine-impl.hpp"

namespace warg
{

	template class search_engine	<std::string>;
	template class search_plain		<std::string>;
	template class search_regex		<std::string>;

	template class search_engine	<Glib::ustring, Gtk::TextBuffer>;
	template class search_plain		<Glib::ustring, Gtk::TextBuffer>;
	template class search_regex		<Glib::ustring, Gtk::TextBuffer, boost::icu_regex_traits>;

} // namespace warg
