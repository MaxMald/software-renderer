# DirectX Graphics library
file(GLOB_RECURSE DXGRAPHICS_HEADERS "include/*.h")
file(GLOB_RECURSE DXGRAPHICS_SOURCES "src/*.cpp")

# Grouping source files in IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" 
             PREFIX "Header Files" 
             FILES ${DXGRAPHICS_HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src"
             PREFIX "Source Files"
             FILES ${DXGRAPHICS_SOURCES})

# Create the shared library target
add_library(geDXGraphics SHARED 
  ${DXGRAPHICS_SOURCES} 
  ${DXGRAPHICS_HEADERS}
)

# Target properties
set_target_properties(geDXGraphics PROPERTIES
  OUTPUT_NAME "geDXGraphics"
  DEBUG_POSTFIX "-d"
  VS_CHARSET "" # Character set: Not set (default)
)

# Compiler options
target_compile_options(geDXGraphics PRIVATE
  # C++ Warning level
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>
  $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>
  
  # Multiprocessor compilation
  $<$<CXX_COMPILER_ID:MSVC>:/MP>

  # SDL checks
  $<$<CXX_COMPILER_ID:MSVC>:/sdl>
)

target_include_directories(geDXGraphics
  PUBLIC "include"
  PRIVATE "${CMAKE_SOURCE_DIR}/hcUtilities/include"
  PRIVATE "${CMAKE_SOURCE_DIR}/geCore/include"
)

target_link_libraries(geDXGraphics
  PRIVATE hcUtilities
  PRIVATE geCore
)

add_dependencies(geDXGraphics
  hcUtilities
  geCore
)

# Install the library to the 'lib' directory
install(TARGETS geDXGraphics DESTINATION lib)
