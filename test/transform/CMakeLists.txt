add_executable(${PROJECT_NAME}_test_transform test_transform.cpp )
target_link_libraries(${PROJECT_NAME}_test_transform ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_transform PRIVATE -std=c++17)
add_test(test_transform ${PROJECT_NAME}_test_transform)

add_executable(${PROJECT_NAME}_test_smart_rotation test_smart_rotation.cpp )
target_link_libraries(${PROJECT_NAME}_test_smart_rotation ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_smart_rotation PRIVATE -std=c++17)
add_test(test_smart_rotation ${PROJECT_NAME}_test_smart_rotation)
