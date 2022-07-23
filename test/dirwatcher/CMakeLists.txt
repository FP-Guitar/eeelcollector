set( TEST_NAME TestDirwatcher)
add_executable(${TEST_NAME} FilenameMatcher_Test.cpp DirectoryFileListRetriever_Test.cpp)
target_link_libraries(${TEST_NAME} PRIVATE dirwatcher GTest::gtest_main eeelcollector::project_options eeelcollector::project_warnings)
gtest_discover_tests(${TEST_NAME})