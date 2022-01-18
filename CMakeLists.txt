cmake_minimum_required(VERSION 3.0.2)
project(urdf_test)

find_package(catkin REQUIRED COMPONENTS
  urdf
  roscpp
  std_msgs
  robot_state_publisher
)

catkin_package(
  INCLUDE_DIRS include
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

link_libraries(${catkin_LIBRARIES})

add_executable(pen_joint_node src/pen_joint_node.cpp)
target_link_libraries(pen_joint_node ${catkin_LIBRARIES})

add_executable(sc_joint_node src/sc_joint_node.cpp)
target_link_libraries(sc_joint_node ${catkin_LIBRARIES})