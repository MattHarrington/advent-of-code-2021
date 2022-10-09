# Based on https://gitlab.com/CLIUtils/modern-cmake/-/blob/master/examples/extended-project/tests/CMakeLists.txt

find_package(Catch2 3 CONFIG REQUIRED)

IF (WIN32)
    configure_file(../apps/day16_sample_input.txt day16_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(../apps/day16_input.txt day16_input.txt NEWLINE_STYLE WIN32)
ELSE ()
    configure_file(../apps/day16_sample_input.txt day16_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(../apps/day16_input.txt day16_input.txt NEWLINE_STYLE UNIX)
ENDIF ()

# Tests need to be added as executables first
add_executable(day16-tests testlib.cpp)

# Using C++20 in the test
target_compile_features(day16-tests PRIVATE cxx_std_20)

if (MSVC)
    target_compile_options(day16-tests PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else ()
    target_compile_options(day16-tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif ()

# Should be linked to the main library, as well as Catch2
target_link_libraries(day16-tests PRIVATE day16-core Catch2::Catch2WithMain)

# Discover tests
include(Catch)
catch_discover_tests(day16-tests)
