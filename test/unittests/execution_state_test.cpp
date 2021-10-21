// ivmone: Fast Ethereum Virtual Machine implementation
// Copyright 2020 The ivmone Authors.
// SPDX-License-Identifier: Apache-2.0

#include <ivmone/analysis.hpp>
#include <ivmone/execution_state.hpp>
#include <gtest/gtest.h>
#include <type_traits>

static_assert(std::is_default_constructible<ivmone::ExecutionState>::value);
static_assert(!std::is_move_constructible<ivmone::ExecutionState>::value);
static_assert(!std::is_copy_constructible<ivmone::ExecutionState>::value);
static_assert(!std::is_move_assignable<ivmone::ExecutionState>::value);
static_assert(!std::is_copy_assignable<ivmone::ExecutionState>::value);

static_assert(std::is_default_constructible<ivmone::AdvancedExecutionState>::value);
static_assert(!std::is_move_constructible<ivmone::AdvancedExecutionState>::value);
static_assert(!std::is_copy_constructible<ivmone::AdvancedExecutionState>::value);
static_assert(!std::is_move_assignable<ivmone::AdvancedExecutionState>::value);
static_assert(!std::is_copy_assignable<ivmone::AdvancedExecutionState>::value);

TEST(execution_state, construct)
{
    ivmc_message msg{};
    msg.gas = -1;
    const ivmc_host_interface host_interface{};
    const uint8_t code[]{0x0f};
    const ivmone::ExecutionState st{
        msg, IVMC_MAX_REVISION, host_interface, nullptr, code, std::size(code)};

    EXPECT_EQ(st.gas_left, -1);
    EXPECT_EQ(st.stack.size(), 0);
    EXPECT_EQ(st.memory.size(), 0);
    EXPECT_EQ(st.msg, &msg);
    EXPECT_EQ(st.rev, IVMC_MAX_REVISION);
    EXPECT_EQ(st.return_data.size(), 0);
    EXPECT_EQ(st.code.data(), &code[0]);
    EXPECT_EQ(st.code.size(), std::size(code));
    EXPECT_EQ(st.status, IVMC_SUCCESS);
    EXPECT_EQ(st.output_offset, 0);
    EXPECT_EQ(st.output_size, 0);
}

TEST(execution_state, default_construct)
{
    const ivmone::ExecutionState st;

    EXPECT_EQ(st.gas_left, 0);
    EXPECT_EQ(st.stack.size(), 0);
    EXPECT_EQ(st.memory.size(), 0);
    EXPECT_EQ(st.msg, nullptr);
    EXPECT_EQ(st.rev, IVMC_FRONTIER);
    EXPECT_EQ(st.return_data.size(), 0);
    EXPECT_EQ(st.code.data(), nullptr);
    EXPECT_EQ(st.code.size(), 0);
    EXPECT_EQ(st.status, IVMC_SUCCESS);
    EXPECT_EQ(st.output_offset, 0);
    EXPECT_EQ(st.output_size, 0);
}

TEST(execution_state, default_construct_advanced)
{
    const ivmone::AdvancedExecutionState st;

    EXPECT_EQ(st.gas_left, 0);
    EXPECT_EQ(st.stack.size(), 0);
    EXPECT_EQ(st.memory.size(), 0);
    EXPECT_EQ(st.msg, nullptr);
    EXPECT_EQ(st.rev, IVMC_FRONTIER);
    EXPECT_EQ(st.return_data.size(), 0);
    EXPECT_EQ(st.code.data(), nullptr);
    EXPECT_EQ(st.code.size(), 0);
    EXPECT_EQ(st.status, IVMC_SUCCESS);
    EXPECT_EQ(st.output_offset, 0);
    EXPECT_EQ(st.output_size, 0);

    EXPECT_EQ(st.current_block_cost, 0u);
    EXPECT_EQ(st.analysis.advanced, nullptr);
}

