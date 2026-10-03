cmake_minimum_required(VERSION 3.20)
project(spore_decomp CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(spore_resource
  src/resource/DBPF.cpp
  src/resource/RefPack.cpp
  src/resource/Hash.cpp)
target_include_directories(spore_resource PUBLIC src)
if(MSVC)
  target_compile_options(spore_resource PRIVATE /W4)
else()
  target_compile_options(spore_resource PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(dbpf_tool tools/dbpf_tool.cpp)
target_link_libraries(dbpf_tool PRIVATE spore_resource)

enable_testing()
add_executable(resource_tests tests/resource_tests.cpp)
target_link_libraries(resource_tests PRIVATE spore_resource)
add_test(NAME resource_unit COMMAND resource_tests)
# Corpus tests need the user's own game data; point SPORE_DATA at Spore/Data.
if(DEFINED ENV{SPORE_DATA})
  add_test(NAME resource_corpus COMMAND resource_tests --corpus $ENV{SPORE_DATA})
endif()
