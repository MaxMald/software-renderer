# Install script for directory: F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/GraphicsEngine")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp6.0.4-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/Repositories/MaxMald/software-renderer/build/lib/Debug/assimp-vc145-mtd.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/Repositories/MaxMald/software-renderer/build/lib/Release/assimp-vc145-mt.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/Repositories/MaxMald/software-renderer/build/lib/MinSizeRel/assimp-vc145-mt.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/Repositories/MaxMald/software-renderer/build/lib/RelWithDebInfo/assimp-vc145-mt.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp6.0.4" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "F:/Repositories/MaxMald/software-renderer/build/bin/Debug/assimp-vc145-mtd.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "F:/Repositories/MaxMald/software-renderer/build/bin/Release/assimp-vc145-mt.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "F:/Repositories/MaxMald/software-renderer/build/bin/MinSizeRel/assimp-vc145-mt.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "F:/Repositories/MaxMald/software-renderer/build/bin/RelWithDebInfo/assimp-vc145-mt.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/anim.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/aabb.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/ai_assert.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/camera.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/color4.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/color4.inl"
    "F:/Repositories/MaxMald/software-renderer/build/dependencies/assimp-6.0.4/code/../include/assimp/config.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/ColladaMetaData.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/commonMetaData.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/defs.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/cfileio.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/light.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/material.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/material.inl"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/matrix3x3.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/matrix3x3.inl"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/matrix4x4.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/matrix4x4.inl"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/mesh.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/ObjMaterial.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/pbrmaterial.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/GltfMaterial.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/postprocess.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/quaternion.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/quaternion.inl"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/scene.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/metadata.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/texture.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/types.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/vector2.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/vector2.inl"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/vector3.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/vector3.inl"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/version.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/cimport.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/AssertHandler.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/importerdesc.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/Importer.hpp"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/DefaultLogger.hpp"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/ProgressHandler.hpp"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/IOStream.hpp"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/IOSystem.hpp"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/Logger.hpp"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/LogStream.hpp"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/NullLogger.hpp"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/cexport.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/Exporter.hpp"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/DefaultIOStream.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/DefaultIOSystem.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/ZipArchiveIOSystem.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/SceneCombiner.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/fast_atof.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/qnan.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/BaseImporter.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/Hash.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/MemoryIOWrapper.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/ParsingUtils.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/StreamReader.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/StreamWriter.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/StringComparison.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/StringUtils.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/SGSpatialSort.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/GenericProperty.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/SpatialSort.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/SkeletonMeshBuilder.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/SmallVector.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/SmoothingGroups.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/SmoothingGroups.inl"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/StandardShapes.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/RemoveComments.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/Subdivision.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/Vertex.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/LineSplitter.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/TinyFormatter.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/Profiler.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/LogAux.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/Bitmap.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/XMLTools.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/IOStreamBuffer.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/CreateAnimMesh.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/XmlParser.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/BlobIOSystem.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/MathFunctions.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/Exceptional.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/ByteSwapper.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/Base64.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/Compiler/pushpack1.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/Compiler/poppack1.h"
    "F:/Repositories/MaxMald/software-renderer/dependencies/assimp-6.0.4/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "F:/Repositories/MaxMald/software-renderer/build/bin/Debug/assimp-vc145-mtd.pdb")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "F:/Repositories/MaxMald/software-renderer/build/bin/Release/assimp-vc145-mt.pdb")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "F:/Repositories/MaxMald/software-renderer/build/bin/MinSizeRel/assimp-vc145-mt.pdb")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "F:/Repositories/MaxMald/software-renderer/build/bin/RelWithDebInfo/assimp-vc145-mt.pdb")
  endif()
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "F:/Repositories/MaxMald/software-renderer/build/dependencies/assimp-6.0.4/code/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
