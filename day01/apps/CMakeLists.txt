IF (WIN32)
    configure_file(day01_sample_input.txt day01_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(day01_input.txt day01_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(day01_sample_input.txt day01_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(day01_input.txt day01_input.txt NEWLINE_STYLE UNIX)
ENDIF()

add_executable(day01 app.cpp)
target_compile_features(day01 PRIVATE cxx_std_20)

target_link_libraries(day01 PRIVATE day01-core fmt::fmt)

if(MSVC)
    target_compile_options(day01 PRIVATE /W4 /WX)
else()
    target_compile_options(day01 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
