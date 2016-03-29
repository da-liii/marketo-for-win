cmake_minimum_required(VERSION 3.2)

project(Icons)

cmake_policy(SET CMP0054 NEW)

find_package(Qt5 NO_MODULE REQUIRED Core)

add_executable(qrcAlias main.cpp)
target_link_libraries(qrcAlias PUBLIC Qt5::Core)

add_custom_command(OUTPUT breeze.rcc
    COMMAND rcc -project -o icons.qrc

    COMMAND $<TARGET_FILE_NAME:qrcAlias> -i icons.qrc -o aliased.qrc

    COMMAND rcc -binary -o ${CMAKE_BINARY_DIR}/breeze.rcc -root /icons/breeze aliased.qrc

    #COMMAND ${CMAKE_COMMAND} -E remove icons.qrc aliased.qrc

    WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/share/icons/breeze
    DEPENDS qrcAlias
)

add_custom_target(icons ALL
    DEPENDS breeze.rcc
)

install(FILES ${CMAKE_BINARY_DIR}/breeze.rcc DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)

