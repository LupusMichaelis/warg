#ifndef H_WARG_CLI_APP
#	define H_WARG_CLI_APP

#	include <iostream>
#	include "app.hpp"

namespace warg
{

	class app_cli
		: public app
	{
			friend class app;

		public:
			typedef app parent_t;
			static const std::string c_appname;

		protected:
			std::istream	* mp_in;
			std::ostream	* mp_out;

		public:
			app_cli();

			virtual
			~app_cli();

			void set_in(std::istream * in) { mp_in = in ; }
			void set_out(std::ostream * out) { mp_out = out ; }

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
			void error_clear();

			virtual
			void error_display(std::string msg, std::ptrdiff_t position);

			virtual
			void switch_engine(int const id);
	} /* class app_cli */;


} // namespace warg

#endif // H_WARG_CLI_APP
