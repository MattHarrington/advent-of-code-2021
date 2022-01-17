IF (WIN32)
    configure_file(day13_sample_input.txt day13_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(day13_input.txt day13_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(day13_sample_input.txt day13_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(day13_input.txt day13_input.txt NEWLINE_STYLE UNIX)
ENDIF()

add_executable(day13 app.cpp)
target_compile_features(day13 PRIVATE cxx_std_20)

target_link_libraries(day13 PRIVATE day13-core)

if(MSVC)
    target_compile_options(day13 PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else()
    target_compile_options(day13 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
