set(HEADER_FILES
)

set(SOURCE_FILES
ast.cpp
to_string_visitor.cpp
)

add_library(ast ${SOURCE_FILES})
#target_include_directories(tinystl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
