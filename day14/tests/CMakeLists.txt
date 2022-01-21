find_package(doctest CONFIG REQUIRED)

IF (WIN32)
    configure_file(../apps/day14_sample_input.txt day14_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(../apps/day14_input.txt day14_input.txt NEWLINE_STYLE WIN32)
ELSE ()
    configure_file(../apps/day14_sample_input.txt day14_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(../apps/day14_input.txt day14_input.txt NEWLINE_STYLE UNIX)
ENDIF ()

# Tests need to be added as executables first
add_executable(day14-tests testlib.cpp)

# I'm using C++20 in the test
target_compile_features(day14-tests PRIVATE cxx_std_20)

# Should be linked to the main library, as well as the Doctest testing library
target_link_libraries(day14-tests PRIVATE day14-core doctest::doctest)

if (MSVC)
    target_compile_options(day14-tests PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else ()
    target_compile_options(day14-tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif ()
