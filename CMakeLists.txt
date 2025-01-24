# Solar Engine CMAKE Script:
cmake_minimum_required(VERSION 3.9)

project(
    Sojson
    VERSION 1.0.00
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")    
    if(PROJECT_USE_ASAN)
        add_compile_options(-fsanitize=address)
        add_link_options(-fsanitize=address)     
    endif()
endif()

find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

# Function that set the binary output to the target folder to keep Solar RPG Engine Folder
# Organization, every project inside their projects.
function(set_library_binary_output target)
    set_target_properties(
        ${target}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${target}/"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${target}/"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${target}/"
    )
endfunction()

# Functions that expose the includes to the compiler:

function(add_lower_solar_engine_includes target)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Logica/include/)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sojson/include/)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Fera/include/)
endfunction()

function(add_high_solar_engine_includes target)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Progator/include/)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Solar/include/)
endfunction()

#
# Lower Modules
#

function(build_logica)
    file(GLOB_RECURSE LOGICA_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Logica/src/Logica/*.cpp)
    add_library(Logica ${LOGICA_SOURCES})
    set_library_binary_output(Logica)
    add_lower_solar_engine_includes(Logica)
endfunction()

function(build_sojson)
    file(GLOB_RECURSE SOJSON_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Sojson/src/Sojson/*.cpp)
    add_library(Sojson ${SOJSON_SOURCES})

    # NOTE: Sojson is directly dependent on the Logica, as everything else: 
    target_link_libraries(Sojson PUBLIC Logica)

    set_library_binary_output(Sojson)
    add_lower_solar_engine_includes(Sojson)
endfunction()

function(build_fera)
    file(GLOB_RECURSE FERA_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Fera/src/Fera/*.cpp)
    add_library(Fera ${FERA_SOURCES})
    target_link_libraries(Fera PUBLIC Logica)
    set_library_binary_output(Fera)
    add_lower_solar_engine_includes(Fera)
endfunction()

#
# High Modules
#

function(build_progator)
    file(GLOB_RECURSE PROGATOR_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Progator/src/Progator/*.cpp)
    add_library(Progator ${PROGATOR_SOURCES})
    target_link_libraries(Progator PUBLIC Logica)

    # Third party libraries:
    target_link_libraries(Progator PUBLIC SDL2)
    target_link_libraries(Progator PUBLIC GLEW)
    target_link_libraries(Progator PUBLIC GL)

    set_library_binary_output(Progator)
    add_lower_solar_engine_includes(Progator)
    add_high_solar_engine_includes(Progator)
endfunction()

function(build_solar)
    file(GLOB_RECURSE SOLAR_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Solar/src/Solar/*.cpp)
    add_library(Solar ${SOLAR_SOURCES})
    target_link_libraries(Solar PUBLIC Logica)
    target_link_libraries(Solar PUBLIC Sojson)
    target_link_libraries(Solar PUBLIC Fera)
    target_link_libraries(Solar PUBLIC Progator)

    # Third party libraries:
    target_link_libraries(Solar PUBLIC SDL2)

    set_library_binary_output(Solar)
    add_lower_solar_engine_includes(Solar)
    add_high_solar_engine_includes(Solar)
endfunction()

# Build all the lower modules in their dependency order:
function(build_solar_engine_lower_modules)
    cmake_language(CALL build_logica)
    cmake_language(CALL build_sojson)
    cmake_language(CALL build_fera)
endfunction()    

# Build all the high modules in their dependency order:
function(build_solar_engine_high_modules)
    cmake_language(CALL build_progator)
    cmake_language(CALL build_solar)
endfunction()

#
# Build the Application (Game itself or main.cpp)
#

function(build_app)
    add_executable(App ${CMAKE_CURRENT_SOURCE_DIR}/App/main.cpp)
    target_link_libraries(App PUBLIC Logica)
    target_link_libraries(App PUBLIC Sojson)
    target_link_libraries(App PUBLIC Fera)
    target_link_libraries(App PUBLIC Progator)
    target_link_libraries(App PUBLIC Solar)
    set_library_binary_output(App)
    add_lower_solar_engine_includes(App)
    add_high_solar_engine_includes(App)
endfunction()

#
# Builds the Entire Engine
#

function(build_solar_engine)
    cmake_language(CALL build_solar_engine_lower_modules)
    cmake_language(CALL build_solar_engine_high_modules)
    cmake_language(CALL build_app)
endfunction()
cmake_language(CALL build_solar_engine)