


macro(Check_Environment)
    

# 需要在project生成之后
message(STATUS "—————————————————————————————————————————————————————————————————————————————————————")
message(STATUS "					环境信息检测")
message(STATUS "—————————————————————————————————————————————————————————————————————————————————————")
message(STATUS "操作系统:\t${CMAKE_SYSTEM_NAME}")
message(STATUS "目标CPU架构:\t${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS "当前CPU架构:\t${CMAKE_SYSTEM_PROCESSOR}")
# message(STATUS "void*大小(Byte): ${CMAKE_SIZEOF_VOID_P}") #验证32/64位字长的机器
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(STATUS "机器字长:\t32位") 
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "机器字长:\t64位")
else()
    message(STATUS "void*大小(Byte):\t${CMAKE_SIZEOF_VOID_P}") #验证32/64位字长的机器的真正方法
endif()

message(STATUS "编译器类型:\t${CMAKE_CXX_COMPILER_ID}")
message(STATUS "—————————————————————————————————————————————————————————————————————————————————————")

endmacro(Check_Environment)