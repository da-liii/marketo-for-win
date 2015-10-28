cmake_minimum_required(VERSION 3.2)

project(Icons)

cmake_policy(SET CMP0054 NEW)

add_custom_command(OUTPUT breeze/COPYING-ICONS
    COMMAND git clone git://anongit.kde.org/breeze
)

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/tmp/icons/breeze/index.theme
    COMMAND ${CMAKE_COMMAND} -E remove_directory tmp
    COMMAND ${CMAKE_COMMAND} -E make_directory tmp
    COMMAND ${CMAKE_COMMAND} -E make_directory tmp/icons
    COMMAND ${CMAKE_COMMAND} -E copy_directory breeze/icons tmp/icons/breeze
    DEPENDS breeze/COPYING-ICONS
)

add_custom_command(OUTPUT breeze.rcc
    COMMAND rcc -project -o ../breeze.qrc
    COMMAND ${CMAKE_COMMAND} -E rename ../breeze.qrc breeze.qrc
    COMMAND rcc -binary -o breeze.rcc breeze.qrc
    COMMAND ${CMAKE_COMMAND} -E rename breeze.rcc ../breeze.rcc
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tmp
    DEPENDS ${CMAKE_BINARY_DIR}/tmp/icons/breeze/index.theme
)

add_custom_target(icons ALL
    DEPENDS breeze.rcc
)

install(FILES ${CMAKE_BINARY_DIR}/breeze.rcc DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)

