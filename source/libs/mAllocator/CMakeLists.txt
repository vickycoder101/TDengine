aux_source_directory(src MALLOCATOR_SRC)
add_library(mAllocator STATIC ${MALLOCATOR_SRC})
target_include_directories(
    mAllocator
    PUBLIC "${CMAKE_SOURCE_DIR}/include/libs/mAllocator"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)
target_link_libraries(mAllocator os)