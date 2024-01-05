add_executable(${PROJECT_NAME}_test_ecef_converter test_ecef_converter.cpp )
target_link_libraries(${PROJECT_NAME}_test_ecef_converter ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_ecef_converter PRIVATE -std=c++17)
add_test(test_ecef_converter ${PROJECT_NAME}_test_ecef_converter)

add_executable(${PROJECT_NAME}_test_enu_converter test_enu_converter.cpp )
target_link_libraries(${PROJECT_NAME}_test_enu_converter ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_enu_converter PRIVATE -std=c++17)
add_test(test_enu_converter ${PROJECT_NAME}_test_enu_converter)

add_executable(${PROJECT_NAME}_test_lambert_converter test_lambert_converter.cpp )
target_link_libraries(${PROJECT_NAME}_test_lambert_converter ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_lambert_converter PRIVATE -std=c++17)
add_test(test_enu_converter ${PROJECT_NAME}_test_lambert_converter)
