cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME sertos_stm32h533)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Configure the local path to the parent SertOS repository
set(SERTOS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../sertos" CACHE PATH "Path to the SertOS root directory")
set(SERTOS_LIB_NAME "libsertos_cortex_m33.a")
set(SERTOS_LIB_PATH "${SERTOS_DIR}/lib/arm/${SERTOS_LIB_NAME}" CACHE FILEPATH "Path to the pre-compiled SertOS Cortex-M33 library")

if(NOT EXISTS "${SERTOS_LIB_PATH}")
    message(FATAL_ERROR "Pre-compiled SertOS library not found at '${SERTOS_LIB_PATH}'. Build the Cortex-M33 target in '${SERTOS_DIR}' first.")
endif()

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    "${SERTOS_DIR}/lib/arm"
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/app/sertos_stm32h533.c"
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/app"
    "${SERTOS_DIR}/inc"
    "${SERTOS_DIR}/port"
    "${SERTOS_DIR}/modules/ring_buffer"
    "${SERTOS_DIR}/modules/linked_list"
    "${SERTOS_DIR}/modules/bitmap"
    "${SERTOS_DIR}/modules/atomic"
    "${SERTOS_DIR}/modules/memory_pool"
    "${SERTOS_DIR}/modules/crc"
    "${SERTOS_DIR}/modules/fsm"
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    "${SERTOS_LIB_PATH}"
)
