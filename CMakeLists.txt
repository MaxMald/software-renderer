cmake_minimum_required(VERSION 4.2)
project(GraphicsEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

#Shared Variables
if(WIN32)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(GE_ARCH "x64" CACHE STRING "GraphicsEngine architecture")
  elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(GE_ARCH "x86" CACHE STRING "GraphicsEngine architecture")
  else()
    set(GE_ARCH "unknown" CACHE STRING "GraphicsEngine architecture")
  endif()
else()
  set(GE_ARCH "" CACHE STRING "GraphicsEngine architecture")
endif()

# Define version
set(GE_VERSION_MAJOR 0)
set(GE_VERSION_MINOR 1)
set(GE_VERSION_PATCH 0)

# Enable CMake's built-in testing engine (CTest)
enable_testing()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Current shared libs state
set(_OLD_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})

## Subdirectories
# Assimp
set(BUILD_SHARED_LIBS ON)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)

add_subdirectory(dependencies/assimp-6.0.4)

# Group assimp targets in a folder
set(_assimp_targets_with_folder
  assimp
  zlibstatic
  uninstall
  UpdateAssimpLibsDebugSymbolsAndDLLs
)

foreach(_target_name IN LISTS _assimp_targets_with_folder)
  if(TARGET ${_target_name})
    set_target_properties(${_target_name} PROPERTIES FOLDER "Assimp")
  endif()
endforeach()

set(BUILD_SHARED_LIBS ${_OLD_BUILD_SHARED_LIBS})

# Sfml 
set(BUILD_SHARED_LIBS ON)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_GRAPHICS OFF CACHE BOOL "" FORCE)
add_subdirectory(dependencies/SFML-3.0.2)
set(BUILD_SHARED_LIBS ${_OLD_BUILD_SHARED_LIBS})

# ImGui
add_subdirectory(dependencies/IMGUI)

# Graphics Engine Subdirectories
add_subdirectory(geApplication)
add_subdirectory(geCore)
add_subdirectory(hcUtilities)


# Editor as startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT geApplication)
