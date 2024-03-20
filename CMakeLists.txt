# #   项目名称
# project (sunnet)
# #   Cmake最低版本号要求
# cmake_minimum_required (VERSION 2.8)
# #   头文件目录
# include_directories(include)
# #   查找./src目录下的所有源文件，保存到DIR_SRCS变量中
# aux_source_directory(./src DIR_SRCS)
# #   用C++11
# add_definitions(-std=c++11)
# #   指定生成目标文件
# add_executable(sunnet ${DIR_SRCS})
# #   库文件
# find_package (Threads)
# target_link_libraries (sunnet ${CMAKE_THREAD_LIBS_INIT})

#   项目名称
project (my_sunnet)
#   Cmake最低版本号要求
cmake_minimum_required (VERSION 2.8)
#   头文件目录
include_directories(include)
#   查找./src目录下的所有源文件，保存到DIR_SRCS变量中
aux_source_directory(./src/com.blackCat.core DIR_SRCS)
#   用C++11
add_definitions(-std=c++11)
#   指定生成目标文件
add_executable(my_sunnet ${DIR_SRCS})
#   库文件
find_package (Threads)
target_link_libraries (my_sunnet ${CMAKE_THREAD_LIBS_INIT})

#   gdb调试
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


#   Lua头文件、库
include_directories(./3rd/lua-5.4.6/src)
target_link_libraries(my_sunnet liblua.a)
target_link_libraries(my_sunnet dl)
