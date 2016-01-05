cmake_minimum_required(VERSION 3.2)

project(Icons)

cmake_policy(SET CMP0054 NEW)

add_custom_command(OUTPUT breeze.rcc
    COMMAND rcc -project -o icons.qrc
    COMMAND rcc -binary -o ${CMAKE_BINARY_DIR}/breeze.rcc -root /icons/breeze icons.qrc

    WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/share/icons/breeze
)

add_custom_target(icons ALL
    DEPENDS breeze.rcc
)

install(FILES ${CMAKE_BINARY_DIR}/breeze.rcc DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)

