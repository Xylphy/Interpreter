find_package(GTest REQUIRED)

file(GLOB HEADER_FILES "${CMAKE_SOURCE_DIR}/src/Headers/*.hpp" "${CMAKE_SOURCE_DIR}/src/Headers/Lib/*.hpp")
file(GLOB SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

list(REMOVE_ITEM SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/main.cpp")

add_executable(tests 
    ${HEADER_FILES}
    ${SOURCE_FILES}
    test.cc
)

target_link_libraries(
    tests
    GTest::gtest_main
)
