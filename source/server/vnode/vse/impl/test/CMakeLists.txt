# APP Tests
add_executable(vseAppTests "")
target_sources(vseAppTests
    PRIVATE
    "vseAppTests.cpp"
)
target_link_libraries(vseAppTests vse gtest_main)

# Internal Tests