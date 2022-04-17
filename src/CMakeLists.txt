cmake_minimum_required(VERSION 3.16)

add_library(inieditor SHARED)
mo2_configure_plugin(inieditor WARNINGS OFF)
mo2_install_target(inieditor)
