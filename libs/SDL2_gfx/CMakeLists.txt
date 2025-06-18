add_library(SDL2_gfx STATIC
    SDL2_gfxPrimitives.c
    SDL2_rotozoom.c
)

target_include_directories(SDL2_gfx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(SDL2_gfx SDL2::SDL2)

