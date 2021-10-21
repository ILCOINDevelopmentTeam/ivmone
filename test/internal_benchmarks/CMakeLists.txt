# ivmone: Fast Ethereum Virtual Machine implementation
# Copyright 2019-2020 The ivmone Authors.
# SPDX-License-Identifier: Apache-2.0

add_executable(
    ivmone-bench-internal
    find_jumpdest_bench.cpp
    memory_allocation.cpp
)

target_link_libraries(ivmone-bench-internal PRIVATE benchmark::benchmark)
