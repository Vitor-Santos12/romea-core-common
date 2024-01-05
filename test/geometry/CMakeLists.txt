add_executable(${PROJECT_NAME}_test_geometry_pose2d test_geometry_pose2d.cpp )
target_link_libraries(${PROJECT_NAME}_test_geometry_pose2d ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_geometry_pose2d PRIVATE -std=c++17)
add_test(test_geometry_pose2d ${PROJECT_NAME}_test_geometry_pose2d)

add_executable(${PROJECT_NAME}_test_geometry_pose3d test_geometry_pose3d.cpp )
target_link_libraries(${PROJECT_NAME}_test_geometry_pose3d ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_geometry_pose3d PRIVATE -std=c++17)
add_test(test_geometry_pose3d ${PROJECT_NAME}_test_geometry_pose3d)
