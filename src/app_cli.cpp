
#include "app_cli.hpp"


namespace warg
{
	const std::string app_cli::c_appname = BIN_NAME_CLI;

	app_cli::app_cli(int argc, char *argv[])
		: app {argc, argv}
	{
	}

	app_cli::~app_cli()
	{
	}

	void app_cli::search()
	{
	}

	void app_cli::highlight_clear()
	{
	}

	void app_cli::highlight_results()
	{
	}

	void app_cli::store_results()
	{
	}

	void app_cli::unstore_results()
	{
	}

	void app_cli::error_clear()
	{
	}

	void app_cli::error_display(std::string msg, std::ptrdiff_t position)
	{
	}

	void app_cli::switch_engine(int const id)
	{
	}
} // namespace warg
