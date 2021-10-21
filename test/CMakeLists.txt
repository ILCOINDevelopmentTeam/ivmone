# ivmone: Fast Ethereum Virtual Machine implementation
# Copyright 2019-2020 The ivmone Authors.
# SPDX-License-Identifier: Apache-2.0

include(GoogleTest)
include(${PROJECT_SOURCE_DIR}/ivmc/cmake/IVMC.cmake)

set(ivmone_private_include_dir ${PROJECT_SOURCE_DIR}/lib)

hunter_add_package(benchmark)
find_package(benchmark CONFIG REQUIRED)

add_subdirectory(utils)
add_subdirectory(bench)
add_subdirectory(integration)
add_subdirectory(internal_benchmarks)
add_subdirectory(unittests)

set(targets ivmone-bench ivmone-bench-internal ivmone-unittests testutils)

if(IVMONE_FUZZING)
    add_subdirectory(fuzzer)
    list(APPEND targets ivmone-fuzzer)
endif()

set_target_properties(
    ${targets} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}
)

get_target_property(type ivmone TYPE)
if(type STREQUAL SHARED_LIBRARY)
    ivmc_add_vm_test(NAME ${PROJECT_NAME}/ivmc-vmtester TARGET ivmone)

    if(TARGET evm-test)
        add_test(NAME ${PROJECT_NAME}/evm-test COMMAND evm-test $<TARGET_FILE:ivmone>)
    endif()
endif()
