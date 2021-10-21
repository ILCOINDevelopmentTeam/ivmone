// evmone: Fast Ethereum Virtual Machine implementation
// Copyright 2018-2019 The evmone Authors.
// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <ivmc/ivmc.h>
#include <ivmc/utils.h>

namespace evmone
{
struct AdvancedExecutionState;
struct AdvancedCodeAnalysis;

/// Execute the already analyzed code using the provided execution state.
IVMC_EXPORT ivmc_result execute(
    AdvancedExecutionState& state, const AdvancedCodeAnalysis& analysis) noexcept;

/// IVMC-compatible execute() function.
ivmc_result execute(ivmc_vm* vm, const ivmc_host_interface* host, ivmc_host_context* ctx,
    ivmc_revision rev, const ivmc_message* msg, const uint8_t* code, size_t code_size) noexcept;
}  // namespace evmone
