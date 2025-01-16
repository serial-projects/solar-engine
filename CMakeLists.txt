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

# Logica Build:
function(build_logica)
    file(GLOB_RECURSE LOGICA_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/Logica/*.cpp)
    add_library(Logica ${LOGICA_SOURCES})
    target_include_directories(Logica PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endfunction()

# Sojson Build:
function(build_sojson)
    file(GLOB_RECURSE SOJSON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/Sojson/*.cpp)
    add_library(Sojson ${SOJSON_SOURCES})
    target_include_directories(Sojson PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(Sojson PUBLIC Logica)
endfunction()

# Fera Build:
function(build_fera)
    file(GLOB_RECURSE FERA_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/Fera/*.cpp)
    add_library(Fera ${FERA_SOURCES})
    target_include_directories(Fera PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(Fera PUBLIC Logica)
endfunction()

# Testing with main:
function(build_sojson_test_unit)
    add_executable(SojsonTest ${CMAKE_CURRENT_SOURCE_DIR}/Tests/Sojson.cpp)
    target_include_directories(SojsonTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
    set_target_properties(SojsonTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Tests/)
    target_link_libraries(SojsonTest PUBLIC Logica)
    target_link_libraries(SojsonTest PUBLIC Sojson)
    target_link_libraries(SojsonTest PUBLIC Fera)
endfunction()

function(build_fera_backends_obj_test_unit)
    add_executable(FeraBackendOBJTestUnit ${CMAKE_CURRENT_SOURCE_DIR}/Tests/FeraBackendsOBJ.cpp)
    target_include_directories(FeraBackendOBJTestUnit PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
    set_target_properties(FeraBackendOBJTestUnit PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Tests/)
    target_link_libraries(FeraBackendOBJTestUnit PUBLIC Logica)
    target_link_libraries(FeraBackendOBJTestUnit PUBLIC Sojson)
    target_link_libraries(FeraBackendOBJTestUnit PUBLIC Fera)
endfunction()

# Solar Engine is split in lower modules & high modules:

# Lower Modules:
function(build_solar_engine_lower_modules)
    message("*** Building Solar RPG Engine Lower Modules ***") 
    cmake_language(CALL build_logica)
    cmake_language(CALL build_sojson)
    cmake_language(CALL build_fera)
    cmake_language(CALL build_sojson_test_unit)
    cmake_language(CALL build_fera_backends_obj_test_unit)
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