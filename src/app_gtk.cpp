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
		, mp_search_engine(std::make_unique<search_plain<Glib::ustring, Gtk::TextBuffer>>())
	{

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

		Glib::ustring needle{mp_needle->begin(), mp_needle->end()};
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

		auto p_table_results = mp_haystack->get_tag_table();
		auto p_tag_result = Gtk::TextBuffer::Tag::create();
		p_tag_result->property_foreground() = "blue";
		p_table_results->add(p_tag_result);

		list_results results = mp_search_engine->get_results();
		for(auto const & result: results)
			mp_haystack->apply_tag(p_tag_result, result.first, result.second);

		auto p_table_marks = mp_needle->get_tag_table();

		auto p_tag_marks = Gtk::TextBuffer::Tag::create();
		p_tag_marks->property_foreground() = "cyan";
		p_table_marks->add(p_tag_marks);
/*
		typedef search_engine<Glib::ustring, Gtk::TextBuffer>::needle_string::list_pair_it list_marks;
		list_marks const & marks = static_cast<search_regex<Glib::ustring,Gtk::TextBuffer> *>(mp_search_engine)
			->retrieve_marks();
		for(list_marks::const_iterator p_mark = marks.begin()
				; p_mark != marks.end()
				; p_mark++)
			mp_needle->apply_tag(p_tag_result, p_mark->first, p_mark->second);
*/
	}

	void app_gtk::store_results()
	{
		auto const & results = mp_search_engine->get_results();

		unsigned idx = 0;
		for(auto const & result: results)
		{
			++idx;
			Glib::ustring match_caption{result.first, result.second};
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

		decltype(mp_search_engine) p_search_engine;
		switch(id)
		{
			case 1:
				p_search_engine = std::make_unique<search_plain<Glib::ustring,Gtk::TextBuffer>>();
				std::swap(mp_search_engine, p_search_engine);
				break;
/*
			case 2:
				p_search_engine = std::make_unique<search_regex<Glib::ustring,Gtk::TextBuffer>>();
				std::swap(mp_search_engine, p_search_engine);
				break;
*/
			default:
				// XXX throw?
				mp_search_engine.reset();
		}
	}

	void app_gtk::error_clear()
	{
		mp_needle->remove_all_tags(mp_needle->begin(), mp_needle->end());
	}

	void app_gtk::error_display(std::string const & msg, std::ptrdiff_t position)
	{
		auto p_tag = Gtk::TextBuffer::Tag::create();
		p_tag->property_foreground() = "red";

		auto p_table = mp_needle->get_tag_table();
		p_table->add(p_tag);

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

		mp_needle->apply_tag(p_tag, first, second);
		m_window.set_status(msg);
	}

} // namespace warg


