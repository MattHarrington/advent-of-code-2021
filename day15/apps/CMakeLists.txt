IF (WIN32)
    configure_file(day15_sample_input.txt day15_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(day15_input.txt day15_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(day15_sample_input.txt day15_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(day15_input.txt day15_input.txt NEWLINE_STYLE UNIX)
ENDIF()

add_executable(day15 app.cpp)
target_compile_features(day15 PRIVATE cxx_std_20)

target_link_libraries(day15 PRIVATE day15-core)

if(MSVC)
    target_compile_options(day15 PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else()
    target_compile_options(day15 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
