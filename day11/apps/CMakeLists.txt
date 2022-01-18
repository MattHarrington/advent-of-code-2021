IF (WIN32)
    configure_file(day11_sample_input.txt day11_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(day11_input.txt day11_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(day11_sample_input.txt day11_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(day11_input.txt day11_input.txt NEWLINE_STYLE UNIX)
ENDIF()

add_executable(day11 app.cpp)
target_compile_features(day11 PRIVATE cxx_std_20)

target_link_libraries(day11 PRIVATE day11-core)

if(MSVC)
    target_compile_options(day11 PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else()
    target_compile_options(day11 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
