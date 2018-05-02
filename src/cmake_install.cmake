# Install script for directory: C:/msys64/home/Satvik/meta/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/meta")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/analyzers/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/classify/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/corpus/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/embeddings/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/features/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/graph/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/index/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/io/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/learn/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/lm/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/parser/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/regression/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/sequence/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/stats/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/succinct/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/tools/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/topics/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/utf/cmake_install.cmake")
  include("C:/Users/Satvik/of_v0.9.8_vs_release/apps/myApps/final-project-ssethia2/src/util/cmake_install.cmake")

endif()

