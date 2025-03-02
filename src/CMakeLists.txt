file(GLOB HEADER_FILES "Headers/*.hpp" "Headers/Lib/*.hpp")
file(GLOB SOURCE_FILES "*.cpp")

add_executable(Interpreter
  ${HEADER_FILES}
  ${SOURCE_FILES}
)
