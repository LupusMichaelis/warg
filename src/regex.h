#ifndef H_WARG_MATCHER
#	define H_WARG_MATCHER

#	include <list>
#	include <algorithm>
#	include <iostream>

#	include <boost/regex.hpp>

namespace warg
{
	class matcher
		: public std::unary_function<void,std::string const &>
	{
		protected:
			std::string const & m_line ;
			std::list<std::string> m_results ;

		public:
			matcher(std::string const & line)
				: m_line(line), m_results() { }

			void operator() (std::string const & pattern)
			{
				using namespace boost ;
				regex re(pattern) ;

				smatch matches ;
				match_flag_type flags = match_default ; // | match_perl | match_any ;

				std::string::const_iterator start = m_line.begin() ;
				std::string::const_iterator end = m_line.end() ;

				while(regex_search(start, end, matches, re, flags))
				{
					for(unsigned i = 0 ; i < matches.size() ; i++)
						m_results.push_back(std::string(matches[i].first, matches[i].second)) ;

					start = matches[0].second ;
				}
			}
	} /* class matcher */ ;


} // namespace warg

#endif // H_WARG_MATCHER
