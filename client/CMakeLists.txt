file(GLOB_RECURSE CLIENT_SOURCES
        CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)


target_sources(taller_client
        PRIVATE
        ${CLIENT_SOURCES}
)

target_include_directories(taller_client
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(taller_client
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Protocol
        ${CMAKE_CURRENT_SOURCE_DIR}/Constants
)

