
#include <iostream>

#include <list>
#include <algorithm>
#include <boost/regex.hpp>

#include "app.h"

namespace warg
{
	const int app::c_shell_success = 0 ;
	const int app::c_shell_err_appname = 1 ;
	const int app::c_shell_err_todo = 2 ;

	char const * c_version = VERSION ;
	char const * c_appname = APPNAME ;

#if 0
	const std::string app_gtk::c_appname = BIN_NAME_GTK ;
	const std::string app_cli::c_appname = BIN_NAME_CLI ;

	int app::main(int argc, char **argv)
	{
		std::string app_name(*argv) ;

		/* \xxx app_name must be the filename, not the complete path
		*/
		if(app_name == app_gtk::c_appname)
		{
			Gtk::Main kit(argc, argv) ;
			warg::app_gtk app ;
			Gtk::Main::run(app.m_window) ;
		}
		else if(app_name == app_cli::c_appname)
			return c_shell_err_todo ;
		else
		{
			std::cout
				<< boost::format("The application name (%s) is not recognize.")
				% app_name
				<< std::endl ;

			return c_shell_err_appname ;
		}

		return c_shell_success ;
	}
#endif // 0

	app::app()
	{
	}

	app::~app()
	{
	}

} // namespace warg
