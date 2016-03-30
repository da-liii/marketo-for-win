cmake_minimum_required(VERSION 3.2)

project(Installer)

cmake_policy(SET CMP0054 NEW)


message(STATUS ${CMAKE_BUILD_TYPE})
if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(NsisScript "kate-installer-release.nsi")

    add_custom_target(invalidate_files ALL
                  COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_SOURCE_DIR}/${NsisScript}
    )

    string(TIMESTAMP BUILD_TIME_STAMP "%Y.%m.%d")

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${NsisScript} ${CMAKE_INSTALL_PREFIX}/${NsisScript} @ONLY)

    add_custom_target(installer ALL
        COMMAND makensis ${NsisScript}
        WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}
        DEPENDS invalidate_files
    )
endif()
