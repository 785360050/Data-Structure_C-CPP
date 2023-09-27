

option(Build_CPP "Build C++ code" ON)
# add_subdirectory(C++)

if(Build_CPP)
    add_subdirectory(C++)
else()
    add_subdirectory(C)
endif()

