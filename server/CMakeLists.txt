file(GLOB_RECURSE SERVER_SOURCES
        CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

target_sources(taller_server
        PRIVATE
        ${SERVER_SOURCES}
)

target_include_directories(taller_server
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(taller_server
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Handlers
        ${CMAKE_CURRENT_SOURCE_DIR}/Protocol
        ${CMAKE_CURRENT_SOURCE_DIR}/Orders
        ${CMAKE_CURRENT_SOURCE_DIR}/Requests
        ${CMAKE_CURRENT_SOURCE_DIR}/Constants
        ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces
)

