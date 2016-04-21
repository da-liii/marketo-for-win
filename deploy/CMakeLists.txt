cmake_minimum_required(VERSION 3.2)

project(Deploy)

cmake_policy(SET CMP0054 NEW)

add_custom_target(deploy ALL
    COMMAND windeployqt.exe  -script -network -printsupport -xml -webenginecore -webenginewidgets -webchannel ${CMAKE_INSTALL_PREFIX}/bin/marknoto.exe
    COMMAND windeployqt.exe  -script -network -printsupport -xml -webenginecore -webenginewidgets -webchannel ${CMAKE_INSTALL_PREFIX}/bin/markpado.exe
)

install(FILES ${CMAKE_SOURCE_DIR}/gpl3.txt DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)
