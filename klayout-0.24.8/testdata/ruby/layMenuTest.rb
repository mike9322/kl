
$:.push(File::dirname($0))

load("test_prologue.rb")

class LAYMenuTest_TestClass < TestBase

  def test_1

    app = RBA::Application.instance
    mw = app.main_window
    menu = mw.menu

    app.set_config( "ruler-templates", "" )

    def item_str( menu ) 
      def collect_children(space, menu, item)
        res = "#{space}#{item}\n"
        menu.items(item).each { |child| res += collect_children("  #{space}", menu, child) }
        return res;
      end
      res = ""
      menu.items("").each { |item| res += collect_children("", menu, item) }
      return res
    end

    # since the menu is somewhat dynamic, this is not really a good idea
    # (in addition, the menu depends on the mode - editable or not)
    if false
      assert_equal( item_str(menu), <<RESULT )
file_menu
...
  @hcp_context_menu.save_as
RESULT
    end

    menu.delete_item("@toolbar.partial")
    menu.delete_item("@toolbar.instance")
    menu.delete_item("@toolbar.polygon")
    menu.delete_item("@toolbar.box")
    menu.delete_item("@toolbar.path")
    menu.delete_item("@toolbar.text")
    menu.delete_item("@hcp_context_menu")
    menu.delete_item("@lcp_context_menu")
    menu.delete_item("help_group")
    menu.delete_item("tools_menu")
    menu.delete_item("edit_menu")
    menu.delete_item("file_menu.reader_options")
    menu.delete_item("file_menu.session_group")
    menu.delete_item("file_menu.restore_session")
    menu.delete_item("file_menu.save_session")
    menu.delete_item("zoom_menu")

    $a1 = RBA::Action::new
    $a1.title = "New title"
    $a1.icon_text = "X"
    $a1.shortcut = "Shift+Ctrl+F7"
    menu.insert_menu( "end", "my_menu", "My menu" )
    menu.insert_item( "my_menu.end", "new_item", $a1 )
    menu.insert_item( "file_menu.begin", "new_item_1", $a1 )
    menu.insert_separator( "file_menu.#3", "sep" )
    menu.insert_item( "file_menu.#3", "new_item_2", $a1 )

    assert_equal( menu.action("my_menu").title, "My menu" )

    if false # disabled because hard to keep updated
    assert_equal( item_str(menu), <<RESULT )
file_menu
  file_menu.new_item_1
  file_menu.new_layout
  file_menu.new_panel
  file_menu.new_item_2
  file_menu.sep
  file_menu.post_new_group
  file_menu.open
  file_menu.open_same_panel
  file_menu.open_new_panel
  file_menu.close
  file_menu.clone
  file_menu.reload
  file_menu.pull_in
  file_menu.open_recent_group
  file_menu.open_recent_menu
  file_menu.import_group
  file_menu.import_menu
    file_menu.import_menu.import_gerber_menu
      file_menu.import_menu.import_gerber_menu.import_gerber_new
      file_menu.import_menu.import_gerber_menu.import_gerber_new_free
      file_menu.import_menu.import_gerber_menu.import_gerber_open
      file_menu.import_menu.import_gerber_menu.import_gerber_recent
    file_menu.import_menu.import_stream
    file_menu.import_menu.import_lef
    file_menu.import_menu.import_def
  file_menu.save_group
  file_menu.save
  file_menu.save_as
  file_menu.setup_group
  file_menu.setup
  file_menu.misc_group
  file_menu.screenshot
  file_menu.layout_props
  file_menu.layer_group
  file_menu.load_layer_props
  file_menu.save_layer_props
  file_menu.exit_group
  file_menu.exit
bookmark_menu
  bookmark_menu.goto_bookmark_menu
  bookmark_menu.bookmark_view
  bookmark_menu.bookmark_mgm_group
  bookmark_menu.manage_bookmarks
  bookmark_menu.load_bookmarks
  bookmark_menu.save_bookmarks
help_menu
  help_menu.about
