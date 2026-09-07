cmake_minimum_required(VERSION 4.3)

project(LWE_ISEF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-lto")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-lto")

# Matplot++
add_subdirectory(
        "C:/Users/LENOVO/matplotplusplus"
        "${CMAKE_BINARY_DIR}/matplotplusplus"
)

# OpenFHE
find_package(OpenFHE CONFIG REQUIRED
        PATHS "C:/Users/LENOVO/openfhe-development/build"
        NO_DEFAULT_PATH
)

add_executable(lwe
        main.cpp
        denemeler/deneme1/client.h
        baseInclude.h
        denemeler/deneme1/context.h
        denemeler/deneme1/ortam.cpp
        denemeler/deneme1/ortam.h
        denemeler/deneme1/server.h
        denemeler/deneme1/parser.h
)

target_include_directories(lwe PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "C:/Users/LENOVO/eigen"

        "C:/Users/LENOVO/boost_1_89_0"

        "C:/Users/LENOVO/openfhe-development/src/pke/include"
        "C:/Users/LENOVO/openfhe-development/src/core/include"
        "C:/Users/LENOVO/openfhe-development/build/src/core"
        "C:/Users/LENOVO/openfhe-development/third-party/cereal/include"
        "C:/Users/LENOVO/openfhe-development/src/binfhe/include"
)

target_link_libraries(lwe PRIVATE
        matplot
        OPENFHEcore
        OPENFHEpke
        OPENFHEbinfhe
)

add_custom_command(TARGET lwe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "C:/Users/LENOVO/openfhe-development/build/lib"
        "$<TARGET_FILE_DIR:lwe>"
)