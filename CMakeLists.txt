cmake_minimum_required(VERSION 2.8.8)
project(ixxx CXX)

# guard from super-projects, i.e. when it is added as subdirectory
IF(${CMAKE_PROJECT_NAME} STREQUAL "ixxx")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

  # only for the unittests, ixxx.cc/h don't depend on it
  find_package(Boost 1.53
    COMPONENTS
      system
      filesystem
      unit_test_framework
    REQUIRED)

endif()

#SET_SOURCE_FILES_PROPERTIES(ixxx.cc PROPERTIES COMPILE_FLAGS -D_XOPEN_SOURCE=600)

#include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(CMAKE_SYSTEM_NAME STREQUAL "SunOS" AND CMAKE_SYSTEM_VERSION STREQUAL "5.10")
  # Request POSIX 2001 definitions since Solaris 10 doesn't have more
  # the setting _XOPEN_SOURCE=700 is a nop then
  add_definitions(-D_XOPEN_SOURCE=600)
else()
  # Request POSIX 2008 definitions
  add_definitions(-D_XOPEN_SOURCE=700)
endif()

# Access mkdtemp() on Mac OS X
# (it is in POSIX 2008 but this is too new for Apple)
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  add_definitions(-D_DARWIN_C_SOURCE)
endif()

set(LIB_SRC
  ixxx/ixxx.cc
  ixxx/ansi.cc
  ixxx/posix.cc
  ixxx/linux.cc
  )

# guard from super-projects, i.e. when it is added as subdirectory
IF(${CMAKE_PROJECT_NAME} STREQUAL "ixxx")

  add_executable(ut
    ${LIB_SRC}
    unittest/main.cc
    unittest/ixxx.cc
  )
  target_link_libraries(ut ${Boost_LIBRARIES})
  set_property(TARGET ut PROPERTY INCLUDE_DIRECTORIES
    ${Boost_INCLUDE_DIRS}
  )

  # for executing it from a quickfix environment
  add_custom_target(check COMMAND ut)

endif()

add_library(ixxx SHARED
  ${LIB_SRC}
)
add_library(ixxx_static STATIC
  ${LIB_SRC}
)

# under windows shared/static libraries have the same extension ...
if(${UNIX})
  set_target_properties(ixxx_static PROPERTIES OUTPUT_NAME ixxx)
endif()

