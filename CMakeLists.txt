cmake_minimum_required(VERSION 2.8.3)
project(barulic_rviz_plugins)

add_compile_options(-std=c++17)

find_package(catkin REQUIRED COMPONENTS rviz sensor_msgs)

catkin_package()

include_directories(
 include
 ${catkin_INCLUDE_DIRS}
)

link_libraries(
  ${catkin_LIBRARY_DIRS}
)

find_package(Qt5 ${rviz_QT_VERSION} EXACT REQUIRED Core Widgets)

set(CMAKE_AUTORCC ON)

QT5_WRAP_CPP(MOC_FILES
  include/${PROJECT_NAME}/battery_display.h
  include/${PROJECT_NAME}/battery_visual.h
)

add_library(${PROJECT_NAME}
  src/${PROJECT_NAME}/battery_display.cpp
  src/${PROJECT_NAME}/battery_visual.cpp
  resources/resources.qrc
  ${MOC_FILES}
)

add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets ${catkin_LIBRARIES})

install(TARGETS
  ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(FILES
  plugin_description.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

install(DIRECTORY icons/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/icons)
