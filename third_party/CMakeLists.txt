# Third-party libraries for Spore (zlib, libpng, libjpeg, OpenSSL).
#
# SKETCH: not wired into the top-level CMakeLists.txt yet (nothing there links these). To try it:
#     cmake -S third_party -B build/third_party && cmake --build build/third_party
# or, from the top level, add_subdirectory(third_party) and link spore::zlib etc.
#
# Two modes:
#  * Portable (default): system/pkg-config libraries. zlib, libpng and libjpeg(-turbo) are API compatible
#    with what the game uses (jpeg 6a API is the libjpeg-6 ABI that libjpeg-turbo keeps in its default
#    build). OpenSSL is optional here: Spore only needs a TLS client and a handful of 0.9.8 APIs.
#  * Faithful (-DSPORE_THIRD_PARTY_FAITHFUL=ON): link the pinned, byte-matched static libraries produced by
#    tools/third_party/build_faithful.py (work/third_party/lib/*.lib, MSVC 2008 x86 ABI). This is the
#    configuration that ships the ORIGINAL OpenSSL 0.9.8g on purpose (decision recorded in
#    third_party/README.md, including the known security risk). It only makes sense in a 32-bit
#    MSVC-compatible link; the .lib files are produced by cl 15.00 and use the /MD CRT.
cmake_minimum_required(VERSION 3.20)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  project(spore_third_party C)
endif()

option(SPORE_THIRD_PARTY_FAITHFUL "Use the pinned byte-faithful static libs from work/third_party/lib" OFF)
option(SPORE_WITH_OPENSSL "Provide spore::openssl (system OpenSSL in portable mode)" OFF)

set(_faithful_lib_dir "${CMAKE_CURRENT_SOURCE_DIR}/../work/third_party/lib")

function(_spore_faithful name file)
  if(NOT EXISTS "${_faithful_lib_dir}/${file}")
    message(FATAL_ERROR "${file} not found in ${_faithful_lib_dir}; run tools/third_party/fetch.py and build_faithful.py")
  endif()
  add_library(spore::${name} STATIC IMPORTED GLOBAL)
  set_target_properties(spore::${name} PROPERTIES IMPORTED_LOCATION "${_faithful_lib_dir}/${file}")
endfunction()

if(SPORE_THIRD_PARTY_FAITHFUL)
  if(NOT MSVC OR NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(WARNING "SPORE_THIRD_PARTY_FAITHFUL expects a 32-bit MSVC toolchain")
  endif()
  _spore_faithful(zlib zlib.lib)
  _spore_faithful(png libpng.lib)
  _spore_faithful(jpeg libjpeg.lib)
  target_link_libraries(spore::png INTERFACE spore::zlib)
  # Headers: the pinned sources live in work/third_party/src after fetch.py.
  set(_src "${CMAKE_CURRENT_SOURCE_DIR}/../work/third_party/src")
  target_include_directories(spore::zlib INTERFACE "${_src}/zlib-1.2.3")
  target_include_directories(spore::png INTERFACE "${_src}/libpng-1.2.25")
  target_include_directories(spore::jpeg INTERFACE "${_src}/jpeg-6a" "${CMAKE_CURRENT_SOURCE_DIR}/jpeg-6a")
  if(SPORE_WITH_OPENSSL)
    _spore_faithful(openssl openssl.lib)
    target_include_directories(spore::openssl INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/../work/third_party/build/openssl-0.9.8g/include")
    target_link_libraries(spore::openssl INTERFACE ws2_32 gdi32 advapi32 user32)
  endif()
else()
  find_package(ZLIB REQUIRED)
  find_package(PNG REQUIRED)
  find_package(JPEG REQUIRED)
  add_library(spore::zlib INTERFACE IMPORTED GLOBAL)
  target_link_libraries(spore::zlib INTERFACE ZLIB::ZLIB)
  add_library(spore::png INTERFACE IMPORTED GLOBAL)
  target_link_libraries(spore::png INTERFACE PNG::PNG)
  add_library(spore::jpeg INTERFACE IMPORTED GLOBAL)
  target_link_libraries(spore::jpeg INTERFACE JPEG::JPEG)
  if(SPORE_WITH_OPENSSL)
    find_package(OpenSSL REQUIRED)  # modern OpenSSL: needs a small adapter for the 0.9.8 APIs (not written yet)
    add_library(spore::openssl INTERFACE IMPORTED GLOBAL)
    target_link_libraries(spore::openssl INTERFACE OpenSSL::SSL OpenSSL::Crypto)
  endif()
endif()
