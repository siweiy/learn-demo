# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (demo)

# 工程版本号
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file (
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_SOURCE_DIR}/config.h"
)

# 是否使用自己的 calc 库
option (USE_MYMATH "Use provided math implementation" OFF)
option (DEBUG "Use debug for gdb" OFF)

if (DEBUG)

# 调试
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")

else ()

# release版本优化编译
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

endif (DEBUG)

# 是否加入 calc 库
if (USE_MYMATH)

include_directories ("${PROJECT_SOURCE_DIR}/math")
add_subdirectory (math)
set (EXTRA_LIBS ${EXTRA_LIBS} calc)

endif (USE_MYMATH)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(demo ${DIR_SRCS})

target_link_libraries (demo ${EXTRA_LIBS})

# 指定安装路径
install (TARGETS demo DESTINATION bin)
install (FILES "${PROJECT_SOURCE_DIR}/config.h" DESTINATION include)