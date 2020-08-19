# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(${Boost_INCLUDE_DIR})
# Note: a target should be already defined using 'add_executable' or 'add_library'
add_executable(gtk_algebra_test main.cpp token_tests.cpp parser_tests.cpp expression_tests.cpp)
target_link_libraries(gtk_algebra_test gtk_algebra_lib ${Boost_LIBRARIES})
