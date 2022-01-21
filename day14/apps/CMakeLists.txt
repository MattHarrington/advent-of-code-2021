IF (WIN32)
    configure_file(day14_sample_input.txt day14_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(day14_input.txt day14_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(day14_sample_input.txt day14_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(day14_input.txt day14_input.txt NEWLINE_STYLE UNIX)
ENDIF()

add_executable(day14 app.cpp)
target_compile_features(day14 PRIVATE cxx_std_20)

target_link_libraries(day14 PRIVATE day14-core)

if(MSVC)
    target_compile_options(day14 PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else()
    target_compile_options(day14 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
