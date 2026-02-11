add_executable(unit unit.cpp)
target_link_libraries(unit PRIVATE avl_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit)