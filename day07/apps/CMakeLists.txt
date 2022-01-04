IF (WIN32)
    configure_file(day07_sample_input.txt day07_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(day07_input.txt day07_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(day07_sample_input.txt day07_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(day07_input.txt day07_input.txt NEWLINE_STYLE UNIX)
ENDIF()

add_executable(day07 app.cpp)
target_compile_features(day07 PRIVATE cxx_std_20)

target_link_libraries(day07 PRIVATE day07-core)

if(MSVC)
    target_compile_options(day07 PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else()
    target_compile_options(day07 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
