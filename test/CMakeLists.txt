get_filename_component(TEST_WITH_DATA_TEST_DIR "data" ABSOLUTE)
configure_file(test_helper.h.in test_helper.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}_test_transform test_transform.cpp )
target_link_libraries(${PROJECT_NAME}_test_transform ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_transform PRIVATE -std=c++17)
add_test(test_transform ${PROJECT_NAME}_test_transform)

add_executable(${PROJECT_NAME}_test_time test_time.cpp )
target_link_libraries(${PROJECT_NAME}_test_time ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_time PRIVATE -std=c++17)
add_test(test_time test_time ${PROJECT_NAME})

add_executable(${PROJECT_NAME}_test_pointset test_pointset.cpp )
target_link_libraries(${PROJECT_NAME}_test_pointset ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_pointset PRIVATE -std=c++17)
add_test(test_pointset ${PROJECT_NAME}_test_pointset)

add_executable(${PROJECT_NAME}_test_math_algorithm test_math_algorithm.cpp )
target_link_libraries(${PROJECT_NAME}_test_math_algorithm ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_math_algorithm PRIVATE -std=c++17)
add_test(test_math_algorithm ${PROJECT_NAME}_test_math_algorithm)

add_executable(${PROJECT_NAME}_test_math_euler test_math_euler.cpp )
target_link_libraries(${PROJECT_NAME}_test_math_euler ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_math_euler PRIVATE -std=c++17)
add_test(test_math_euler ${PROJECT_NAME}_test_math_euler)

add_executable(${PROJECT_NAME}_test_math_interval test_math_interval.cpp )
target_link_libraries(${PROJECT_NAME}_test_math_interval ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_math_interval PRIVATE -std=c++17)
add_test(test_math_interval ${PROJECT_NAME}_test_math_interval)

add_executable(${PROJECT_NAME}_test_math_matrix test_math_matrix.cpp )
target_link_libraries(${PROJECT_NAME}_test_math_matrix ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_math_matrix PRIVATE -std=c++17)
add_test(test_math_matrix ${PROJECT_NAME}_test_math_matrix)

add_executable(${PROJECT_NAME}_test_coordinates test_coordinates.cpp )
target_link_libraries(${PROJECT_NAME}_test_coordinates ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_coordinates PRIVATE -std=c++17)
add_test(test_coordinates ${PROJECT_NAME}_test_coordinates)

add_executable(${PROJECT_NAME}_test_geodesy test_geodesy.cpp )
target_link_libraries(${PROJECT_NAME}_test_geodesy ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_geodesy PRIVATE -std=c++17)
add_test(test_geodesy ${PROJECT_NAME}_test_geodesy)

add_executable(${PROJECT_NAME}_test_containers_bb test_containers_bb.cpp )
target_link_libraries(${PROJECT_NAME}_test_containers_bb ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_containers_bb PRIVATE -std=c++17)
add_test(test_containers_bb ${PROJECT_NAME}_test_containers_bb test_containers_bb)

add_executable(${PROJECT_NAME}_test_containers_grid test_containers_grid.cpp )
target_link_libraries(${PROJECT_NAME}_test_containers_grid ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_containers_grid PRIVATE -std=c++17)
add_test(test_containers_grid ${PROJECT_NAME}_test_containers_grid)

add_executable(${PROJECT_NAME}_test_containers_ray test_containers_ray.cpp )
target_link_libraries(${PROJECT_NAME}_test_containers_ray ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_containers_ray PRIVATE -std=c++17)
add_test(test_containers_ray ${PROJECT_NAME}_test_containers_ray)

add_executable(${PROJECT_NAME}_test_monitoring test_monitoring.cpp )
target_link_libraries(${PROJECT_NAME}_test_monitoring ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_monitoring PRIVATE -std=c++17)
add_test(test_monitoring ${PROJECT_NAME}_test_monitoring)

add_executable(${PROJECT_NAME}_test_diagnostic test_diagnostic.cpp )
target_link_libraries(${PROJECT_NAME}_test_diagnostic ${PROJECT_NAME} GTest::GTest GTest::Main)
target_compile_options(${PROJECT_NAME}_test_diagnostic PRIVATE -std=c++17)
add_test(test_diagnostic ${PROJECT_NAME}_test_diagnostic)

