IF (WIN32)
    configure_file(day05_sample_input.txt day05_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(day05_input.txt day05_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(day05_sample_input.txt day05_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(day05_input.txt day05_input.txt NEWLINE_STYLE UNIX)
ENDIF()

add_executable(day05 app.cpp)
target_compile_features(day05 PRIVATE cxx_std_20)

target_link_libraries(day05 PRIVATE day05-core)

if(MSVC)
    target_compile_options(day05 PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else()
    target_compile_options(day05 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
