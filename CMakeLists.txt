cmake_minimum_required(VERSION 3.16)
project(libcore C)

# C11, strict: no GNU extensions (so void* arithmetic gets flagged)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Sanitizers on by default. This must come BEFORE the targets below,
# because add_compile_options only affects targets created after it.
option(LIBCORE_SANITIZE "Build with AddressSanitizer and UBSan" ON)
if (LIBCORE_SANITIZE)
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
endif ()

# The library itself: builds libcore.a
add_library(core STATIC src/vec.c src/str.c
        include/str.h)
target_include_directories(core PUBLIC include)
target_compile_options(core PRIVATE -Wall -Wextra -Wpedantic)

# Tests
enable_testing()
add_executable(tests tests/test_main.c
        include/tests.h)
target_link_libraries(tests PRIVATE core)
target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME libcore_tests COMMAND tests)

# Example program
add_executable(wordfreq examples/wordfreq.c)
target_link_libraries(wordfreq PRIVATE core)