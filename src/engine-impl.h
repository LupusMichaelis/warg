#ifndef H_WARG_IMPL_ENGINE
#	define H_WARG_IMPL_ENGINE
#else



#ifdef DEBUG
#	include <iostream>
#endif // DEBUG

#include "engine.h"

#include <algorithm>
#include <boost/format.hpp>

namespace warg
{
	// search_plain ////////////////////////////////////////////////////////////////
	template<typename StrNeedle, typename StrHaystack>
	search_plain<StrNeedle,StrHaystack>::operator bool ()
	{
#ifdef DEBUG
		/*
		std::cout 
			<< boost::format("Search (%s) in (%s)")
				% Glib::ustring(this->m_needle.first, this->m_needle.second)
				% Glib::ustring(this->m_haystack.first, this->m_haystack.second)
			<< std::endl ;
			*/
#endif // DEBUG

		this->m_results.clear() ;

		typename parent_t::haystack_string::type::iterator p_offset = this->m_haystack.first ;
		typename parent_t::haystack_string::type::iterator p_match ;

		typename parent_t::needle_string::type::iterator::difference_type needle_size ;
		needle_size = this->m_needle.size() ;
		
#ifdef DEBUG
		std::cout 
			<< boost::format("Needle size (%d)")
				% needle_size
			<< std::endl ;
#endif // DEBUG

		if(needle_size < 1)
			return true ;

		do
		{
			p_match = std::search(p_offset, this->m_haystack.second
					, this->m_needle.begin(), this->m_needle.end()) ;

			if(p_match != this->m_haystack.second)
			{
				typename parent_t::haystack_string::pair_it result(p_match, p_match) ;
				typename parent_t::needle_string::type::iterator::difference_type size = needle_size ;
				// \xxx
				// can't add needle_size, because some iterators (like
				// Gtk::TextModel::TextIter)
				// cast to bool and don't overload
				// iterator operator+(int)
				// and
				// iterator operator-(int)
				while(size--)	result.second++ ;

				this->m_results.push_back(result) ;
				p_offset = result.second ;
			}
		}
		while(p_match != this->m_haystack.second) ;

		return !this->m_results.empty() ;
	}

	// search_regex ////////////////////////////////////////////////////////////////

	template<typename StrNeedle, typename StrHaystack>
	search_regex<StrNeedle,StrHaystack>::operator bool ()
	{
		this->m_results.clear() ;
		retrieve_marks() ;

		boost::match_results<typename parent_t::haystack_string::type::iterator> matches  ;

		typename parent_t::haystack_string::type::iterator
			start = this->m_haystack.first
			, end = this->m_haystack.second ;

		boost::match_flag_type flags = boost::match_default ;
		flags |= boost::match_perl ;
		flags |= boost::match_any ;
		// flags |= match_not_null ;

		/*
		std::cout << boost::format("submatches (%u) Position 1 (%u) sub()")
				% m_regex.mark_count()
				% matches.position(0)
				<< std::endl ;
		*/

		while(start != end and regex_search(start, end, matches, m_regex, flags))
		{
			this->m_results.push_back(matches[0]) ;

			if(matches.size() > 1)
			{
				typename parent_t::haystack_string::list_pair_it subresults ;

				for(unsigned idx = 1 ; idx < matches.size() ; idx++)
					subresults.push_back(matches[idx]) ;

				this->m_subresults.push_back(subresults) ;
			}

			if(matches[0].first == matches[0].second)
				start++ ;
			else
				start = matches[0].second ;

			flags |= boost::match_prev_avail; 
			flags |= boost::match_not_bob; 
		}

		return true ;
	}

	template<typename StrNeedle, typename StrHaystack>
	typename search_engine<StrNeedle,StrHaystack>::needle_string::list_pair_it
	search_regex<StrNeedle,StrHaystack>::retrieve_marks()
	{
		m_marks_list.clear() ;

		for(size_t index ; index < m_regex.mark_count() ; index++)
			m_marks_list.push_back(m_regex.get_mark(index)) ;

		return m_marks_list ;
	}

} // namespace warg

#endif // H_WARG_IMPL_ENGINE