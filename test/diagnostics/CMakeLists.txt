add_executable(${PROJECT_NAME}_test_checkup_equal_to test_checkup_equal_to.cpp )
target_link_libraries(${PROJECT_NAME}_test_checkup_equal_to ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_checkup_equal_to PRIVATE -std=c++17)
add_test(test_checkup_equal_to ${PROJECT_NAME}_test_checkup_equal_to)

add_executable(${PROJECT_NAME}_test_checkup_greater_than test_checkup_greater_than.cpp )
target_link_libraries(${PROJECT_NAME}_test_checkup_greater_than ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_checkup_greater_than PRIVATE -std=c++17)
add_test(test_checkup_greater_than ${PROJECT_NAME}_test_checkup_greater_than)

add_executable(${PROJECT_NAME}_test_checkup_lower_than test_checkup_lower_than.cpp )
target_link_libraries(${PROJECT_NAME}_test_checkup_lower_than ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_checkup_lower_than PRIVATE -std=c++17)
add_test(test_lower_greater_than ${PROJECT_NAME}_test_checkup_lower_than)

add_executable(${PROJECT_NAME}_test_checkup_greater_than_rate test_checkup_greater_than_rate.cpp )
target_link_libraries(${PROJECT_NAME}_test_checkup_greater_than_rate ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_checkup_greater_than_rate PRIVATE -std=c++17)
add_test(test_checkup_greater_than_rate ${PROJECT_NAME}_test_checkup_greater_than_rate)

add_executable(${PROJECT_NAME}_test_checkup_equal_to_rate test_checkup_equal_to_rate.cpp )
target_link_libraries(${PROJECT_NAME}_test_checkup_equal_to_rate ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_checkup_equal_to_rate PRIVATE -std=c++17)
add_test(test_checkup_equal_to_rate ${PROJECT_NAME}_test_checkup_equal_to_rate)

add_executable(${PROJECT_NAME}_test_checkup_reliability test_checkup_reliability.cpp )
target_link_libraries(${PROJECT_NAME}_test_checkup_reliability ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_checkup_reliability PRIVATE -std=c++17)
add_test(test_checkup_reliability ${PROJECT_NAME}_test_checkup_reliability)

add_executable(${PROJECT_NAME}_test_diagnostic_status test_diagnostic_status.cpp )
target_link_libraries(${PROJECT_NAME}_test_diagnostic_status ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_diagnostic_status PRIVATE -std=c++17)
add_test(test_diagnostic_status ${PROJECT_NAME}_test_diagnostic_status)

add_executable(${PROJECT_NAME}_test_diagnostic_report test_diagnostic_report.cpp )
target_link_libraries(${PROJECT_NAME}_test_diagnostic_report ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_diagnostic_report PRIVATE -std=c++17)
add_test(test_diagnostic_report ${PROJECT_NAME}_test_diagnostic_report)
