cmake_minimum_required(VERSION 3.2)

project(Icons)

cmake_policy(SET CMP0054 NEW)

add_custom_command(OUTPUT breeze.rcc
    COMMAND ${CMAKE_COMMAND} -E copy categories/16/applications-system.svg actions/16/games-config-options.svg
    COMMAND ${CMAKE_COMMAND} -E copy categories/22/applications-system.svg actions/22/games-config-options.svg
    COMMAND ${CMAKE_COMMAND} -E copy categories/32/applications-system.svg actions/32/games-config-options.svg

    COMMAND ${CMAKE_COMMAND} -E copy categories/16/applications-system.svg actions/16/configure-shortcuts.svg
    COMMAND ${CMAKE_COMMAND} -E copy categories/22/applications-system.svg actions/22/configure-shortcuts.svg
    COMMAND ${CMAKE_COMMAND} -E copy categories/32/applications-system.svg actions/32/configure-shortcuts.svg

    COMMAND ${CMAKE_COMMAND} -E copy actions/16/configure.svg actions/16/configure-toolbars.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/22/configure.svg actions/22/configure-toolbars.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/24/configure.svg actions/24/configure-toolbars.svg

    COMMAND ${CMAKE_COMMAND} -E copy actions/16/window-close.svg actions/16/dialog-close.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/22/window-close.svg actions/22/dialog-close.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/24/window-close.svg actions/24/dialog-close.svg

    COMMAND ${CMAKE_COMMAND} -E copy actions/16/go-bottom.svg actions/16/go-down-search.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/22/go-bottom.svg actions/22/go-down-search.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/24/go-bottom.svg actions/24/go-down-search.svg

    COMMAND ${CMAKE_COMMAND} -E copy actions/16/go-top.svg actions/16/go-up-search.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/22/go-top.svg actions/22/go-up-search.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/24/go-top.svg actions/24/go-up-search.svg

    COMMAND ${CMAKE_COMMAND} -E copy actions/16/edit-clear.svg actions/16/edit-clear-history.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/22/edit-clear.svg actions/22/edit-clear-history.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/24/edit-clear.svg actions/24/edit-clear-history.svg

    COMMAND ${CMAKE_COMMAND} -E copy actions/16/edit-clear.svg actions/16/edit-clear-list.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/22/edit-clear.svg actions/22/edit-clear-list.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/24/edit-clear.svg actions/24/edit-clear-list.svg

    COMMAND ${CMAKE_COMMAND} -E copy actions/16/edit-clear.svg actions/16/edit-clear-locationbar-ltr.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/22/edit-clear.svg actions/22/edit-clear-locationbar-ltr.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/24/edit-clear.svg actions/24/edit-clear-locationbar-ltr.svg

    COMMAND ${CMAKE_COMMAND} -E copy actions/16/edit-clear.svg actions/16/edit-clear-locationbar-rtl.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/22/edit-clear.svg actions/22/edit-clear-locationbar-rtl.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/24/edit-clear.svg actions/24/edit-clear-locationbar-rtl.svg

    COMMAND ${CMAKE_COMMAND} -E copy actions/16/document-edit.svg actions/16/edit-rename.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/22/document-edit.svg actions/22/edit-rename.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/24/document-edit.svg actions/24/edit-rename.svg

    COMMAND ${CMAKE_COMMAND} -E copy actions/16/document-preview-archive.svg actions/16/document-preview.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/22/document-preview-archive.svg actions/22/document-preview.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/24/document-preview-archive.svg actions/24/document-preview.svg

    COMMAND ${CMAKE_COMMAND} -E copy actions/16/document-preview-archive.svg actions/16/document-print-preview.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/22/document-preview-archive.svg actions/22/document-print-preview.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/24/document-preview-archive.svg actions/24/document-print-preview.svg

    COMMAND ${CMAKE_COMMAND} -E copy actions/16/edit-delete.svg actions/16/edit-delete-shred.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/22/edit-delete.svg actions/22/edit-delete-shred.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/24/edit-delete.svg actions/24/edit-delete-shred.svg

    COMMAND ${CMAKE_COMMAND} -E copy mimetypes/16/application-x-executable.svg mimetypes/16/application-x-ms-dos-executable.svg
    COMMAND ${CMAKE_COMMAND} -E copy mimetypes/22/application-x-executable.svg mimetypes/22/application-x-ms-dos-executable.svg
    COMMAND ${CMAKE_COMMAND} -E copy mimetypes/32/application-x-executable.svg mimetypes/32/application-x-ms-dos-executable.svg
    COMMAND ${CMAKE_COMMAND} -E copy mimetypes/64/application-x-executable.svg mimetypes/64/application-x-ms-dos-executable.svg

    COMMAND rcc -project -o icons.qrc
    COMMAND rcc -binary -o ${CMAKE_BINARY_DIR}/breeze.rcc -root /icons/breeze icons.qrc

    WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/share/icons/breeze
)

add_custom_target(icons ALL
    DEPENDS breeze.rcc
)

install(FILES ${CMAKE_BINARY_DIR}/breeze.rcc DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)

