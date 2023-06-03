cmake_minimum_required(VERSION 3.7...3.26)
project(ixxx CXX)

set(LIB_SRC
  ixxx/sys_error.cc
  ixxx/ansi.cc
  ixxx/posix.cc
  ixxx/linux.cc
  ixxx/socket.cc
  ixxx/pthread.cc
)

add_library(ixxx        SHARED ${LIB_SRC})
add_library(ixxx_static STATIC ${LIB_SRC})

target_include_directories(ixxx        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ixxx_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(ixxx        PRIVATE cxx_std_11)
target_compile_features(ixxx_static PRIVATE cxx_std_11)

# ok, Solaris 10 is end-of life, just leaving it in for general entertainment
if(CMAKE_SYSTEM_NAME STREQUAL "SunOS" AND CMAKE_SYSTEM_VERSION STREQUAL "5.10")
    # Request POSIX 2001 definitions since Solaris 10 doesn't have more
    # the setting _XOPEN_SOURCE=700 is a nop then
    target_compile_definitions(ixxx        PRIVATE _XOPEN_SOURCE=600)
    target_compile_definitions(ixxx_static PRIVATE _XOPEN_SOURCE=600)
else()
    # Request POSIX 2008 definitions
    target_compile_definitions(ixxx        PRIVATE _XOPEN_SOURCE=700)
    target_compile_definitions(ixxx_static PRIVATE _XOPEN_SOURCE=700)
endif()

# Access mkdtemp() on Mac OS X
# (it is in POSIX 2008 but this is too new for Apple)
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(ixxx        PRIVATE _DARWIN_C_SOURCE)
    target_compile_definitions(ixxx_static PRIVATE _DARWIN_C_SOURCE)
endif()

if(WIN32)
    target_link_libraries(ixxx        PRIVATE wsock32 ws2_32)
    target_link_libraries(ixxx_static PRIVATE wsock32 ws2_32)
endif()

# under windows shared/static libraries have the same extension ...
if(UNIX)
    set_target_properties(ixxx_static PROPERTIES OUTPUT_NAME ixxx)
endif()


# guard from super-projects, i.e. when it is added as subdirectory
IF(CMAKE_PROJECT_NAME STREQUAL "ixxx")
    # only for the unittests, ixxx.cc/h don't depend on it
    find_package(Boost 1.53
        COMPONENTS
            system
            filesystem
            unit_test_framework
        REQUIRED)

    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    set(THREADS_PREFER_PTHREAD_FLAG TRUE)
    find_package(Threads REQUIRED)

    add_executable(ut
      unittest/main.cc
      unittest/ixxx.cc
    )
    target_link_libraries(ut PUBLIC
        ${Boost_LIBRARIES}
        ixxx_static
        Threads::Threads
    )
    target_include_directories(ut PUBLIC ${Boost_INCLUDE_DIRS})

    # for executing it from a quickfix environment
    add_custom_target(check COMMAND ut)

    add_executable(unlink example/unlink.cc)
    target_link_libraries(unlink ixxx_static)
endif()


