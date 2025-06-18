# client/CMakeLists.txt
file(GLOB_RECURSE CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

file(GLOB_RECURSE CLIENT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
     "${CMAKE_SOURCE_DIR}/server/GameStatus.h"
     "${CMAKE_SOURCE_DIR}/server/Readers/*.h")
set(CLIENT_SOURCES
    ${CLIENT_SOURCES}
    PARENT_SCOPE)
set(CLIENT_HEADERS
    ${CLIENT_HEADERS}
    PARENT_SCOPE)

# Debug: verificar que el archivo existe
if(EXISTS ${RESOURCE_FILE})
    message(STATUS "Resource file found: ${RESOURCE_FILE}")
else()
    message(WARNING "Resource file NOT found: ${RESOURCE_FILE}")
endif()

# Export resource file path to parent scope
set(CLIENT_RESOURCE_FILE ${RESOURCE_FILE} PARENT_SCOPE)