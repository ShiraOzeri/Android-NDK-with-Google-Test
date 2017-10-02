# Android-NDK-with-Google-Test

How to use GoogleTest on Android Studio?

Requirements:

The latest version of NDK has the gtest included. (my ndk : 15.2.4203891)

I did not find a clear guide how to do it, But I followed this document and this questions.

If you are opening a new project, do not forget to check the 'include c++'.

## Step1:

Create jni folder or use app/src/main/cpp folder.

Create 3 file:

foo.cpp:

    int foo(int x, int y) { return x + y; }


foo.h:

    extern int foo(int x, int y);


foo_unittest.cc:

    #include <gtest/gtest.h>
    #include "foo.h"

    TEST(FooTest,ZeroZero) {
       EXPECT_EQ(0, foo(0, 0));
    }
    TEST(FooTest,OneOne) {
       EXPECT_EQ(2, foo(1, 1));
    }
  
## Step 2:

Add to CMakeLists.txt

    cmake_minimum_required(VERSION 3.4.1)

    add_library(foo SHARED src/main/jni/foo.cpp)

    set(GOOGLETEST_ROOT ${ANDROID_NDK}/sources/third_party/googletest/googletest)
    add_library(gtest STATIC ${GOOGLETEST_ROOT}/src/gtest_main.cc ${GOOGLETEST_ROOT}/src/gtest-all.cc)
    target_include_directories(gtest PRIVATE ${GOOGLETEST_ROOT})
    target_include_directories(gtest PUBLIC ${GOOGLETEST_ROOT}/include)

    add_executable(foo_unittest src/main/jni/foo_unittest.cc)
    target_link_libraries(foo_unittest gtest foo)

Add to build.gradle(app)

    android {
        compileSdkVersion 26
        buildToolsVersion "26.0.1"
        defaultConfig {
           applicationId "com.example.utest"
            minSdkVersion 21 #lower from this can throw error: "error: only position independent executables (PIE) are supported. Aborted"
            targetSdkVersion 26
           versionCode 1
            versionName "1.0"
            ndk { abiFilters 'x86'}  #make sure that the ABI matches the target you use
            externalNativeBuild {
                cmake {
                    targets "foo_unittest"  #important. this line add the test file
                }
           }
        }
       externalNativeBuild {
            cmake {
               path "CMakeLists.txt"
            }
       }
    }


## Step 3:

Sync the project,  run "Make Project".

If your build succeeds, will build both 'libfoo.so' and 'foo_unittest' under:

    app/build/intermediates/cmake/debug/obj/x86/libfoo.so

    app/.externalNativeBuild/cmake/debug/x86/foo_unittest

## Step 4:

Open device or emulator and from the terminal (you can open the terminal from Android Studio, located at the bottom) write:

    adb push app/build/intermediates/cmake/debug/obj/x86/libfoo.so /data/local/tmp/
    adb push app/.externalNativeBuild/cmake/debug/x86/foo_unittest /data/local/tmp/
    adb shell chmod 775 /data/local/tmp/foo_unittest
    adb shell "LD_LIBRARY_PATH=/data/local/tmp /data/local/tmp/foo_unittest"
    
  
![sms](https://wiki.mtlabs.local/xwiki/bin/download/R%26D/Client%20Android/Android%20NDK%20with%20Google%20Test/WebHome/image.png?width=1100&height=379)  
    
