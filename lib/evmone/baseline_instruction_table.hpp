// evmone: Fast Ethereum Virtual Machine implementation
// Copyright 2020 The evmone Authors.
// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <ivmc/ivmc.h>
#include <array>

namespace evmone::baseline
{
struct InstructionTableEntry
{
    int16_t gas_cost;
    int8_t stack_height_required;
    bool can_overflow_stack;
};

using InstructionTable = std::array<InstructionTableEntry, 256>;

const InstructionTable& get_baseline_instruction_table(ivmc_revision rev) noexcept;
}  // namespace evmone::baseline
