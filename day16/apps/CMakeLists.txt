# Based on https://gitlab.com/CLIUtils/modern-cmake/-/blob/master/examples/extended-project/apps/CMakeLists.txt

IF (WIN32)
    configure_file(day16_sample_input.txt day16_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(day16_input.txt day16_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(day16_sample_input.txt day16_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(day16_input.txt day16_input.txt NEWLINE_STYLE UNIX)
ENDIF()

add_executable(day16 app.cpp)
target_compile_features(day16 PRIVATE cxx_std_20)

target_link_libraries(day16 PRIVATE day16-core)

if(MSVC)
    target_compile_options(day16 PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else()
    target_compile_options(day16 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
