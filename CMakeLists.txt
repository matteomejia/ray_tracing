cmake_minimum_required(VERSION 3.20)

project(RayTracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracing main.cpp lib/camera.cpp lib/cylinder.cpp lib/light.cpp lib/plane.cpp lib/sphere.cpp lib/vec3.cpp lib/world.cpp)

message(STATUS "Looking for X11...")
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)                                                                                              
                                                                                                                                        
include_directories(include)

target_link_libraries(RayTracing PRIVATE m Threads::Threads ${X11_LIBRARIES})