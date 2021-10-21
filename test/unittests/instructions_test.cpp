// ivmone: Fast Ethereum Virtual Machine implementation
// Copyright 2019 The ivmone Authors.
// SPDX-License-Identifier: Apache-2.0

#include <ivmc/instructions.h>
#include <ivmone/analysis.hpp>
#include <ivmone/instruction_traits.hpp>
#include <gtest/gtest.h>
#include <test/utils/bytecode.hpp>

namespace
{
constexpr int unspecified = -1000000;

constexpr int get_revision_defined_in(size_t op) noexcept
{
    for (size_t r = IVMC_FRONTIER; r <= IVMC_MAX_REVISION; ++r)
    {
        if (ivmone::instr::gas_costs[r][op] != ivmone::instr::undefined)
            return static_cast<int>(r);
    }
    return unspecified;
}
}  // namespace

TEST(instructions, validate_since)
{
    for (size_t op = 0x00; op <= 0xff; ++op)
    {
        const auto since = ivmone::instr::traits[op].since;
        const auto test_value = since.has_value() ? *since : unspecified;
        const auto expected = get_revision_defined_in(op);
        EXPECT_EQ(test_value, expected) << std::hex << op;
    }
}

TEST(instructions, compare_with_ivmc_instruction_tables)
{
    for (int r = IVMC_FRONTIER; r <= IVMC_MAX_REVISION; ++r)
    {
        const auto rev = static_cast<ivmc_revision>(r);
        const auto& instr_tbl = ivmone::instr::gas_costs[rev];
        const auto& ivmone_tbl = ivmone::get_op_table(rev);
        const auto* ivmc_tbl = ivmc_get_instruction_metrics_table(rev);

        for (size_t i = 0; i < ivmone_tbl.size(); ++i)
        {
            const auto gas_cost = (instr_tbl[i] != ivmone::instr::undefined) ? instr_tbl[i] : 0;
            const auto& metrics = ivmone_tbl[i];
            const auto& ref_metrics = ivmc_tbl[i];

            const auto case_descr = [rev](size_t opcode) {
                auto case_descr_str = std::ostringstream{};
                case_descr_str << "opcode " << to_name(ivmc_opcode(opcode), rev);
                case_descr_str << " on revision " << rev;
                return case_descr_str.str();
            };

            EXPECT_EQ(gas_cost, ref_metrics.gas_cost) << case_descr(i);
            EXPECT_EQ(metrics.gas_cost, ref_metrics.gas_cost) << case_descr(i);
            EXPECT_EQ(metrics.stack_req, ref_metrics.stack_height_required) << case_descr(i);
            EXPECT_EQ(metrics.stack_change, ref_metrics.stack_height_change) << case_descr(i);
        }
    }
}

TEST(instructions, compare_undefined_instructions)
{
    for (int r = IVMC_FRONTIER; r <= IVMC_MAX_REVISION; ++r)
    {
        const auto rev = static_cast<ivmc_revision>(r);
        const auto& instr_tbl = ivmone::instr::gas_costs[rev];
        const auto* ivmc_names_tbl = ivmc_get_instruction_names_table(rev);

        for (size_t i = 0; i < instr_tbl.size(); ++i)
            EXPECT_EQ(instr_tbl[i] == ivmone::instr::undefined, ivmc_names_tbl[i] == nullptr) << i;
    }
}

TEST(instructions, compare_with_ivmc_instruction_names)
{
    const auto* ivmc_tbl = ivmc_get_instruction_names_table(IVMC_MAX_REVISION);
    for (size_t i = 0; i < ivmone::instr::traits.size(); ++i)
    {
        EXPECT_STREQ(ivmone::instr::traits[i].name, ivmc_tbl[i]);
    }
}
