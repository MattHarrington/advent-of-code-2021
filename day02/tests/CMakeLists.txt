find_package(doctest CONFIG REQUIRED)

IF (WIN32)
    configure_file(../apps/day02_sample_input.txt day02_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(../apps/day02_input.txt day02_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(../apps/day02_sample_input.txt day02_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(../apps/day02_input.txt day02_input.txt NEWLINE_STYLE UNIX)
ENDIF()

# Tests need to be added as executables first
add_executable(day02-tests testlib.cpp)

# I'm using C++17 in the test
target_compile_features(day02-tests PRIVATE cxx_std_17)

# Should be linked to the main library, as well as the Doctest testing library
target_link_libraries(day02-tests PRIVATE day02-core doctest::doctest)

if(MSVC)
    target_compile_options(day02-tests PRIVATE /W4 /WX)
else()
    target_compile_options(day02-tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
