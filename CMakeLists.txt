cmake_minimum_required(VERSION 2.8.3)
project(romea_common)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weffc++ -Wall -Wextra -std=c++17 -O3")

#######################
## Find dependencies ##
#######################
find_package(catkin REQUIRED COMPONENTS roscpp)
find_package(Boost REQUIRED COMPONENTS system)

find_package( PkgConfig )
pkg_check_modules( EIGEN3 REQUIRED eigen3 )


###################################
## catkin specific configuration ##
###################################
catkin_package(
    INCLUDE_DIRS include
    LIBRARIES ${PROJECT_NAME}
    CATKIN_DEPENDS ${${PROJECT_NAME}_CATKIN_DEPS})

###########
## Build ##
###########

include_directories(
    include
    SYSTEM ${catkin_INCLUDE_DIRS}
    SYSTEM ${EIGEN3_INCLUDE_DIRS})

add_library(romea_common
    src/containers/grid/GridIndexMapping.cpp
    src/containers/grid/RayTracing.cpp
    src/containers/boundingbox/AxisAlignedBoundingBox.cpp
    src/containers/boundingbox/OrientedBoundingBox.cpp
    src/diagnostics/DiagnosticRate.cpp
    src/diagnostics/DiagnosticReliability.cpp
    src/diagnostics/DiagnosticReport.cpp
    src/diagnostics/DiagnosticStatus.cpp
    src/geometry/Circle.cpp
    src/geometry/Ellipse.cpp
    src/geodesy/EarthEllipsoid.cpp
    src/geodesy/ECEFConverter.cpp
    src/geodesy/ENUConverter.cpp
    src/geodesy/GeodeticCoordinates.cpp
    src/geodesy/WGS84Coordinates.cpp
    src/monitoring/RateMonitoring.cpp
    src/monitoring/OnlineAverage.cpp
    src/monitoring/OnlineVariance.cpp
    src/regression/leastsquares/LeastSquares.cpp
    src/regression/leastsquares/MEstimator.cpp
    src/regression/leastsquares/NLSE.cpp
    src/regression/ransac/Ransac.cpp
    src/regression/ransac/RansacModel.cpp
    src/regression/ransac/RansacIterations.cpp
    src/regression/ransac/RansacRandomCorrespondences.cpp
    src/pointset/algorithms/Correspondence.cpp
    src/pointset/algorithms/PointSetPreconditioner.cpp
    src/pointset/algorithms/PreconditionedPointSet.cpp
    src/pointset/algorithms/NormalAndCurvatureEstimation.cpp
    src/pointset/KdTree.cpp
    src/signal/Noise.cpp
    src/signal/FirstOrderButterworth.cpp
    src/transform/estimation/FindRigidTransformationByICP.cpp
    src/transform/estimation/FindRigidTransformationByLeastSquares.cpp
    src/transform/estimation/RansacRigidTransformationModel.cpp
    src/transform/estimation/FindRigidTransformationBySVD.cpp
    src/transform/SmartRotation3D.cpp
    )

target_link_libraries(romea_common ${catkin_LIBRARIES})


#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
#install(TARGETS romea
#    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#    )

## Mark cpp header files for installation
#install(DIRECTORY include/${PROJECT_NAME}/
#    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#    FILES_MATCHING PATTERN "*.hpp"
#    PATTERN ".svn" EXCLUDE
#    )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

#get_filename_component(TEST_WITH_DATA_TEST_DIR "test/data" ABSOLUTE)
#configure_file(test/test_helper.h.in test/test_helper.h)
#include_directories(${CMAKE_CURRENT_BINARY_DIR}/test)

if(CATKIN_ENABLE_TESTING)
  add_subdirectory(test)
endif(CATKIN_ENABLE_TESTING)
