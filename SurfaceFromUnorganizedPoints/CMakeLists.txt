
cmake_minimum_required(VERSION 2.8)

PROJECT(SurfaceFromUnorganizedPoints)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(SurfaceFromUnorganizedPoints MACOSX_BUNDLE SurfaceFromUnorganizedPoints)

if(VTK_LIBRARIES)
  target_link_libraries(SurfaceFromUnorganizedPoints ${VTK_LIBRARIES})
else()
  target_link_libraries(SurfaceFromUnorganizedPoints vtkHybrid vtkWidgets)
endif()
