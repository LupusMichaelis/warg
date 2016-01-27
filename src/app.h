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
	extern char const * c_version;
	extern char const * c_appname;

	class app
	{
		public:
			static int main(int argc, char **argv);

			static const int c_shell_success;
			static const int c_shell_err_appname;
			static const int c_shell_err_todo;

		public:
			app();

			virtual
			void search() = 0;
			
			virtual
			~app();

			virtual
			void highlight_clear() = 0;

			virtual
			void highlight_results() = 0;

			virtual
			void store_results() = 0;

			virtual
			void unstore_results() = 0;

			virtual
			void switch_engine(int const id) = 0;

			virtual
			void error_display(std::string const & msg, std::ptrdiff_t position) = 0;

	} /* class app */;


} // namespace warg

#endif // H_WARG_APP
