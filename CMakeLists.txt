cmake_minimum_required(VERSION 3.19)
project(sts_seed_search)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -O3)

add_executable(sts_seed_search main.cpp seed_search.cpp seed_search.h sts_impl.h java_random.h seed_search_fast.h sts_constants.h sts_impl.cpp sts_map.cpp sts_map.h)