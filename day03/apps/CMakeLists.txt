IF (WIN32)
    configure_file(day03_sample_input.txt day03_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(day03_input.txt day03_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(day03_sample_input.txt day03_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(day03_input.txt day03_input.txt NEWLINE_STYLE UNIX)
ENDIF()

add_executable(day03 app.cpp)
target_compile_features(day03 PRIVATE cxx_std_20)

target_link_libraries(day03 PRIVATE day03-core fmt::fmt)

if(MSVC)
    target_compile_options(day03 PRIVATE /W4 /WX)
else()
    target_compile_options(day03 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
