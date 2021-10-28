aux_source_directory(src VSE_SRC)
add_library(vse STATIC ${VSE_SRC})
target_include_directories(vse
    PUBLIC "${CMAKE_SOURCE_DIR}/include/server/vnode/vse"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)
target_link_libraries(vse
    PUBLIC meta
    PUBLIC tsdb
    PUBLIC mAllocator
)

if(${BUILD_TEST})
    add_subdirectory(test)
endif(${BUILD_TEST})
