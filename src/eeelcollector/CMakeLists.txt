

# Generic test that uses conan libs
add_executable(eeelcollector main.cpp)
target_link_libraries(
	eeelcollector
	PUBLIC project_options project_warnings
	PRIVATE CLI11::CLI11 fmt::fmt spdlog::spdlog appcontrol)

target_include_directories(eeelcollector PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
