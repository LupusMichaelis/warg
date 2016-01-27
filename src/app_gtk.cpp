#include "app_gtk.hpp"

namespace warg
{

	const std::string app_gtk::c_appname = BIN_NAME_GTK;

	app_gtk::~app_gtk()
	{
	}

	app_gtk::app_gtk()
		: app()
		, m_window()
		, mp_results(tree_model::create())
		, mp_haystack(Gtk::TextBuffer::create())
		, mp_needle(Gtk::TextBuffer::create())
		, mp_search_engine(0)
	{
		mp_search_engine = new search_plain<Glib::ustring, Gtk::TextBuffer>;

		m_window.set_size_request(430,330);
		m_window.set_default_size(430,600);
		m_window.move(120, 120);

		mp_haystack->set_text("They are some people who think the answer is 42.");
		mp_needle->set_text("(\\w+) (\\d+)");

		m_window.bind_haystack(mp_haystack);
		m_window.bind_results(mp_results);
		m_window.bind_pattern(mp_needle);
		m_window.signal_match().connect(sigc::mem_fun(*this, &app::search));
		m_window.signal_choose().connect(sigc::mem_fun(*this, &app::switch_engine));

		m_window.show_all();
	}

	void app_gtk::search()
	{
		unstore_results();
		highlight_clear();
		error_clear();

		if(!mp_search_engine)
			return;

		Glib::ustring needle(mp_needle->begin(), mp_needle->end());
		try
		{
			mp_search_engine->set_needle(needle);
		}
		catch(boost::regex_error & e)
		{
			error_display(e.what(), e.position());
			return;
		}

		mp_search_engine->set_haystack(mp_haystack->begin(), mp_haystack->end());

		if(!*mp_search_engine)
			return;

		store_results();
		highlight_results();
	}

	void app_gtk::highlight_clear()
	{
		mp_haystack->remove_all_tags(mp_haystack->begin(), mp_haystack->end());
	}

	void app_gtk::highlight_results()
	{
		// \xxx tag memory leak ?
		//
		// \xxx how can I fetch the system higlight color ?
		// tag->property_background() = "blue";

		Glib::RefPtr<Gtk::TextBuffer::TagTable> table_results = mp_haystack->get_tag_table();
		Glib::RefPtr<Gtk::TextBuffer::Tag> tag_result = Gtk::TextBuffer::Tag::create();
		tag_result->property_foreground() = "blue";
		table_results->add(tag_result);

		list_results results = mp_search_engine->get_results();
		for(list_results::iterator p_result = results.begin()
				; p_result != results.end()
				; p_result++)
			mp_haystack->apply_tag(tag_result
					, p_result->first
					, p_result->second
					);


		Glib::RefPtr<Gtk::TextBuffer::TagTable> table_marks = mp_needle->get_tag_table();

		Glib::RefPtr<Gtk::TextBuffer::Tag> tag_marks = Gtk::TextBuffer::Tag::create();
		tag_marks->property_foreground() = "cyan";
		table_marks->add(tag_marks);

/*
		typedef search_engine<Glib::ustring, Gtk::TextBuffer>::needle_string::list_pair_it list_marks;
		list_marks const & marks = static_cast<search_regex<Glib::ustring,Gtk::TextBuffer> *>(mp_search_engine)
			->retrieve_marks();
		for(list_marks::const_iterator p_mark = marks.begin()
				; p_mark != marks.end()
				; p_mark++)
			mp_needle->apply_tag(tag_result, p_mark->first, p_mark->second);
*/
	}

	void app_gtk::store_results()
	{
		typedef search_engine<Glib::ustring, Gtk::TextBuffer>::haystack_string::list_pair_it list;
		list const & results = mp_search_engine->get_results();

		unsigned idx = 0;
		for(list::const_iterator p_result = results.begin()
				; p_result != results.end()
				; p_result++, idx++)
		{
			Glib::ustring match_caption(p_result->first, p_result->second);
			mp_results->append(idx, match_caption);
		}

		//m_window.set_status(Glib::ustring("Subresults ") + (mp_search_engine->has_subresults() ? "available" : "unavailable"));
	}

	void app_gtk::unstore_results()
	{
		mp_results->clear();
	}

	void app_gtk::switch_engine(int const id)
	{
		highlight_clear();
		unstore_results();
		error_clear();

		if(mp_search_engine)
			delete mp_search_engine;

		switch(id)
		{
			case 1 :
				mp_search_engine = new search_plain<Glib::ustring,Gtk::TextBuffer>;
				break;
/*
			case 2 :
				mp_search_engine = new search_regex<Glib::ustring,Gtk::TextBuffer>;
				break;
*/
			default:
				mp_search_engine = 0;
		}
	}

	void app_gtk::error_clear()
	{
		mp_needle->remove_all_tags(mp_needle->begin(), mp_needle->end());
	}

	void app_gtk::error_display(std::string const & msg, std::ptrdiff_t position)
	{
		Glib::RefPtr<Gtk::TextBuffer::Tag> tag =
		    Gtk::TextBuffer::Tag::create();
		tag->property_foreground() = "red";

		Glib::RefPtr<Gtk::TextBuffer::TagTable> table =
			mp_needle->get_tag_table();
		table->add(tag);

		Gtk::TextBuffer::iterator first, second;

		if(position == mp_needle->size())
		{
			first = mp_needle->get_iter_at_offset(position-1);
			second = mp_needle->get_iter_at_offset(position);
		}
		else
		{
			first = mp_needle->get_iter_at_offset(position);
			second = mp_needle->get_iter_at_offset(position+1);
		}

		mp_needle->apply_tag(tag, first, second);
		m_window.set_status(msg);
	}

} // namespace warg


