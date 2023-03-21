if(NOT DEFINED CMAKE_OSX_ARCHITECTURES)
    find_path(FREEGLUT_ROOT  REQUIRED)
    include_directories(${FREEGLUT_ROOT}/include)
    link_directories(${FREEGLUT_ROOT}/lib)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(gim  ${CMAKE_SOURCE_DIR}/examples/gim/gim.c)

if(NOT DEFINED CMAKE_OSX_ARCHITECTURES)
    if(MSVC)
        set_target_properties(gim PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=${FREEGLUT_ROOT}/bin;%PATH% \$(LocalDebuggerEnvironment)")

        target_link_libraries(gim  freeglut_static.lib)
        target_link_libraries(gim  opengl32.lib)
        target_link_libraries(gim  glu32.lib)
    else()
        target_link_libraries(gim  freeglut_static)
        target_link_libraries(gim  OpenGL)
        target_link_libraries(gim  GLU)
    endif()
endif()

# Link the target opengi library
target_link_libraries(gim  opengi)

install(TARGETS  gim DESTINATION bin)

