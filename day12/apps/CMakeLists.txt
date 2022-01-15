IF (WIN32)
    configure_file(day12_sample_input.txt day12_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(day12_input.txt day12_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(day12_sample_input.txt day12_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(day12_input.txt day12_input.txt NEWLINE_STYLE UNIX)
ENDIF()

add_executable(day12 app.cpp)
target_compile_features(day12 PRIVATE cxx_std_20)

target_link_libraries(day12 PRIVATE day12-core)

if(MSVC)
    target_compile_options(day12 PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else()
    target_compile_options(day12 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
