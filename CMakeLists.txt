# Entire Solar Engine
cmake_minimum_required(VERSION 3.9)

project(
    Sojson
    VERSION 1.0.00
)

# Set Requirements:
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find some packages on your system.
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

# Set the binary output for the libraries:
function(set_library_binary_output target)
    set_target_properties(
        ${target}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${target}/"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${target}/"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${target}/"
    )
endfunction()

# Function to add the includes:
function(add_lower_solar_engine_includes target)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Logica/include/)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sojson/include/)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Fera/include/)
endfunction()

# Logica Build:
function(build_logica)
    file(GLOB_RECURSE LOGICA_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Logica/src/Logica/*.cpp)
    add_library(Logica ${LOGICA_SOURCES})
    set_library_binary_output(Logica)
    add_lower_solar_engine_includes(Logica)
endfunction()

# Sojson Build:
function(build_sojson)
    file(GLOB_RECURSE SOJSON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Sojson/src/Sojson/*.cpp)
    add_library(Sojson ${SOJSON_SOURCES})

    # NOTE: Sojson is directly dependent on the Logica, as everything else: 
    target_link_libraries(Sojson PUBLIC Logica)

    set_library_binary_output(Sojson)
    add_lower_solar_engine_includes(Sojson)
endfunction()

# Fera Build:
function(build_fera)
    file(GLOB_RECURSE FERA_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Fera/src/Fera/*.cpp)
    add_library(Fera ${FERA_SOURCES})
    target_link_libraries(Fera PUBLIC Logica)
    set_library_binary_output(Fera)
    add_lower_solar_engine_includes(Fera)
endfunction()

# Solar Engine is split in lower modules & high modules:

# Lower Modules:
function(build_solar_engine_lower_modules)
    message("*** Building Solar RPG Engine Lower Modules ***")
    cmake_language(CALL build_logica)
    cmake_language(CALL build_sojson)
    cmake_language(CALL build_fera)
endfunction()    

# High Modules:
function(build_solar_engine_high_modules)
    message("*** Build Solar RPG Engine High Modules ***")
endfunction()

# Entire Engine:
function(build_solar_engine)
    cmake_language(CALL build_solar_engine_lower_modules)
    cmake_language(CALL build_solar_engine_high_modules)
endfunction()

cmake_language(CALL build_solar_engine)