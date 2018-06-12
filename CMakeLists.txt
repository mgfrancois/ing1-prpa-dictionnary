cmake_minimum_required (VERSION 3.6)
project (ProgParallel)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

find_package(Threads REQUIRED)
find_package(benchmark REQUIRED)
find_package(GTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-W -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=thread")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

include_directories(lib/include)

add_library(dictionary
  src/IDictionary.hpp
  src/IAsyncDictionary.hpp
  src/naive_dictionary.hpp
  src/naive_async_dictionary.hpp
  src/tools.hpp

  src/naive_dictionary.cpp
  src/naive_async_dictionary.cpp
  src/tools.cpp
  )

set_source_files_properties(src/tools.cpp PROPERTIES COMPILE_DEFINITIONS WORD_LIST_FILE="${CMAKE_SOURCE_DIR}/words_alpha.txt")
add_executable(tests src/tests.cpp)
target_link_libraries(tests dictionary GTest::GTest GTest::Main Threads::Threads)


add_executable(bench src/bench.cpp)
target_link_libraries(bench dictionary benchmark::benchmark)
