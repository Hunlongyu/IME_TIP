cmake_minimum_required(VERSION 3.28)

project(IME_Tip)

set(VERSION 0.0.1)

set(LANGUAGE CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
	src/main.cpp
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES} "src/window_manager/window_manager.h" "src/window_manager/window_manager.cpp" "src/cursor_tracker/cursor_tracker.h" "src/cursor_tracker/cursor_tracker.cpp" "src/overlay_window/overlay_window.h" "src/overlay_window/overlay_window.cpp" "src/input_method_detector/input_method_detector.h" "src/input_method_detector/input_method_detector.cpp" "src/config_manager/config_manager.h" "src/config_manager/config_manager.cpp" "src/marker_renderer/marker_renderer.h" "src/marker_renderer/marker_renderer.cpp")

target_include_directories(
	${PROJECT_NAME}
	PRIVATE
)

find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
	gdiplus
	imm32
	user32
	gdi32
	dwmapi
	nlohmann_json::nlohmann_json
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /MP)
endif()

configure_file(${CMAKE_SOURCE_DIR}/config/config.json ${CMAKE_BINARY_DIR}/config.json COPYONLY)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES ${CMAKE_BINARY_DIR}/config.json DESTINATION bin)
