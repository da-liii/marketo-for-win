cmake_minimum_required(VERSION 3.2)

project(Deploy)

cmake_policy(SET CMP0054 NEW)

add_custom_target(deploy ALL
    COMMAND windeployqt.exe  -script -network -printsupport ${CMAKE_INSTALL_PREFIX}/bin/kate.exe
)

install(FILES ${CMAKE_SOURCE_DIR}/qt.conf DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)
