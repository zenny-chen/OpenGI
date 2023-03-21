include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB  h_src ${CMAKE_SOURCE_DIR}/src/*.h)
file(GLOB  c_src ${CMAKE_SOURCE_DIR}/src/*.c)
file(GLOB  h_ext ${CMAKE_SOURCE_DIR}/include/GL/glext.h)
file(GLOB  h_lib ${CMAKE_SOURCE_DIR}/include/GI/gi.h)

source_group("EXT"  FILES ${h_ext})
source_group("LIB"  FILES ${h_lib})

add_library(opengi  STATIC ${h_src} ${c_src} ${h_ext} ${h_lib})

install(TARGETS  opengi DESTINATION lib)
install(DIRECTORY  ${CMAKE_SOURCE_DIR}/include/GI DESTINATION include)

