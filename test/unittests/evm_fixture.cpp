// evmone: Fast Ethereum Virtual Machine implementation
// Copyright 2019-2020 The evmone Authors.
// SPDX-License-Identifier: Apache-2.0

#include "evm_fixture.hpp"
#include <evmone/evmone.h>

namespace evmone::test
{
namespace
{
ivmc::VM advanced_vm{ivmc_create_evmone(), {{"O", "2"}}};
ivmc::VM baseline_vm{ivmc_create_evmone(), {{"O", "0"}}};

const char* print_vm_name(const testing::TestParamInfo<ivmc::VM*>& info) noexcept
{
    if (info.param == &advanced_vm)
        return "advanced";
    if (info.param == &baseline_vm)
        return "baseline";
    return "unknown";
}
}  // namespace

INSTANTIATE_TEST_SUITE_P(evmone, evm, testing::Values(&advanced_vm, &baseline_vm), print_vm_name);
}  // namespace evmone::test
