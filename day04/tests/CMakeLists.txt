find_package(doctest CONFIG REQUIRED)

IF (WIN32)
    configure_file(../apps/day04_sample_input.txt day04_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(../apps/day04_input.txt day04_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(../apps/day04_sample_input.txt day04_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(../apps/day04_input.txt day04_input.txt NEWLINE_STYLE UNIX)
ENDIF()

# Tests need to be added as executables first
add_executable(day04-tests testlib.cpp)

# I'm using C++17 in the test
target_compile_features(day04-tests PRIVATE cxx_std_17)

# Should be linked to the main library, as well as the Doctest testing library
target_link_libraries(day04-tests PRIVATE day04-core doctest::doctest)

if(MSVC)
    target_compile_options(day04-tests PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else()
    target_compile_options(day04-tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
