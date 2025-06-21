cmake_minimum_required(VERSION 3.24)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_EXTENSIONS ON)

project(
        taller_tp
        VERSION 1.0
        HOMEPAGE_URL "https://github.com/URL-HERE"
        LANGUAGES C CXX
)

# Qt
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

option(TALLER_TESTS "Enable / disable tests." ON)
option(TALLER_CLIENT "Enable / disable client program." ON)
option(TALLER_SERVER "Enable / disable server program." ON)
option(TALLER_EDITOR "Enable / disable editor program." ON)
option(TALLER_MAKE_WARNINGS_AS_ERRORS "Enable / disable warnings as errors." ON)
option(ENABLE_MUSIC "Enable menu music (Qt Multimedia)" ON)

message(CMAKE_CXX_COMPILER_ID="${CMAKE_CXX_COMPILER_ID}")

add_library(taller_common STATIC
        server/Handlers/ClientStatus.h
)
add_subdirectory(common/)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(taller_common ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

target_include_directories(taller_common PUBLIC .)

if(TALLER_CLIENT OR TALLER_EDITOR)
    include(FetchContent)

    # SDL2
    FetchContent_Declare(
            SDL2
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-2.30.8
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
            OVERRIDE_FIND_PACKAGE
    )

    FetchContent_Declare(
            SDL2_image
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
            GIT_TAG release-2.8.2
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
            OVERRIDE_FIND_PACKAGE
    )

    set(SDL2PP_WITH_IMAGE ON CACHE BOOL "Enable SDL2_image support in SDL2pp" FORCE)

    FetchContent_Declare(
            libSDL2pp
            OVERRIDE_FIND_PACKAGE
            URL https://github.com/libSDL2pp/libSDL2pp/archive/cc198c9a5657048bee67ece82de620b2d5661084.zip
    )

    FetchContent_Declare(
            SDL2_mixer
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
            GIT_TAG release-2.8.0
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
            OVERRIDE_FIND_PACKAGE
    )

    FetchContent_Declare(
            SDL2_ttf
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
            GIT_TAG release-2.22.0
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
            OVERRIDE_FIND_PACKAGE
    )

    FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_mixer SDL2_ttf libSDL2pp)
endif()

# Program section


if(TALLER_CLIENT)
    add_subdirectory(client)
    add_subdirectory(libs/SDL2_gfx)

    add_executable(taller_client ${CLIENT_SOURCES} ${CLIENT_HEADERS}
            client/Login/Audio/MusicManager.cpp
            client/Login/Audio/MusicManager.h)
    target_include_directories(taller_client PRIVATE client)

    set(CMAKE_AUTORCC ON)

    set(CLIENT_RESOURCES "client/Login/resources.qrc")

    target_link_libraries(taller_client
            taller_common
            SDL2pp::SDL2pp
            SDL2_gfx
            Qt6::Widgets
    )

    if(ENABLE_MUSIC)
        target_link_libraries(taller_client Qt6::Multimedia)
        target_compile_definitions(taller_client PUBLIC ENABLE_MUSIC)
    endif()
endif()

if(TALLER_SERVER)
    find_package(fkYAML REQUIRED)
    add_executable(taller_server)
    add_dependencies(taller_server taller_common)
    add_subdirectory(server)
    set_project_warnings(taller_server ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)
    target_link_libraries(taller_server taller_common fkYAML::fkYAML)
endif()

if(TALLER_EDITOR)
    add_executable(taller_editor)
    add_dependencies(taller_editor taller_common SDL2pp::SDL2pp)
    add_subdirectory(editor)
    set_project_warnings(taller_editor ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)
    target_include_directories(taller_editor PRIVATE ${libSDL2pp_SOURCE_DIR})
    target_link_libraries(taller_editor taller_common SDL2pp::SDL2pp)
endif()

# Tests
if(TALLER_TESTS)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)

    add_executable(taller_tests)
    add_dependencies(taller_tests taller_common)
    add_subdirectory(tests/)
    set_project_warnings(taller_tests ${TALLER_MAKE_WARNINGS_AS_ERRORS} TRUE)
    target_include_directories(taller_tests PUBLIC . ${gtest_SOURCE_DIR}/include ${gmock_SOURCE_DIR}/include)
    target_link_libraries(taller_tests taller_common GTest::gtest_main)
endif()
