#ifndef H_WARG_GTK_APP
#	define H_WARG_GTK_APP

#	include "app.hpp"

#	include <memory>

namespace warg
{
	extern char const * c_appdsn;

	class app_gtk
		: public app
	{
			friend class app;

		public:
			typedef app parent_t;
			static const std::string c_appname;

			app_gtk(int argc, char **argv);

		protected:
			std::unique_ptr<main_window>	mp_window;
			//warg::tree_model_cols			m_cols ; // \xxx
			Glib::RefPtr<tree_model>		mp_results;
			// Glib::RefPtr<Gtk::ListStore>	mp_results;
			Glib::RefPtr<Gtk::TextBuffer>	mp_haystack;
			Glib::RefPtr<Gtk::TextBuffer>	mp_needle;

			typedef search_engine<Glib::ustring, Gtk::TextBuffer> search_engine_type;
			typedef search_engine_type::haystack_string::list_pair_it list_results;
			std::unique_ptr<search_engine_type> mp_search_engine;

		public:
			virtual
			~app_gtk();

			virtual
			int run();

			virtual
			void search();

			virtual
			void highlight_clear();

			virtual
			void highlight_results();

			virtual
			void store_results();

			virtual
			void unstore_results();

			virtual
			void switch_engine(int const id);

			virtual
			void error_clear();

			virtual
			void error_display(std::string const & msg, std::ptrdiff_t position);

		private:
			Glib::RefPtr<Gtk::Application> mp_app;

	} /* class app_gtk */;


} // namespace warg
#endif // H_WARG_GTK_APP
