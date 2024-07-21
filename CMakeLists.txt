cmake_minimum_required(VERSION 3.1)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR
        "In-source builds not allowed.
        Please make a new directory (called a build directory) and run CMake from there.
        You may need to remove CMakeCache.txt."
    )
endif()

# OS variables
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.14" CACHE STRING "macOS Deployment Target" FORCE)

# Project
project(whoa)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "dist" CACHE PATH "Installation prefix" FORCE)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)

include(lib/system/cmake/system.cmake)

# Compiler options
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" or CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Some templates abuse offsetof
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof")

    if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT DEFINED WHOA_ALLOW_UNDEFINED_BEHAVIOR)
        # Enable UBsan
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
        # Allow strange alignments
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-sanitize=alignment")
    else()
        # Disable UBsan completely
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-sanitize=undefined")
    endif()
endif()

# OS defines
if(WHOA_SYSTEM_WIN)
    # Avoid win32 header hell
    add_compile_definitions(
        NOMINMAX
        WIN32_LEAN_AND_MEAN
    )

    # Make DirectXMath boring
    add_definitions(
        -D_XM_NO_INTRINSICS_
    )

    # Lua uses various "unsafe" C functions
    add_definitions(
        -D_CRT_SECURE_NO_WARNINGS
    )
endif()

if(WHOA_SYSTEM_MAC)
    # Suppress OpenGL deprecation warnings
    add_definitions(
        -DGL_SILENCE_DEPRECATION
    )
endif()

# Threads
if(WHOA_SYSTEM_LINUX OR WHOA_SYSTEM_MAC)
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    find_package(Threads REQUIRED)
endif()

# Library search paths
if(WHOA_SYSTEM_MAC)
    set(CMAKE_SKIP_BUILD_RPATH FALSE)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    set(CMAKE_INSTALL_RPATH "@executable_path")
elseif(WHOA_SYSTEM_LINUX)
    set(CMAKE_SKIP_BUILD_RPATH FALSE)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    set(CMAKE_INSTALL_RPATH "$ORIGIN")
endif()

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(vendor)
