cmake_minimum_required(VERSION 3.2)

project(Installer)

cmake_policy(SET CMP0054 NEW)

add_custom_target(deploy ALL
    COMMAND echo run nsis
)
