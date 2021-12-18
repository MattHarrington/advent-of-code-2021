IF (WIN32)
    configure_file(day04_sample_input.txt day04_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(day04_input.txt day04_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(day04_sample_input.txt day04_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(day04_input.txt day04_input.txt NEWLINE_STYLE UNIX)
ENDIF()

add_executable(day04 app.cpp)
target_compile_features(day04 PRIVATE cxx_std_20)

target_link_libraries(day04 PRIVATE day04-core fmt::fmt)

if(MSVC)
    target_compile_options(day04 PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else()
    target_compile_options(day04 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
