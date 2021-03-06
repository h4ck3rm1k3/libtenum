cmake_minimum_required(VERSION 2.8)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(GNUInstallDirs)
include(ParseVersion)
include(AddSubmodule)

project(libtenum CXX)
parse_version(libtenum VERSION 0.9.5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost COMPONENTS unit_test_framework test_exec_monitor REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories(include)

# -------------------------------------------------------------------------
# installation
install(DIRECTORY include/tenum
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES include/tenum.hpp
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# -------------------------------------------------------------------------
# tests
if(CMAKE_BUILD_TESTS)
  enable_testing()

  add_executable(unit-test-bit-field
    test/test_bit_field.cpp
  )
  target_link_libraries(unit-test-bit-field ${Boost_LIBRARIES})
  add_test(unit-test-bit-field unit-test-bit-field)

  add_executable(unit-test-dynamic-enum
    test/test_dynamic_enum.cpp
  )
  target_link_libraries(unit-test-dynamic-enum ${Boost_LIBRARIES})
  add_test(unit-test-dynamic-enum unit-test-dynamic-enum)

  add_executable(unit-test-static-enum
    test/test_static_enum.cpp
  )
  target_link_libraries(unit-test-static-enum ${Boost_LIBRARIES})
  add_test(unit-test-static-enum unit-test-static-enum)
endif()
