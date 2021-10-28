add_subdirectory(meta)
add_subdirectory(tsdb)

aux_source_directory(. VSE_SRC)
add_library(vse STATIC ${VSE_SRC})
target_include_directories(
    vse
    PUBLIC "${CMAKE_SOURCE_DIR}/include/server/vnode/vse"
)
target_link_libraries(
    vse
    PUBLIC meta
    PUBLIC tsdb
)