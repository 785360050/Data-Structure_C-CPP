
option(Build_CPP "Build C++ code" ON)
option(Build_C_Reference "Build C reference code" OFF)

if(Build_CPP)
    add_subdirectory(C++)
endif()

if(Build_C_Reference)
    add_subdirectory(C)
endif()

if(NOT Build_CPP AND NOT Build_C_Reference)
    message(FATAL_ERROR "At least one build target must be enabled: Build_CPP or Build_C_Reference")
endif()
