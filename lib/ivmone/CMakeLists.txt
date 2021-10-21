# ivmone: Fast Ethereum Virtual Machine implementation
# Copyright 2019-2020 The ivmone Authors.
# SPDX-License-Identifier: Apache-2.0

include(LibraryTools)

hunter_add_package(intx)
find_package(intx CONFIG REQUIRED)

add_library(ivmone
    ${include_dir}/ivmone/ivmone.h
    analysis.cpp
    analysis.hpp
    baseline.cpp
    baseline.hpp
    baseline_instruction_table.cpp
    baseline_instruction_table.hpp
    execution.cpp
    execution.hpp
    instruction_traits.hpp
    instructions.cpp
    instructions.hpp
    instructions_calls.cpp
    limits.hpp
    opcodes_helpers.h
    tracing.cpp
    tracing.hpp
    vm.cpp
    vm.hpp
)
target_link_libraries(ivmone PUBLIC ivmc::ivmc intx::intx PRIVATE ivmc::instructions ivmc::hex ethash::keccak)
target_include_directories(ivmone PUBLIC
    $<BUILD_INTERFACE:${include_dir}>$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
if(CABLE_COMPILER_GNULIKE)
    target_compile_options(ivmone PRIVATE -fno-exceptions -fno-rtti)
endif()
set_target_properties(
    ivmone
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_SOVERSION}
)

if(NOT SANITIZE)
    # On Linux, check if all symbols in ivmone are resolved during linking.
    target_link_options(ivmone PRIVATE $<$<PLATFORM_ID:Linux>:LINKER:--no-undefined>)
endif()

set_source_files_properties(vm.cpp PROPERTIES COMPILE_DEFINITIONS PROJECT_VERSION="${PROJECT_VERSION}")

add_standalone_library(ivmone)