@toolbar
  @toolbar.select
  @toolbar.move
  @toolbar.ruler
my_menu
  my_menu.new_item
RESULT
    end

    assert_equal( menu.is_valid?( "file_menu.#0" ), true )
    assert_equal( menu.is_valid?( "fill_menu" ), false )
    assert_equal( menu.is_menu?( "fill_menu" ), false )
    assert_equal( menu.is_menu?( "file_menu" ), true )
    assert_equal( menu.is_menu?( "file_menu.#0" ), false )
    assert_equal( menu.is_separator?( "fill_menu" ), false )
    assert_equal( menu.is_separator?( "file_menu.#0" ), false )
    assert_equal( menu.is_separator?( "file_menu.sep" ), true )

    assert_equal( menu.action( "file_menu.#0" ).title, "New title" )
    assert_equal( menu.action( "file_menu.#0" ).shortcut, "Ctrl+Shift+F7" )
    assert_equal( menu.action( "file_menu.#3" ).icon_text, "X" )
    assert_equal( menu.action( "my_menu.new_item" ).is_visible?, true )
    assert_equal( menu.action( "file_menu.#3" ).is_checked?, false )
    assert_equal( menu.action( "my_menu.new_item" ).is_enabled?, true )

    $a1.visible = false
    assert_equal( menu.action( "my_menu.new_item" ).is_visible?, false )
    assert_equal( menu.action( "my_menu.new_item" ).is_checked?, false )
    assert_equal( menu.action( "my_menu.new_item" ).is_enabled?, false )

    $a1.checked = true
    assert_equal( menu.action( "file_menu.#3" ).is_visible?, false )
    assert_equal( menu.action( "file_menu.#3" ).is_checked?, false )
    assert_equal( menu.action( "file_menu.#3" ).is_checkable?, false )
    assert_equal( menu.action( "file_menu.#3" ).is_enabled?, false )

    $a1.checkable = true;
    assert_equal( menu.action( "my_menu.new_item" ).is_visible?, false )
    assert_equal( menu.action( "my_menu.new_item" ).is_checked?, false )
    assert_equal( menu.action( "my_menu.new_item" ).is_checkable?, true )
    assert_equal( menu.action( "my_menu.new_item" ).is_enabled?, false )
    $a1.checked = true
    assert_equal( menu.action( "file_menu.#0" ).is_checked?, true )

    $a1.enabled = false
    assert_equal( menu.action( "my_menu.new_item" ).is_visible?, false )
    assert_equal( menu.action( "my_menu.new_item" ).is_checked?, true )
    assert_equal( menu.action( "my_menu.new_item" ).is_enabled?, false )

    $a1.visible = true
    assert_equal( menu.action( "my_menu.new_item" ).is_visible?, true )
    assert_equal( menu.action( "my_menu.new_item" ).is_checked?, true )
    assert_equal( menu.action( "my_menu.new_item" ).is_enabled?, false )

    $a1.enabled = true
    assert_equal( menu.action( "my_menu.new_item" ).is_visible?, true )
    assert_equal( menu.action( "my_menu.new_item" ).is_checked?, true )
    assert_equal( menu.action( "my_menu.new_item" ).is_enabled?, true )

  end

  class MenuHandler < RBA::Action
    def initialize( t, k, &action ) 
      self.title = t
      self.shortcut = k
      @action = action
    end
    def triggered 
      @action.call( self ) 
    end
  private
    @action
  end

  def test_2

    app = RBA::Application.instance
    mw = app.main_window
    menu = mw.menu

    triggered = false

    $f7_handler = MenuHandler.new( "Ruby Test", "F7" ) {
      triggered = true
    }

    menu.insert_item("file_menu.begin", "new_item", $f7_handler)
    menu.action("file_menu.#0").trigger

    assert_equal( triggered, true )

    triggered = false

    menu.insert_item("help_menu.end", "new_item_copy", menu.action("file_menu.#0") )

    menu.action("help_menu.new_item_copy").trigger

    assert_equal( triggered, true )

  end

end

load("test_epilogue.rb")

