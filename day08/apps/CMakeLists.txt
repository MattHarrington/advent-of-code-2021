IF (WIN32)
    configure_file(day08_sample_input.txt day08_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(day08_input.txt day08_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(day08_sample_input.txt day08_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(day08_input.txt day08_input.txt NEWLINE_STYLE UNIX)
ENDIF()

add_executable(day08 app.cpp)
target_compile_features(day08 PRIVATE cxx_std_20)

target_link_libraries(day08 PRIVATE day08-core)

if(MSVC)
    target_compile_options(day08 PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else()
    target_compile_options(day08 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
