# Core library
file(GLOB_RECURSE CORE_HEADERS "include/*.h")
file(GLOB_RECURSE CORE_SOURCES "src/*.cpp")

# Grouping source files in IDEs
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" 
             PREFIX "Header Files" 
             FILES ${CORE_HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src"
             PREFIX "Source Files"
             FILES ${CORE_SOURCES})

# Create the shared library target
add_library(geCore SHARED 
  ${CORE_SOURCES} 
  ${CORE_HEADERS}
)

# Target properties
set_target_properties(geCore PROPERTIES
  OUTPUT_NAME "geCore"
  DEBUG_POSTFIX "-d"
  VS_CHARSET "" # Character set: Not set (default)
)

# Compiler options
target_compile_options(geCore PRIVATE
  # C++ Warning level
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>
  $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>
  
  # Multiprocessor compilation
  $<$<CXX_COMPILER_ID:MSVC>:/MP>

  # SDL checks
  $<$<CXX_COMPILER_ID:MSVC>:/sdl>
)

# Required dependencies (loaded at runtime)
add_dependencies(geCore
  hcUtilities
)

# Includes
target_include_directories(geCore 
  PUBLIC "include"
  PRIVATE "${CMAKE_SOURCE_DIR}/hcUtilities/include"
)

target_link_libraries(geCore 
  PRIVATE hcUtilities
)

# Install the library to the 'lib' directory
install(TARGETS geCore DESTINATION lib)
