IF (WIN32)
    configure_file(day06_sample_input.txt day06_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(day06_input.txt day06_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(day06_sample_input.txt day06_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(day06_input.txt day06_input.txt NEWLINE_STYLE UNIX)
ENDIF()

add_executable(day06 app.cpp)
target_compile_features(day06 PRIVATE cxx_std_20)

target_link_libraries(day06 PRIVATE day06-core)

if(MSVC)
    target_compile_options(day06 PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else()
    target_compile_options(day06 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
