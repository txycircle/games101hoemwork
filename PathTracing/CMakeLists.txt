# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.10)

project ("PathTracing")
set(CMAKE_CXX_STANDARD 17)


add_executable (PathTracing "main.cpp" "vector.hpp" "object.hpp" "material.cpp" "material.hpp" "common.hpp" "Triangle.cpp" "Triangle.hpp" "Bounds3.cpp" "Bounds3.hpp" 
"BVH.cpp" "BVH.hpp" "Intersection.hpp" "Ray.hpp"    "Scene.cpp" "Scene.hpp"  "Render.cpp" "Render.hpp"  )

