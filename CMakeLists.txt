cmake_minimum_required(VERSION 3.24)

if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_EXTENSIONS ON)
# set(YAML_CPP_BUILD_TESTS OFF CACHE INTERNAL "Disable yaml-cpp tests")
project(
  taller_tp
  VERSION 1.0
  HOMEPAGE_URL "https://github.com/URL-HERE"
  LANGUAGES CXX)

option(TALLER_TESTS "Enable / disable tests." ON)
option(TALLER_CLIENT "Enable / disable client program." ON)
option(TALLER_SERVER "Enable / disable server program." ON)
option(TALLER_EDITOR "Enable / disable editor program." ON)
option(TALLER_MAKE_WARNINGS_AS_ERRORS "Enable / disable warnings as errors." ON)

message(CMAKE_CXX_COMPILER_ID="${CMAKE_CXX_COMPILER_ID}")
add_library(taller_common STATIC)
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
    OVERRIDE_FIND_PACKAGE)

  # SDL2_image
  FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.2
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    OVERRIDE_FIND_PACKAGE)

  set(SDL2PP_WITH_IMAGE
      ON
      CACHE BOOL "Enable SDL2_image support in SDL2pp" FORCE)

  # SDL2pp
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
    OVERRIDE_FIND_PACKAGE)

  FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.22.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    OVERRIDE_FIND_PACKAGE)

  # FetchContent_Declare( libSDL2pp OVERRIDE_FIND_PACKAGE URL
  # https://github.com/libSDL2pp/libSDL2pp/archive/cc198c9a5657048bee67ece82de620b2d5661084.zip
  # )

  FetchContent_MakeAvailable(SDL2 SDL2_image SDL2_mixer SDL2_ttf libSDL2pp)
endif()

# Program section
# ---------------
if(TALLER_CLIENT)
  add_subdirectory(client)
  add_executable(taller_client ${CLIENT_SOURCES} ${CLIENT_HEADERS})
  target_include_directories(taller_client PRIVATE client)
  target_link_libraries(taller_client taller_common SDL2pp::SDL2pp)
endif()

if(TALLER_SERVER)

  project(
    fkYAML
    VERSION 0.4.2
    LANGUAGES CXX)
  FetchContent_Declare(
    fkYAML
    GIT_REPOSITORY https://github.com/fktn-k/fkYAML.git
    GIT_TAG v0.4.2)
  # HACK: arreglar esa cosa dudosa de lio
  #

  # ) FetchContent_Declare( yaml-cpp GIT_REPOSITORY
  # https://github.com/jbeder/yaml-cpp.git GIT_TAG yaml-cpp-0.6.3 # ✅ esta es la
  # tag válida para esa versión ) FetchContent_MakeAvailable(yaml-cpp)
  FetchContent_MakeAvailable(fkYAML)

  add_executable(taller_server)
  add_dependencies(taller_server taller_common)
  add_subdirectory(server)
  # add_subdirectory(libs/fkYAML)
  set_project_warnings(taller_server ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)
  target_link_libraries(taller_server taller_common fkYAML)

endif()

if(TALLER_EDITOR)
  add_executable(taller_editor)
  add_dependencies(taller_editor taller_common SDL2pp::SDL2pp)
  add_subdirectory(editor)
  set_project_warnings(taller_editor ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)
  target_include_directories(taller_editor PRIVATE ${libSDL2pp_SOURCE_DIR})
  target_link_libraries(taller_editor taller_common SDL2pp::SDL2pp)
endif()

# Testing section
# ---------------

if(TALLER_TESTS)
  # Let's use google test
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )

  # For Windows: Prevent overriding the parent project's compiler/linker
  # settings (borrowed from
  # https://google.github.io/googletest/quickstart-cmake.html)
  set(gtest_force_shared_crt
      ON
      CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  include(GoogleTest)

  # target for testing HEY!! TODO XXX: Change the name of the executable to the
  # one you like!
  add_executable(taller_tests)

  # HEY!! TODO XXX: I'm assuming that the code under testing is in taller_common
  # Change this if you have to.
  add_dependencies(taller_tests taller_common)

  # Say where to find the xoz headers HEY!! TODO XXX: add more subfolders here
  target_include_directories(taller_tests PUBLIC .)

  # Add the source files to the taller_tests target HEY!! TODO XXX: add more
  # subfolders here
  add_subdirectory(tests/)

  # Set the compiler warnings to the tests target (but be a little lesser
  # strict)
  set_project_warnings(taller_tests ${TALLER_MAKE_WARNINGS_AS_ERRORS} TRUE)

  # Say where googletest headers can be found
  target_include_directories(taller_tests PUBLIC ${gtest_SOURCE_DIR}/include
                                                 ${gmock_SOURCE_DIR}/include)

  # HEY!! TODO XXX: I'm assuming that the code under testing is in taller_common
  # Change this if you have to.
  target_link_libraries(taller_tests taller_common GTest::gtest_main)
endif()
