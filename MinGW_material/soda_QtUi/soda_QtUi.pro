SOURCES += \
    configuration_widget.cpp \
    library_list_table.cpp \
    main.cpp \
    main_window.cpp \
    soda_thread.cpp \
    module_list_table.cpp \
    module_parameter_list_table.cpp \
    simple_table_cell.cpp \
    module_parameter_widget.cpp \
    module_list_widget.cpp \
    domain_jump_configuration_widget.cpp \
    domain_jump_table.cpp \
    gzstream.cpp \
    parser_base.tpp \
    xmlParser.cpp \
    dom_parser.cpp \
    run_control_widget.cpp \
    configuration_dialog_widget.cpp \
    osm_diff_watcher.cpp \
    sax_parser.cpp \
    module_manager.cpp \
    osm_ressources.cpp \
    common_api_wrapper.cpp \
    dom2cpp_analyzer.cpp \
    internal_database.cpp \
    osm_diff_dom_parser.cpp \
    url_reader.cpp \
    module_wrapper.cpp \
    download_buffer.cpp \
    osm_cache.cpp \
    information_table.cpp \
    osm_cache_compatibility_db.cpp \
    osm_api.cpp \
    dom_osm_parser.cpp \
    osm_cache_core_element_table_description.cpp \
    osm_cache_user.cpp \
    osm_cache_core_element.cpp \
    osm_cache_named_item.cpp \
    osm_cache_named_item_table_description.cpp \
    osm_cache_node.cpp \
    osm_cache_node_table_description.cpp \
    osm_cache_object_tag.cpp \
    osm_cache_object_tag_table_description.cpp \
    osm_cache_relation_member.cpp \
    osm_cache_user_table_description.cpp \
    osm_cache_way_member.cpp \
    osm_cache_way_member_table_description.cpp \
    osm_cache_relation_member_table_description.cpp \
    osm_change.cpp \
    osm_changeset.cpp \
    osm_node.cpp \
    osm_way.cpp \
    osm_core_element.cpp \
    osm_relation.cpp \
    module_display_widget.cpp

HEADERS += \
    configuration_widget.h \
    library_list_table.h \
    main_window.h \
    soda_thread.h \
    module_list_table.h \
    module_parameter_list_table.h \
    module_configuration.h \
    simple_table_cell.h \
    module_parameter_widget.h \
    module_list_widget.h \
    domain_jump_configuration_widget.h \
    domain_jump_table.h \
    configuration.h \
    configuration_parser.h \
    dom_analyzer_generic_if.h \
    dom_tree.h \
    xmlParser.h \
    gzstream.h \
    zlib.h \
    zconf.h \
    replication_domain_jump.h \
    run_control_widget.h \
    configuration_dialog_widget.h \
    curl/curl.h \
    osm_diff_watcher.h \
    soda_Ui_if.h \
    osm_diff_state.h \
    module_display_widget.h


QT += webkit

win32: LIBS += -L$$PWD/LIBS -lsqlite3 -lexpat -lcurl -lidn-11 -leay32 -lssleay32

DEPENDPATH += $$PWD/LIBS































