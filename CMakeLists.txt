cmake_minimum_required(VERSION 3.15)

project(OpenGI  LANGUAGES  C)

if(WIN32)
    add_compile_definitions(_CRT_SECURE_NO_DEPRECATE=1)
endif()

if(NOT DEFINED CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD  11)
endif()

include(ProcessorCount)
ProcessorCount(MAX_THREADS)

if(MAX_THREADS EQUAL 0)
    set(MAX_THREADS  1)
endif()

string(TOUPPER ${CMAKE_SYSTEM_PROCESSOR} PROCESSOR_ARCH)

if((PROCESSOR_ARCH MATCHES "AMD") OR
    (PROCESSOR_ARCH MATCHES "X86") OR
    (PROCESSOR_ARCH MATCHES "X64") OR
    (PROCESSOR_ARCH MATCHES "INTEL"))
    set(USE_SSE_VERSION  3)
else()
    set(USE_SSE_VERSION  0)
endif()

message(STATUS "Detected processor count: ${MAX_THREADS}")
message(STATUS "Detected CPU architecture: ${CMAKE_SYSTEM_PROCESSOR}, so use SSE version: ${USE_SSE_VERSION}")

configure_file(${CMAKE_SOURCE_DIR}/config.h.in  ${CMAKE_SOURCE_DIR}/include/config.h  @ONLY)

# Build opengi as a static library by default
add_compile_definitions(OPENGI_STATIC=1)

add_subdirectory(src)
add_subdirectory(examples/gim)

