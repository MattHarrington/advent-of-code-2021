find_package(doctest CONFIG REQUIRED)

IF (WIN32)
    configure_file(../apps/day03_sample_input.txt day03_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(../apps/day03_input.txt day03_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(../apps/day03_sample_input.txt day03_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(../apps/day03_input.txt day03_input.txt NEWLINE_STYLE UNIX)
ENDIF()

# Tests need to be added as executables first
add_executable(day03-tests testlib.cpp)

# I'm using C++17 in the test
target_compile_features(day03-tests PRIVATE cxx_std_17)

# Should be linked to the main library, as well as the Doctest testing library
target_link_libraries(day03-tests PRIVATE day03-core doctest::doctest)

if(MSVC)
    target_compile_options(day03-tests PRIVATE /W4 /WX)
else()
    target_compile_options(day03-tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
