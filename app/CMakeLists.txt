cmake_minimum_required(VERSION 3.4.1)

add_library(foo SHARED src/main/cpp/foo.cpp)

set(GOOGLETEST_ROOT ${ANDROID_NDK}/sources/third_party/googletest/googletest)
add_library(gtest STATIC ${GOOGLETEST_ROOT}/src/gtest_main.cc ${GOOGLETEST_ROOT}/src/gtest-all.cc)
target_include_directories(gtest PRIVATE ${GOOGLETEST_ROOT})
target_include_directories(gtest PUBLIC ${GOOGLETEST_ROOT}/include)

add_executable(foo_unittest src/main/cpp/foo_unittest.cc)
target_link_libraries(foo_unittest gtest foo)