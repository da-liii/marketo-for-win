cmake_minimum_required(VERSION 3.2)

project(Icons)

cmake_policy(SET CMP0054 NEW)

message(STATUS ${CMAKE_BINARY_DIR}/breeze.qrc ${CMAKE_BINARY_DIR}/breeze.rcc)

add_custom_command(OUTPUT breeze.rcc
    COMMAND rcc -project -o icons.qrc
    COMMAND rcc -binary -o ${CMAKE_BINARY_DIR}/breeze.rcc -root /icons icons.qrc

    WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/share/icons
)

add_custom_target(icons ALL
    DEPENDS breeze.rcc
)

install(FILES ${CMAKE_BINARY_DIR}/breeze.rcc DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)

