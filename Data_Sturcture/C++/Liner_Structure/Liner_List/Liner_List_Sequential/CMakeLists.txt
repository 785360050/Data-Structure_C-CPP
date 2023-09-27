

add_executable(Demo_Sequential_List Test.cpp)

if(MSVC) # VS热修复
  target_compile_options(Demo_Sequential_List PUBLIC "/ZI")
  target_link_options(Demo_Sequential_List PUBLIC "/INCREMENTAL")
endif()

# set_property(Demo_Sequential_List 
#     output
# )