get_filename_component(TEST_WITH_DATA_TEST_DIR "data" ABSOLUTE)
configure_file(test_helper.h.in test_helper.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

catkin_add_gtest(${PROJECT_NAME}_test_transform test_transform.cpp )
target_link_libraries(${PROJECT_NAME}_test_transform ${PROJECT_NAME})

catkin_add_gtest(${PROJECT_NAME}_test_time test_time.cpp )
target_link_libraries(${PROJECT_NAME}_test_time ${PROJECT_NAME})

catkin_add_gtest(${PROJECT_NAME}_test_pointset test_pointset.cpp )
target_link_libraries(${PROJECT_NAME}_test_pointset ${PROJECT_NAME})

catkin_add_gtest(${PROJECT_NAME}_test_math_algorithm test_math_algorithm.cpp )
target_link_libraries(${PROJECT_NAME}_test_math_algorithm ${PROJECT_NAME})

catkin_add_gtest(${PROJECT_NAME}_test_math_euler test_math_euler.cpp )
target_link_libraries(${PROJECT_NAME}_test_math_euler ${PROJECT_NAME})

catkin_add_gtest(${PROJECT_NAME}_test_math_interval test_math_interval.cpp )
target_link_libraries(${PROJECT_NAME}_test_math_interval ${PROJECT_NAME})

catkin_add_gtest(${PROJECT_NAME}_test_math_matrix test_math_matrix.cpp )
target_link_libraries(${PROJECT_NAME}_test_math_matrix ${PROJECT_NAME})

catkin_add_gtest(${PROJECT_NAME}_test_coordinates test_coordinates.cpp )
target_link_libraries(${PROJECT_NAME}_test_coordinates ${PROJECT_NAME})

catkin_add_gtest(${PROJECT_NAME}_test_geodesy test_geodesy.cpp )
target_link_libraries(${PROJECT_NAME}_test_geodesy ${PROJECT_NAME})

catkin_add_gtest(${PROJECT_NAME}_test_containers_bb test_containers_bb.cpp )
target_link_libraries(${PROJECT_NAME}_test_containers_bb ${PROJECT_NAME})

catkin_add_gtest(${PROJECT_NAME}_test_containers_grid test_containers_grid.cpp )
target_link_libraries(${PROJECT_NAME}_test_containers_grid ${PROJECT_NAME})

catkin_add_gtest(${PROJECT_NAME}_test_containers_ray test_containers_ray.cpp )
target_link_libraries(${PROJECT_NAME}_test_containers_ray ${PROJECT_NAME})

catkin_add_gtest(${PROJECT_NAME}_test_monitoring test_monitoring.cpp )
target_link_libraries(${PROJECT_NAME}_test_monitoring ${PROJECT_NAME})

catkin_add_gtest(${PROJECT_NAME}_test_diagnostic test_diagnostic.cpp )
target_link_libraries(${PROJECT_NAME}_test_diagnostic ${PROJECT_NAME})

