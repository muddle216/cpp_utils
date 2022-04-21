# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.


project(ZEngineTest)
set(CMAKE_CXX_STANDARD 11)

include_directories(../../include)
include_directories(../../include/Common)
aux_source_directory(. ZEngineTest_DIR_SRCS)
add_executable(ZEngineTest ${ZEngineTest_DIR_SRCS})
