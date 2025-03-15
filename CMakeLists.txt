cmake_minimum_required(VERSION 3.31.3)

project(Interpreter)

set(CMAKE_CXX_STANDARD 23)

# #For debugging
# set(CMAKE_BUILD_TYPE Debug)
# set(ENV{LSAN_OPTIONS} "verbosity=1:log_threads=1")
# add_compile_options(-Wall -Werror -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer -g)
# add_link_options(-Wall -Werror -fsanitize=address -fsanitize=leak -fno-omit-frame-pointer -g)

#For release
# set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -flto -funroll-loops -ftree-vectorize -ffast-math -march=native -fstrict-aliasing ")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/4902ea2d7c6faed89b6facee00baa34bb108fc0d.zip
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
FetchContent_MakeAvailable(googletest)

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

# Enable clang-tidy
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,readability-*,modernize-*,performance-*,clang-analyzer-*")
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,performance-*")

# add_subdirectory(src)
add_subdirectory(tool)

# enable_testing()
# add_subdirectory(tests)
