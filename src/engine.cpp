
#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include <string>
#include <glibmm/unicode.h>
#include <gtkmm/textview.h>

#include "engine.h"
#include "engine-impl.h"

namespace warg
{

	template class search_engine	<std::string> ;
	template class search_plain		<std::string> ;
	//template class search_regex		<std::string> ;

	template class search_plain		<Glib::ustring, Gtk::TextBuffer>;

} // namespace warg
