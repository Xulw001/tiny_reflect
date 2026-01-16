cmake_minimum_required (VERSION 3.0)
set(project_name reflect_sample)
project ("${project_name}")

include_directories(../include)
aux_source_directory(. DIR_SRC)
add_executable(${project_name} ${DIR_SRC})