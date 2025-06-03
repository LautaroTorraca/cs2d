# common/CMakeLists.txt

# Busca todos los archivos .cpp (recursivamente si querés)
file(GLOB_RECURSE
        COMMON_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Constants/*.cpp
        ${CMAKE_SOURCE_DIR}/server/*.cpp
)

# Busca todos los headers para incluirlos (opcional, solo para que IDEs los vean)
file(GLOB_RECURSE COMMON_HEADERS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Constants/*.h"
        "${CMAKE_SOURCE_DIR}/server/*.h"
)

target_include_directories(
        taller_common
        PRIVATE ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/server
)

# Agrega las fuentes a la librería 'taller_common' definida en root CMakeLists
target_sources(taller_common
    PRIVATE
        ${COMMON_SOURCES}
        ${COMMON_HEADERS}
)

# Incluye la carpeta actual para headers
target_include_directories(taller_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Constants)

