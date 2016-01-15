cmake_minimum_required(VERSION 3.2)

project(Icons)

cmake_policy(SET CMP0054 NEW)

add_custom_command(OUTPUT breeze.rcc
    COMMAND ${CMAKE_COMMAND} -E copy categories/16/applications-system.svg actions/16/games-config-options.svg
    COMMAND ${CMAKE_COMMAND} -E copy categories/22/applications-system.svg actions/22/games-config-options.svg
    COMMAND ${CMAKE_COMMAND} -E copy categories/32/applications-system.svg actions/32/games-config-options.svg

    COMMAND ${CMAKE_COMMAND} -E copy actions/16/window-close.svg actions/16/dialog-close.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/22/window-close.svg actions/22/dialog-close.svg
    COMMAND ${CMAKE_COMMAND} -E copy actions/24/window-close.svg actions/24/dialog-close.svg
    COMMAND rcc -project -o icons.qrc
    COMMAND rcc -binary -o ${CMAKE_BINARY_DIR}/breeze.rcc -root /icons/breeze icons.qrc

    WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/share/icons/breeze
)

add_custom_target(icons ALL
    DEPENDS breeze.rcc
)

install(FILES ${CMAKE_BINARY_DIR}/breeze.rcc DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)

