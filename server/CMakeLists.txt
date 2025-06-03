# Glob all .cpp files en las subcarpetas relevantes

file(
        GLOB
        COMMON_SOURCES
        ${CMAKE_SOURCE_DIR}/common/*.cpp
        ${CMAKE_SOURCE_DIR}/common/Protocol/*.cpp
        ${CMAKE_SOURCE_DIR}/common/Interfaces/*.cpp
        ${CMAKE_SOURCE_DIR}/common/Constants/*.cpp)

file(
        GLOB
        SERVER_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Protocol/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Readers/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Requests/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Sender/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Orders/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Handlers/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Constants/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Lobby/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/*.cpp)

file(
        GLOB
        SERVER_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Protocol/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Readers/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Requests/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Sender/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Orders/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Handlers/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Constants/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Lobby/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/*.h)

# Agregar las fuentes al target existente
target_sources(taller_server PRIVATE ${SERVER_SOURCES})
target_sources(taller_server PRIVATE ${COMMON_SOURCES})

# Asegurar que los headers sean visibles
target_include_directories(
        taller_server
        PRIVATE ${CMAKE_SOURCE_DIR}/common
        ${CMAKE_SOURCE_DIR}/common/Protocol
        ${CMAKE_SOURCE_DIR}/common/Interfaces
        ${CMAKE_SOURCE_DIR}/common/Constants)

target_include_directories(
        taller_server
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Protocol
        ${CMAKE_CURRENT_SOURCE_DIR}/Readers
        ${CMAKE_CURRENT_SOURCE_DIR}/Requests
        ${CMAKE_CURRENT_SOURCE_DIR}/Sender
        ${CMAKE_CURRENT_SOURCE_DIR}/Orders
        ${CMAKE_CURRENT_SOURCE_DIR}/Handlers
        ${CMAKE_CURRENT_SOURCE_DIR}/Constants
        ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces
        ${CMAKE_CURRENT_SOURCE_DIR}/Lobby
        ${CMAKE_CURRENT_SOURCE_DIR}/DTO)