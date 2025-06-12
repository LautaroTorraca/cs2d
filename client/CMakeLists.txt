# Collect all source and header files
file(GLOB_RECURSE CLIENT_ROOT_SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB_RECURSE CLIENT_ROOT_HEADERS CONFIGURE_DEPENDS "*.h")

# Debug info
message(STATUS "CLIENT_ROOT_SOURCES: ${CLIENT_ROOT_SOURCES}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR in client: ${CMAKE_CURRENT_SOURCE_DIR}")

# Set sources and headers for parent scope
set(CLIENT_SOURCES ${CLIENT_SOURCES} ${CLIENT_ROOT_SOURCES} PARENT_SCOPE)
set(CLIENT_HEADERS ${CLIENT_HEADERS} ${CLIENT_ROOT_HEADERS} PARENT_SCOPE)

# Define the resource file path (ahora desde client/ directamente)
set(RESOURCE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc")

# Debug: verificar que el archivo existe
if(EXISTS ${RESOURCE_FILE})
    message(STATUS "Resource file found: ${RESOURCE_FILE}")
else()
    message(WARNING "Resource file NOT found: ${RESOURCE_FILE}")
endif()

# Export resource file path to parent scope
set(CLIENT_RESOURCE_FILE ${RESOURCE_FILE} PARENT_SCOPE)