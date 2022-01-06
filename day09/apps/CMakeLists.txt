IF (WIN32)
    configure_file(day09_sample_input.txt day09_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(day09_input.txt day09_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(day09_sample_input.txt day09_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(day09_input.txt day09_input.txt NEWLINE_STYLE UNIX)
ENDIF()

add_executable(day09 app.cpp)
target_compile_features(day09 PRIVATE cxx_std_20)

target_link_libraries(day09 PRIVATE day09-core)

if(MSVC)
    target_compile_options(day09 PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else()
    target_compile_options(day09 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
