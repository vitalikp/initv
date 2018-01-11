project(initv)
cmake_minimum_required(VERSION 3.0)

set(PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(VERSION 0.1-dev)
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()
string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_C_FLAGS "-std=c11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2")

# directories
set(bindir ${CMAKE_INSTALL_PREFIX}/bin)
set(datadir ${CMAKE_INSTALL_PREFIX}/share)
#set(datadir /home/vitalik/.local/share)

# dependencies
find_package(PkgConfig REQUIRED)

# check program and library
include(check.cmake)

# directories
set(bindir ${CMAKE_INSTALL_PREFIX}/bin)
set(sbindir ${CMAKE_INSTALL_PREFIX}/sbin)
set(includedir ${CMAKE_INSTALL_PREFIX}/include)
set(libdir ${CMAKE_INSTALL_PREFIX}/lib64)
set(datadir ${CMAKE_INSTALL_PREFIX}/share)
set(localedir ${CMAKE_INSTALL_PREFIX}/share/locale)
set(logdir /var/log)

# config
configure_file(config.h.cmake config.h)
add_definitions(-include ${PROJECT_BINARY_DIR}/config.h)

# locales
include(po/lang.cmake)

add_subdirectory(src)

# show current config
message("   ${CMAKE_PROJECT_NAME} ${VERSION}(${CMAKE_BUILD_TYPE})")
message("      prefix:      ${CMAKE_INSTALL_PREFIX}")
message("      CFLAGS:      ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_${BUILD_TYPE}}")
message("       tests:      ${TESTS_ENABLE}")
message("     SELinux:      ${SELINUX_ENABLE}")
