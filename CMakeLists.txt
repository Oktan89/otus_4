cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "3" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(print_ip VERSION ${PROJECT_VESRION})

option(WITH_GOOGLE_TEST "Whether to build Google tets" ON)

configure_file(version.h.in version.h)

add_executable(print_ip main.cpp)
add_library(print_ver lib.cpp)

set_target_properties(print_ip PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(print_ver
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(print_ip PRIVATE
    print_ver
)

if(WITH_GOOGLE_TEST)
#git submodule add https://github.com/google/googletest.git
#git submodule update --init --recursive
    add_subdirectory(./googletest EXCLUDE_FROM_ALL)
    add_executable(google_test_version test_version_g.cpp)

    set_target_properties(google_test_version PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(google_test_version 
        gtest_main 
        gmock
        print_ver
    )
endif()

if (MSVC)
    target_compile_options(print_ip PRIVATE
        /W4
    )
    target_compile_options(print_ver PRIVATE
        /W4
    )
    if(WITH_GOOGLE_TEST)
        target_compile_options(google_test_version PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(print_ip PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(print_ver PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_GOOGLE_TEST)
        target_compile_options(google_test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT r.zhigalenko@mail.ru)
include(CPack)

if(WITH_GOOGLE_TEST)
    enable_testing()
    include(GoogleTest)
    gtest_discover_tests(google_test_version)
endif()