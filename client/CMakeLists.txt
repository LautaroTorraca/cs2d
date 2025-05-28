file(GLOB_RECURSE CLIENT_SOURCES
        CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)


target_sources(taller_client
    PRIVATE
    # .cpp files
    main.cpp
    GameRenderer.cpp
    TextureManager.cpp
    PUBLIC
    GameRenderer.h
    TextureManager.h
    # .h files
    )
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

