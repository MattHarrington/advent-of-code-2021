IF (WIN32)
    configure_file(day10_sample_input.txt day10_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(day10_input.txt day10_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(day10_sample_input.txt day10_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(day10_input.txt day10_input.txt NEWLINE_STYLE UNIX)
ENDIF()

add_executable(day10 app.cpp)
target_compile_features(day10 PRIVATE cxx_std_20)

target_link_libraries(day10 PRIVATE day10-core)

if(MSVC)
    target_compile_options(day10 PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else()
    target_compile_options(day10 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
