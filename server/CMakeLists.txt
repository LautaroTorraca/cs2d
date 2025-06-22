# server/CMakeLists.txt

# Glob all .cpp files en las subcarpetas relevantes
file(GLOB_RECURSE COMMON_SOURCES ${CMAKE_SOURCE_DIR}/common/*.cpp
        ${CMAKE_SOURCE_DIR}/common/Constants/*.cpp)

file(
        GLOB_RECURSE
        SERVER_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Protocol/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Readers/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Requests/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Sender/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Orders/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Handlers/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Constants/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Lobby/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Monitor/*.cpp)

file(
        GLOB_RECURSE
        SERVER_HEADERS
        "${CMAKE_SOURCE_DIR}/common/*.h"
        "${CMAKE_SOURCE_DIR}/common/Constants/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Protocol/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Readers/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Requests/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Sender/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Orders/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Handlers/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Constants/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Lobby/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/DTO/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Monitor/*.h")

# Agregar las fuentes al target existente
target_sources(taller_server PRIVATE ${SERVER_SOURCES})
target_sources(taller_server PRIVATE ${COMMON_SOURCES})
target_sources(taller_server PRIVATE ${SERVER_HEADERS})

# IMPORTANTE: Configurar los directorios de inclusión Definir lista de
# subdirectorios
set(SERVER_INCLUDE_DIRS
        Constants DTO Handlers Interfaces Lobby Orders
        Protocol Readers Requests Sender Monitor)

# Agregar directorio base
target_include_directories(taller_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Agregar cada subdirectorio
foreach(subdir ${SERVER_INCLUDE_DIRS})
  target_include_directories(taller_server
          PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${subdir})
endforeach()

# Agregar directorios de common si es necesario
target_include_directories(
        taller_server PRIVATE ${CMAKE_SOURCE_DIR}/common
        ${CMAKE_SOURCE_DIR}/common/Constants)

set(SERVER_SOURCES
        ${SERVER_SOURCES}
        PARENT_SCOPE)
set(SERVER_HEADERS
        ${SERVER_HEADERS}
        PARENT_SCOPE)