cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(Data_Structure LANGUAGES CXX VERSION 1.0.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Cmake")  # 添加cmake模块的搜索目录
include(Check_Environment)
Check_Environment()

include(GNUInstallDirs)	# 该模块用于确保项目布局的可移植性
# 设置构建项目的结构(这里设置与安装目录结构相同)  先设置最后生成可执行文件，不然某些设置不生效
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}) # bin
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}) # bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}) # lib
# 更多位置见https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html#gnuinstalldirs
# .
# ├── bin
# └── lib


set(Cmake_Demo_Output_Directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Demo)

# 设置默认以Debug版本构建项目
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build Type:	${CMAKE_BUILD_TYPE}")


add_subdirectory(Data_Sturcture)