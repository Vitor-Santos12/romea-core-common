add_executable(${PROJECT_NAME}_test_find_correspondences test_find_correspondences.cpp )
target_link_libraries(${PROJECT_NAME}_test_find_correspondences ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_find_correspondences PRIVATE -std=c++17)
add_test(test_find_correspondences ${PROJECT_NAME}_test_find_correspondences)

add_executable(${PROJECT_NAME}_test_compute_normals test_compute_normals.cpp )
target_link_libraries(${PROJECT_NAME}_test_compute_normals ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_compute_normals PRIVATE -std=c++17)
add_test(test_compute_normals ${PROJECT_NAME}_test_compute_normals)
