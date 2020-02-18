#ifndef BOOST_BASIC_REGEX_RE_H
#	define BOOST_BASIC_REGEX_RE_H

namespace boost
{

	template <typename charT, typename traits >
	class basic_regex_ex
		: public basic_regex<charT, traits>
	{
		public:
			template <charT, traits >
			friend std::ostream & operator << (std::ostream & out, basic_regex_ex<charT,traits> const & self);
	} /* class basic_regex_ex <charT,traits> */;

} // namespace boost

#endif // BOOST_BASIC_REGEX_RE_H
