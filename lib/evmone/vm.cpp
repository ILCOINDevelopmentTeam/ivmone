// evmone: Fast Ethereum Virtual Machine implementation
// Copyright 2018 The evmone Authors.
// SPDX-License-Identifier: Apache-2.0

/// @file
/// IVMC instance (class VM) and entry point of evmone is defined here.

#include "vm.hpp"
#include "baseline.hpp"
#include "execution.hpp"
#include <evmone/evmone.h>
#include <cassert>
#include <iostream>

namespace evmone
{
namespace
{
void destroy(ivmc_vm* vm) noexcept
{
    assert(vm != nullptr);
    delete static_cast<VM*>(vm);
}

constexpr ivmc_capabilities_flagset get_capabilities(ivmc_vm* /*vm*/) noexcept
{
    return IVMC_CAPABILITY_EVM1;
}

ivmc_set_option_result set_option(ivmc_vm* c_vm, char const* c_name, char const* c_value) noexcept
{
    const auto name = (c_name != nullptr) ? std::string_view{c_name} : std::string_view{};
    const auto value = (c_value != nullptr) ? std::string_view{c_value} : std::string_view{};
    auto& vm = *static_cast<VM*>(c_vm);

    if (name == "O")
    {
        if (value == "0")
        {
            c_vm->execute = evmone::baseline::execute;
            return IVMC_SET_OPTION_SUCCESS;
        }
        else if (value == "2")
        {
            c_vm->execute = evmone::execute;
            return IVMC_SET_OPTION_SUCCESS;
        }
        return IVMC_SET_OPTION_INVALID_VALUE;
    }
    else if (name == "trace")
    {
        vm.add_tracer(create_instruction_tracer(std::cerr));
        return IVMC_SET_OPTION_SUCCESS;
    }
    else if (name == "histogram")
    {
        vm.add_tracer(create_histogram_tracer(std::cerr));
        return IVMC_SET_OPTION_SUCCESS;
    }
    return IVMC_SET_OPTION_INVALID_NAME;
}

}  // namespace


inline constexpr VM::VM() noexcept
  : ivmc_vm{
        IVMC_ABI_VERSION,
        "evmone",
        PROJECT_VERSION,
        evmone::destroy,
        evmone::execute,
        evmone::get_capabilities,
        evmone::set_option,
    }
{}

}  // namespace evmone

extern "C" {
IVMC_EXPORT ivmc_vm* ivmc_create_evmone() noexcept
{
    return new evmone::VM{};
}
}
