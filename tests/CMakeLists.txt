# tests/CMakeLists.txt

set(TEST_SOURCES
    foo.cpp
)

target_sources(taller_tests PRIVATE ${TEST_SOURCES})

target_include_directories(taller_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
