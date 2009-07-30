#ifndef H_WARG_APP
#	define H_WARG_APP

#	include <string>

#	include "config.h"

#	include "regex.h"
/*
#	include "xml.h"
#	include "sql.h"
*/
#	include "engine.h"
#	include "gui.h"

namespace warg
{
	extern char const * c_version ;
	extern char const * c_appname ;

	class app
	{
		protected:
			app() ;

		public:
			static int main(int argc, char **argv) ;

			static const int c_shell_success ;
			static const int c_shell_err_appname  ;
			static const int c_shell_err_todo ;

		public:
			virtual
			void search() = 0 ;
			
			virtual
			~app() ;

			virtual
			void highlight_clear() = 0 ;

			virtual
			void highlight_results() = 0 ;

			virtual
			void store_results() = 0 ;

			virtual
			void unstore_results() = 0 ;

			virtual
			void switch_engine(int const & id) = 0 ;

			virtual
			void error_display(std::string const & msg, std::ptrdiff_t position) = 0 ;

		protected:
			search_engine<Glib::ustring, Gtk::TextBuffer> * mp_search_engine ;

	} /* class app */ ;


	class app_cli
		: public app
	{
			friend class app ;

		public:
			typedef app parent_t ;
			static const std::string c_appname ;

		protected:
			app_cli() ;

		public:
			virtual
			~app_cli() ;

			virtual
			void search() = 0 ;

			virtual
			void highlight_clear() = 0 ;

			virtual
			void highlight_results() = 0 ;

			virtual
			void store_results() = 0 ;

			virtual
			void unstore_results() = 0 ;

			virtual
			void error_clear() = 0 ;

			virtual
			void error_display(std::string msg, std::ptrdiff_t position) = 0 ;

	} /* class app_cli */ ;


	class app_gtk
		: public app
	{
			friend class app ;

		public:
			typedef app parent_t ;
			static const std::string c_appname ;

		protected:
			app_gtk() ;

		protected:
			main_window m_window ;

			//warg::tree_model_cols			m_cols ; // \xxx
			Glib::RefPtr<tree_model>		mp_results ;
			// Glib::RefPtr<Gtk::ListStore>	mp_results ;
			Glib::RefPtr<Gtk::TextBuffer>	mp_haystack ;
			Glib::RefPtr<Gtk::TextBuffer>	mp_needle ;

		public:
			virtual
			~app_gtk() ;

			virtual
			void search() ;

			virtual
			void highlight_clear() ;

			virtual
			void highlight_results() ;

			virtual
			void store_results() ;

			virtual
			void unstore_results() ;

			virtual
			void switch_engine(int const & id) ;

			virtual
			void error_clear() ;

			virtual
			void error_display(std::string const & msg, std::ptrdiff_t position) ;

	} /* class app_gtk */ ;

} // namespace warg

#endif // H_WARG_APP
