#include "app.h"
#include "gui.h"
#include "config.h"

#if DEBUG
#	include <iostream>
#endif // DEBUG

namespace warg
{
	main_menubar::main_menubar()
		: parent_t()

		, m_menu_file()
		, m_menu_edit()
		, m_menu_about()

		, m_file(_("File"))
		, m_file_open(_("Open"))
		, m_file_save(_("Save"))
		, m_edit(_("Edit"))
		, m_edit_copy(_("Copy"))
		, m_edit_paste(_("Paste"))
		, m_edit_cut(_("Cut"))
		, m_about(_("About"))
	{
		m_file.set_submenu(m_menu_file);

		m_menu_file.append(m_file_open);
		m_menu_file.append(m_file_save);
		m_file.set_submenu(m_menu_file);
		append(m_file);

		m_menu_edit.append(m_edit_copy);
		m_menu_edit.append(m_edit_paste);
		m_menu_edit.append(m_edit_cut);
		m_edit.set_submenu(m_menu_edit);
		append(m_edit);

		m_about.set_right_justified();
		append(m_about);

		for(Gtk::Menu::MenuList::iterator mi = items().begin()
				; mi != items().end()
				; mi++) mi->set_sensitive(false);

		/*
		using namespace boost::lambda;
		std::for_each(items().begin(), items().end()
			, bind(&Gtk::Widget::set_sensitive, _1, false));
		*/

		m_about.set_sensitive();
	}

	Glib::SignalProxy0<void> main_menubar::signal_about()
	{
		return m_about.signal_select();
	}

	engine_switcher::engine_switcher()
		: parent_t(_("Select engine"))
		, m_plain(_("Plain"))
		, m_regex(_("Regex"))
		, m_container()
		, m_signal_choose()
	{
		Gtk::RadioButton::Group grp = m_plain.get_group();
		m_regex.set_group(grp);

		m_container.pack_start(m_plain, Gtk::PACK_SHRINK);
		m_container.pack_start(m_regex, Gtk::PACK_SHRINK);
		add(m_container);

		// \xxx avoid hard coded parameter
		m_plain.signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &engine_switcher::on_signal_choose), 1));
		m_regex.signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &engine_switcher::on_signal_choose), 2));
	}

	sigc::signal<void,int> & engine_switcher::signal_choose()
	{
		return m_signal_choose;
	}

	void engine_switcher::on_signal_choose(int idx)
	{
		m_signal_choose(idx);
	}

	engine_switcher::~engine_switcher()
	{
	}

	frame_dialog::~frame_dialog()
	{
	}

	frame_dialog::frame_dialog
		( Glib::ustring const & caption
		, Glib::ustring const & action_label)
		: parent_t(caption)
		, m_input()
		, m_submit(action_label)
		, m_container()
	{
		m_container.pack_start(m_input);
		m_container.pack_end(m_submit, false, 0);
		
		add(m_container);
	}

	Glib::SignalProxy0<void> frame_dialog::signal_submit()
	{
		return m_submit.signal_clicked();
	}

	void frame_dialog::set_buffer(Glib::RefPtr<Gtk::TextBuffer> const & buffer)
	{
		m_input.set_buffer(buffer);
	}

	main_window::main_window()
		: parent_t()
		, m_input_frame
			( _("Pattern")
			, _("Match !")
			)
		, m_switcher()
		, m_text()
		, m_results()
		, m_status()
		, m_menu()
		, m_container(false)

		, m_about_dlg()
	{ 
		set_title(c_appname);

		set_border_width(5);

		m_container.pack_start(m_menu, false, 0);
		m_container.pack_start(m_input_frame, false, 0);
		m_container.pack_start(m_switcher, Gtk::PACK_SHRINK);
		m_container.pack_start(m_text, Gtk::PACK_SHRINK);
		m_container.pack_start(m_results);
		m_container.pack_start(m_status, false, 0);

		m_text.set_size_request(-1, 150);

		add(m_container);

		m_about_dlg.set_transient_for(*this);
		m_menu.signal_about().connect
			(sigc::mem_fun(*this, &main_window::on_about) );
	}

	void main_window::on_about()
	{
		m_about_dlg.show();
	}

	void main_window::bind_pattern(Glib::RefPtr<Gtk::TextBuffer> & p_model)
	{
		m_input_frame.set_buffer(p_model);
	}

	void main_window::bind_haystack(Glib::RefPtr<Gtk::TextBuffer> & p_model)
	{
		m_text.set_buffer(p_model);
	}

	void main_window::bind_results(Glib::RefPtr<tree_model> & p_model)
	{
		m_results.set_model(p_model);
	}

	void tree_view::set_model(Glib::RefPtr<Gtk::TreeModel> const & p_model)
	{
		parent_t::set_model(p_model);

		Glib::RefPtr<tree_model> const & lp_model =
			Glib::RefPtr<tree_model>::cast_static(p_model);

		append_column(_("Index"), lp_model->get_index_column());
		append_column(_("Match"), lp_model->get_match_column());
	}

	Glib::SignalProxy0<void> main_window::signal_match()
	{
		return m_input_frame.signal_submit();
	}

	sigc::signal<void,int> & main_window::signal_choose()
	{
		return m_switcher.signal_choose();
	}

	void main_window::set_status(Glib::ustring const & status)
	{
		m_status.push(status);
	}

	tree_model::tree_model()
		: parent_t()
		, m_index()
		, m_match()
	{
		Gtk::TreeModelColumnRecord cols;
		cols.add(m_index);
		cols.add(m_match);

		set_column_types(cols);
	}

	Glib::RefPtr<tree_model> tree_model::create()
	{
		return Glib::RefPtr<tree_model>(new tree_model);
	}

	Gtk::TreeModelColumn<unsigned> & tree_model::get_index_column()
	{
		return m_index;
	}

	Gtk::TreeModelColumn<unsigned> const & tree_model::get_index_column() const
	{
		return const_cast<Gtk::TreeModelColumn<unsigned> & >(m_index);
	}

	Gtk::TreeModelColumn<Glib::ustring> & tree_model::get_match_column()
	{
		return m_match;
	}

	Gtk::TreeModelColumn<Glib::ustring> const & tree_model::get_match_column() const
	{
		return const_cast<Gtk::TreeModelColumn<Glib::ustring> & >(m_match);
	}

	void tree_model::append(guint index, Glib::ustring & matched)
	{
		tree_model::Row row = *(parent_t::append());

		row.set_value(m_index, index);
		row.set_value(m_match, matched);
	}

	about_dialog::~about_dialog()
	{
	}

	about_dialog::about_dialog()
		: parent_t()
	{
		using boost::format;

		set_title((format(_("About %s")) % c_appname).str());
		set_comments(_("An application to ride through datas with some sort of query."));
		set_copyright("Mickael Wolff <mickael@lupusmic.org>");

		set_website("http://warg.lupusmic.org");
		set_website_label(_("Warg website"));

		set_program_name(c_appname);
		set_version(c_version);

		/** \bug can't find what signal connect for catching close
		 *  button
		 *
		*/
		signal_response().connect
			(sigc::mem_fun(*this, &about_dialog::on_response) );
	}

	void about_dialog::on_response(int response_id)
	{
		hide();
		parent_t::on_response(response_id);
	}

} // namespace warg
