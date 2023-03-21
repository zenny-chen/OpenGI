cmake_minimum_required(VERSION 3.15)

project(OpenGI  LANGUAGES  C)

if(WIN32)
    add_compile_definitions(_CRT_SECURE_NO_DEPRECATE=1)
endif()

if(NOT DEFINED CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD  11)
endif()

# Build opengi as a static library by default
add_compile_definitions(OPENGI_STATIC=1)

add_subdirectory(src)
add_subdirectory(examples/gim)

