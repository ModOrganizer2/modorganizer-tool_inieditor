cmake_minimum_required(VERSION 3.16)

find_package(mo2-cmake CONFIG REQUIRED)
find_package(mo2-uibase CONFIG REQUIRED)

add_library(inieditor SHARED)
mo2_configure_plugin(inieditor WARNINGS 4)
target_link_libraries(inieditor PRIVATE mo2::uibase)
mo2_install_plugin(inieditor)
