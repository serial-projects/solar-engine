cmake_minimum_required(VERSION 3.9)

project(
    Solar
    VERSION                 1.0.000
    DESCRIPTION             "Solar RPG Engine"
)

# NOTE: This is standard for the Logica:
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# In case you are using debug:
if(CMAKE_BUILD_TYPE STREQUAL "Debug")    
    if(PROJECT_USE_ASAN)
        add_compile_options(-fsanitize=address)
        add_link_options(-fsanitize=address)     
    endif()
    if(PROJECT_FORCE_COLORS)
        add_compile_options(-fdiagnostics-color=always)
        add_link_options(-fdiagnostics-color=always)
    endif()
endif()

# This keeps the target based on the Solar Engine Organization System (SEOS):
function(set_library_binary_output target)
    set_target_properties(
        ${target}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${target}/"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${target}/"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${target}/"
    )
endfunction()

# Build the Logica System:
function(include_everything target)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Logica/include/)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Sojson/include/)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Fera/include/)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Progator/include/)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Solar/include/)
endfunction()

function(build_library target linkwith)
    file(GLOB_RECURSE ${target}_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${target}/src/*.cpp)
    add_library(${target} ${${target}_SOURCES})
    include_everything(${target})
    set_library_binary_output(${target})

    # Set the libraries to link with:
    foreach(tolink ${linkwith})
        target_link_libraries(${target} PUBLIC ${tolink})
    endforeach()
endfunction()

function(build_app linkwith)
    add_executable(App ${CMAKE_CURRENT_SOURCE_DIR}/App/main.cpp)
    include_everything(App)
    set_library_binary_output(App)
    foreach(tolink ${linkwith})
        target_link_libraries(App PUBLIC ${tolink})
    endforeach()
endfunction()

function(build_solar)
    build_library(Logica "")
    build_library(Sojson "Logica")
    build_app("Logica;Sojson")
endfunction()
cmake_language(CALL build_solar)