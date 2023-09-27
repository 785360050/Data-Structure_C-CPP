

option(Build_CPP "Build C++ code" ON)

if(Build_CPP)
    add_subdirectory(C++)
else()
    add_subdirectory(C)
endif()

