cmake_minimum_required(VERSION 2.8.3)

# Project name
set(PROJECT_NAME uw_slam)
project(${PROJECT_NAME})

## Compile as C++11, supported in ROS Melodic and newer
add_compile_options(-std=c++11)

# Opencv Library (local)
#set(OpenCV_INCLUDE_DIRS /usr/local/)
#set(OpenCV_LIBS /usr/local/lib/libopencv_core.so)

# Required libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  visualization_msgs
  image_transport
  cv_bridge
  message_generation
)
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

set(CMAKE_BUILD_TYPE Debug)

if(CUDA_FOUND)
    INCLUDE(FindCUDA)
  # If the package has been found, several variables will
  # be set, you can find the full list with descriptions
  # in the CUDAConfig.cmake file.
  # Print some message showing some of them
  message(STATUS "CUDA library status:")
  message(STATUS "    toolkit root dir: ${CUDA_TOOLKIT_ROOT_DIR}")
  message(STATUS "    versions: ${CUDA_VERSION}")
  message(STATUS "    libraries: ${CUDA_LIBRARIES}")
  message(STATUS "    include path: ${CUDA_INCLUDE_DIRS}")
endif(CUDA_FOUND)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  visualization_msgs
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp visualization_msgs message_runtime
)

# Path for DataStructure
set(DATA_STRUCTURE_PATH code/src)

# Source files
set(uw_slam_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/${DATA_STRUCTURE_PATH}/System.cpp
    ${PROJECT_SOURCE_DIR}/${DATA_STRUCTURE_PATH}/Tracker.cpp
    ${PROJECT_SOURCE_DIR}/${DATA_STRUCTURE_PATH}/CameraModel.cpp
    ${PROJECT_SOURCE_DIR}/${DATA_STRUCTURE_PATH}/Options.cpp 
    ${PROJECT_SOURCE_DIR}/${DATA_STRUCTURE_PATH}/Visualizer.cpp 
    ${PROJECT_SOURCE_DIR}/${DATA_STRUCTURE_PATH}/Map.cpp     
    ${PROJECT_SOURCE_DIR}/${DATA_STRUCTURE_PATH}/LeastSquares.cpp 
    
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/code/include
  ${PROJECT_SOURCE_DIR}/code/thirdparty
)

add_library(uw_lib ${uw_slam_SOURCE_FILES})

add_executable(${PROJECT_NAME}_node ${PROJECT_SOURCE_DIR}/code/${PROJECT_NAME}_node.cpp)

## IMPORTANT - TO WORK WITH CUDA AND ROS (CUDA INSTALLED IN ANOTHER OPENCV)
string(REPLACE "/opt/ros/kinetic/lib/libopencv_core3.so.3.3;" "" catkin_LIBRARIES "${catkin_LIBRARIES}")

target_link_libraries(${PROJECT_NAME}_node uw_lib ${OpenCV_LIBS} ${CERES_LIBRARIES} ${catkin_LIBRARIES} ${CUDA_LIBRARIES})
