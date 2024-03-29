
#include <iostream>

#include <list>
#include <algorithm>
#include <boost/regex.hpp>

#include "app.hpp"
#include "app_gtk.hpp"
#include "app_cli.hpp"

namespace warg
{
	const int app::c_shell_success = 0;
	const int app::c_shell_err_appname = 1;
	const int app::c_shell_err_todo = 2;

	char const * c_version = VERSION;
	char const * c_appname = APPNAME;

	int app::main(int argc, char **argv)
	{
		std::string app_name{*argv};

		if(app_name.cend() != std::find_end(app_name.cbegin(), app_name.cend(), std::begin(app_gtk::c_appname), std::end(app_gtk::c_appname)))
		{
			auto p_app = std::make_unique<app_gtk>(argc, argv);
			return p_app->run();
		}
		else if(app_name.cend() != std::find_end(app_name.cbegin(), app_name.cend(), std::begin(app_cli::c_appname), std::end(app_cli::c_appname)))
			return c_shell_err_todo;
		else
		{
			std::cout
				<< boost::format("The application name (%s) is not recognize.")
				% app_name
				<< std::endl;

			return c_shell_err_appname;
		}

		return c_shell_success;
	}

	app::app(int argc, char **argv)
		: m_argc {argc}
		, m_argv {argv}
	{
	}

	app::~app()
	{
	}

} // namespace warg
