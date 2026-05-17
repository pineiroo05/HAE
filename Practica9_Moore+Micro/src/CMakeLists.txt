cmake_minimum_required(VERSION 3.19)

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(p9a LANGUAGES MikroC)
else()
    project(p9a LANGUAGES C ASM)
endif()

set(PROJECT_TYPE "legacy" CACHE STRING "" FORCE)

if(NOT MIKROSDK_TYPE STREQUAL "legacy")
    message(SEND_ERROR "Cannot configure imported project with mikroSDK configuration. Please choose configuration with legacy SDK.")
    message(FATAL_ERROR "LEGACY_SDK_NOT_FOUND")
endif()



add_executable(p9a
    "p9a.c"
)

find_package(MikroC.System REQUIRED)
target_link_libraries(p9a PUBLIC MikroC.System)


target_include_directories(p9a
    PUBLIC
    
)

target_compile_options(p9a
    PUBLIC
    
)

target_link_options(p9a
    PUBLIC
    
)

target_compile_definitions(p9a
    PUBLIC
    __MIKROC_PRO_FOR_PIC__
)
