cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests LANGUAGES CXX)

# ---- Test as standalone project the exported config package ----

if (PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
	enable_testing()

	find_package(eeelcollector CONFIG REQUIRED) # for intro, project_options, ...

	if (NOT TARGET eeelcollector::project_options)
		message(FATAL_ERROR "Requiered config package not found!")
		return() # be strictly paranoid for Template Janitor github action! CK
	endif ()
endif ()

# ---- Dependencies ----
find_package(GTest)
include(GoogleTest)

# Provide a simple smoke test to make sure that the CLI works and can display a --help message
add_test(NAME cli.has_help COMMAND eeelcollector --help)

# Provide a test to verify that the version being reported from the application
# matches the version given to CMake. This will be important once you package
# your program. Real world shows that this is the kind of simple mistake that is easy
# to make, but also easy to test for.
add_test(NAME cli.version_matches COMMAND eeelcollector --version)
set_tests_properties(cli.version_matches PROPERTIES PASS_REGULAR_EXPRESSION "${PROJECT_VERSION}")

add_subdirectory(dirwatcher)
add_subdirectory(appcontrol)
add_subdirectory(util)
add_subdirectory(datacollector)
