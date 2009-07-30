
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include <string>
#include <glibmm/unicode.h>
#include <gtkmm/textbuffer.h>

#include "engine-impl.h"
#include "engine-impl.h"

namespace warg
{
	template class search_engine	<std::wstring> ;
	template class search_plain		<std::wstring> ;
	template class search_regex		<std::wstring> ;

	template class search_engine	<std::string> ;
	template class search_plain		<std::string> ;
	template class search_regex		<std::string> ;

	template class search_engine	<Glib::ustring> ;
	template class search_plain		<Glib::ustring> ;
	template class search_regex		<Glib::ustring> ;

	template class search_engine	<Glib::ustring, Gtk::TextBuffer> ;
	template class search_plain		<Glib::ustring, Gtk::TextBuffer> ;
	template class search_regex		<Glib::ustring, Gtk::TextBuffer> ;

} // namespace warg
