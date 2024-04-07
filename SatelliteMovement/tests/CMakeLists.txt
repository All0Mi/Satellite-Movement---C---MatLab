find_package(Catch2 3 REQUIRED HINTS "../Catch2/build/lib/cmake/Catch2/")

file(GLOB_RECURSE
        TESTS_SRC
        *.cpp
)

add_executable(tests ${TESTS_SRC})

target_link_libraries(tests PRIVATE  Catch2::Catch2 Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(tests)