cmake_minimum_required(VERSION 3.2)

project(Installer)

cmake_policy(SET CMP0054 NEW)

message(STATUS ${CMAKE_BUILD_TYPE})
if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(NsisScript "kate-installer-release.nsi")
else ()
    set(NsisScript "kate-installer-debug.nsi")
endif()

add_custom_target(installer ALL
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${NsisScript} ${CMAKE_INSTALL_PREFIX}
    COMMAND makensis ${NsisScript}
    WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}
)
