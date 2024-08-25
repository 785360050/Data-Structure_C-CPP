cmake_minimum_required(VERSION 3.16)

project(QT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# find View.hpp
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/Utilities/
)



set(PROJECT_SOURCES
        main.cpp
        Window.cpp
        Window.hpp
        Window.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QT
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        # View/GraphicsView.hpp
        # QT_Stream_Buffer.hpp QT_Stream_Buffer.cpp

        # Painter/Binary_Tree.hpp Painter/Binary_Tree.cpp

        # Painter/Painter.hpp
        # View/Structure.hpp View/Structure.cpp View/Structure.ui

        # View/Binary_Tree.hpp View/Binary_Tree.cpp
        # View/Skip_List.hpp View/Skip_List.cpp

        # Painter/Skip_List.hpp Painter/Skip_List.cpp
        # Painter/Tree.hpp
        # View/Search_Tree.hpp View/Search_Tree.cpp
        # Painter/Search_Tree.hpp Painter/Search_Tree.cpp
        # Demo/View_Tree.hpp
        # Demo/Painter_Tree.hpp
        # Structure/Stack.hpp Structure/Stack.cpp

        Utilities/GraphicsView.hpp
        Demo/Painter_Binary_Tree.cpp
        Structure/Linear_Structure/Skip_List.cpp
        Structure/Linear_Structure/Stack.cpp
        Structure/Tree_Structure/Search_Tree.cpp
        Structure/Structure.cpp
        Structure/Tree_Structure/AVL_Tree.hpp Structure/Tree_Structure/AVL_Tree.cpp
        Structure/Tree_Structure/Red_Black_Tree.hpp
        Structure/Tree_Structure/Red_Black_Tree.cpp
        Structure/Tree_Structure/Heap.cpp
        Structure/Tree_Structure/Heap.hpp
        Structure/Linear_Structure/Queue.hpp
        Structure/Linear_Structure/Queue.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QT APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QT SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QT
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QT PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QT)
endif()
set_target_properties(QT PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QT)
endif()
