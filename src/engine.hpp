#ifndef H_WARG_ENGINE
#	define H_WARG_ENGINE

#	include <exception>
#	include <map>
#	include <list>
#	include <vector>

/*
#	include <gtkmm/textbuffer.h>
*/

#	include <boost/regex.hpp>
#	include <boost/regex/icu.hpp>

namespace warg
{
#if 0
	class search_exception
		: public std::runtime_error
	{
		public:
			explicit search_exception();
			
			virtual
			~search_exception();

		protected:
	} /* class search_exception */;
#endif // 0

	template<typename StrNeedle, typename StrHaystack = StrNeedle>
	class search_engine;

	template<typename StrNeedle, typename StrHaystack = StrNeedle>
	class search_plain;

	template<typename StrNeedle, typename StrHaystack = StrNeedle, typename RegexTraits = boost::regex_traits<typename StrNeedle::value_type>>
	class search_regex;

	// search_engine ////////////////////////////////////////////////////////////////
	template<typename StrNeedle, typename StrHaystack>
	class search_engine
	{
			template<typename Str>
			struct str
			{
				typedef Str								type;
				typedef typename type::iterator			iterator;
				typedef std::pair<iterator, iterator>	pair_it;
				typedef std::vector<pair_it>			list_pair_it;
				typedef std::vector<list_pair_it>		list_list_pair_it;
			} /* struct str<Str> */;

		public:
			typedef str<StrNeedle>		needle_string;
			typedef str<StrHaystack>	haystack_string;

			// typedef std::list<std::pair<typename Str::iterator, typename Str::iterator> > list_pair_it;

		protected:
			typename needle_string::type					m_needle;

			typename haystack_string::pair_it				m_haystack;
			typename haystack_string::list_pair_it			m_results;
			typename haystack_string::list_list_pair_it		m_subresults;

		public:
			search_engine();

			virtual
			~search_engine() { };

			virtual
			operator bool() = 0;

			virtual
			void set_needle(StrNeedle const needle);

			virtual
			void set_haystack
				( typename haystack_string::iterator begin
				, typename haystack_string::iterator end);

			virtual
			typename haystack_string::list_pair_it const &
			get_results() const;

			virtual
			typename haystack_string::list_pair_it const & get_subresults(size_t const idx) const;

			virtual
			bool has_subresults() const;

			virtual
			typename haystack_string::list_pair_it::size_type size_subresults() const;

	} /* class search_engine<StrNeedle,StrHaystack> */;

	template<typename StrNeedle, typename StrHaystack>
	search_engine<StrNeedle,StrHaystack>::search_engine()
		: m_needle()
		, m_haystack()
		, m_results()
	{
	}

	template<typename StrNeedle, typename StrHaystack>
	void search_engine<StrNeedle,StrHaystack>::set_needle(StrNeedle const needle)
	{
		m_needle = needle;
	}

	template<typename StrNeedle, typename StrHaystack>
	void search_engine<StrNeedle,StrHaystack>::set_haystack
	( typename haystack_string::iterator begin
	, typename haystack_string::iterator end)
	{
		m_haystack = typename haystack_string::pair_it(begin, end);
	}

	template<typename StrNeedle, typename StrHaystack>
	typename search_engine<StrNeedle, StrHaystack>::haystack_string::list_pair_it const &
	search_engine<StrNeedle,StrHaystack>::get_results() const
	{
		return m_results;
	}

	template<typename StrNeedle, typename StrHaystack>
	typename search_engine<StrNeedle,StrHaystack>::haystack_string::list_pair_it const & 
	search_engine<StrNeedle,StrHaystack>::get_subresults(size_t const idx) const
	{
		return m_subresults[idx];
	}

	template<typename StrNeedle, typename StrHaystack>
	bool search_engine<StrNeedle,StrHaystack>::has_subresults() const
	{
		return m_subresults.size() > 0;
	}

	template<typename StrNeedle, typename StrHaystack>
	typename search_engine<StrNeedle,StrHaystack>::haystack_string::list_pair_it::size_type
	search_engine<StrNeedle,StrHaystack>::size_subresults() const
	{
		return m_subresults.size();
	}

	// search_regex ////////////////////////////////////////////////////////////////
	template<typename StrNeedle, typename StrHaystack, typename RegexTraits>
	class search_regex
		: public search_engine<StrNeedle, StrHaystack>
	{
		public:
			typedef search_engine<StrNeedle,StrHaystack> parent_t;

			typedef boost::match_results
				<typename parent_t::haystack_string::type::iterator>
				regex_results;

			/*
			typedef boost::basic_regex<typename parent_t::needle_string::type::value_type, RegexTraits>
			*/
			typedef boost::u32regex
				regex_type;

		protected:
			regex_type m_regex;

			typename parent_t::needle_string::list_pair_it m_subexpressions_list;

		public:
			search_regex()
				: parent_t()
				, m_regex()
				, m_subexpressions_list()
			{
			}
			
			virtual
			~search_regex() { }

			virtual
			operator bool ();

			virtual
			void set_needle(StrNeedle const needle);

			virtual
			void // typename parent_t::needle_string::list_pair_it
			retrieve_marks();

	} /* class search_regex<StrNeedle,StrHaystack,RegexTraits> */;

	template<typename StrNeedle, typename StrHaystack, typename RegexTraits>
	void search_regex<StrNeedle, StrHaystack, RegexTraits>::set_needle(StrNeedle const needle)
	{
		this->m_needle = needle;
		m_regex.assign(needle.begin(), needle.end(), regex_type::save_subexpression_location);
	}

	// search_plain ////////////////////////////////////////////////////////////////
	template<typename StrNeedle, typename StrHaystack>
	class search_plain
		: public search_engine<StrNeedle, StrHaystack>
	{
		public:
			typedef search_engine<StrNeedle,StrHaystack> parent_t;

		protected:
			
		public:
			search_plain() : parent_t() { }
			
			virtual
			~search_plain() { }

			virtual
			operator bool ();

	} /* class search_plain<StrNeedle,StrHaystack> */;

	extern template class search_engine<std::string>;
	extern template class search_regex<std::string>;
	extern template class search_plain<std::string>;

} // namespace warg

#endif // H_WARG_ENGINE
