# ivmone: Fast Ethereum Virtual Machine implementation
# Copyright 2018-2020 The ivmone Authors.
# SPDX-License-Identifier: Apache-2.0

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

# The internal ivmone unit tests. The generic EVM ones are also built in.
add_executable(ivmone-unittests
    analysis_test.cpp
    bytecode_test.cpp
    evm_fixture.cpp
    evm_fixture.hpp
    evm_test.cpp
    evm_calls_test.cpp
    evm_eip2929_test.cpp
    evm_eip3198_basefee_test.cpp
    evm_state_test.cpp
    evm_other_test.cpp
    evm_benchmark_test.cpp
    ivmone_test.cpp
    execution_state_test.cpp
    instructions_test.cpp
    tracing_test.cpp
    utils_test.cpp
)
target_link_libraries(ivmone-unittests PRIVATE ivmone testutils ivmc::instructions GTest::gtest GTest::gtest_main)
target_include_directories(ivmone-unittests PRIVATE ${ivmone_private_include_dir})

gtest_discover_tests(ivmone-unittests TEST_PREFIX ${PROJECT_NAME}/unittests/)

option(IVMONE_EVM_TEST_TOOL "Enable EVM unit testing tool for IVMC implementations (not maintained)" OFF)
if(IVMONE_EVM_TEST_TOOL)
    # The evm-test tool that contains the all evm-unittests and loads VMs as IVMC modules.
    add_executable(evm-test main.cpp)
    target_link_libraries(evm-test PRIVATE evm-unittests testutils ivmc::ivmc ivmc::loader GTest::gtest)
endif()

# Provide the project version to selected source files.
set_source_files_properties(
    ivmone_test.cpp
    main.cpp
    PROPERTIES COMPILE_DEFINITIONS PROJECT_VERSION="${PROJECT_VERSION}"
)
