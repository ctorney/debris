
# Top-Level CmakeLists.txt
cmake_minimum_required(VERSION 2.8)
PROJECT( SFM )

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})


ADD_SUBDIRECTORY( vtkSurface )

INCLUDE_DIRECTORIES(${SFM_SOURCE_DIR}/vtkSurface)

ADD_EXECUTABLE(SFM main)

TARGET_LINK_LIBRARIES(SFM vtkSurface ${VTK_LIBRARIES})
