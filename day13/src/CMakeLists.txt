# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Requires CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${day13_SOURCE_DIR}/include/*.hpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(day13-core lib.cpp ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(day13-core PUBLIC ../include)

# Using Eigen in this library
target_link_libraries(day13-core PUBLIC Eigen3::Eigen)

# All users of this library will need at least C++20
target_compile_features(day13-core PUBLIC cxx_std_20)

# Increase warnings
if(MSVC)
    target_compile_options(day13-core PRIVATE /external:anglebrackets /external:W0 /analyze:external- /W4 /WX)
else()
    target_compile_options(day13-core PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
