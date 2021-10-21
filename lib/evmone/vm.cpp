// ivmone: Fast Ethereum Virtual Machine implementation
// Copyright 2018 The ivmone Authors.
// SPDX-License-Identifier: Apache-2.0

/// @file
/// IVMC instance (class VM) and entry point of ivmone is defined here.

#include "vm.hpp"
#include "baseline.hpp"
#include "execution.hpp"
#include <ivmone/ivmone.h>
#include <cassert>
#include <iostream>

namespace ivmone
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
            c_vm->execute = ivmone::baseline::execute;
            return IVMC_SET_OPTION_SUCCESS;
        }
        else if (value == "2")
        {
            c_vm->execute = ivmone::execute;
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
        "ivmone",
        PROJECT_VERSION,
        ivmone::destroy,
        ivmone::execute,
        ivmone::get_capabilities,
        ivmone::set_option,
    }
{}

}  // namespace ivmone

extern "C" {
IVMC_EXPORT ivmc_vm* ivmc_create_ivmone() noexcept
{
    return new ivmone::VM{};
}
}
