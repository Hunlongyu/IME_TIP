cmake_minimum_required(VERSION 3.28)

project(webview-demo)

set(VERSION 0.0.1)

set(LANGUAGE CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(WIN32)
    set(RESOURCE_FILE "resource.rc")
    file(WRITE ${RESOURCE_FILE} "#include \"resource.h\"\n")
    file(APPEND ${RESOURCE_FILE} "IDI_APP_ICON ICON \"${CMAKE_SOURCE_DIR}/assets/image/logo.ico\"\n")
    file(WRITE resource.h "#define IDI_APP_ICON 101\n")
endif()

if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${RESOURCE_FILE})
else()
    add_executable(${PROJECT_NAME})
endif()

file(GLOB_RECURSE SOURCES 
    "${CMAKE_SOURCE_DIR}/resource.h"
    "${CMAKE_SOURCE_DIR}/src/*.h*" 
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${SOURCES}
)

include(FetchContent)

FetchContent_Declare(
    webview
    GIT_REPOSITORY https://github.com/webview/webview
    GIT_TAG 0.12.0)
FetchContent_MakeAvailable(webview)

find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    webview::core
    nlohmann_json::nlohmann_json
)

install(FILES ${CMAKE_BINARY_DIR}/config/config.json DESTINATION bin)
