// ivmone: Fast Ethereum Virtual Machine implementation
// Copyright 2021 The ivmone Authors.
// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "tracing.hpp"
#include <ivmc/ivmc.h>

namespace ivmone
{
/// The ivmone IVMC instance.
class VM : public ivmc_vm
{
    std::unique_ptr<Tracer> m_first_tracer;

public:
    inline constexpr VM() noexcept;

    void add_tracer(std::unique_ptr<Tracer> tracer) noexcept
    {
        // Find the first empty unique_ptr and assign the new tracer to it.
        auto* end = &m_first_tracer;
        while (*end)
            end = &(*end)->m_next_tracer;
        *end = std::move(tracer);
    }

    [[nodiscard]] Tracer* get_tracer() const noexcept { return m_first_tracer.get(); }
};
}  // namespace ivmone
