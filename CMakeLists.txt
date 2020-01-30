cmake_minimum_required(VERSION 3.3)
project(SfzFilters)

set(CMAKE_CXX_STANDARD 11)

add_library(SfzFilters STATIC src/SfzFilter.cpp)
target_include_directories(SfzFilters PUBLIC src)

###

find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
  pkg_check_modules(JACK "jack")
  find_package(Qt5 COMPONENTS Widgets REQUIRED)
endif()

if(JACK_FOUND AND TARGET Qt5::Widgets)
  set(CMAKE_AUTOUIC ON)
  add_executable(SfzFiltersDemo demo/demo.cpp demo/MainWindow.ui)
  target_include_directories(SfzFiltersDemo PRIVATE ${JACK_INCLUDE_DIRS})
  target_link_libraries(SfzFiltersDemo PRIVATE SfzFilters ${JACK_LIBRARIES} Qt5::Widgets)
endif()
