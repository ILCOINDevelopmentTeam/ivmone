// evmone: Fast Ethereum Virtual Machine implementation
// Copyright 2020 The evmone Authors.
// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <ivmc/ivmc.h>
#include <ivmc/utils.h>
#include <memory>
#include <vector>

namespace evmone
{
struct ExecutionState;
class VM;

namespace baseline
{
struct CodeAnalysis
{
    using JumpdestMap = std::vector<bool>;

    const std::unique_ptr<uint8_t[]> padded_code;
    const JumpdestMap jumpdest_map;
};

/// Analyze the code to build the bitmap of valid JUMPDEST locations.
IVMC_EXPORT CodeAnalysis analyze(const uint8_t* code, size_t code_size);

/// Executes in Baseline interpreter using IVMC-compatible parameters.
ivmc_result execute(ivmc_vm* vm, const ivmc_host_interface* host, ivmc_host_context* ctx,
    ivmc_revision rev, const ivmc_message* msg, const uint8_t* code, size_t code_size) noexcept;

/// Executes in Baseline interpreter on the given external and initialized state.
IVMC_EXPORT ivmc_result execute(
    const VM&, ExecutionState& state, const CodeAnalysis& analysis) noexcept;

}  // namespace baseline
}  // namespace evmone
