#ifndef H_WARG_GUI
#	define H_WARG_GUI

#	include <gtkmm.h>
#	include <gtkmm/window.h>
#	include <gtkmm/textview.h>
#	include <gtkmm/button.h>
#	include <gtkmm/listviewtext.h>

#	include <boost/format.hpp>
#	include <boost/lambda/lambda.hpp>

#	define GETTEXT_PACKAGE "gtk20"
#	include <glib/gi18n.h>

namespace warg
{
	class about_dialog
		: public Gtk::AboutDialog
	{
		protected:
			typedef Gtk::AboutDialog parent_t;

		public:
			about_dialog();
			~about_dialog();

			virtual
			void on_response(int response_id);

	} /* class about_dialog */;

	class main_menubar
		: public Gtk::MenuBar
	{
		protected:
			typedef Gtk::MenuBar parent_t;

		protected:
			Gtk::Menu m_menu_file;
			Gtk::Menu m_menu_edit;
			Gtk::Menu m_menu_about;

			Gtk::MenuItem m_file;
			Gtk::MenuItem m_file_open;
			Gtk::MenuItem m_file_save;
			Gtk::MenuItem m_edit;
			Gtk::MenuItem m_edit_copy;
			Gtk::MenuItem m_edit_paste;
			Gtk::MenuItem m_edit_cut;
			Gtk::MenuItem m_about;

		public:
			main_menubar();

			virtual
			Glib::SignalProxy0<void> signal_about();

	} /* class main_menu */;

	class engine_switcher
		: public Gtk::Frame
	{
		public:
			typedef Gtk::Frame parent_t;

		protected:
			// std::list<Gtk::RadioButton> m_radios;
			Gtk::RadioButton	m_plain;
			Gtk::RadioButton	m_regex;
			Gtk::HBox			m_container;

			sigc::signal<void, int> m_signal_choose;

		public:
			engine_switcher();
			~engine_switcher();

			virtual
			sigc::signal<void,int> & signal_choose();

			virtual
			void on_signal_choose(int idx);

	} /* class engine_switcher */;

	class frame_dialog
		: public Gtk::Frame
	{
		public:
			typedef Gtk::Frame parent_t;

		protected:
			Gtk::TextView	m_input;
			Gtk::Button		m_submit;
			Gtk::HBox		m_container;

		public:
			frame_dialog
				( Glib::ustring const & caption
				, Glib::ustring const & action_label);

			virtual
			Glib::SignalProxy0<void> signal_submit();

			void set_buffer(Glib::RefPtr<Gtk::TextBuffer> const & buffer);

			virtual
			~frame_dialog();

	} /* class frame_dialog */;

	class tree_view
		: public Gtk::TreeView
	{
		public:
			typedef Gtk::TreeView parent_t;

		public:
			virtual
			void set_model(const Glib::RefPtr<Gtk::TreeModel> & model);
	} /* class tree_view */;

	class tree_model
		: public Gtk::ListStore
	{
		public:
			typedef Gtk::ListStore parent_t;
			typedef parent_t::Row Row;

			static Glib::RefPtr<tree_model> create();

		protected:
			Gtk::TreeModelColumn<guint> m_index;
			Gtk::TreeModelColumn<Glib::ustring> m_match;

		public:
			tree_model();

			Gtk::TreeModelColumn<guint> &				get_index_column();
			Gtk::TreeModelColumn<guint> const &			get_index_column() const;
			Gtk::TreeModelColumn<Glib::ustring> &		get_match_column();
			Gtk::TreeModelColumn<Glib::ustring> const &	get_match_column() const;

			void append(guint index, Glib::ustring & matched);

	} /* class tree_model */;


	class app_gtk;

	class main_window
		: public Gtk::Window
	{
		protected:
			typedef Gtk::Window parent_t;

		protected:
			frame_dialog	m_input_frame;
			engine_switcher m_switcher;
			Gtk::TextView	m_text;
			tree_view		m_results;
			Gtk::Statusbar	m_status;
			main_menubar	m_menu;
			Gtk::VBox		m_container;

			about_dialog	m_about_dlg;

		public:
			main_window(app_gtk & main_app);

			virtual
			void bind_haystack(Glib::RefPtr<Gtk::TextBuffer> & p_model);

			virtual
			void bind_pattern(Glib::RefPtr<Gtk::TextBuffer> & p_model);

			virtual
			void bind_results(Glib::RefPtr<tree_model> & p_model);

			virtual
			void set_status(Glib::ustring const & status);

			virtual
			Glib::SignalProxy0<void> signal_match();

			virtual
			sigc::signal<void,int> & signal_choose();

			virtual
			void on_about();

	} /* class main_window */;

} // namespace warg

#endif // H_WARG_GUI
