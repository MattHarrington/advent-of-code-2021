find_package(doctest CONFIG REQUIRED)

IF (WIN32)
    configure_file(../apps/day11_sample_input.txt day11_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(../apps/day11_input.txt day11_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(../apps/day11_sample_input.txt day11_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(../apps/day11_input.txt day11_input.txt NEWLINE_STYLE UNIX)
ENDIF()

# Tests need to be added as executables first
add_executable(day11-tests testlib.cpp)

# I'm using C++17 in the test
target_compile_features(day11-tests PRIVATE cxx_std_17)

# Should be linked to the main library, Eigen, and the Doctest testing library
target_link_libraries(day11-tests PRIVATE day11-core Eigen3::Eigen doctest::doctest)

if(MSVC)
    target_compile_options(day11-tests PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else()
    target_compile_options(day11-tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