TEST(execution_state, reset_advanced)
{
    const ivmc_message msg{};
    const uint8_t code[]{0xff};
    ivmone::AdvancedCodeAnalysis analysis;

    ivmone::AdvancedExecutionState st;
    st.gas_left = 1;
    st.stack.push({});
    st.memory.grow(64);
    st.msg = &msg;
    st.rev = IVMC_BYZANTIUM;
    st.return_data.push_back('0');
    st.code = {code, std::size(code)};
    st.status = IVMC_FAILURE;
    st.output_offset = 3;
    st.output_size = 4;
    st.current_block_cost = 5;
    st.analysis.advanced = &analysis;

    EXPECT_EQ(st.gas_left, 1);
    EXPECT_EQ(st.stack.size(), 1);
    EXPECT_EQ(st.memory.size(), 64);
    EXPECT_EQ(st.msg, &msg);
    EXPECT_EQ(st.rev, IVMC_BYZANTIUM);
    EXPECT_EQ(st.return_data.size(), 1);
    EXPECT_EQ(st.code.data(), &code[0]);
    EXPECT_EQ(st.code.size(), 1);
    EXPECT_EQ(st.status, IVMC_FAILURE);
    EXPECT_EQ(st.output_offset, 3);
    EXPECT_EQ(st.output_size, 4u);
    EXPECT_EQ(st.current_block_cost, 5u);
    EXPECT_EQ(st.analysis.advanced, &analysis);

    {
        ivmc_message msg2{};
        msg2.gas = 13;
        const ivmc_host_interface host_interface2{};
        const uint8_t code2[]{0x80, 0x81};

        st.reset(msg2, IVMC_HOMESTEAD, host_interface2, nullptr, code2, std::size(code2));

        // TODO: We are not able to test HostContext with current API. It may require an execution
        //       test.
        EXPECT_EQ(st.gas_left, 13);
        EXPECT_EQ(st.stack.size(), 0);
        EXPECT_EQ(st.memory.size(), 0);
        EXPECT_EQ(st.msg, &msg2);
        EXPECT_EQ(st.rev, IVMC_HOMESTEAD);
        EXPECT_EQ(st.return_data.size(), 0);
        EXPECT_EQ(st.code.data(), &code2[0]);
        EXPECT_EQ(st.code.size(), 2);
        EXPECT_EQ(st.status, IVMC_SUCCESS);
        EXPECT_EQ(st.output_offset, 0);
        EXPECT_EQ(st.output_size, 0);
        EXPECT_EQ(st.current_block_cost, 0u);
        EXPECT_EQ(st.analysis.advanced, nullptr);
    }
}

TEST(execution_state, stack_clear)
{
    ivmone::Stack stack;

    stack.clear();
    EXPECT_EQ(stack.size(), 0);
    EXPECT_EQ(stack.top_item + 1, stack.storage);

    stack.push({});
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top_item, stack.storage);

    stack.clear();
    EXPECT_EQ(stack.size(), 0);
    EXPECT_EQ(stack.top_item + 1, stack.storage);

    stack.clear();
    EXPECT_EQ(stack.size(), 0);
    EXPECT_EQ(stack.top_item + 1, stack.storage);
}

TEST(execution_state, const_stack)
{
    ivmone::Stack stack;
    stack.push(1);
    stack.push(2);

    const auto& cstack = stack;

    EXPECT_EQ(cstack[0], 2);
    EXPECT_EQ(cstack[1], 1);
}

TEST(execution_state, memory_view)
{
    ivmone::Memory memory;
    memory.grow(32);

    ivmone::bytes_view view{memory.data(), memory.size()};
    ASSERT_EQ(view.size(), 32);
    EXPECT_EQ(view[0], 0x00);
    EXPECT_EQ(view[1], 0x00);
    EXPECT_EQ(view[2], 0x00);

    memory[0] = 0xc0;
    memory[2] = 0xc2;
    ASSERT_EQ(view.size(), 32);
    EXPECT_EQ(view[0], 0xc0);
    EXPECT_EQ(view[1], 0x00);
    EXPECT_EQ(view[2], 0xc2);
}
