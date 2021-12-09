IF (WIN32)
    configure_file(day02_sample_input.txt day02_sample_input.txt NEWLINE_STYLE WIN32)
    configure_file(day02_input.txt day02_input.txt NEWLINE_STYLE WIN32)
ELSE()
    configure_file(day02_sample_input.txt day02_sample_input.txt NEWLINE_STYLE UNIX)
    configure_file(day02_input.txt day02_input.txt NEWLINE_STYLE UNIX)
ENDIF()

add_executable(day02 app.cpp)
target_compile_features(day02 PRIVATE cxx_std_20)

target_link_libraries(day02 PRIVATE day02-core fmt::fmt)

if(MSVC)
    target_compile_options(day02 PRIVATE /W4 /WX)
else()
    target_compile_options(day02 PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
