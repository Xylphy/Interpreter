cmake_minimum_required(VERSION 3.31.3)

project(Interpreter)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU") # GCC
  execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
  # if(GCC_VERSION VERSION_GREATER_EQUAL 14.0)
  #   set(CMAKE_CXX_STANDARD 26)
  #   add_compile_options(-std=c++2c)
  # else()
  set(CMAKE_CXX_STANDARD 23)
  # endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang") # Clang
  set(CMAKE_CXX_STANDARD 23)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC") # MSVC
  set(CMAKE_CXX_STANDARD 23)
endif()

# #For debugging
# set(CMAKE_BUILD_TYPE Debug)
# string(REPLACE "{" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -fsanitize=address")

# #For release
# set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -flto -funroll-loops -ftree-vectorize -ffast-math -march=native -fstrict-aliasing ")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
  file(GLOB_RECURSE ALL_SOURCE_FILES
    src/*.cpp src/Headers/*.hpp src/Headers/Lib/*.hpp
  )

  add_custom_target(
    format
    COMMAND ${CLANG_FORMAT} -i ${ALL_SOURCE_FILES}
    COMMENT "Formatting code with clang-format..."
  )
endif()

# Enable AddressSanitizer (ASan)
# if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
#   # Add flags for both compile and link stages
#   add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
#   add_link_options(-fsanitize=address -fno-omit-frame-pointer)
# endif()
# Enable clang-tidy
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,readability-*,modernize-*,performance-*,clang-analyzer-*")
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,performance-*")

add_subdirectory(src)
add_subdirectory(tool)

# enable_testing()
# add_subdirectory(tests)