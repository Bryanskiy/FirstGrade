cmake_minimum_required(VERSION 2.8)
project(lirs C)

set(CMAKE_C_STANDARD 11)

include_directories(lirs)
include_directories(queue)
include_directories(hm)

add_library(queue STATIC queue/queue.c)
add_library(queue_test STATIC queue/queue_test.c)
add_library(hm STATIC hm/hashmap.c)
add_library(hm_test STATIC hm/hashmap_test.c)
add_library(lirs STATIC lirs/lirs.c)
add_library(lirs_test STATIC lirs/lirs_tests.c)

add_executable(main main.c)
target_link_libraries(main lirs hm queue lirs_test hm_test queue_test)